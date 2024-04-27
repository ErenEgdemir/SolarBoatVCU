/*
 * THROTTLE.c
 *
 *  Created on: Mar 16, 2024
 *      Author: erenegdemir
 */



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



/**********************************************************************************************
 * Function Name  : float pt1Filter_2(float INPUT, float Kp, float Ti, float Ts)
 * Description    : Filtering duty cycle for soft throttle signals
 * Input          : raw duty cycle, Kp (integral phactor), Ti (time integral constant), Ts (timing period).
 * Output         : None
 * Return         : Filtered duty cycle
 * Attention	  : None
 **********************************************************************************************/
uint32_t THR_pt1Filter_2(float INPUT, float Kp, float Ti, float Ts){
	float T_ERROR = 0;
	static float Output2;
	static float prevOutput2;
//	float Kp = 20;
//	float Ti = 1.0;  // Integral time constant
//	float Ts = 0.001; // Sampling time

	T_ERROR = INPUT - prevOutput2;
	Output2 = Output2 + (Kp * T_ERROR * Ts) / (1 + Ti * Ts);

	prevOutput2 = Output2;

	return (uint32_t)Output2;

}

/**********************************************************************************************
 * Function Name  : void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
 * Description    : interrupt handler for adc
 * Input          : None
 * Output         : Pot variables
 * Return         : None
 * Attention	  : None
 **********************************************************************************************/
uint32_t THR_map(uint32_t VARIABLE, uint32_t VAR_LOW_VAL, uint32_t VAR_HIGH_VAL, uint32_t MAP_LOW_VAL, uint32_t MAP_HIGH_VAL) {

	uint32_t MAPPED_VALUE = 0;

	MAPPED_VALUE = ((VARIABLE - VAR_LOW_VAL) * (MAP_HIGH_VAL - MAP_LOW_VAL) / VAR_HIGH_VAL) + MAP_LOW_VAL;

	return MAPPED_VALUE;


}
