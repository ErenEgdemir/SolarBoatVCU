/*
 * RANGE.c
 *
 *  Created on: Mar 20, 2024
 *      Author: erenegdemir
 */

#include "RANGE.h"

void R_initCircularBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->count = 0;
}

void R_addCurrentReading(CircularBuffer *cb, float currentValue) {
    cb->buffer[cb->head] = currentValue;
    cb->head = (cb->head + 1) % BUFFER_SIZE;

    if (cb->count < BUFFER_SIZE) {
        cb->count++;
    }

}

float R_calculateAverage(CircularBuffer *cb) {
    float sum = 0.0;
    int i;
    for (i = 0; i < cb->count; i++) {
        sum += cb->buffer[i];
    }
    return sum / cb->count;
}
