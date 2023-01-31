/**
 *  @file COMfunpack.s
 *  @brief This file contains a function to unpack a floating point operand.
 *         The source code below was taken from the C30 Dspic Math Library. (C30 Version 2.03). 
 *
 *  @date 15Jan2007
 *
 *  @author Stephen Hallacy
 *
 *  @par <b> Description: </b>
 *     - Unpacks a floating-point operand.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _funpack
 *
 *  @par <b> Change History: </b> <BR>
 *     This file is part of the compact math library for the dsPIC30. 
 *     (c) Microchip Technology. 2003.
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 15Jan2007 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 16Sep2008  <td> <center>  "  </center>   <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMfunpack.s 5889 2008-09-23 17:49:31Z karthikn $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

.include "COMlibm.inc"

;***********  Variable Declarations  ************


.global __funpack


/**
 * @brief Unpacks a floating-point operand.
 *
 * @par <b> Detailed Description: </b>
 *
 *\verbatim
 *
 *  _funpack
 *      Unpacks a floating-point operand.
 *
 *  Input:
 *      (w1:w0) Floating-point number to be unpacked
 *
 *  Output:
 *      (w1:w0) Significand (1.f)
 *      (w4)    Type { ZEROTYPE, FINITETYPE, INFTYPE, NANTYPE }
 *      (w5)    Biased exponent
 *
 *  Notes:
 *      If the argument is finite and non-zero, a significand
 *      in the form 1.f is returned, even if the argument is subnormal.
 *      The exponent is adjusted accordingly, if necessary.
 *
 *  Register Usage:
 *      None other than the input and output registers.
 *\endverbatim
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *	    INT1.0102.S.ADS.3.003.D01  \n 
 *	    INT1.0102.S.IMU.2.001.D04  \n 
 *          INT2.0101.S.MSU.16.007.D01 \n
 *
 * @par <b> Parameters: </b> <br> 
 *    <i> None </i> (void)
 */
__funpack:

;------ Extract fraction & biased exponent

        lsr     w1,#7,w5        ; (w5)=sign & biased exponent
        and     #0x7F,w1        ; (w1:w0)=fraction
        and     #0xFF,w5        ; (w5)=biased exponent (strip sign)

;------ Check for Zeroes and subnormals (biased exp == 0)

        bra     z,zeroorsub     ; Zero or subnormal ...

;------ Check for NaNs and Infinities

        add.b   w5,#1,[w15]     ; exp==255 (NaN or Infinity) ?
        bra     z,nanorinf      ; Yes ...

;------ Finite, non-zero

finitereturn:
        bset    w1,#7           ; Explicit 1.f
        retlw   #FINITETYPE,w4  ; Finite

;------ NaN or Infinity

nanorinf:
        ior     w0,w1,[w15]     ; fraction == 0 ?
        bra     z,infinite      ; Yes ...
        retlw   #NANTYPE,w4     ; NaN
infinite:
        retlw   #INFTYPE,w4     ; Infinite

;------ Zero or subnormal

zeroorsub:
        ior     w0,w1,[w15]     ; fraction == 0 ?
        bra     nz,subnormal    ; No ...
        retlw   #ZEROTYPE,w4    ; 0.0f

;------ Subnormal: normalize

normalize:
        dec     w5,w5           ; exp--
subnormal:
        add     w0,w0,w0        ; fraction <<= 1
        addc.b  w1,w1,w1        ; *
        bra     nn,normalize    ; Loop until normalized ...

        bset    w1,#7           ; Explicit 1.f
        retlw   #FINITETYPE,w4  ; Finite
;-----------------------------------------------------------------------;
        .end

;   END OF FILE (COMfunpack.s)
