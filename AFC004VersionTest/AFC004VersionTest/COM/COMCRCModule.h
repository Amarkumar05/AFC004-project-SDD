/** @file COMCRCModule.h
 *  @brief This file implements the 32 bit CRC Validation Module.
 *
 *  @par <b> Description: </b>
 *     - Contains function declarations for COMBoundsCheckData.c
 *
 *  @date 18May2006
 *  @author Vamshi Gangumalla
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 01Aug2006 <td> <center>Draft</center>   <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 10Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM PR_CR_017
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 20Nov2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *  </table>
 *  <BR>
 *  @note $Id: COMCRCModule.h 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006.  Archangel Systems, Inc. </i> <BR>
 */

/* Conditional Compile for including the Header file. */
#ifndef   COMCRCMODULE_H
   #define COMCRCMODULE_H

/*********************   Data Type Alias assignment header file. ***********************/
   #include "COMtypedefs.h"/*   System data type declaring library. */

   #include "COMDefines.h" /* Common define header file. */

/* Label for the Most Significant Bit of a 32 bit number. */
   /**
    * This value represents a Most significant bit of a 32 bit number.
    */
   #define MS_BIT 0x80000000

/*********************   Function Prototype declaration. *********************************/
/* This function generates the CRC look up table. */
   void v_Generate32BitCRCTable ( u32 u32CRCPolynomialKey ) ;

/* This function calculates the CRC remainder. */
   u32 u32_Calculate32BitCRC (
      u8 *u8paCRCCalculationMessage , /* CRC calculation Message. */
      u16 u16StartPositionOfCRC ,  /* Start Index position of CRC calculation Message. */
      u16 u16StopPositionOfCRC ,   /* End Index position of CRC calculation Message. */
      u32 u32InitilizeCRCRemainder ) ; /* CRC remainder to be initialized in the function. */

/* Message Header and CRC verification function. **/
   void v_LoadMessageHeaderAndCRCResult (
      u8 *u8paCRCCalculationMessage ,     /* Pointer to the Message */
      u16 u16LengthOfCRCMessageMinusOne , /* Length of the Message buffer. */
      u8  u8HeaderByte ,                  /* The Message Header Byte, ie. 0xFF   */
      u16 u16HeaderSize ) ;               /* Size of Message Header        */

/* This function verifies the CRC of communication message. */
   u16 u16_VerifyCRCofTheMessage (
      u8 *u8paCRCCalculationMessage ,       /* Pointer to the Message. */
      u16 u16LengthOfCRCMessageMinusOne ) ; /* Length of the Message buffer. */

#endif
/* End of COMCRCModule.h Module. */


