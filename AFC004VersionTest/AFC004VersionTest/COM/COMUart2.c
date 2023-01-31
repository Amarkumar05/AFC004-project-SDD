/*
 * Filename: COMUart2.c
 * 
 * Author: Henry Gilbert
 * 
 * Date: 8 April 2022 
 * 
 * Description:  *    COMUart2 module contains function calls necessary to initialize the UART2 peripheral, 
 *    send and receive serial data, and the interrupt implementation. Static file variables
 *    hold the transmit and receive circular buffers. These variables are local to the file 
 *    module itself. 
 * 
 * All rights reserved. Copyright 2022. Archangel Systems Inc.
 */
#include "COMUART2.h"

static const uint16_t RX_PRIORITY_MASK = 0x07;
static const uint16_t TX_PRIORITY_MASK = 0x70;

/* Local Variables */
static circBuffer_t* U2RxCBuff;
static circBuffer_t* U2TxCBuff;

/* Function: UART2_Initialize
 * 
 * Description: 
 *      Runs a check on the input parameters, and exits the function if the parameters are NULL.
 *      Declares the data direction of the TX and RX UART Pins. Links the static circular buffers to the 
 *      input pointers. Clears the interrupt transmit and receive flags, sets interrupt priority,
 *      sets the UART baud rate, configures mode of operation, configures the status register, 
 *      and enables the interrupt bit. 
 * 
 * Return: None (void)
 * 
 * Requirement Implemented: 
 **/
void UART2_Initialize( uint16_t interruptConfig,
                       uint16_t baudRate,
                       uint16_t modeConfig,
                       uint16_t statusConfig,
                       circBuffer_t * uart2RxCircBuff,
                       circBuffer_t * uart2TxCircBuff )
{
    /* UART2 Tx pin digital output */
    TRISFbits.TRISF5 = 0;

    /* UART2 Rx pin digital input */
    TRISFbits.TRISF4 = 1;

    /* Link the UART receive and transmit circular buffers to the local variables */
    U2RxCBuff = uart2RxCircBuff;
    U2TxCBuff = uart2TxCircBuff;
    cb_reset( U2RxCBuff );
    cb_reset( U2TxCBuff );

    /* Clear the Interrupt Transmit and Receive interrupt flags. */
    IFS1bits.U2RXIF = 0;
    IFS1bits.U2TXIF = 0;

    /* Set the priority of transmit and receive interrupt module. */
    IPC6bits.U2RXIP = (RX_PRIORITY_MASK & interruptConfig);
    IPC6bits.U2TXIP = (TX_PRIORITY_MASK & interruptConfig) >> 4u;

    /* Configure baud rate, mode config, and status config */
    U2BRG = baudRate;
    U2MODE = modeConfig;
    U2STA = statusConfig;

    /* Configure UART2 control register, Interrupt flag bit is set when receive buffer has 4 data characters  */
    U2STAbits.URXISEL = 3;

    /* UART transmit and receive enable/ disable interrupt bit. */
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 1;
    return;
}

/* Function: UART2_ReadToRxCircBuff
 * 
 * Description:
 *      Checks the init status of UART2. Checks the circular buffer params are correct.
 *      If both checks pass, manually trip the interrupt flag to start the receive ISR.
 * 
 * Return: None (void)
 *
 * Requirement(s) Implemented: INT1.0102.S.IOP.5.002 
 **/
void UART2_ReadToRxCircBuff( void )
{
    if ((U2RxCBuff->head > U2RxCBuff->capacity) ||
            (U2RxCBuff->tail > U2RxCBuff->capacity))
    {
        /* Error! Unexpected buffer parameters */
        cb_reset( U2RxCBuff );
    }
    else
    {
        IFS1bits.U2RXIF = 1; // Manually trip interrupt flag 
    }
    return;
}

/* Function: UART2_RxInterrupt
 * 
 * Description:
 *      While the UART2 status receive data available flag is set, push the UART2
 *      hardware buffer data onto the receive circular buffer. 
 * 
 * Return: None (void)
 *
 * Requirement(s) Implemented: INT1.0102.S.IOP.5.003 
 **/
void UART2_RxInterrupt( void )
{
    uint8_t buffData;
    /* While the receive buffer data available bit is set, push data to the circular buffer */
    while (1 == U2STAbits.URXDA)
    {
        buffData = U2RXREG;
        cb_push( U2RxCBuff, buffData );
    }
    /* Clear the Interrupt and overflow flags */
    IFS1bits.U2RXIF = 0;
    U2STAbits.OERR = 0;
    return;
}

/* Function: UART2_TxStart
 * 
 * Description: 
 *      Called manually to start UART transmission. This function assumes that the transmit 
 *      buffer has been loaded accordingly before calling. 
 * 
 * Return: None (void)
 *
 * Requirement(s) Implemented: INT1.0102.S.IOP.5.004
 **/
void UART2_TxStart( void )
{
    if (1 != IEC1bits.U2TXIE)
    {
        IEC1bits.U2TXIE = 1; // Enable the transmit interrupt
    }
    return;
}

/* Function: UART2_TxInterrupt
 * 
 * Description: 
 *      Transmit ISR used when writing to the UART2 transmit line. If the tail is greater than the 
 *      head, disable interrupts. Otherwise, clear the interrupt flag, and while the transmit buffer is 
 *      not full, pop data from the transmit circular buffer to write to the transmit line. If the tail
 *      equals the head, ie, the tx buffer is empty, exit the function. 
 * 
 * Return: None (void)
 *
 * Requirement(s) Implemented: INT1.0102.S.IOP.5.005
 **/
void UART2_TxInterrupt( void )
{
    if (U2TxCBuff->tail == U2TxCBuff->head)
    {
        IEC1bits.U2TXIE = 0; // Disable UART2 transmit interrupt 
    }
    else
    {
        IFS1bits.U2TXIF = 0; // Clear interrupt flag 

        /* While transmit buffer is not full AND the tail does not equal the head, transmit. */
        while ((0 == U2STAbits.UTXBF) &&
                (U2TxCBuff->tail != U2TxCBuff->head))
        {
            U2TXREG = cb_pop( U2TxCBuff );
        }
    }
    return;
}
