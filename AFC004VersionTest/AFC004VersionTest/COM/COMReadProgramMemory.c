/**
 *  @file COMReadProgramMemory.c
 *  @brief This module contains a function to Read program memory.
 *
 *  @date 14Jun2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Description: </b>
 *       - Contains functions to read an entry of program memory of dsPIC.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *       - u32_ReadProgramMemory
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 14Jun2006 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM, PR_CR_004 and PR_CR_017
 *        <tr><td> 17Sep2008 <td>   <center>"</center>     <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 03Nov2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281: PR_CR_246,
 *        <tr><td> 19Feb2009 <td>  <center> 1.2 </center>   <td> <center>KN</center> <td> ADHR343
 *        <tr><td> 27Jan2019 <td>  <center> 2.0 </center>   <td> <center>BA</center> <td> Changed to use __dsPIC30F__ #ifdef
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMReadProgramMemory.c 6187 2009-02-19 22:21:09Z karthikn $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008-2019.  Archangel Systems, Inc. </i> <BR>
 */

#include "COMReadProgramMemory.h"
#include "COMDefines.h"
//#include "COMEEPROM.h"

/**
 * @brief This function reads a single 32-bit value from Program memory
 *
 * @par <b> Detailed Description: </b>
 * When used in a dsPIC, calls low-level table functions to read the contents of flash memory.
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.7.003.D01 \n
 *
 * @param [in] u32Address  address in program memory
 */

/*---------------------------------------------------------------------------*\
Function Name: u32_ReadProgramMemory

Returns      : The 32-bit value stored at address W1:W0.  The Upper 8 bits
               should be ignored since Program memory is only 24-bits wide.
               The Upper 8 bits will always be read as zero.

Purpose      : This function reads a single 32-bit value from Program memory

Author       : Stephen Hallacy

Date         : 11Jul06

Description  : When used in a dsPIC, calls low-level table functions to
               read the contents of flash memory.
\*---------------------------------------------------------------------------*/
u32 u32_ReadProgramMemory ( u32 u32Address ) /* address in program memory */
{
#   ifdef __dsPIC30F__
   u32_val u32Value ; /* contents of program memory location */

   u32Value.word.LW = u16_ReadNonVolatileLowWord ( u32Address ) ;
   u32Value.word.HW = u16_ReadNonVolatileHighWord ( u32Address ) ;

   return u32Value.Val ;
   /** @return The 32-bit value stored at address W1:W0.
             The Upper 8 bits should be ignored since Program memory is only 24-bits wide.
             The Upper 8 bits will always be read as zero. */
#   else
   return *( u32* ) u32Address ;
#   endif

}
