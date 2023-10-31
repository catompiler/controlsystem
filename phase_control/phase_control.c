#include "phase_control.h"


METHOD_INIT_IMPL(M_phase_control, phc)
{
}

METHOD_DEINIT_IMPL(M_phase_control, phc)
{
}

METHOD_CALC_IMPL(M_phase_control, phc) {

    // Нормализация угла цикла управления.
    phc->m_angle = phc->in_angle_pu & PHASE_CONTROL_CYCLE_ANGLE_MASK;

    // Детект начала цикла управления.
    phc->out_cycle = (phc->m_angle_z1 > PHASE_CONTROL_CYCLE_ANGLE_END
            && phc->m_angle < PHASE_CONTROL_CYCLE_ANGLE_BEGIN);

    // Детект начала периода.
    phc->out_period = (phc->m_angle_z1 > PHASE_CONTROL_CYCLE_ANGLE_END
            && phc->in_angle_pu < PHASE_CONTROL_CYCLE_ANGLE_BEGIN);

    // Обработка начала цикла управления.
    if (phc->out_cycle) {
        // Если начало управления было между предыдущим и текущим семплом
        // и угол начала управления в начале цикла управления
        // (в последнем случае угол управления больше либо равен углу цикла).
        if (phc->m_out_control && phc->m_control_angle >= PHASE_CONTROL_CYCLE_ANGLE) { //(phc->m_control_angle < CTRL_CYCLE_ANGLE_BEGIN || ){
            // Отметим что в этом цикле управления начало управления уже произошло.
            phc->m_control_state = FLAG_ACTIVE;//phc->m_out_control;
        } else {
            // Иначе сбросим флаг начала управления для нового цикла управления.
            phc->m_control_state = FLAG_NONE;
        }

    }

    // Сброс стробов.
    phc->m_out_control = STROBE_NONE;

    // Флаги сравнения углов.
    // Момент начала управления.
    // Опоздание - угол управления меньше текущего угла.
    flag_t late = 0;
    // Опережение - угол управления лежит между текущим и следующим семплом.
    flag_t between = 0;

    // Если управление разрешено.
    if (phc->control & CONTROL_ENABLE) {

        // Угол начала управления.
        iq24_t a_control = phc->in_control_angle_pu;

        // Если угол управления находится в разрешённом диапазоне.
        if (a_control >= phc->in_min_angle_to_control_pu
                && a_control <= phc->in_max_angle_to_control_pu) {

            // Общие углы.
            // Текущий угол.
            iq24_t a_cur = phc->m_angle;
            // Следующий угол.
            iq24_t a_next = phc->m_angle + phc->p_angle_win_pu;
            // Детект конца цикла управления.
            flag_t cycle_at_end = (a_cur < PHASE_CONTROL_CYCLE_ANGLE
                    && a_next >= PHASE_CONTROL_CYCLE_ANGLE);

            // Флаг нахождения критерия "между"
            // в начале следующего цикла управления.
            flag_t next_cycle_between = 0;
            // Угол начала управления для проверки его нахождения
            // между текущим и следующим семплом.
            iq24_t a_between = a_control;
            // Если достигнут конец цикла управления и
            // угол начала управления находится в начале цикла управления.
            if (cycle_at_end && a_control < PHASE_CONTROL_CYCLE_ANGLE_BEGIN) {
                // Приведём угол начала управления к одному диапазону со счётчиком углов.
                a_between += PHASE_CONTROL_CYCLE_ANGLE;
            }

            // Если угол начала управления находится в следующем цикле.
            if (a_between >= PHASE_CONTROL_CYCLE_ANGLE) {
                // Управление для следующего цикла управления.
                next_cycle_between = 1;
            }

            // Флаг нахождения текущего угла в допустимом диапазоне углов для управления.
            flag_t allow_late = (a_cur >= phc->in_min_angle_to_control_pu
                    && a_cur <= phc->in_max_angle_to_control_pu);

            late = ((a_control <= a_cur) && allow_late);
            between = ((a_between > a_cur) && (a_between <= a_next));
            flag_t occured = (late || between);
            flag_t needed_for_next_cycle = next_cycle_between && between;

            // Управление ещё не установлено И его необходимо установить, ИЛИ
            // начало управления находится до первого семпла следующего цикла управления.
            if ((phc->m_control_state == 0 && occured)
                    || needed_for_next_cycle) {

                phc->m_out_control = STROBE_ACTIVE;
                phc->m_control_state = FLAG_ACTIVE;

                // Угол управления.
                iq24_t control_angle = 0;

                // Управление в промежутке.
                if (between) {
                    // Угол управления равен установленному.
                    control_angle = a_between;
                    // Опаздываем - начало управления было "вчера".
                } else {
                    // Угол управления равен текущему.
                    control_angle = a_cur;
                }

                // Установим угол управления.
                phc->m_control_angle = control_angle;

                // Выход угла управления установим
                // относительно входного угла.
                phc->out_control_angle_pu = phc->in_angle_pu + control_angle - a_cur; //control_angle;

            }

        }

    }

    phc->out_control = phc->m_out_control;
    phc->out_control_late = late;
    phc->out_control_between = between;

    phc->m_angle_z1 = phc->m_angle;

}
