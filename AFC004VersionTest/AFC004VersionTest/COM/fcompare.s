/**
 *  @file fcompare.s
 *  @brief This file contains low level functions for doing the following:<BR>
 *         Single-precision floating-point comparison.
 *
 *  @date 
 *
 *  @author 
 *
 *  @par <b> Description: </b>
 *     - Single-precision floating-point comparison.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _fcompare
 *
 *  @par <b> Change History: </b> <BR>
 *     This file is part of the compact math library for the dsPIC30. 
 *     (c) Microchip Technology. 2003.
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td>  - <td> <center>Draft</center>   <td> <center> - </center> <td> Initial Draft
 *        <tr><td> 16Sep2008  <td> <center>  "  </center>   <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *  </table>
 *  <BR>
 *
 *  @note $Id: fcompare.s 5889 2008-09-23 17:49:31Z karthikn $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */
        .include "libm.inc"
	.section .libm,code

/**
 * @brief This function operates Floating-point comparison
 *
 * @par <b> Detailed Description: </b>
 *     - Compares two floating point numbers.
 *\verbatim
 *
 *    Inputs (defined by user or linker):
 *      (w1:w0) Operand a
 *      (w3:w2) Operand b
 *      (w4)    Value to return if isNaN(a) || isNaN(b)
 *
 *    Outputs:
 *      (w0)    Result of comparison, or (w4) if either operand is a NaN.
 *              -1      a < b
 *               0      a = b
 *              +1      a > b
 *      (cc)    Reflects the returned value
 *
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
        .global __fcompare
;-----------------------------------------------------------------------;

__fcompare:
        mov.d   w8,[w15++]              ; Preserve scratch
        mov.d   w10,[w15++]             ; Preserve scratch
        mov     w4,[w15++]              ; Preserve return for NaNs

;------ Unpack the operands

        rcall   __funpack2              ; Unpack both operands
        mov     [--w15],w0              ; Assume NaN
        bra     n,exit                  ; isNaN(a) || isNaN(b) ...

;-----------------------------------------------------------------------;
;
;       (w7:w6) a(Significand)
;       (w9:w8) a
;       (w10)   a(Type)
;       (w11)   a(Biased exponent)
;
;       (w1:w0) b(Significand)
;       (w3:w2) b
;       (w4)    b(Type)
;       (w5)    b(Biased exponent)
;
;-----------------------------------------------------------------------;

        mov     #-1,w0                  ; Assume a < b

        xor     w9,w3,[w15]             ; sign(a) == sign(b) ?
        bra     nn,comparemag           ; Yes ... compare magnitude ...

;------ Signs differ

        and     w10,w4,w10              ; isZero(a) && isZero(b) ?
        btsc    w10,#ZEROBIT            ; *
        bra     returnEqual             ; Yes ... a == b

        btss    w9,#15                  ; a < 0 ?
        mov     #1,w0                   ; No ... a > b
        bra     exit                    ; Done

;------ Signs are the same: compare magnitude

comparemag:
        sub     w8,w2,[w15]             ; Form a - b
        subb    w9,w3,[w15]             ; (flags) = (a - b)
        bra     ltu,adjust              ; a < b ...
        mov     #1,w0                   ; Assume a > b
        bra     gtu,adjust              ; a > b ...
returnEqual:
        mov     #0,w0                   ; a == b
adjust:
        btsc    w9,#15                  ; Operands < 0 ?
        neg     w0,w0                   ; Yes ... reverse the sense
exit:
        mov.d   [--w15],w10             ; Recover scratch
        mov.d   [--w15],w8              ; Recover scratch
        cp0     w0                      ; Set condition codes
        return                          ; Done

;-----------------------------------------------------------------------;

        .end

