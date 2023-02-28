#ifndef IQ_TYPES_H
#define IQ_TYPES_H

#include <stdint.h>

/*
   Формат с фиксированной запятой
   +------------------+
   |S|III|QQQQQQQQQQQQ|
   +------------------+
   S - бит знака
   I - биты целой части
   Q - биты дробной части
   В примере на диаграмме изображена
   страктура числа с фиксированной запятой
   со знаком, с тремя битами целой части и
   с двенадцатью битами дробной части.
*/

/**
 * Числа с фиксированной запятой разрядностью 8 бит.
 */

//! Знаковые без целой части.
typedef int8_t qb_t; //!< S1 I0 Qm
typedef int8_t q1b_t; //!< S1 I0 Q1
typedef int8_t q2b_t; //!< S1 I0 Q2
typedef int8_t q3b_t; //!< S1 I0 Q3
typedef int8_t q4b_t; //!< S1 I0 Q4
typedef int8_t q5b_t; //!< S1 I0 Q5
typedef int8_t q6b_t; //!< S1 I0 Q6
typedef int8_t q7b_t; //!< S1 I0 Q7
//! Знаковые с целой частью.
typedef int8_t iqb_t; //!< S1 In Qm
typedef int8_t iq1b_t; //!< S1 I6 Q1
typedef int8_t iq2b_t; //!< S1 I5 Q2
typedef int8_t iq3b_t; //!< S1 I4 Q3
typedef int8_t iq4b_t; //!< S1 I3 Q4
typedef int8_t iq5b_t; //!< S1 I2 Q5
typedef int8_t iq6b_t; //!< S1 I1 Q6
//! Беззнаковые без целой части.
typedef uint8_t uqb_t; //!< S0 I0 Qm
typedef uint8_t uq1b_t; //!< S0 I0 Q1
typedef uint8_t uq2b_t; //!< S0 I0 Q2
typedef uint8_t uq3b_t; //!< S0 I0 Q3
typedef uint8_t uq4b_t; //!< S0 I0 Q4
typedef uint8_t uq5b_t; //!< S0 I0 Q5
typedef uint8_t uq6b_t; //!< S0 I0 Q6
typedef uint8_t uq7b_t; //!< S0 I0 Q7
typedef uint8_t uq8b_t; //!< S0 I0 Q8
//! Беззнаковые с целой частью.
typedef uint8_t uiqb_t; //!< S0 In Qm
typedef uint8_t uiq1b_t; //!< S0 I7 Q1
typedef uint8_t uiq2b_t; //!< S0 I6 Q2
typedef uint8_t uiq3b_t; //!< S0 I5 Q3
typedef uint8_t uiq4b_t; //!< S0 I4 Q4
typedef uint8_t uiq5b_t; //!< S0 I3 Q5
typedef uint8_t uiq6b_t; //!< S0 I2 Q6
typedef uint8_t uiq7b_t; //!< S0 I1 Q7


/**
 * Числа с фиксированной запятой разрядностью 16 бит.
 */

