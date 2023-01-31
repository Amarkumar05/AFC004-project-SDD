/*
 * Filename:  CircularBuffer.h
 * 
 * Author: Henry Gilbert
 * 
 * Data: 8 April 2022 
 * 
 * Description: Module to implement circular buffer objects, 8 bits and 32 bits. 
 * 
 * All rights reserved. Copyright 2022. Archangel Systems Inc.
 */

#ifndef CIRCULAR_BUFF_H
#define CIRCULAR_BUFF_H

/**************  Included File(s) **************************/
#include <stddef.h>
#include <stdint.h>

/**************  Type Definition(s) ************************/
typedef struct circBuffer_t {
    uint8_t* data; /* Pointer to data*/
    const size_t capacity; /* Circular buffer capacity */
    size_t tail; /* Read pointer */
    size_t head; /* Write pointer */
} circBuffer_t;


/**************  Function Definition(s) ********************/
/* Pushes data to a circ buffer */
void cb_push(circBuffer_t* cb, /* Pointer to circular buffer struct */
        const uint8_t data); /* Data to push */

/* Pops data and returns from circ buffer */
uint8_t cb_pop(circBuffer_t * const cb); /* Pointer to circular buffer struct */

/* Circular buffer reset */
void cb_reset(circBuffer_t * const cb); /* Pointer to circular buffer struct */

/* Peeks at nth index of circ buffer */
uint8_t cb_peek(const circBuffer_t * const cb, /* Pointer to circular buffer struct */
        const size_t offset); /* Offset value */

/* Calculates bytes used in circ buffer. */
size_t cb_bytesUsed(const circBuffer_t * const cb); /* Pointer to circular buffer struct */

/* Advances circular buffer tail by n spaces*/
void cb_advanceTail(circBuffer_t * const cb, /* Pointer to circular buffer struct */
        const size_t num);

/* Flushes a source array into a circular buffer */
size_t cb_flushIn(circBuffer_t * const cb, /* Pointer to circular buffer struct */
        uint8_t * const srcBuff, /* Buffer to read data from */
        const size_t numBytesToFlush);

/* Flushes a circular buffer to a source array */
size_t cb_flushOut(circBuffer_t * const cb, /* Pointer to circular buffer struct */
        uint8_t * const destBuff, /* Buffer to store data to */
        const size_t numBytesToFlush);

#endif 
/* End circularBuffer.h header file */
