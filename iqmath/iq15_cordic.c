#include "iq15_cordic.h"
#include "iq15_cordic_tan_table.h"
#include <stddef.h>
#include <stdbool.h>



void iq15_cordic_atan2_hyp_pu(iq15_t x, iq15_t y, iq15_t* angle, iq15_t* hyp)
{
    if(angle == NULL && hyp == NULL) return;
    
    iq15_t sum_angle = 0;
    iq15_t new_x, new_y;
    
    if(x < 0){
        x = -x;
        y = -y;
        sum_angle = IQ15_CORDIC_ANGLE_PU_180;
    }else if(y < 0){
        sum_angle = IQ15_CORDIC_ANGLE_PU_360;
    }

    int i;
#pragma GCC unroll 15
    for(i = 0; i < IQ15_CORDIC_TAN_TABLE_SIZE; i ++){
        if(y > 0){
            new_x = x + (y >> i);
            new_y = y - (x >> i);
            sum_angle += iq15_cordic_tan_table[i];
        }else{
            new_x = x - (y >> i);
            new_y = y + (x >> i);
            sum_angle -= iq15_cordic_tan_table[i];
        }
        x = new_x;
        y = new_y;
    }
    
    if(angle) { *angle = sum_angle; }
    if(hyp)   { *hyp = iq15_mul(x, IQ15_CORDIC_GAIN); }
}

void iq15_cordic_sincos_pu(iq15_t angle, iq15_t* sin, iq15_t* cos)
{
    if(sin == NULL && cos == NULL) return;
    
    iq15_t sum_angle = 0;
    
    iq15_t x = IQ15_CORDIC_GAIN;
    iq15_t y = 0;
    
    iq15_t new_x, new_y;
    
    // Работа в периодических единицах, поэтому
    // достаточно дробной части.
    angle = angle & IQ15_FRACT_MASK;
    //if(angle >= IQ15_CORDIC_ANGLE_PU_360) angle -= IQ15_CORDIC_ANGLE_PU_360;
    //else if(angle <= -IQ15_CORDIC_ANGLE_PU_360) angle += IQ15_CORDIC_ANGLE_PU_360;
    //if(angle < 0) angle = IQ15_CORDIC_ANGLE_PU_360 + angle;
    
    if(angle > IQ15_CORDIC_ANGLE_PU_270) sum_angle = IQ15_CORDIC_ANGLE_PU_360;
    else if(angle > IQ15_CORDIC_ANGLE_PU_90) sum_angle = IQ15_CORDIC_ANGLE_PU_180;
    
    int i;
#pragma GCC unroll 15
    for(i = 0; i < IQ15_CORDIC_TAN_TABLE_SIZE; i ++){
        if(sum_angle < angle){
            new_x = x - (y >> i);
            new_y = y + (x >> i);
            sum_angle += iq15_cordic_tan_table[i];
        }else{
            new_x = x + (y >> i);
            new_y = y - (x >> i);
            sum_angle -= iq15_cordic_tan_table[i];
        }
        x = new_x;
        y = new_y;
    }
    
    if(angle > IQ15_CORDIC_ANGLE_PU_90 && angle <= IQ15_CORDIC_ANGLE_PU_270){ x = -x; y = -y; }
    
    if(sin) { *sin = y; }
    if(cos) { *cos = x; }
}