//! Знаковые без целой части.
typedef int16_t qs_t; //!< S1 I0 Qm
typedef int16_t q1s_t; //!< S1 I0 Q1
typedef int16_t q2s_t; //!< S1 I0 Q2
typedef int16_t q3s_t; //!< S1 I0 Q3
typedef int16_t q4s_t; //!< S1 I0 Q4
typedef int16_t q5s_t; //!< S1 I0 Q5
typedef int16_t q6s_t; //!< S1 I0 Q6
typedef int16_t q7s_t; //!< S1 I0 Q7
typedef int16_t q8s_t; //!< S1 I0 Q8
typedef int16_t q9s_t; //!< S1 I0 Q9
typedef int16_t q10s_t; //!< S1 I0 Q10
typedef int16_t q11s_t; //!< S1 I0 Q11
typedef int16_t q12s_t; //!< S1 I0 Q12
typedef int16_t q13s_t; //!< S1 I0 Q13
typedef int16_t q14s_t; //!< S1 I0 Q14
typedef int16_t q15s_t; //!< S1 I0 Q15
//! Знаковые с целой частью.
typedef int16_t iqs_t; //!< S1 In Qm
typedef int16_t iq1s_t; //!< S1 I14 Q1
typedef int16_t iq2s_t; //!< S1 I13 Q2
typedef int16_t iq3s_t; //!< S1 I12 Q3
typedef int16_t iq4s_t; //!< S1 I11 Q4
typedef int16_t iq5s_t; //!< S1 I10 Q5
typedef int16_t iq6s_t; //!< S1 I9 Q6
typedef int16_t iq7s_t; //!< S1 I8 Q7
typedef int16_t iq8s_t; //!< S1 I7 Q8
typedef int16_t iq9s_t; //!< S1 I6 Q9
typedef int16_t iq10s_t; //!< S1 I5 Q10
typedef int16_t iq11s_t; //!< S1 I4 Q11
typedef int16_t iq12s_t; //!< S1 I3 Q12
typedef int16_t iq13s_t; //!< S1 I2 Q13
typedef int16_t iq14s_t; //!< S1 I1 Q14
//! Беззнаковые без целой части.
typedef uint16_t uqs_t; //!< S0 I0 Qm
typedef uint16_t uq1s_t; //!< S0 I0 Q1
typedef uint16_t uq2s_t; //!< S0 I0 Q2
typedef uint16_t uq3s_t; //!< S0 I0 Q3
typedef uint16_t uq4s_t; //!< S0 I0 Q4
typedef uint16_t uq5s_t; //!< S0 I0 Q5
typedef uint16_t uq6s_t; //!< S0 I0 Q6
typedef uint16_t uq7s_t; //!< S0 I0 Q7
typedef uint16_t uq8s_t; //!< S0 I0 Q8
typedef uint16_t uq9s_t; //!< S0 I0 Q9
typedef uint16_t uq10s_t; //!< S0 I0 Q10
typedef uint16_t uq11s_t; //!< S0 I0 Q11
typedef uint16_t uq12s_t; //!< S0 I0 Q12
typedef uint16_t uq13s_t; //!< S0 I0 Q13
typedef uint16_t uq14s_t; //!< S0 I0 Q14
typedef uint16_t uq15s_t; //!< S0 I0 Q15
typedef uint16_t uq16s_t; //!< S0 I0 Q16
//! Беззнаковые с целой частью.
typedef uint16_t uiqs_t; //!< S0 In Qm
typedef uint16_t uiq1s_t; //!< S0 I15 Q1
typedef uint16_t uiq2s_t; //!< S0 I14 Q2
typedef uint16_t uiq3s_t; //!< S0 I13 Q3
typedef uint16_t uiq4s_t; //!< S0 I12 Q4
typedef uint16_t uiq5s_t; //!< S0 I11 Q5
typedef uint16_t uiq6s_t; //!< S0 I10 Q6
typedef uint16_t uiq7s_t; //!< S0 I9 Q7
typedef uint16_t uiq8s_t; //!< S0 I8 Q8
typedef uint16_t uiq9s_t; //!< S0 I7 Q9
typedef uint16_t uiq10s_t; //!< S0 I6 Q10
typedef uint16_t uiq11s_t; //!< S0 I5 Q11
typedef uint16_t uiq12s_t; //!< S0 I4 Q12
typedef uint16_t uiq13s_t; //!< S0 I3 Q13
typedef uint16_t uiq14s_t; //!< S0 I2 Q14
typedef uint16_t uiq15s_t; //!< S0 I1 Q15


/**
 * Числа с фиксированной запятой разрядностью 32 бит.
 */

