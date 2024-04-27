/*
 * THERMALCONTROL.c
 *
 *  Created on: Mar 19, 2024
 *      Author: erenegdemir
 */

#include "adc.h"
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "math.h"


/**********************************************************************************************
 * Function Name  : void TMA_get_temparature(uint32_t ADC_VALUE)
 * Description    : calculates temperature value
 * Input          : None
 * Output         : Pot variables
 * Return         : None
 * Attention	  : None
 **********************************************************************************************/
float TMA_calc_temperature(uint32_t ADC_VALUE)
{

    float VERIABLE_1 = -16.41683476;
	float VERIABLE_2 = 33.80584618;
	float VERIABLE_3 = -147.7124671;


	static float R = 0.0;
	static float VOLTAGE = 0.0;
	static float TEMP;


	VOLTAGE = (ADC_VALUE * 3.3) / 4095;

	R = (33000 / VOLTAGE) - 10000;

	TEMP = VERIABLE_1 + VERIABLE_2*(log(R)) + (VERIABLE_3*log(R)*log(R)*log(R));
	TEMP = 1 / TEMP;
	TEMP = TEMP - 273.15;

	return TEMP;



}

/**********************************************************************************************
 * Function Name  : void TMA_cooling_automation(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, float TEMPERATURE, uint32_t HIGH_THRESHOLD, uint32_t TOLERANCE, _Bool TOGGLE)
 * Description    : cooling automation
 * Input          : float TEMPERATURE, uint32_t THRESHOLD, uint32_t TOLERANCE, _Bool TOGGLE
 * Output         : None
 * Return         : None
 * Attention	  : None
 **********************************************************************************************/
void TMA_cooling_automation(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, float TEMPERATURE, uint32_t HIGH_THRESHOLD, uint32_t TOLERANCE, _Bool TOGGLE)
{
	uint32_t LOW_THRESHOLD = 0;

	LOW_THRESHOLD = HIGH_THRESHOLD - TOLERANCE;

	if(TOGGLE == 1){

		if(TEMPERATURE > HIGH_THRESHOLD){
			HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

		}
		else if(TEMPERATURE < LOW_THRESHOLD){
			HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
		}
	}
	else{
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	}
}

/**********************************************************************************************
 * Function Name  : float temp_select(float TEMP_1, float TEMP_2)
 * Description    : selected upper value of variables
 * Input          : float TEMPERATURE, uint32_t THRESHOLD, uint32_t TOLERANCE, _Bool TOGGLE
 * Output         : None
 * Return         : None
 * Attention	  : None
 **********************************************************************************************/
float temp_select(float TEMP_1, float TEMP_2)
{
	float TEMP_FINAL = 0;
	if(TEMP_1 > TEMP_2) TEMP_FINAL = TEMP_1;
	else TEMP_FINAL = TEMP_2;

	return TEMP_FINAL;

}


/**********************************************************************************************
 * Function Name  : static void TMA_Drive_Multiplexer(uint8_t PIN)
 * Description    : Driver for 16 pin 4 bit Multiplexer
 * Input          : uint8_t PIN
 * Output         : None
 * Return         : None
 * Attention	  : None
 **********************************************************************************************/
static void TMA_Drive_Multiplexer(uint8_t PIN)
{
	uint8_t BIN_NUM_REV[8];
	uint8_t BIN_NUM[8];
	uint8_t i = 0;
	uint8_t n = 0;
	uint8_t j = 0;

	while(n > 0) {

		BIN_NUM_REV[i] = PIN % 2;
	    n = n / 2;
	    i++;
    }

	for(j = i - 1; j >=0; j--){
		BIN_NUM[n] = BIN_NUM_REV[j];
		n++;
	}

	if(BIN_NUM[0] == 1){
		HAL_GPIO_WritePin(MPX_1_GPIO_Port, MPX_1_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(MPX_1_GPIO_Port, MPX_1_Pin, GPIO_PIN_RESET);
	}
	if(BIN_NUM[1] == 1){
		HAL_GPIO_WritePin(MPX_1_GPIO_Port, MPX_1_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(MPX_1_GPIO_Port, MPX_1_Pin, GPIO_PIN_RESET);
	}
	if(BIN_NUM[2] == 1){
		HAL_GPIO_WritePin(MPX_1_GPIO_Port, MPX_1_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(MPX_1_GPIO_Port, MPX_1_Pin, GPIO_PIN_RESET);
	}
	if(BIN_NUM[3] == 1){
		HAL_GPIO_WritePin(MPX_1_GPIO_Port, MPX_1_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(MPX_1_GPIO_Port, MPX_1_Pin, GPIO_PIN_RESET);
	}

}


