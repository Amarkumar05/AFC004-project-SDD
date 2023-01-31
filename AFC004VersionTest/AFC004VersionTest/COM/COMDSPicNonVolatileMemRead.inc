/** @file COMDSPicNonVolatileMemRead.inc
 *  @brief This is the header file for COMDSPicNonVolatileMemRead.s
 *
 *  @par <b> Description: </b>
 *     - None
 *
 *  @date 22Nov2005
 *  @author Stephen Hallacy
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 22Nov2005 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 27Jan2019 <td>  <center> 1.1 </center>   <td> <center>BA</center> <td> Changed .include
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMDSPicNonVolatileMemRead.inc 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006-2019.  Archangel Systems, Inc. </i> <BR>
 */

.include "pic_inc/p30fxxxx.inc"

/* Make the these function visible outside of COMDSPicLowLevelNonVolatileMemory.s.
   The leading underscore is not used when a c-routine calls these functions. */
.global _u16_ReadNonVolatileLowWord
.global _u16_ReadNonVolatileHighWord
    