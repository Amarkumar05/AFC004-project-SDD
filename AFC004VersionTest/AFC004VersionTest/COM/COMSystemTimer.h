/** @file COMSystemTimer.h
 *  @brief This file implements the system frequency interrupt.
 *
 *  @par <b> Description: </b>
 *     - This function initializes the Interrupt timer.
 *     - This function services the Interrupt service routine.
 *     - This function returns the  system frequency flag.
 *     - This function resets the system frequency flag.
 *
 *  @date 18May2006
 *  @author Vamshi Gangumalla
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 01Jun2006 <td> <center>Draft</center>   <td> <center>VM</center> <td> Initial Draft
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 20Nov2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMSystemTimer.h 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006.  Archangel Systems, Inc. </i> <BR>
 */

/**************  Include Files  ************************/
#ifndef COMSYSTEMTIMER_H
#define COMSYSTEMTIMER_H

/*********************   Data Type Alias assignment header file. ***********************/
#include "COMtypedefs.h"       /* Include System data type declaring library. */
#include "../COM/pic_h/p30F6014A.h"
#include "COMDefines.h"     /* Include Common definitions module. */

/* Timer 4 Interrupt Service Routine. */
/**
 * This macro denotes a Timer 4 Interrupt Service Routine.
 */
#define v_T4Interrupt __attribute__ ((interrupt,no_auto_psv)) _T4Interrupt

void v_T4Interrupt(void);

/*********************   Function Prototype declaration. *********************************/
void v_InitializeTMR4(/*   TIMER4 Initialization function. */
        u16 u16TMR4Config, /*   TIMER4 Port configuration register. */
        u16 u16TMR4Period, /*   TIMER4 Period configuration register. */
        u16 u16TMR4Interrupt); /*   TIMER4 Interrupt configuration register. */

/* Function to read the status of frequency flag. */
u16 u16_ReadSystemFrequencyFlag(void);

/* This function resets the system frequency flag. */
void v_ResetSystemFrequencyFlag(void);

#endif
/* End of COMSPI1.h Module. */


