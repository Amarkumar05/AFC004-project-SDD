/**
 *  @file COMSystemTimer.c
 *  @brief This file implements the system frequency interrupt.
 *
 *  @date 18May2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Description: </b>
 *       - This function initializes the Interrupt timer.
 *       - This function services the Interrupt service routine.
 *       - This function returns the  system frequency flag.
 *       - This function resets the system frequency flag.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *       - v_InitializeTMR4
 *       - v_T4Interrupt
 *       - u16_ReadSystemFrequencyFlag
 *       - v_ResetSystemFrequencyFlag
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 18May2006 <td> <center>Draft</center>   <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 17Sep2008 <td>   <center>"</center>     <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 02Dec2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMSystemTimer.c 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

/*********************   Data Type Alias assignment header file. ***********************/
   #include "COMSystemTimer.h"

/***********  Global Variable Declarations  ************/
/* The System frequency flag is set in the ISR and cleared in the polling function. */
   static u16 u16SystemFrequencyFlag ; /**< File level variable. */



/**
 * @brief This function initializes the TimerFOUR peripheral to interrupt at System frequency.
 *
 * @par <b> Detailed Description: </b>
 * The interrupt and port config registers are configured in this function.
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.17.001 \n
 *
 * @param [in] u16TMR4Config  TIMER4 Port configuration register.
 * @param [in] u16TMR4Period  TIMER4 Period configuration register.
 * @param [in] u16TMR4Interrupt  TIMER4 Interrupt configuration register.
 */

void v_InitializeTMR4 ( u16 u16TMR4Config ,     /* TIMER4 Port configuration register. */
                        u16 u16TMR4Period ,     /* TIMER4 Period configuration register. */
                        u16 u16TMR4Interrupt ) /* TIMER4 Interrupt configuration register. */
{
 /* Initialize the System Frequency Flag */
   u16SystemFrequencyFlag = ( u16 ) CLEAR ;

/* Clear timer1 register to start counting from Zero. */
   TMR4 = ( u16 ) ZERO ;

/* Set the Period of the interrupt frequency. */
   PR4   =  u16TMR4Period ;

/* Set the pre scale factor and turn on the timer*/
   T4CON =  u16TMR4Config ;

/* Clear the timer interrupt flag. */
   IFS1bits.T4IF = ( u16 ) CLEAR ;

/* Set the priority level of the timer interrupt. */
   IPC5bits.T4IP = ( ( ( u16 ) BITMASK_0x07 ) & u16TMR4Interrupt ) ;

/* Enable the timer interrupt. */
   IEC1bits.T4IE = ( ( ( u16 ) BITMASK_0x08 ) & u16TMR4Interrupt ) >> ( u16 ) SHIFT_3 ;

   return ;/** @return \a None (void) */
}/* End of v_InitializeTMR4 function. */


/**
 * @brief This Interrupt Service Routine Services the TIMER4 peripheral at System Frequency.
 *
 * @par <b> Detailed Description: </b>
 * The interrupt flag is cleared and the System frequency flag is set.
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.17.002 \n
 *
 * @par <b> Parameters: </b> <br>
 *    <i> None </i> (void)
 */

void v_T4Interrupt ( void )
{

/* Clear interrupt flag. */
   IFS1bits.T4IF = ( u16 ) CLEAR ;

/* Assert the 100 Hz interrupt flag. */
   u16SystemFrequencyFlag = ( u16 ) SET ;

   return ;/** @return \a None (void) */
}/* End of v_T4Interrupt Interrupt Service Routine. */

/**
 * @brief This function return the System frequency flag.
 *
 * @par <b> Detailed Description: </b>
 * The system frequency flag is returned from this function.
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.17.003 \n
 *
 * @par <b> Parameters: </b> <br>
 *    <i> None </i> (void)
 */

u16 u16_ReadSystemFrequencyFlag ( void )
{
/* Return from the function.*/
   return ( u16SystemFrequencyFlag ) ;
   /** @return \a u16SystemFrequencyFlag - Returns the  system frequency flag. */

}/* End of u16_ReadSystemFrequencyFlag function. */

/**
 * @brief This function resets the System frequency flag.
 *
 * @par <b> Detailed Description: </b>
 * The system frequency flag is reset in this function.
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.17.003 \n
 *
 * @par <b> Parameters: </b> <br>
 *    <i> None </i> (void)
 */

void v_ResetSystemFrequencyFlag ( void )
{
/* Clear the SPI Received Flag. */
   u16SystemFrequencyFlag = ( u16 ) CLEAR ;

   return ; /** @return \a None (void) */
}/* End of v_ResetSystemFrequencyFlag function. */


/* End of COMSystemTimer.c Module. */

