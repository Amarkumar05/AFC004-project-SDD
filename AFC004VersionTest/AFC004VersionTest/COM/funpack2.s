/**
 *  @file funpack2.s
 *  @brief This file contains low level functions for doing the following:<BR>
 *         Single-precision floating-point unpack utility.
 *
 *  @date 
 *
 *  @author 
 *
 *  @par <b> Description: </b>
 *     - Unpacks two floating-point operands 
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _funpack2
 *
 *  @par <b> Change History: </b> <BR>
 *     This file is part of the compact math library for the dsPIC30. 
 *     (c) Microchip Technology. 2003.
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td>   <td> <center>Draft</center>   <td> <center>  </center> <td> Initial Draft
 *        <tr><td> 16Sep2008  <td> <center>  "  </center>   <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *  </table>
 *  <BR>
 *
 *  @note $Id: funpack2.s 5889 2008-09-23 17:49:31Z karthikn $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

        .include "libm.inc"
	.section .libm,code

/**
 * @brief This function unpacks two floating-point operands.
 *
 * @par <b> Detailed Description: </b>
 *     - Unpacks two floating-point operands
 *\verbatim
 *
 *   Inputs (defined by user or linker):
 *      (w1:w0) Operand a
 *      (w3:w2) Operand b
 *
 *   Outputs:
 *      (w7:w6) a(Significand)
 *      (w9:w8) a
 *      (w10)   a(Type)
 *      (w11)   a(Biased exponent)
 *      (w1:w0) b(Significand)
 *      (w3:w2) b
 *      (w4)    b(Type)
 *      (w5)    b(Biased exponent)
 *      (N)     Set if either operand is a NaN
 *
 *   Register Usage:
 *      None other than the input and output registers.
 *\endverbatim
 * @author 
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *	    INT1.0102.S.ADS.3.003.D01  \n 
 *	    INT1.0102.S.IMU.2.001.D04  \n 
 *          INT2.0101.S.MSU.16.007.D01 \n
 *
 * @par <b> Parameters: </b> <br> 
 *    <i> None </i> (void)
 */

        .global __funpack2

__funpack2:

;------ Unpack operand a

        mov.d   w0,w8           ; (w9:w8)=a
         rcall   __funpack       ; (w4)   =a(Type)
                                ; (w5)   =a(Biased exponent)
                                ; (w1:w0)=a(Significand)
        mov.d   w0,w6           ; (w6:w7)=a(Significand)
        mov.d   w4,w10          ; (w10)  =a(Type)
                                ; (w11)  =a(Biased exponent)

;------ Unpack operand b

        mov.d   w2,w0           ; b to argreg for funpack
        rcall   __funpack       ; (w4)   =b(Type)
                                ; (w5)   =b(Biased exponent)
                                ; (w1:w0)=b(Significand)

;------ Check for NaNs

        ior.b   w10,w4,[w15]    ; isNaN(a) || isNaN(b) ?
        return                  ; (N) set if so

;-----------------------------------------------------------------------;
        .end
