#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include "defs/defs.h"



/**
 * Макрос для обработки первого входа в состояние.
 * Валиден только после вызова fsm_begin.
 */
#define FSM_STATE_ENTRY(fsm)\
            if(fsm_state_entry((fsm)))

//! Тип состояния конечного автомата.
typedef uint32_t fsm_state_t;

//! Тип флага конечного автомата.
typedef uint32_t fsm_flag_t;

//! Тип структуры конечного автомата.
typedef struct _S_Fsm {
    fsm_state_t state; //!< Состояние.
    fsm_state_t prev_state; //!< Предыдущее состояние.
//    fsm_state_t next_state; //!< Состояние для перехода в конце обработки.
    fsm_state_t m_cur_state; //!< Текущее обрабатываемое состояние.
    fsm_flag_t m_state_entry; //!< Флаг первого входа в текущее состояние.
} fsm_t;

//! Значение структуры конечного автомата по-умолчанию.
#define FSM_DEFAULTS {0}

/**
 * Инициализирует конечный автомат.
 * @param fsm Конечный автомат.
 */
ALWAYS_INLINE static void fsm_init(fsm_t* fsm)
{
    fsm->state = 0;
    fsm->prev_state = 0;
//    fsm->next_state = 0;
    fsm->m_cur_state = 0;
    fsm->m_state_entry = 0;
}

/**
 * Деинициализирует конечный автомат.
 * @param fsm Конечный автомат.
 */
ALWAYS_INLINE static void fsm_deinit(fsm_t* fsm)
{
    fsm->state = 0;
    fsm->prev_state = 0;
//    fsm->next_state = 0;
    fsm->m_cur_state = 0;
    fsm->m_state_entry = 0;
}

/**
 * Сбрасывает конечный автомат.
 * @param fsm Конечный автомат.
 */
ALWAYS_INLINE static void fsm_reset(fsm_t* fsm)
{
    fsm->state = 0;
    fsm->prev_state = 0;
}

/**
 * Получает состояние конечного автомата.
 * @param fsm Конечный автомат.
 * @return Состояние конечного автомата.
 */
ALWAYS_INLINE static fsm_state_t fsm_state(fsm_t* fsm)
{
    return fsm->state;
}

/**
 * Устанавливает состояние конечного автомата.
 * @param fsm Конечный автомат.
 * @param state Состояние.
 */
ALWAYS_INLINE static void fsm_set_state(fsm_t* fsm, fsm_state_t state)
{
    fsm->state = state;
}

/**
 * Получает предыдущее состояние конечного автомата.
 * @param fsm Конечный автомат.
 * @return Предыдущее состояние конечного автомата.
 */
ALWAYS_INLINE static fsm_state_t fsm_prev_state(fsm_t* fsm)
{
    return fsm->prev_state;
}

/**
 * Устанавливает предыдущее состояние конечного автомата.
 * @param fsm Конечный автомат.
 * @param state Состояние.
 */
ALWAYS_INLINE static void fsm_set_prev_state(fsm_t* fsm, fsm_state_t state)
{
    fsm->prev_state = state;
}

/**
 * Начинает обработку состояния конечного автомата.
 * @param fsm Конечный автомат.
 */
ALWAYS_INLINE static void fsm_begin(fsm_t* fsm)
{
    fsm->m_cur_state = fsm->state;
    fsm->m_state_entry = fsm->m_cur_state != fsm->prev_state;
}

/**
 * Получает текущее состояние конечного автомата.
 * @param fsm Конечный автомат.
 * @return Текущее состояние конечного автомата.
 */
ALWAYS_INLINE static fsm_state_t fsm_cur_state(fsm_t* fsm)
{
    return fsm->m_cur_state;
}

/**
 * Получает флаг первого входа в текущее состояние.
 * @param fsm Конечный автомат.
 * @return Флаг первого входа в текущее состояние.
 */
ALWAYS_INLINE static fsm_flag_t fsm_state_entry(fsm_t* fsm)
{
    return fsm->m_state_entry;
}

///**
// * Получает следующее состояние.
// * Переход в следующее состояние происходит
// * в конце обработке текущего состояния
// * при вызове fsm_end.
// * @param fsm Конечный автомат.
// * @return Следующее состояние.
// */
//ALWAYS_INLINE static fsm_state_t fsm_next_state(fsm_t* fsm)
//{
//    return fsm->next_state;
//}

///**
// * Устанавливает следующее состояние.
// * Переход в следующее состояние происходит
// * в конце обработке текущего состояния
// * при вызове fsm_end.
// * @param fsm Конечный автомат.
// * @param state Следующее состояние.
// */
//ALWAYS_INLINE static void fsm_set_next_state(fsm_t* fsm, fsm_state_t state)
//{
//    fsm->next_state = state;
//}

/**
 * Заканчивает обработку состояний конечного автомата.
 * @param fsm Конечный автомат.
 */
ALWAYS_INLINE static void fsm_end(fsm_t* fsm)
{
    fsm->prev_state = fsm->m_cur_state;
//    fsm->state = fsm->next_state;
}


#endif /* FSM_H */
