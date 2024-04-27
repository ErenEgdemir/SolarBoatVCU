/*
 * THERMALCONTROL.h
 *
 *  Created on: Mar 19, 2024
 *      Author: erenegdemir
 */

#ifndef INC_THERMALCONTROL_H_
#define INC_THERMALCONTROL_H_

#include "adc.h"
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <THROTTLE.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define true 1
#define false 0

float TMA_calc_temperature(uint32_t ADC_VALUE);

void TMA_cooling_automation(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t TEMPERATURE, uint32_t THRESHOLD, uint32_t TOLERANCE, _Bool TOGGLE);

float temp_select(float TEMP_1, float TEMP_2);





#endif /* INC_THERMALCONTROL_H_ */
