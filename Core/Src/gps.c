/*
 * gps.c
 *
 *  Created on: Feb 11, 2024
 *      Author: EmreÇANKAYA
 */

#include "gps.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

uint8_t Rxdata[750];
char Txdata[750];
char GPS_Payyload[100];
int Msgindex;
char *ptr;




void GPS_init(void)
{
	 HAL_UART_Receive_DMA(&huart2, (uint8_t*)Rxdata, 700);
}


void GPS_get_location1(void)
{

    if (gps_flag == 1)
    {
    	Msgindex=0;
    			strcpy(Txdata,(char*)(Rxdata));
    			ptr=strstr(Txdata,"GPRMC");
    			if(*ptr=='G')
    			{
    				while(1)
    				{
    					GPS_Payyload[Msgindex]=*ptr;
    					Msgindex++;
    					*ptr=*(ptr+Msgindex);
    					if(*ptr=='\n')
    					{
    						GPS_Payyload[Msgindex]='\0';
    						break;
    					}
    				}
    				sscanf(GPS_Payyload,"GPRMC,%f,A,%f,N,%f,E,%f",&gps1.time,&gps1.Latitude,&gps1.Longitude,&gps1.speed);

    				memcpy(&gps1.speedread, &gps1.speed, sizeof(gps1.speedread));

//    				GPS_Format_data(gps1.time, gps1.Latitude, gps1.Longitude, gps1.speed, gps1.altitude);
    				HAL_Delay(1);
    				gps_flag=0;
    			}
    }
}



void GPS_get_location2(void)
{


	if(gps_flag==1)
		{

			Msgindex=0;
			strcpy(Txdata,(char*)(Rxdata));
			ptr=strstr(Txdata,"GPGGA");
			if(*ptr=='G')
			{
				while(1)
				{
					GPS_Payyload[Msgindex]=*ptr;
					Msgindex++;
					*ptr=*(ptr+Msgindex);
					if(*ptr=='\n')
					{
						GPS_Payyload[Msgindex]='\0';
						break;
					}
				}
				sscanf(GPS_Payyload,"GPGGA,%f,%f,N,%f,E,%f,%f,%f,%f",&gps1.time,&gps1.Latitude,&gps1.Longitude,&gps1.trash,&gps1.trash,&gps1.trash,&gps1.altitude);
//				GPS_Format_data(gps1.time, gps1.Latitude, gps1.Longitude, gps1.speed, gps1.altitude);
				HAL_Delay(1);
				gps_flag=0;
    			}
    }
}

//void GPS_Format_data(float Time, float Lat, float Long, float Speed, float Altitude)
//{
//    char Data[100];
//    gps1.Hours = (int)Time / 10000;
//    gps1.Min = (int)(Time - (gps1.Hours * 10000)) / 100;
//    gps1.Sec = (int)(Time - ((gps1.Hours * 10000) + (gps1.Min * 100)));
//    sprintf(Data, "\r\nTime=%d:%d:%d Lat=%f,Long=%f,Speed=%f,Altitude=%f", gps1.Hours + 3, gps1.Min, gps1.Sec, gps1.Latitude, gps1.Longitude, gps1.speed, gps1.altitude,Altitude);
//    HAL_UART_Transmit(&huart2, (uint8_t*)Data, strlen(Data), HAL_MAX_DELAY);
//    HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n\n", 3, HAL_MAX_DELAY);
//}
