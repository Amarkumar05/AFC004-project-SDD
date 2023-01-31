/**
 *  @file futil.s
 *  @brief This file contains low level functions for doing the following:<BR>
 *         Single-precision floating-point utilities.
 *
 *  @date 
 *
 *  @author 
 *
 *  @par <b> Description: </b>
 *     - Propagate a NaN
 *     - Return a quiet NaN
 *     - Common exit from floating-point operations
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _fPropagateNaN
 *     - _fbopReturnNaN
 *     - _fbopExit
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
 *  @note $Id: futil.s 5889 2008-09-23 17:49:31Z karthikn $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

        .include "libm.inc"
	.section .libm,code

/**
 * @brief This function Propagate a NaN in conformance with the IEEE standard.
 *
 * @par <b> Detailed Description: </b>
 *  - All floating-point operations that return NaN must return a quiet NaN. On entry to this function, either isNaN(a) or isNaN(b),
 *    or both operands are NaN. In the case that only one of the operands is NaN, then a quiet version of that NaN is returned.
 *    If both operands are NaN, then if only one of them is quiet, return that NaN. If both are quiet, return a.
 *    If both a signalling, return a quiet version of b. A quiet NaN has bit 23 set to 1.
 *\verbatim
 *
 *  Input:
 *      (w9:w8) a
 *      (w10)   a(Type)
 *      (w3:w2) b
 *      (w4)    b(Type)
 *
 *  Output:
 *      (w1:w0) NaN
 *
 *  Notes:
 *      This exit block is branched to, not called.
 *
 *  Register usage:
 *      This exit block restores the standard set of scratch
 *      registers, and returns to the caller.
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

        .global __fPropagateNaN

;-----------------------------------------------------------------------;

__fPropagateNaN:
        mov.d   w2,w0           ; Assume the result is b
        cp      w10,#INFTYPE    ; isNaN(a) ?
        bra     leu,return0     ; No ... return(b)
        cp      w4,#INFTYPE     ; isNaN(b) ?
        bra     leu,return8     ; No ... return(a)

;------ Both operands are NaNs

        btst    w9,#6           ; isSignaling(a) ?
        bra     nz,return0      ; Yes ... return(b)
return8:
        mov.d   w8,w0           ; Result is a
return0:
        bset    w1,#6           ; Force quiet NaN for result

;------ Fall through to common exit block


/**
 * @brief This function return to the C environment.
 *
 * @par <b> Detailed Description: </b>
 *     - This exit block restores the common set of scratch registers,and returns to the caller.
 *
 *\verbatim
 *  Notes:
 *      This exit stub is branched to, not called.
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

        .global __fbopExit

__fbopExit:
        mov.w   [--w15],w12     ; Recover scratch
        mov.d   [--w15],w10     ; Recover scratch
        mov.d   [--w15],w8      ; Recover scratch
        return                  ; Back to the C environment



/**
 * @brief This function Return a NaN from an elementary operation.
 *
 * @par <b> Detailed Description: </b>
 *     - Return a NaN from an elementary operation
 *
 *\verbatim
 *  Notes:
 *      This exit stub is branched to, not called.
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


        .global __fbopReturnNaN

__fbopReturnNaN:
        mov.w   #NaNLO,w0               ; Result is NaN
        mov.w   #NaNHI,w1               ; *
        bra     __fbopExit              ; Exit ...
;-----------------------------------------------------------------------;
        .end

