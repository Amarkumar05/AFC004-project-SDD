/**
 *  @file feqltle.s
 *  @brief This file contains low level functions for doing the following:<BR>
 *         Single-precision floating-point comparison: ==, <, <=
 *
 *  @date 
 *
 *  @author 
 *
 *  @par <b> Description: </b>
 *     - Floating-point comparison: ==
 *     - Floating-point comparison: <
 *     - Floating-point comparison: <=
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _eqsf2
 *     - _ltsf2
 *     - _lesf2
 *
 *  @par <b> Change History: </b> <BR>
 *     This file is part of the compact math library for the dsPIC30. 
 *     (c) Microchip Technology. 2003.
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td>   <td> <center>Draft</center>   <td> <center>  </center> <td> Initial Draft
 *        <tr><td> 16Sep2008  <td> <center>  "  </center>   <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 05Feb2009 <td>  <center> 1.1 </center>   <td> <center>JD</center> <td> ADHR332:PR_LLRRBT_198
 *  </table>
 *  <BR>
 *
 *  @note $Id: feqltle.s 6146 2009-02-09 16:27:24Z jayd $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */
        .include "libm.inc"
	.section .libm,code

/**
 * @brief This functions Compare two floating point numbers.
 *
 * @par <b> Detailed Description: </b>
 *     - The comparison is done by the common comparison routine __fcompare. The return value for NaN is loaded into the
 *       parameter register before branching to the common routine.
 *\verbatim
 *
 *   Inputs (defined by user or linker):
 *      (w1:w0) Operand a
 *      (w3:w2) Operand b
 *
 *   Outputs:
 *      (w0)    If either operand is a NaN, 1.
 *              Else result of comparison, as follows:
 *              -1      a < b
 *               0      a = b
 *              +1      a > b
 *      (cc)    Reflects the returned value
 *\endverbatim
 * @author 
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *	    INT1.0102.S.ADS.3.003.D01  \n 
 *	    INT1.0102.S.IMU.2.001.D04  \n 
 *          INT2.0101.S.MSU.16.007.D01 \n
 *
 * @par <b> Parameters: </b> <br> 
 */
        .global ___eqsf2
        .global ___ltsf2
        .global ___lesf2

___eqsf2:
___ltsf2:
___lesf2:
        mov     #1,w4                   ; Return value for NaNs
        bra     __fcompare              ; Do the comparison ...

;-----------------------------------------------------------------------;

        .end

