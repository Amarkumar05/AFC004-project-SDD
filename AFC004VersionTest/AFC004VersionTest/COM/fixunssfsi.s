/**
 *  @file fixunssfsi.s
 *  @brief This file contains low level functions for doing the following:<BR>
 *         Convert floating-point to 32-bit, unsigned integer. 
 *
 *  @date 
 *
 *  @author 
 *
 *  @par <b> Description: </b>
 *     - convert floating-point to 32-bit, unsigned integer 
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _fixunssfsi
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
 *  @note $Id: fixunssfsi.s 5889 2008-09-23 17:49:31Z karthikn $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */
        .include "libm.inc"
	.section .libm,code

/**
 * @brief This function converts floating-point to 32-bit, unsigned integer.
 *
 * @par <b> Detailed Description: </b>
 *     - Convert a single-precision, floating-point number to a 32-bit, unsigned integer.For compatibility with the C compiler,
 *       the conversion is rounded towards zero.
 *     - The C standard specifies that if the floating-point number is negative, the result is undefined. This implementation returns
 *       zero for negative arguments. The portable range of floating-point values is (-1,ULONG_MAX+1).
 *\verbatim
 *
 *   Inputs (defined by user or linker):
 *      (w1:w0) Floating-point number to be converted
 *
 *   Outputs:
 *      (w1:w0) 32-bit, unsigned integer representation of input value.
 *              If the input argument is NaN, ULONG_MAX is returned.
 *              If the conversion overflows, ULONG_MAX is returned.
 *              If the inpit argument is negative, ULONG_MIN is returned.
 *              If the conversion underflows, zero is returned.
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

        .global ___fixunssfsi

___fixunssfsi:

;------ Unpack the argument

        mov.d   w0,w2                   ; (w3:w2) = Input argument
        rcall   __funpack               ; (w1:w0) = Significand (1.f)
                                        ; (w4)    = Type
                                        ; (w5)    = Biased exponent
        btsc    w4,#NANBIT              ; isNaN(arg) ?
        bclr    w3,#15                  ; Yes ... clear sign
        btst    w3,#15                  ; x < 0 ?
        bra     nz,returnzero           ; Yes ... return zero

;------ Determine shift count for aligning the binary point

        sub     #FLT_PREC-1+FLT_BIAS,w5 ; (w5) = shift count
        bra     z,exit                  ; No shift required ...
        bra     lt,shiftright           ; Right shift required ...

;------ Left shift required

        cp      w5,#33-FLT_PREC         ; Overflow ?
        bra     lt,shiftleft            ; No ...

;------ Overflow

        mov     #0x8000,w1              ; (w1:w0) = ULONG_MAX
        retlw   #0,w0                   ; Done

;------ Shift left

shiftleft:
        add     w0,w0,w0                ; (w1:w0) = (sig <<= 1)
        addc    w1,w1,w1                ; *
        dec     w5,w5                   ; (w5) = count--
        bra     nz,shiftleft            ; Loop until aligned ...
        return                          ; Done

;------ Shift right

shiftright:
        add     w5,#FLT_PREC,[w15]      ; Underflow to zero ?
        bra     lt,returnzero           ; Yes ...
shiftrightloop:
        lsr     w1,w1                   ; (w1:w0) = (sig >>= 1)
        rrc     w0,w0                   ; *
        inc     w5,w5                   ; (w5) = count++
        bra     nz,shiftrightloop       ; Loop until aligned ...
exit:
        return                          ; Done

;------ Result is zero

returnzero:
        clr     w1                      ; Return 0
        retlw   #0,w0                   ; *

;-----------------------------------------------------------------------;

        .end
