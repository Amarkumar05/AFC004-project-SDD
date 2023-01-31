/** @file COMDSPicNonVolatileMemRead.h
 *  @brief Contains prototypes for low level NVM read functions.
 *
 *  @par <b> Description: </b>
 *     - Contains prototypes for low level NVM read functions.
 *
 *  @date 08Jun2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 13Jun2006 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> PR_CR_017
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> PR_CR_012
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 06Nov2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281- PR_CR_066
 *  </table>
 *  <BR>
 *  @note $Id: COMDSPicNonVolatileMemRead.h 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006.  Archangel Systems, Inc. </i> <BR>
 */

#ifndef COMDSPICNONVOLATILEMEMREAD_H
#define COMDSPICNONVOLATILEMEMREAD_H

extern u16 u16_ReadNonVolatileLowWord ( u32 u32Address ) ;
extern u16 u16_ReadNonVolatileHighWord ( u32 u32Address ) ;

#endif

/* End of COMdsPicNonVolatileMemRead.h header file. */