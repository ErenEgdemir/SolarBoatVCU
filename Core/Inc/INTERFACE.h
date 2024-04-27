/*********************************************************************************************************
 *
 *       File: Interface.h
 *    Purpose: E Paper Display Interfacing Handling
 * Created on: Mar 6, 2024
 *     Author: Eren Egdemir,Mehmet Emre Cankaya(taklacı guvercin)
 *       Team: TU YILDIZ SOLAR BOAT TEAM ELECTRONICS AND COMMUNICATIONS DEPARTMENT
 *
 *********************************************************************************************************/

#ifndef INC_INTERFACE_H_
#define INC_INTERFACE_H_


// includes

#include "interface.h"
#include "display.h"
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include <freertos.h>

//extern struct THR_V;
//extern struct TMA_V;
//extern struct GPS_V;
//extern struct PWR_V;
//extern struct HYD_V;
////
//extern THR_V THROTTLE;
//extern TMA_V TEMP;
//extern GPS_V GPS;
//extern PWR_V POWER;
//extern HYD_V HYDROFOIL;


//Function Prototypes

void interface_init(void);

void interface_page1(void);
void interface_page2(void);

//Initialization Functions

void interface_write_logo(int X0, int Y0);

//First Page Functions
void interface_write_speed(int X0, int Y0, uint32_t SPEED);
void interface_write_power(int X0, int Y0, uint32_t POWER);
void interface_write_remainingPower(int X0, int Y0, uint32_t R_POWER);
void interface_write_remaningTime(int X0, int Y0, uint32_t R_TIME);
void interface_write_range(int X0, int Y0, uint32_t RANGE);
void interface_write_mtrTmp(int X0, int Y0, float MTR_TMP);
void interface_write_escTmp(int X0, int Y0, float ESC_TMP);
void interface_write_wCoolingStatus(int X0, int Y0, uint32_t W_COOLING_STATUS);
void interface_write_hAngle(int X0, int Y0, uint32_t H_ANGLE);
void interface_write_erors(int X0, int Y0, uint32_t ERORS);

//Second Page Functions
void interface_write_temps(int X0, int Y0);
void interface_write_coolings(int X0, int Y0, uint32_t COOLINGS);
void interface_write_powers(int X0, int Y0, uint32_t POWERS);











#endif /* INC_INTERFACE_H_ */
