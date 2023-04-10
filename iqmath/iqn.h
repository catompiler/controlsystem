#ifndef IQ_BASE_H
#define IQ_BASE_H


// TYPE - Тип числа.
// BASE_TYPE - Тип для базового значения (1.0).
// MASK_TYPE - Тип для маски.
// EXT_TYPE - Тип, вмещающий больше разрядов (int32_t для int16_t).
// INT_BITS - Число целых бит.
// FRACT_BITS - Число дробных бит.
// N - Число дробный бит исходного числа.
// M - Число дробный бит преобразованного числа.

// Ограничения:
// FRACT_BITS > 0

//! Делитель дробной части (значение 1.0).
#define IQN_BASE(FRACT_BITS, BASE_TYPE) (((BASE_TYPE)1) << (FRACT_BITS))

//! Маска дробной части.
#define IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE) ((((MASK_TYPE)1)<<((FRACT_BITS)-1)) | ((((MASK_TYPE)1)<<((FRACT_BITS)-1))-1)) //((((MASK_TYPE)1) << (FRACT_BITS)) - 1)

//! Маска знака.
#define IQN_SIGN_MASK(INT_BITS, FRACT_BITS, MASK_TYPE) (((MASK_TYPE)1) << (INT_BITS+FRACT_BITS))

//! Бит сатурации.
#define IQN_SAT_BIT(INT_BITS, FRACT_BITS) ((INT_BITS+FRACT_BITS) + 1)


//! Вычисляет число с фиксированной запятой по float.
#define IQN(F, FRACT_BITS, TYPE, BASE_TYPE) ((TYPE)((F) * IQN_BASE(FRACT_BITS, BASE_TYPE)))

//! Вычисляет число с фиксированной запятой по int.
#define IQNI(I, FRACT_BITS, TYPE) (((TYPE)(I)) << (FRACT_BITS))

//! Вычисляет число с фиксированной запятой по дроби A/B.
#define IQNF(A, B, FRACT_BITS, TYPE, EXT_TYPE) ((TYPE)((((EXT_TYPE)(A)) << (FRACT_BITS)) / (B)))


//! Половина в виде числа с фиксированной запятой.
#define IQN_HALF(FRACT_BITS, TYPE) IQN_BASE(((FRACT_BITS)-1), TYPE)


//! Преобразовывает число с фиксированной запятой
//! из формата Qn в формат Qm.
#define IQN_N_TO_M(Q, N, M) ((M > N) ? ((Q) << (M - N)) : ((Q) >> (N - M)))

//! Получает модуль числа с фиксированной запятой.
#define IQN_ABS(Q) (((Q) >= 0) ? ((Q)) : (-(Q)))


//! Максимальное число IQ.
#define IQN_MAX(INT_BITS, FRACT_BITS, TYPE, MASK_TYPE) ((TYPE)((((MASK_TYPE)1)<<((INT_BITS)+(FRACT_BITS)-1)) | ((((MASK_TYPE)1)<<((INT_BITS)+(FRACT_BITS)-1))-1))) //((TYPE)((((MASK_TYPE)1)<<((INT_BITS)+(FRACT_BITS)))-1))

//! Минимальное число IQ.
#define IQN_MIN(INT_BITS, FRACT_BITS, TYPE, MASK_TYPE) ((TYPE)(((MASK_TYPE)-1)<<((INT_BITS)+(FRACT_BITS))))


//! Максимальное беззнаковое число IQ.
#define UIQN_MAX(INT_BITS, FRACT_BITS, TYPE, MASK_TYPE) ((TYPE)((((MASK_TYPE)1)<<((INT_BITS)+(FRACT_BITS)-1)) | ((((MASK_TYPE)1)<<((INT_BITS)+(FRACT_BITS)-1))-1)))

//! Минимальное беззнаковое число IQ.
#define UIQN_MIN(INT_BITS, FRACT_BITS, TYPE, MASK_TYPE) ((TYPE)(0))


//! Максимальная целая часть IQ.
#define IQN_IMAX(INT_BITS, FRACT_BITS, TYPE, MASK_TYPE, BASE_TYPE) ((TYPE)(IQN_MAX(INT_BITS,FRACT_BITS,TYPE,MASK_TYPE)/IQN_BASE(FRACT_BITS,BASE_TYPE)))

//! Минимальная целая часть IQ.
#define IQN_IMIN(INT_BITS, FRACT_BITS, TYPE, MASK_TYPE, BASE_TYPE) ((TYPE)(IQN_MIN(INT_BITS,FRACT_BITS,TYPE,MASK_TYPE)/IQN_BASE(FRACT_BITS,BASE_TYPE)))


//! Максимальная беззнаковая целая часть IQ.
#define UIQN_IMAX(INT_BITS, FRACT_BITS, TYPE, MASK_TYPE, BASE_TYPE) ((TYPE)(UIQN_MAX(INT_BITS,FRACT_BITS,TYPE,MASK_TYPE)/IQN_BASE(FRACT_BITS,BASE_TYPE)))

//! Минимальная беззнаковая целая часть IQ.
#define UIQN_IMIN(INT_BITS, FRACT_BITS, TYPE, MASK_TYPE, BASE_TYPE) ((TYPE)(UIQN_MIN(INT_BITS,FRACT_BITS,TYPE,MASK_TYPE)/IQN_BASE(FRACT_BITS,BASE_TYPE)))


//! Получает целую часть числа с фиксированной запятой.
#define IQN_INT(Q, FRACT_BITS) (((Q) >= 0) ? ((Q) >> (FRACT_BITS)) : (-((-(Q)) >> (FRACT_BITS))))

//! Получает дробную часть числа с фиксированной запятой.
#define IQN_FRACT(Q, FRACT_BITS, MASK_TYPE) (((Q) >= 0) ? ((Q) & IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE)) : (-((-(Q)) & IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE))))


//! Округляет вниз число с фиксированной запятой.
#define IQN_FLOOR(Q, FRACT_BITS, MASK_TYPE) (((Q) >= 0) ? ((Q) & (~IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE))) : (-((-(Q)) & (~IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE)))))

//! Округляет вверх число с фиксированной запятой.
#define IQN_CEIL(Q, FRACT_BITS, TYPE, MASK_TYPE) (((Q) >= 0) ? (((Q)+(TYPE)IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE)) & (~IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE))) : (-(((-(Q))+(TYPE)IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE)) & (~IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE)))))

//! Округляет число с фиксированной запятой.
#define IQN_ROUND(Q, FRACT_BITS, TYPE, MASK_TYPE) (((Q) >= 0) ? (((Q)+IQN_HALF(FRACT_BITS, TYPE)) & (~IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE))) : (-(((-(Q))+IQN_HALF(FRACT_BITS, TYPE)) & (~IQN_FRACT_MASK(FRACT_BITS, MASK_TYPE)))))


#endif /* IQ_BASE_H */
