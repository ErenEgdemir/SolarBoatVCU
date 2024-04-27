/*
 * RANGE.h
 *
 *  Created on: Mar 20, 2024
 *      Author: erenegdemir
 */

#ifndef INC_RANGE_H_
#define INC_RANGE_H_


#define BUFFER_SIZE 250

typedef struct {
    float buffer[BUFFER_SIZE]; // Akım değerlerini saklamak için kullanılacak dizi
    int head; // Tampondaki en son elemanın indeksi
    int count; // Tampondaki eleman sayısı
} CircularBuffer;







void R_initCircularBuffer(CircularBuffer *cb);
void R_addCurrentReading(CircularBuffer *cb, float currentValue);
float R_calculateAverage(CircularBuffer *cb);

#endif /* INC_RANGE_H_ */
