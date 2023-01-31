/** @file COMdsPICunusedISRs.h
 *  @brief This module implements interrupt service routines for the interrupts that are not used.
 *
 *  @par <b> Description: </b>
 *     - This module implements interrupt service routines for the interrupts that are not used.
 *
 *  @date 22Nov2006
 *  @author Vamshi Gangumalla
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 22Nov2006 <td> <center>Draft</center>   <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 21Feb2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR127
 *        <tr><td> 27Mar2008 <td>   <center>"</center>     <td> <center>JD</center> <td> ADHR111
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *  </table>
 *  <BR>
 *  @note $Id: COMdsPICunusedISRs.h 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006.  Archangel Systems, Inc. </i> <BR>
 */

/* Conditional Include of the header file. */
#ifndef COMDSPICUNUSEDISRS_H
   #define COMDSPICUNUSEDISRS_H

/*********************   Constant variables assignment header file.***********************/
#include "p30F6014A.h"
   #include "COMDefines.h"
   #include "COMtypedefs.h"

/* Label prototypes for the Interrupt Service Routines defined in the dsPIC30 compiler. */
   /**
    * This value represents an Interrupt Service Routines for Oscillator fail.
    */
   #define v_OscillatorFail _ISR _OscillatorFail
   /**
    * This value represents an Interrupt Service Routines for Address error.
    */
   #define v_AddressError   _ISR _AddressError
   /**
    * This value represents an Interrupt Service Routines for Stack Error.
    */
   #define v_StackError     _ISR _StackError

   void v_OscillatorFail ( void ) ;
   void v_AddressError ( void ) ;
   void v_StackError ( void ) ;


#endif
/*   End of COMdsPICunusedISRs.h header file. */

