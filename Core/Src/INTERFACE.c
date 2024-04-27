/*********************************************************************************************************
 *
 *       File: Interface.h
 *    Purpose: E Paper Display Interfacing Handling
 * Created on: Mar 6, 2024
 *     Author: Eren Egdemir
 *       Team: TU YILDIZ SOLAR BOAT TEAM ELECTRONICS AND COMMUNICATIONS DEPARTMENT
 *
 *********************************************************************************************************/


#include "interface.h"
#include "display.h"
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "freertos.h"



void interface_init(void)
{

}

void interface_page1(void)
{
//	interface_write_logo(0, 0);
//
//	interface_write_power(300, 20, POWER.CN_CURRENT);
//
//	interface_write_speed(300, 200, GPS.KNT_SPEED);
//
//	interface_write_hAngle(300, 400, HYDROFOIL.H_ANGLE);
//
//	interface_write_remaningTime(50, 200, POWER.R_TIME);
//
//	interface_write_mtrTmp(50, 400, TEMP.TEMP_MOTOR);
//
//	interface_write_escTmp(550, 400, TEMP.TEMP_ESC);

//	interface_write_erors(550, 20, EROR);

}

void interface_page2(void)
{
	interface_write_logo(0, 0);

	interface_write_temps(0, 0);

	display_update();

}


void interface_write_logo(int X0, int Y0)
{
	display_bitmap("XYZ.BMP", X0, Y0);
}

//First Page Functions
void interface_write_speed(int X0, int Y0, uint32_t SPEED)
{
	char str[20];

			sprintf(str, "%ld", SPEED);
			display_set_en_font(ASCII48);
			display_string("SPEED", X0, Y0);

			display_set_en_font(ASCII32);
			display_string("nmi", X0  , Y0 + 43);

			display_set_en_font(ASCII64);
		    display_string(str,  X0  , Y0 + 68);

		    display_update();
}

void interface_write_power(int X0, int Y0, uint32_t POWER)
{
	char str[20];

		sprintf(str, "%ld", POWER);
		display_set_en_font(ASCII48);
		display_string("POWER", X0, Y0);

		display_set_en_font(ASCII32);
		display_string("kWh", X0  , Y0 + 43);

		display_set_en_font(ASCII64);
	    display_string(str,  X0  , Y0 + 69);

		display_update();
}

void interface_write_remainingPower(int X0, int Y0, uint32_t R_POWER)
{
	char str[20];

			sprintf(str, "%ld", R_POWER);
			display_set_en_font(ASCII48);
			display_string("R_POWER", X0, Y0);

			display_set_en_font(ASCII32);
			display_string("kWh", X0  , Y0 + 43);

			display_set_en_font(ASCII64);
		    display_string(str,  X0  , Y0 + 68);

			display_update();

}

void interface_write_remaningTime(int X0, int Y0, uint32_t R_TIME)
{
	char str[20];

			sprintf(str, "%ld", R_TIME);
			display_set_en_font(ASCII48);
			display_string("R TIME", X0, Y0);

			display_set_en_font(ASCII32);
			display_string("dk", X0  , Y0 + 43);

			display_set_en_font(ASCII64);
		    display_string(str,  X0  , Y0 + 68);

			display_update();
}


void interface_write_mtrTmp(int X0, int Y0, float MTR_TMP)
{
	char str[20];

				sprintf(str, "%f", MTR_TMP);
				display_set_en_font(ASCII48);
				display_string("MTR TMP", X0, Y0);

				display_set_en_font(ASCII32);
				display_string("C", X0  , Y0 + 43);

				display_set_en_font(ASCII64);
			    display_string(str,  X0  , Y0 + 68);

				display_update();



}

void interface_write_escTmp(int X0, int Y0, float ESC_TMP)
{
	char str[20];

					sprintf(str, "%f", ESC_TMP);
					display_set_en_font(ASCII48);
					display_string("ESC TMP", X0, Y0);

					display_set_en_font(ASCII32);
					display_string("C", X0  , Y0 + 43);

					display_set_en_font(ASCII64);
				    display_string(str,  X0  , Y0 + 68);

					display_update();

}

void interface_write_wCoolingStatus(int X0, int Y0, uint32_t W_COOLING_STATUS)
{

	char str[20];

						sprintf(str, "%ld", W_COOLING_STATUS);
						display_set_en_font(ASCII48);
						display_string("W COOLING STATUS", X0, Y0);

						display_set_en_font(ASCII32);
						display_string("°C", X0  , Y0 + 43);

						display_set_en_font(ASCII64);
					    display_string(str,  X0  , Y0 + 68);

						display_update();




}

