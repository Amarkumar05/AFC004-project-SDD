/** @file COMReadProgramMemory.h
 *  @brief This module contains a function to Read program memory.
 *
 *  @par <b> Description: </b>
 *     - Contains functions to read an entry of program memory of dsPIC.
 *
 *  @date 08Jun2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 08Jun2006 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM, PR_CR_032 and PR_CR_012
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 02Dec2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *        <tr><td> 27Jan2019 <td>  <center> 2.0 </center>   <td> <center>BA</center> <td> Changed to use __dsPIC30F__ #ifdef
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMReadProgramMemory.h 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006-2019.  Archangel Systems, Inc. </i> <BR>
 */

#ifndef COMREADPROGRAMMEMORY_H
#define COMREADPROGRAMMEMORY_H

#include "COMtypedefs.h"

#ifdef __dsPIC30F__
extern u16 u16_ReadNonVolatileLowWord ( u32 u32Address ) ;
extern u16 u16_ReadNonVolatileHighWord ( u32 u32Address ) ;
#endif
u32 u32_ReadProgramMemory ( u32 u32Address ) ;

#endif

/* End of COMReadProgramMemory.h header file. */