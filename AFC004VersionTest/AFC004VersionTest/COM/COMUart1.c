/*
 * Filename: COMUart1.c
 * 
 * Author: Henry Gilbert
 * 
 * Date: 8 April 2022 
 * 
 * Description: Module used to implement the UART1 peripheral. Requires
 *      transmit and receive circular buffers to be allocated before
 *      calling the initialize function. All calculations are performed
 *      through the file level circular buffer pointers. 
 * 
 * All rights reserved. Copyright 2022. Archangel Systems Inc.
 */


/**************  Included File(s) **************************/
#include "COMUART1.h"


/**************  Local Variable(s) *************************/
static const uint16_t RX_PRIORITY_MASK = 0x07;
static const uint16_t TX_PRIORITY_MASK = 0x70;
static circBuffer_t* U1RxCBuff;
static circBuffer_t* U1TxCBuff;


/**************  Function Definition(s) ********************/

/* Function: UART1_Initialize
 *
 * Description: Initializes the UART1 peripheral with input parameters. Declares
 *              the UART's Tx and Rx pins. Links the input circular buffer to the
 *              local static circular buffer. Sets the receive and transmit     
 *              interrupt priority. Configures the baud rate, mode, and status
 *              registers. Enables the receive and transmit interrupt. 
 * 
 * Return: None 
 * 
 * Requirement Implemented: INT1.0102.S.IOP.2.001 
 */
void UART1_Initialize( const uint16_t interruptConfig, /* Interrupt Configuration */
                       const uint16_t baudRate, /* UART1 Baud Rate Configuration data. */
                       const uint16_t modeConfig, /* UART1 Mode Configuration data. */
                       const uint16_t statusConfig, /* UART1 Status Configuration data. */
                       circBuffer_t * const Uart1RxCircBuff, /* Pointer to UART1 circular rx buffer */
                       circBuffer_t * const Uart1TxCircBuff ) /* Pointer to UART1 circular tx buffer */
{
    if ((NULL == Uart1RxCircBuff) ||
            (NULL == Uart1TxCircBuff))
    {
        return;
    }

    /* UART1 Tx pin digital output. */
    TRISFbits.TRISF3 = 0;

    /* UART1 Rx pin digital input. */
    TRISFbits.TRISF2 = 1;

    /* Link the UART receive and transmit circular buffers to the module 
     * level circular buffer pointers */
    U1RxCBuff = Uart1RxCircBuff;
    U1TxCBuff = Uart1TxCircBuff;
    cb_reset( U1RxCBuff );
    cb_reset( U1TxCBuff );

    /* Clear the Interrupt Transmit and Receive interrupt flags. */
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;

    /* Set the priority of transmit and receive interrupt module. */
    IPC2bits.U1RXIP = (RX_PRIORITY_MASK & interruptConfig);
    IPC2bits.U1TXIP = (TX_PRIORITY_MASK & interruptConfig) >> 4u;

    /* Configure baud rate, mode config, and status config */
    U1BRG = baudRate;
    U1MODE = modeConfig;
    U1STA = statusConfig;

    /* Configure UART1 control register, Interrupt flag bit is 
     * set when receive buffer has 4 data characters  */
    U1STAbits.URXISEL = 3;

    /* UART transmit and receive enable/ disable interrupt bit. */
    IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 1;
    return;
}

/* Function: UART1_ReadToRxCircBuff
 *
 * Description: Manually trips the UART1 receive interrupt flag. This 
 *      flushes out any remaining bytes stored in the receive FIFO.
 *
 * Return: None 
 * 
 * Requirement Implemented: INT1.0102.S.IOP.2.002
 */
void UART1_ReadToRxCircBuff( void )
{
    if ((U1RxCBuff->head > U1RxCBuff->capacity) ||
            (U1RxCBuff->tail > U1RxCBuff->capacity))
    {
        /* Error! Unexpected buffer parameters */
        cb_reset( U1RxCBuff );
    }
    else
    {
        IFS0bits.U1RXIF = 1; // Manually trip interrupt flag 
    }
    return;
}

/* Function: UART1_RxInterrupt
 *
 * Description: While the UART1 rx buffer is set, push the data to the 
 *          receive circular buffer. After the data is finished storing 
 *          to the rx circ buffer, clear the interrupt and oveflow flags. 
 *
 * Return:  None (ISR)
 * 
 * Requirement Implemented: INT1.0102.S.IOP.2.003
 */
void UART1_RxInterrupt( void )
{
    uint8_t buffData;
    while (1 == U1STAbits.URXDA)
    {
        buffData = U1RXREG;
        cb_push( U1RxCBuff, buffData );
    }
    /* Clear the Interrupt and overflow flags */
    IFS0bits.U1RXIF = 0;
    U1STAbits.OERR = 0;
    return;
}

/* Function: UART1_TxStart
 *
 * Description: Manually trips the UART1 Tx interrupt flag. Used to control
 *      when the transmit circular buffer begins sending data. 
 *
 * Return: None (void)
 * 
 * Requirement Implemented: INT1.0102.S.IOP.2.004
 */
void UART1_TxStart( void )
{
    if (1 != IEC0bits.U1TXIE)
    {
        IEC0bits.U1TXIE = 1; // Enable the transmit interrupt
    }
    return;
}

/* Function: UART1_TxInterrupt
 *
 * Description: ISR for UART1 Transmit. Checks if the transmit circular 
 *      buffer's tail equals the head. If so, disable the interrupt and exit.
 *      Otherwise, clear the interrupt flag. While the transmit buffer is 
 *      empty and the tail does not equal the head, pop the tx circular 
 *      buffer and write the popped value to the UART1 Transmit register. 
 *
 * Return: None (ISR)
 * 
 * Requirement Implemented: INT1.0102.S.IOP.2.005
 */
void UART1_TxInterrupt( void )
{
    if (U1TxCBuff->tail == U1TxCBuff->head)
    {
        IEC0bits.U1TXIE = 0; // Disable interrupts
    }
    else
    {
        IFS0bits.U1TXIF = 0; // Clear interrupt flag 

        /* While transmit buffer is not full AND the tail does not equal the head, transmit. */
        while ((0 == U1STAbits.UTXBF) &&
                (U1TxCBuff->tail != U1TxCBuff->head))
        {
            U1TXREG = cb_pop( U1TxCBuff );
        }
    }
    return;
}

/* End COMUart1.c source file */
