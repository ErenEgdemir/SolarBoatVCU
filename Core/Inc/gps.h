/*
 * gps.h
 *
 *  Created on: Feb 11, 2024
 *      Author: EmreÇANKAYA
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include"main.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct gps {
	float speedread;
    float time;
    float Latitude;
    float Longitude;
    float speed;
    float altitude;
    float trash;
    int Hours;
    int Min;
    int Sec;
};
extern struct gps gps1;

extern uint8_t Rxdata[750];
extern char Txdata[750];
extern char GPS_Payyload[100];
extern int Msgindex;
extern char *ptr;

extern uint8_t gps_flag;

void GPS_init(void);


void GPS_get_location1(void);
void GPS_get_location2(void);

void GPS_format_data(float Time, float Lat, float Long, float Speed, float Altitude);





#endif /* INC_GPS_H_ */
