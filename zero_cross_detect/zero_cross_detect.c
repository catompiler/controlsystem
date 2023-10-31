#include "zero_cross_detect.h"
#include "iqmath/iqmath.h"

static iq24_t zero_cross_detect_mean(iq24_t *buf, size_t index, size_t count)
{
    iq24_t val = 0;

    size_t i;
    for (i = index; i < index + count; i++) {
        val = iq24_add(val, buf[i]);
    }

    val = iq24_idiv(val, count);

    return val;
}

static void zero_cross_detect_calc_zero_cross(M_zero_cross_detect *zcd)
{
#define ZCD_LINEAR_INF_POS IQ24_MAX
#define ZCD_LINEAR_INF_NEG IQ24_MIN

    iq24_t f1 = zero_cross_detect_mean(
                    zcd->m_buf,
                    0 * ZERO_CROSS_DETECT_SAMPLES_DISTANCE,
                    ZERO_CROSS_DETECT_SAMPLES_NUMBER
                );
    iq24_t f0 = zero_cross_detect_mean(
                    zcd->m_buf,
                    1 * ZERO_CROSS_DETECT_SAMPLES_DISTANCE,
                    ZERO_CROSS_DETECT_SAMPLES_NUMBER
                );

    iq24_t b = f0;
    iq24_t a = iq24_sub(f1, b);

    flag_t z = 0; // Флаг пересечения.
    iq24_t w = 0; // Вес точки пересечения по X.

    iq24_t r = 0; // Корень.

    if (a != 0) {
        r = iq24_div_sat(-b, a);
    } else {
        if (b >= 0) {
            r = ZCD_LINEAR_INF_NEG;
        } else {
            r = ZCD_LINEAR_INF_POS;
        }
    }

    // Если корень лежит в интервале [0; 1].
    if (r >= IQ24(0) && r <= IQ24(1.0)) {
        z = 1;
        w = r;
    }

    zcd->m_zero_cross = z;
    zcd->m_weight = w * ZERO_CROSS_DETECT_SAMPLES_DISTANCE;

#undef ZCD_LINEAR_INF_NEG
#undef ZCD_LINEAR_INF_POS
}

static iq24_t zero_cross_detect_calc_period(M_zero_cross_detect *zcd)
{
    // Период сигнала = 2 * измеренное время между пересечениями нуля.
    return iq24_add(zcd->m_period_sum, zcd->m_period_sum);
}

METHOD_INIT_IMPL(M_zero_cross_detect, zcd)
{
}

METHOD_DEINIT_IMPL(M_zero_cross_detect, zcd)
{
}

METHOD_CALC_IMPL(M_zero_cross_detect, zcd)
{
    if(!(zcd->control & CONTROL_ENABLE)) return;

    // Сдвинем значения в буфере.
    size_t i;
    for (i = ZERO_CROSS_DETECT_BUF_LEN - 1; i > 0; i--) {
        zcd->m_buf[i] = zcd->m_buf[i - 1];
    }
    // Положим очередной семпл в буфер.
    zcd->m_buf[0] = zcd->in_value;
    // Инкремент числа семплов с последнего детекта перехода через ноль.
    zcd->m_count = zcd->m_count + 1;

    // Вычисление возможного перехода через ноль данными в буфере.
    zero_cross_detect_calc_zero_cross(zcd);

    // Текущий период = предыдущий (нет перехода через ноль).
    iq24_t period = zcd->m_old_period;
    // Флаг пересечения нуля -
    // вычисленное пересечение И
    // первый раз из ряда подряд (при расстоянии между семплами > 1) И
    // число обработанных семплов не меньше минимального.
    flag_t zero_cross = (zcd->m_zero_cross == FLAG_ACTIVE)
            && (zcd->m_old_zero_cross == FLAG_NONE)
            && (zcd->m_count >= ZERO_CROSS_DETECT_SAMPLES_MIN); //zcd->r_samples_min

    // Достоверный результат -
    // был предыдущий детект.
    flag_t valid = (zcd->m_old_period != 0);

    // Если обнаружен переход через ноль.
    if (zero_cross == FLAG_ACTIVE) {
        // Часть периода семпла до пересечения нуля.
        iq24_t period_before_zc = iq24_mul(zcd->m_weight,
                zcd->r_samples_period);
        // Увеличим значение суммы периодов
        // на часть периода семпла до пересечения нуля.
        zcd->m_period_sum = iq24_add(zcd->m_period_sum, period_before_zc);

        // Вычислим текущий период.
        period = zero_cross_detect_calc_period(zcd);

        // Установим начальное значение суммы периодов
        // равное части периода семпла после пересечения нуля.
        zcd->m_period_sum = iq24_sub(zcd->r_samples_period, period_before_zc);
        // Сбросим число семплов с предыдущего детектирования.
        zcd->m_count = 0;
        // Предыдущие величины.
        zcd->m_old_period = period;
    } else { // Переход через ноль не обнаружен, или повторный.
        // Увеличим сумму периодов семплов на один период.
        zcd->m_period_sum = iq24_add(zcd->m_period_sum, zcd->r_samples_period);

        // Вычислим текущий период.
        iq24_t cur_period = zero_cross_detect_calc_period(zcd);

        // Детекта пересечения нуля не было, поэтому
        // если вычисленный период уже оказался больше
        // предудущего.
        if (cur_period > zcd->m_old_period) {
            // Присвоим текущему периоду большее значение.
            period = cur_period;
        }
    }

    // Если данные достоверны - установим выхода.
    if (valid) {
        zcd->out_zero_cross = zero_cross;
        zcd->out_period = period;

        // Частота.
        if (period != 0) {
            zcd->out_freq = iq24_inv_sat(period);
        } else {
            zcd->out_freq = IQ24_MAX;
        }

        // Флаг достоверности данных.
        zcd->status = STATUS_VALID;
    }

    // Флаг предыдущего детекта перехода через ноль.
    zcd->m_old_zero_cross = zcd->m_zero_cross;
}
