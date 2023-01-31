/**
 *  @file fixsfsi.s
 *  @brief This file contains low level functions for doing the following:<BR>
 *         Convert floating-point to 32-bit, signed integer .
 *
 *  @date 
 *
 *  @author 
 *
 *  @par <b> Description: </b>
 *     - Convert floating-point to 32-bit, signed integer 
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _fixsfsi
 *
 *  @par <b> Change History: </b> <BR>
 *     This file is part of the compact math library for the dsPIC30. 
 *     (c) Microchip Technology. 2003.
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td>   <td> <center>Draft</center>   <td> <center>  </center> <td> Initial Draft
 *        <tr><td> 16Sep2008  <td> <center>  "  </center>   <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 12Feb2009 <td>  <center> 1.1 </center>   <td> <center>JD</center> <td> ADHR332:PR_LLRBT_192 
 *        <tr><td> 29May2009 <td>  <center> 1.2 </center>   <td> <center>JD</center> <td> ADHR715:Enabled SVN ID
 *  </table>
 *  <BR>
 *
 *  @note $Id: fixsfsi.s 6360 2009-05-29 18:37:40Z jayd $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */
        .include "libm.inc"
	.section .libm,code	


/**
 * @brief This function converts floating-point to 32-bit, signed integer.
 *
 * @par <b> Detailed Description: </b>
 *     - Convert a single-precision, floating-point number to a 32-bit, signed integer.For compatibility with the C compiler,
 *       the conversion is rounded towards zero.
 *\verbatim
 *
 *   Inputs (defined by user or linker):
 *      (w1:w0) Floating-point number to be converted
 *
 *   Outputs:
 *      (w1:w0) 32-bit, signed integer representation of input value.
 *              If the input argument is NaN, LONG_MAX is returned.
 *              If the conversion overflows, LONG_MIN or LONG_MAX
 *              is returned, depending as the input is negative or positive, respectively.
 *              If the conversion underflows, zero is returned.
 *\endverbatim
 * @author 
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *          INT2.0101.S.MSU.16.007.D01 \n
 *
 * @par <b> Parameters: </b> <br> 
 *    <i> None </i> (void)
 */

        .global ___fixsfsi

___fixsfsi:

;------ Unpack the argument

        mov.d   w0,w2                   ; (w3:w2) = Input argument
        rcall   __funpack               ; (w1:w0) = Significand (1.f)
                                        ; (w4)    = Type
                                        ; (w5)    = Biased exponent
        btsc    w4,#NANBIT              ; isNaN(arg) ?
        bclr    w3,#15                  ; Yes ... clear sign

;------ Determine shift count for aligning the binary point

        sub     #23+FLT_BIAS,w5         ; (w5) = shift count
        bra     z,setsign               ; No shift required ...
        bra     lt,shiftright           ; Right shift required ...

;------ Left shift required

        cp      w5,#8                   ; Overflow ?
        bra     lt,shiftleft            ; No ...

;------ Overflow

        mov     #0xFFFF,w0              ; (w1:w0) = LONG_MAX
        mov     #0x7FFF,w1              ; *
        cp0     w3                      ; arg < 0 ?
        bra     nn,exit                 ; Yes ... return LONG_MIN

        mov     #0x8000,w1              ; (w1:w0) = LONG_MIN
        retlw   #0x0000,w0              ; return LONG_MIN

;------ Shift left

shiftleft:
        add     w0,w0,w0                ; (w1:w0) = (sig <<= 1)
        addc    w1,w1,w1                ; *
        dec     w5,w5                   ; (w5) = count--
        bra     nz,shiftleft            ; Loop until aligned ...
        bra     setsign                 ; Set the sign and return ...

;------ Shift right

shiftright:
        .if (1)                         ; Save time at the expense of space ?
        add     w5,#24,[w15]            ; Underflow to zero ?
        bra     gt,shiftrightloop       ; No ...
        clr     w1                      ; Return 0
        retlw   #0,w0                   ; *
        .endif                          ; Save time at the expense of space ?
shiftrightloop:
        lsr     w1,w1                   ; (w1:w0) = (sig >>= 1)
        rrc     w0,w0                   ; *
        inc     w5,w5                   ; (w5) = count++
        bra     nz,shiftrightloop       ; Loop until aligned ...

;------ Set the sign of the result

setsign:
        cp0     w3                      ; arg < 0 ?
        bra     nn,exit                 ; No ...
        subr    w0,#0,w0                ; (w1:w0) = (result = -result)
        subbr   w1,#0,w1                ; *
exit:
        return                          ; Done

;-----------------------------------------------------------------------;

        .end