//! Знаковые без целой части.
typedef int32_t ql_t; //!< S1 I0 Qm
typedef int32_t q1l_t; //!< S1 I0 Q1
typedef int32_t q2l_t; //!< S1 I0 Q2
typedef int32_t q3l_t; //!< S1 I0 Q3
typedef int32_t q4l_t; //!< S1 I0 Q4
typedef int32_t q5l_t; //!< S1 I0 Q5
typedef int32_t q6l_t; //!< S1 I0 Q6
typedef int32_t q7l_t; //!< S1 I0 Q7
typedef int32_t q8l_t; //!< S1 I0 Q8
typedef int32_t q9l_t; //!< S1 I0 Q9
typedef int32_t q10l_t; //!< S1 I0 Q10
typedef int32_t q11l_t; //!< S1 I0 Q11
typedef int32_t q12l_t; //!< S1 I0 Q12
typedef int32_t q13l_t; //!< S1 I0 Q13
typedef int32_t q14l_t; //!< S1 I0 Q14
typedef int32_t q15l_t; //!< S1 I0 Q15
typedef int32_t q16l_t; //!< S1 I0 Q16
typedef int32_t q17l_t; //!< S1 I0 Q17
typedef int32_t q18l_t; //!< S1 I0 Q18
typedef int32_t q19l_t; //!< S1 I0 Q19
typedef int32_t q20l_t; //!< S1 I0 Q20
typedef int32_t q21l_t; //!< S1 I0 Q21
typedef int32_t q22l_t; //!< S1 I0 Q22
typedef int32_t q23l_t; //!< S1 I0 Q23
typedef int32_t q24l_t; //!< S1 I0 Q24
typedef int32_t q25l_t; //!< S1 I0 Q25
typedef int32_t q26l_t; //!< S1 I0 Q26
typedef int32_t q27l_t; //!< S1 I0 Q27
typedef int32_t q28l_t; //!< S1 I0 Q28
typedef int32_t q29l_t; //!< S1 I0 Q29
typedef int32_t q30l_t; //!< S1 I0 Q30
typedef int32_t q31l_t; //!< S1 I0 Q31
//! Знаковые с целой частью.
typedef int32_t iql_t; //!< S1 In Qm
typedef int32_t iq1l_t; //!< S1 I30 Q1
typedef int32_t iq2l_t; //!< S1 I29 Q2
typedef int32_t iq3l_t; //!< S1 I28 Q3
typedef int32_t iq4l_t; //!< S1 I27 Q4
typedef int32_t iq5l_t; //!< S1 I26 Q5
typedef int32_t iq6l_t; //!< S1 I25 Q6
typedef int32_t iq7l_t; //!< S1 I24 Q7
typedef int32_t iq8l_t; //!< S1 I23 Q8
typedef int32_t iq9l_t; //!< S1 I22 Q9
typedef int32_t iq10l_t; //!< S1 I21 Q10
typedef int32_t iq11l_t; //!< S1 I20 Q11
typedef int32_t iq12l_t; //!< S1 I19 Q12
typedef int32_t iq13l_t; //!< S1 I18 Q13
typedef int32_t iq14l_t; //!< S1 I17 Q14
typedef int32_t iq15l_t; //!< S1 I16 Q15
typedef int32_t iq16l_t; //!< S1 I15 Q16
typedef int32_t iq17l_t; //!< S1 I14 Q17
typedef int32_t iq18l_t; //!< S1 I13 Q18
typedef int32_t iq19l_t; //!< S1 I12 Q19
typedef int32_t iq20l_t; //!< S1 I11 Q20
typedef int32_t iq21l_t; //!< S1 I10 Q21
typedef int32_t iq22l_t; //!< S1 I9 Q22
typedef int32_t iq23l_t; //!< S1 I8 Q23
typedef int32_t iq24l_t; //!< S1 I7 Q24
typedef int32_t iq25l_t; //!< S1 I6 Q25
typedef int32_t iq26l_t; //!< S1 I5 Q26
typedef int32_t iq27l_t; //!< S1 I4 Q27
typedef int32_t iq28l_t; //!< S1 I3 Q28
typedef int32_t iq29l_t; //!< S1 I2 Q29
typedef int32_t iq30l_t; //!< S1 I1 Q30
//! Беззнаковые без целой части.
typedef uint32_t uql_t; //!< S0 I0 Qm
typedef uint32_t uq1l_t; //!< S0 I0 Q1
typedef uint32_t uq2l_t; //!< S0 I0 Q2
typedef uint32_t uq3l_t; //!< S0 I0 Q3
typedef uint32_t uq4l_t; //!< S0 I0 Q4
typedef uint32_t uq5l_t; //!< S0 I0 Q5
typedef uint32_t uq6l_t; //!< S0 I0 Q6
typedef uint32_t uq7l_t; //!< S0 I0 Q7
typedef uint32_t uq8l_t; //!< S0 I0 Q8
typedef uint32_t uq9l_t; //!< S0 I0 Q9
typedef uint32_t uq10l_t; //!< S0 I0 Q10
typedef uint32_t uq11l_t; //!< S0 I0 Q11
typedef uint32_t uq12l_t; //!< S0 I0 Q12
typedef uint32_t uq13l_t; //!< S0 I0 Q13
typedef uint32_t uq14l_t; //!< S0 I0 Q14
typedef uint32_t uq15l_t; //!< S0 I0 Q15
typedef uint32_t uq16l_t; //!< S0 I0 Q16
typedef uint32_t uq17l_t; //!< S0 I0 Q17
typedef uint32_t uq18l_t; //!< S0 I0 Q18
typedef uint32_t uq19l_t; //!< S0 I0 Q19
typedef uint32_t uq20l_t; //!< S0 I0 Q20
typedef uint32_t uq21l_t; //!< S0 I0 Q21
typedef uint32_t uq22l_t; //!< S0 I0 Q22
typedef uint32_t uq23l_t; //!< S0 I0 Q23
typedef uint32_t uq24l_t; //!< S0 I0 Q24
typedef uint32_t uq25l_t; //!< S0 I0 Q25
typedef uint32_t uq26l_t; //!< S0 I0 Q26
typedef uint32_t uq27l_t; //!< S0 I0 Q27
typedef uint32_t uq28l_t; //!< S0 I0 Q28
typedef uint32_t uq29l_t; //!< S0 I0 Q29
typedef uint32_t uq30l_t; //!< S0 I0 Q30
typedef uint32_t uq31l_t; //!< S0 I0 Q31
typedef uint32_t uq32l_t; //!< S0 I0 Q32
//! Беззнаковые с целой частью.
typedef uint32_t uiql_t; //!< S0 In Qm
typedef uint32_t uiq1l_t; //!< S0 I31 Q1
typedef uint32_t uiq2l_t; //!< S0 I30 Q2
typedef uint32_t uiq3l_t; //!< S0 I29 Q3
typedef uint32_t uiq4l_t; //!< S0 I28 Q4
typedef uint32_t uiq5l_t; //!< S0 I27 Q5
typedef uint32_t uiq6l_t; //!< S0 I26 Q6
typedef uint32_t uiq7l_t; //!< S0 I25 Q7
typedef uint32_t uiq8l_t; //!< S0 I24 Q8
typedef uint32_t uiq9l_t; //!< S0 I23 Q9
typedef uint32_t uiq10l_t; //!< S0 I22 Q10
typedef uint32_t uiq11l_t; //!< S0 I21 Q11
typedef uint32_t uiq12l_t; //!< S0 I20 Q12
typedef uint32_t uiq13l_t; //!< S0 I19 Q13
typedef uint32_t uiq14l_t; //!< S0 I18 Q14
typedef uint32_t uiq15l_t; //!< S0 I17 Q15
typedef uint32_t uiq16l_t; //!< S0 I16 Q16
typedef uint32_t uiq17l_t; //!< S0 I15 Q17
typedef uint32_t uiq18l_t; //!< S0 I14 Q18
typedef uint32_t uiq19l_t; //!< S0 I13 Q19
typedef uint32_t uiq20l_t; //!< S0 I12 Q20
typedef uint32_t uiq21l_t; //!< S0 I11 Q21
typedef uint32_t uiq22l_t; //!< S0 I10 Q22
typedef uint32_t uiq23l_t; //!< S0 I9 Q23
typedef uint32_t uiq24l_t; //!< S0 I8 Q24
typedef uint32_t uiq25l_t; //!< S0 I7 Q25
typedef uint32_t uiq26l_t; //!< S0 I6 Q26
typedef uint32_t uiq27l_t; //!< S0 I5 Q27
typedef uint32_t uiq28l_t; //!< S0 I4 Q28
typedef uint32_t uiq29l_t; //!< S0 I3 Q29
typedef uint32_t uiq30l_t; //!< S0 I2 Q30
typedef uint32_t uiq31l_t; //!< S0 I1 Q31