void interface_write_hAngle(int X0, int Y0, uint32_t H_ANGLE)
{
	char str[20];

							sprintf(str, "%ld", H_ANGLE);
							display_set_en_font(ASCII48);
							display_string("H ANGLE", X0, Y0);


							display_set_en_font(ASCII64);
						    display_string(str,  X0  , Y0 + 68);

							display_update();


}

void interface_write_erors(int X0, int Y0, uint32_t ERORS)
{
	char str[20];

								sprintf(str, "%ld", ERORS);

								display_set_en_font(ASCII48);
								display_string("ERORS", X0, Y0);

								display_set_en_font(ASCII64);
							    display_string(str,  X0  , Y0 + 48);

								display_set_en_font(ASCII64);
							    display_string(str,  X0  , Y0 + 48 + 64);

								display_set_en_font(ASCII64);
							    display_string(str,  X0  , Y0 + 48 + 64 + 64);

								display_set_en_font(ASCII64);
							    display_string(str,  X0  , Y0 + 48 + 64 + 64 + 64);

								display_set_en_font(ASCII64);
							    display_string(str,  X0  , Y0 + 48 + 64 + 64 + 64 + 64);
								display_update();
}

//Second Page Functions
void interface_write_temps(int X0, int Y0)
{
//	char TEMP_BUFF[10];
//
//
//
//
//	display_set_en_font(ASCII32);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_MPPT1);
//	display_string("TEMP MPPT 1", X0 + 20, Y0 + 128 + 20);
//	display_string(TEMP_BUFF,  X0 + 20, Y0 + 128 + 20 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_MPPT2);
//	display_string("TEMP MPPT 2", X0 + 20, Y0 + 128 + 20 + 32 + 32);
//	display_string(TEMP_BUFF, X0+20, Y0 + 128 + 20 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_MPPT3);
//	display_string("TEMP MPPT 3", X0 + 20, Y0 + 128 + 20 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 20, Y0+ 128 + 20 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_MPPT4);
//	display_string("TEMP MPPT 4", X0 + 20, Y0 + 128 + 20 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0+20, Y0 + 128 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 );
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_MPPT5);
//	display_string("TEMP MPPT 5",X0 + 20, Y0 + 128 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 20, Y0 + 128 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_MPPT6);
//	display_string("TEMP MPPT 6", X0 + 20, Y0 + 128 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0+20, Y0+ 128 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
////	sprintf(TEMP_BUFF, "%.1f", W_TEMP->TEMP_MPPT1);
////	display_string("TEMP C MPPT", X0+300, Y0+20);
////	display_string(str, X0+300, Y0+20+32);
////	memcpy(TEMP_BUFF,'0',4);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_MOTOR);
//	display_string("TEMP MOTOR", X0 + 300, Y0 + 20 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 300, Y0 + 20 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_ESC);
//	display_string("TEMP ESC", X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_CONV_1);
//	display_string("TEMP CONV 1", X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
////	sprintf(TEMP_BUFF, "%.1f", W_TEMP->TEMP_CONV_2);
//	display_string("TEMP CONV 2", X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_MCU);
//	display_string("TEMP MCU", X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
////	sprintf(TEMP_BUFF, "%.1f", W_TEMP->TEMP_MPPT1);
//	display_string("TEMP M TERM", X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
////	sprintf(TEMP_BUFF, "%.1f", W_TEMP->TEMP_MPPT1);
//	display_string("TEMP M CABLE", X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
//	sprintf(TEMP_BUFF, "%.1f", TEMP.TEMP_BAT);
//	display_string("TEMP BAT", X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 300, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
////	sprintf(TEMP_BUFF, "%.1f", TEMP->TEMP_CABIN);
//	display_string("TEMP CABIN", X0 + 20, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	display_string(TEMP_BUFF, X0 + 20, Y0 + 20 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32 + 32);
//	memcpy(TEMP_BUFF,"0",10);
//
////	sprintf(TEMP_BUFF, "%.1f", TEMP->HUM_CABIN);
//	display_string("HUM CABIN", X0 + 560, Y0 + 20);
//	display_string(TEMP_BUFF, X0 + 560, Y0 + 20 + 32);
//	memcpy(TEMP_BUFF,"0",10);
}

void interface_write_coolings(int X0, int Y0, uint32_t COOLINGS)
{

}

void interface_write_powers(int X0, int Y0, uint32_t POWERS)
{

}
