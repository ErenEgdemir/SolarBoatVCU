/*
 * THROTTLE.h
 *
 *  Created on: Mar 16, 2024
 *      Author: erenegdemir
 */

#ifndef INC_THROTTLE_H_
#define INC_THROTTLE_H_

#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

float Error = 0;




//Functions

uint32_t THR_pt1Filter_2(float INPUT, float Kp, float Ti, float Ts);
uint32_t THR_map(uint32_t VERIABLE, uint32_t VER_LOW_VAL, uint32_t VER_HIGH_VAL, uint32_t MAP_LOW_VAL, uint32_t MAP_HIGH_VALUE);


#endif /* INC_THROTTLE_H_ */