/**
 * Числа с фиксированной запятой разрядностью 64 бит.
 */

//! Знаковые без целой части.
typedef int64_t qll_t; //!< S1 I0 Qm
typedef int64_t q1ll_t; //!< S1 I0 Q1
typedef int64_t q2ll_t; //!< S1 I0 Q2
typedef int64_t q3ll_t; //!< S1 I0 Q3
typedef int64_t q4ll_t; //!< S1 I0 Q4
typedef int64_t q5ll_t; //!< S1 I0 Q5
typedef int64_t q6ll_t; //!< S1 I0 Q6
typedef int64_t q7ll_t; //!< S1 I0 Q7
typedef int64_t q8ll_t; //!< S1 I0 Q8
typedef int64_t q9ll_t; //!< S1 I0 Q9
typedef int64_t q10ll_t; //!< S1 I0 Q10
typedef int64_t q11ll_t; //!< S1 I0 Q11
typedef int64_t q12ll_t; //!< S1 I0 Q12
typedef int64_t q13ll_t; //!< S1 I0 Q13
typedef int64_t q14ll_t; //!< S1 I0 Q14
typedef int64_t q15ll_t; //!< S1 I0 Q15
typedef int64_t q16ll_t; //!< S1 I0 Q16
typedef int64_t q17ll_t; //!< S1 I0 Q17
typedef int64_t q18ll_t; //!< S1 I0 Q18
typedef int64_t q19ll_t; //!< S1 I0 Q19
typedef int64_t q20ll_t; //!< S1 I0 Q20
typedef int64_t q21ll_t; //!< S1 I0 Q21
typedef int64_t q22ll_t; //!< S1 I0 Q22
typedef int64_t q23ll_t; //!< S1 I0 Q23
typedef int64_t q24ll_t; //!< S1 I0 Q24
typedef int64_t q25ll_t; //!< S1 I0 Q25
typedef int64_t q26ll_t; //!< S1 I0 Q26
typedef int64_t q27ll_t; //!< S1 I0 Q27
typedef int64_t q28ll_t; //!< S1 I0 Q28
typedef int64_t q29ll_t; //!< S1 I0 Q29
typedef int64_t q30ll_t; //!< S1 I0 Q30
typedef int64_t q31ll_t; //!< S1 I0 Q31
typedef int64_t q32ll_t; //!< S1 I0 Q32
typedef int64_t q33ll_t; //!< S1 I0 Q33
typedef int64_t q34ll_t; //!< S1 I0 Q34
typedef int64_t q35ll_t; //!< S1 I0 Q35
typedef int64_t q36ll_t; //!< S1 I0 Q36
typedef int64_t q37ll_t; //!< S1 I0 Q37
typedef int64_t q38ll_t; //!< S1 I0 Q38
typedef int64_t q39ll_t; //!< S1 I0 Q39
typedef int64_t q40ll_t; //!< S1 I0 Q40
typedef int64_t q41ll_t; //!< S1 I0 Q41
typedef int64_t q42ll_t; //!< S1 I0 Q42
typedef int64_t q43ll_t; //!< S1 I0 Q43
typedef int64_t q44ll_t; //!< S1 I0 Q44
typedef int64_t q45ll_t; //!< S1 I0 Q45
typedef int64_t q46ll_t; //!< S1 I0 Q46
typedef int64_t q47ll_t; //!< S1 I0 Q47
typedef int64_t q48ll_t; //!< S1 I0 Q48
typedef int64_t q49ll_t; //!< S1 I0 Q49
typedef int64_t q50ll_t; //!< S1 I0 Q50
typedef int64_t q51ll_t; //!< S1 I0 Q51
typedef int64_t q52ll_t; //!< S1 I0 Q52
typedef int64_t q53ll_t; //!< S1 I0 Q53
typedef int64_t q54ll_t; //!< S1 I0 Q54
typedef int64_t q55ll_t; //!< S1 I0 Q55
typedef int64_t q56ll_t; //!< S1 I0 Q56
typedef int64_t q57ll_t; //!< S1 I0 Q57
typedef int64_t q58ll_t; //!< S1 I0 Q58
typedef int64_t q59ll_t; //!< S1 I0 Q59
typedef int64_t q60ll_t; //!< S1 I0 Q60
typedef int64_t q61ll_t; //!< S1 I0 Q61
typedef int64_t q62ll_t; //!< S1 I0 Q62
typedef int64_t q63ll_t; //!< S1 I0 Q63
//! Знаковые с целой частью.
typedef int64_t iqll_t; //!< S1 In Qm
typedef int64_t iq1ll_t; //!< S1 I62 Q1
typedef int64_t iq2ll_t; //!< S1 I61 Q2
typedef int64_t iq3ll_t; //!< S1 I60 Q3
typedef int64_t iq4ll_t; //!< S1 I59 Q4
typedef int64_t iq5ll_t; //!< S1 I58 Q5
typedef int64_t iq6ll_t; //!< S1 I57 Q6
typedef int64_t iq7ll_t; //!< S1 I56 Q7
typedef int64_t iq8ll_t; //!< S1 I55 Q8
typedef int64_t iq9ll_t; //!< S1 I54 Q9
typedef int64_t iq10ll_t; //!< S1 I53 Q10
typedef int64_t iq11ll_t; //!< S1 I52 Q11
typedef int64_t iq12ll_t; //!< S1 I51 Q12
typedef int64_t iq13ll_t; //!< S1 I50 Q13
typedef int64_t iq14ll_t; //!< S1 I49 Q14
typedef int64_t iq15ll_t; //!< S1 I48 Q15
typedef int64_t iq16ll_t; //!< S1 I47 Q16
typedef int64_t iq17ll_t; //!< S1 I46 Q17
typedef int64_t iq18ll_t; //!< S1 I45 Q18
typedef int64_t iq19ll_t; //!< S1 I44 Q19
typedef int64_t iq20ll_t; //!< S1 I43 Q20
typedef int64_t iq21ll_t; //!< S1 I42 Q21
typedef int64_t iq22ll_t; //!< S1 I41 Q22
typedef int64_t iq23ll_t; //!< S1 I40 Q23
typedef int64_t iq24ll_t; //!< S1 I39 Q24
typedef int64_t iq25ll_t; //!< S1 I38 Q25
typedef int64_t iq26ll_t; //!< S1 I37 Q26
typedef int64_t iq27ll_t; //!< S1 I36 Q27
typedef int64_t iq28ll_t; //!< S1 I35 Q28
typedef int64_t iq29ll_t; //!< S1 I34 Q29
typedef int64_t iq30ll_t; //!< S1 I33 Q30
typedef int64_t iq31ll_t; //!< S1 I32 Q31
typedef int64_t iq32ll_t; //!< S1 I31 Q32
typedef int64_t iq33ll_t; //!< S1 I30 Q33
typedef int64_t iq34ll_t; //!< S1 I29 Q34
typedef int64_t iq35ll_t; //!< S1 I28 Q35
typedef int64_t iq36ll_t; //!< S1 I27 Q36
typedef int64_t iq37ll_t; //!< S1 I26 Q37
typedef int64_t iq38ll_t; //!< S1 I25 Q38
typedef int64_t iq39ll_t; //!< S1 I24 Q39
typedef int64_t iq40ll_t; //!< S1 I23 Q40
typedef int64_t iq41ll_t; //!< S1 I22 Q41
typedef int64_t iq42ll_t; //!< S1 I21 Q42
typedef int64_t iq43ll_t; //!< S1 I20 Q43
typedef int64_t iq44ll_t; //!< S1 I19 Q44
typedef int64_t iq45ll_t; //!< S1 I18 Q45
typedef int64_t iq46ll_t; //!< S1 I17 Q46
typedef int64_t iq47ll_t; //!< S1 I16 Q47
typedef int64_t iq48ll_t; //!< S1 I15 Q48
typedef int64_t iq49ll_t; //!< S1 I14 Q49
typedef int64_t iq50ll_t; //!< S1 I13 Q50
typedef int64_t iq51ll_t; //!< S1 I12 Q51
typedef int64_t iq52ll_t; //!< S1 I11 Q52
typedef int64_t iq53ll_t; //!< S1 I10 Q53
typedef int64_t iq54ll_t; //!< S1 I9 Q54
typedef int64_t iq55ll_t; //!< S1 I8 Q55
typedef int64_t iq56ll_t; //!< S1 I7 Q56
typedef int64_t iq57ll_t; //!< S1 I6 Q57
typedef int64_t iq58ll_t; //!< S1 I5 Q58
typedef int64_t iq59ll_t; //!< S1 I4 Q59
typedef int64_t iq60ll_t; //!< S1 I3 Q60
typedef int64_t iq61ll_t; //!< S1 I2 Q61
typedef int64_t iq62ll_t; //!< S1 I1 Q62
//! Беззнаковые без целой части.
typedef uint64_t uqll_t; //!< S0 I0 Qm
typedef uint64_t uq1ll_t; //!< S0 I0 Q1
typedef uint64_t uq2ll_t; //!< S0 I0 Q2
typedef uint64_t uq3ll_t; //!< S0 I0 Q3
typedef uint64_t uq4ll_t; //!< S0 I0 Q4
typedef uint64_t uq5ll_t; //!< S0 I0 Q5
typedef uint64_t uq6ll_t; //!< S0 I0 Q6
typedef uint64_t uq7ll_t; //!< S0 I0 Q7
typedef uint64_t uq8ll_t; //!< S0 I0 Q8
typedef uint64_t uq9ll_t; //!< S0 I0 Q9
typedef uint64_t uq10ll_t; //!< S0 I0 Q10
typedef uint64_t uq11ll_t; //!< S0 I0 Q11
typedef uint64_t uq12ll_t; //!< S0 I0 Q12
typedef uint64_t uq13ll_t; //!< S0 I0 Q13
typedef uint64_t uq14ll_t; //!< S0 I0 Q14
typedef uint64_t uq15ll_t; //!< S0 I0 Q15
typedef uint64_t uq16ll_t; //!< S0 I0 Q16
typedef uint64_t uq17ll_t; //!< S0 I0 Q17
typedef uint64_t uq18ll_t; //!< S0 I0 Q18
typedef uint64_t uq19ll_t; //!< S0 I0 Q19
typedef uint64_t uq20ll_t; //!< S0 I0 Q20
typedef uint64_t uq21ll_t; //!< S0 I0 Q21
typedef uint64_t uq22ll_t; //!< S0 I0 Q22
typedef uint64_t uq23ll_t; //!< S0 I0 Q23
typedef uint64_t uq24ll_t; //!< S0 I0 Q24
typedef uint64_t uq25ll_t; //!< S0 I0 Q25
typedef uint64_t uq26ll_t; //!< S0 I0 Q26
typedef uint64_t uq27ll_t; //!< S0 I0 Q27
typedef uint64_t uq28ll_t; //!< S0 I0 Q28
typedef uint64_t uq29ll_t; //!< S0 I0 Q29
typedef uint64_t uq30ll_t; //!< S0 I0 Q30
typedef uint64_t uq31ll_t; //!< S0 I0 Q31
typedef uint64_t uq32ll_t; //!< S0 I0 Q32
typedef uint64_t uq33ll_t; //!< S0 I0 Q33
typedef uint64_t uq34ll_t; //!< S0 I0 Q34
typedef uint64_t uq35ll_t; //!< S0 I0 Q35
typedef uint64_t uq36ll_t; //!< S0 I0 Q36
typedef uint64_t uq37ll_t; //!< S0 I0 Q37
typedef uint64_t uq38ll_t; //!< S0 I0 Q38
typedef uint64_t uq39ll_t; //!< S0 I0 Q39
typedef uint64_t uq40ll_t; //!< S0 I0 Q40
typedef uint64_t uq41ll_t; //!< S0 I0 Q41
typedef uint64_t uq42ll_t; //!< S0 I0 Q42
typedef uint64_t uq43ll_t; //!< S0 I0 Q43
typedef uint64_t uq44ll_t; //!< S0 I0 Q44
typedef uint64_t uq45ll_t; //!< S0 I0 Q45
typedef uint64_t uq46ll_t; //!< S0 I0 Q46
typedef uint64_t uq47ll_t; //!< S0 I0 Q47
typedef uint64_t uq48ll_t; //!< S0 I0 Q48
typedef uint64_t uq49ll_t; //!< S0 I0 Q49
typedef uint64_t uq50ll_t; //!< S0 I0 Q50
typedef uint64_t uq51ll_t; //!< S0 I0 Q51
typedef uint64_t uq52ll_t; //!< S0 I0 Q52
typedef uint64_t uq53ll_t; //!< S0 I0 Q53
typedef uint64_t uq54ll_t; //!< S0 I0 Q54
typedef uint64_t uq55ll_t; //!< S0 I0 Q55
typedef uint64_t uq56ll_t; //!< S0 I0 Q56
typedef uint64_t uq57ll_t; //!< S0 I0 Q57
typedef uint64_t uq58ll_t; //!< S0 I0 Q58
typedef uint64_t uq59ll_t; //!< S0 I0 Q59
typedef uint64_t uq60ll_t; //!< S0 I0 Q60
typedef uint64_t uq61ll_t; //!< S0 I0 Q61
typedef uint64_t uq62ll_t; //!< S0 I0 Q62
typedef uint64_t uq63ll_t; //!< S0 I0 Q63
typedef uint64_t uq64ll_t; //!< S0 I0 Q64
//! Беззнаковые с целой частью.
typedef uint64_t uiqll_t; //!< S0 In Qm
typedef uint64_t uiq1ll_t; //!< S0 I63 Q1
typedef uint64_t uiq2ll_t; //!< S0 I62 Q2
typedef uint64_t uiq3ll_t; //!< S0 I61 Q3
typedef uint64_t uiq4ll_t; //!< S0 I60 Q4
typedef uint64_t uiq5ll_t; //!< S0 I59 Q5
typedef uint64_t uiq6ll_t; //!< S0 I58 Q6
typedef uint64_t uiq7ll_t; //!< S0 I57 Q7
typedef uint64_t uiq8ll_t; //!< S0 I56 Q8
typedef uint64_t uiq9ll_t; //!< S0 I55 Q9
typedef uint64_t uiq10ll_t; //!< S0 I54 Q10
typedef uint64_t uiq11ll_t; //!< S0 I53 Q11
typedef uint64_t uiq12ll_t; //!< S0 I52 Q12
typedef uint64_t uiq13ll_t; //!< S0 I51 Q13
typedef uint64_t uiq14ll_t; //!< S0 I50 Q14
typedef uint64_t uiq15ll_t; //!< S0 I49 Q15
typedef uint64_t uiq16ll_t; //!< S0 I48 Q16
typedef uint64_t uiq17ll_t; //!< S0 I47 Q17
typedef uint64_t uiq18ll_t; //!< S0 I46 Q18
typedef uint64_t uiq19ll_t; //!< S0 I45 Q19
typedef uint64_t uiq20ll_t; //!< S0 I44 Q20
typedef uint64_t uiq21ll_t; //!< S0 I43 Q21
typedef uint64_t uiq22ll_t; //!< S0 I42 Q22
typedef uint64_t uiq23ll_t; //!< S0 I41 Q23
typedef uint64_t uiq24ll_t; //!< S0 I40 Q24
typedef uint64_t uiq25ll_t; //!< S0 I39 Q25
typedef uint64_t uiq26ll_t; //!< S0 I38 Q26
typedef uint64_t uiq27ll_t; //!< S0 I37 Q27
typedef uint64_t uiq28ll_t; //!< S0 I36 Q28
typedef uint64_t uiq29ll_t; //!< S0 I35 Q29
typedef uint64_t uiq30ll_t; //!< S0 I34 Q30
typedef uint64_t uiq31ll_t; //!< S0 I33 Q31
typedef uint64_t uiq32ll_t; //!< S0 I32 Q32
typedef uint64_t uiq33ll_t; //!< S0 I31 Q33
typedef uint64_t uiq34ll_t; //!< S0 I30 Q34
typedef uint64_t uiq35ll_t; //!< S0 I29 Q35
typedef uint64_t uiq36ll_t; //!< S0 I28 Q36
typedef uint64_t uiq37ll_t; //!< S0 I27 Q37
typedef uint64_t uiq38ll_t; //!< S0 I26 Q38
typedef uint64_t uiq39ll_t; //!< S0 I25 Q39
typedef uint64_t uiq40ll_t; //!< S0 I24 Q40
typedef uint64_t uiq41ll_t; //!< S0 I23 Q41
typedef uint64_t uiq42ll_t; //!< S0 I22 Q42
typedef uint64_t uiq43ll_t; //!< S0 I21 Q43
typedef uint64_t uiq44ll_t; //!< S0 I20 Q44
typedef uint64_t uiq45ll_t; //!< S0 I19 Q45
typedef uint64_t uiq46ll_t; //!< S0 I18 Q46
typedef uint64_t uiq47ll_t; //!< S0 I17 Q47
typedef uint64_t uiq48ll_t; //!< S0 I16 Q48
typedef uint64_t uiq49ll_t; //!< S0 I15 Q49
typedef uint64_t uiq50ll_t; //!< S0 I14 Q50
typedef uint64_t uiq51ll_t; //!< S0 I13 Q51
typedef uint64_t uiq52ll_t; //!< S0 I12 Q52
typedef uint64_t uiq53ll_t; //!< S0 I11 Q53
typedef uint64_t uiq54ll_t; //!< S0 I10 Q54
typedef uint64_t uiq55ll_t; //!< S0 I9 Q55
typedef uint64_t uiq56ll_t; //!< S0 I8 Q56
typedef uint64_t uiq57ll_t; //!< S0 I7 Q57
typedef uint64_t uiq58ll_t; //!< S0 I6 Q58
typedef uint64_t uiq59ll_t; //!< S0 I5 Q59
typedef uint64_t uiq60ll_t; //!< S0 I4 Q60
typedef uint64_t uiq61ll_t; //!< S0 I3 Q61
typedef uint64_t uiq62ll_t; //!< S0 I2 Q62
typedef uint64_t uiq63ll_t; //!< S0 I1 Q63


#endif // IQ_TYPES_H
