#include "iq24_cordic.h"
#include "iq24_cordic_tan_table.h"
#include <stddef.h>
#include <stdbool.h>



void iq24_cordic_atan2_hyp_pu(iq24_t x, iq24_t y, iq24_t* angle, iq24_t* hyp)
{
    if(angle == NULL && hyp == NULL) return;
    
    iq24_t sum_angle = 0;
    iq24_t new_x, new_y;
    
    if(x < 0){
        x = -x;
        y = -y;
        sum_angle = IQ24_CORDIC_ANGLE_PU_180;
    }else if(y < 0){
        sum_angle = IQ24_CORDIC_ANGLE_PU_360;
    }

    int i;
#pragma GCC unroll 23
    for(i = 0; i < IQ24_CORDIC_TAN_TABLE_SIZE; i ++){
        if(y > 0){
            new_x = x + (y >> i);
            new_y = y - (x >> i);
            sum_angle += iq24_cordic_tan_table[i];
        }else{
            new_x = x - (y >> i);
            new_y = y + (x >> i);
            sum_angle -= iq24_cordic_tan_table[i];
        }
        x = new_x;
        y = new_y;
    }
    
    if(angle) { *angle = sum_angle; }
    if(hyp)   { *hyp = iq24_mul(x, IQ24_CORDIC_GAIN); }
}

void iq24_cordic_sincos_pu(iq24_t angle, iq24_t* sin, iq24_t* cos)
{
    if(sin == NULL && cos == NULL) return;
    
    iq24_t sum_angle = 0;
    
    iq24_t x = IQ24_CORDIC_GAIN;
    iq24_t y = 0;
    
    iq24_t new_x, new_y;
    
    // Работа в периодических единицах, поэтому
    // достаточно дробной части.
    angle = angle & IQ24_FRACT_MASK;
    //if(angle >= IQ24_CORDIC_ANGLE_PU_360) angle -= IQ24_CORDIC_ANGLE_PU_360;
    //else if(angle <= -IQ24_CORDIC_ANGLE_PU_360) angle += IQ24_CORDIC_ANGLE_PU_360;
    //if(angle < 0) angle = IQ24_CORDIC_ANGLE_PU_360 + angle;
    
    if(angle > IQ24_CORDIC_ANGLE_PU_270) sum_angle = IQ24_CORDIC_ANGLE_PU_360;
    else if(angle > IQ24_CORDIC_ANGLE_PU_90) sum_angle = IQ24_CORDIC_ANGLE_PU_180;
    
    int i;
#pragma GCC unroll 23
    for(i = 0; i < IQ24_CORDIC_TAN_TABLE_SIZE; i ++){
        if(sum_angle < angle){
            new_x = x - (y >> i);
            new_y = y + (x >> i);
            sum_angle += iq24_cordic_tan_table[i];
        }else{
            new_x = x + (y >> i);
            new_y = y - (x >> i);
            sum_angle -= iq24_cordic_tan_table[i];
        }
        x = new_x;
        y = new_y;
    }
    
    if(angle > IQ24_CORDIC_ANGLE_PU_90 && angle <= IQ24_CORDIC_ANGLE_PU_270){ x = -x; y = -y; }
    
    if(sin) { *sin = y; }
    if(cos) { *cos = x; }
}
