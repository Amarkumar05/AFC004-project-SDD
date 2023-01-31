/*
 * Filename: COMUart1.h
 * 
 * Author: Henry Gilbert
 * 
 * Date: 8 April 2022 
 * 
 * Description: Module used to declare the UART1 peripheral's function and 
 *          interrupt declarations.
 * 
 * All rights reserved. Copyright 2022. Archangel Systems Inc.
 */

#ifndef COMUART1_H
#define COMUART1_H

/**************  Include Files  ************************/
#include "CircularBuffer.h"
#include <stdint.h> 
#include "../COM/pic_h/p30F6014A.h"

/* Interrupt Service routine linking to interrupt vector */
#define UART1_RxInterrupt __attribute__ ((interrupt,no_auto_psv)) _U1RXInterrupt
#define UART1_TxInterrupt __attribute__ ((interrupt,no_auto_psv)) _U1TXInterrupt

/* UART1 Transmit Interrupt Routine */
void UART1_TxInterrupt(void);

/* UART1 Receive Interrupt Routine */
void UART1_RxInterrupt(void);

/* UART1 Initialize Routine */
void UART1_Initialize(const uint16_t interruptConfig, /* Interrupt Configuration */
        const uint16_t baudRate, /* UART1 Baud Rate Configuration data. */
        const uint16_t modeConfig, /* UART1 Mode Configuration data. */
        const uint16_t statusConfig, /* UART1 Status Configuration data. */
        circBuffer_t * const Uart1RxCircBuff, /* Pointer to UART1 circular rx buffer */
        circBuffer_t * const Uart1TxCircBuff); /* Pointer to UART1 circular tx buffer */

/* UART1 Read data to receive circular buffer */
void UART1_ReadToRxCircBuff(void);

/* UART1 Start Transmission*/
void UART1_TxStart(void);

#endif

/* End COMUart1.h header file */
