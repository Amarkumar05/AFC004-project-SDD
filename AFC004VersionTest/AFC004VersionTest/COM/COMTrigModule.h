/** @file COMTrigModule.h
 *  @brief Provides the trigonometric functions: Sine, Cosine, Tangent, ArcSine, ArcCosine and ArcTangent
 *
 *  @par <b> Description: </b>
 *     - Polynomial approximations are used to calculate the values.
 *
 *  @date 02Aug2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 02Aug2006 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 03Aug2006 <td>   <center>"</center>     <td> <center>SH</center> <td> Changed basic types to typedefs and Moved absolute value calculation
 *                                                                                        of ArcTan inputs to its own function and Reformatted to meet new coding standards.
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM, PR_CR_032 and PR_CR_012
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 02Dec2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *        <tr><td> 26Jan2009 <td>  <center> 1.2</center>    <td> <center>JD</center> <td> ADHR327: PR_LLR_COM_021
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMTrigModule.h 6121 2009-01-28 22:50:42Z jayd $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006.  Archangel Systems, Inc. </i> <BR>
 */

#ifndef COM_TRIG_H
#define COM_TRIG_H

/*
 **  Include Files  =============================================================
 */
#include "COMtypedefs.h"
#include "COMDefines.h"
 /*
 **  Local Constants, Enums, Typedefs, and Prototypes  ==========================
 */
    /** These are the constants used in several trig functions. */

 /* constants used in several trig functions */
#define TRIG_PI_OVER_2      1.5707963267f            /*  PI/2  */
#define TRIG_PI             3.1415926535f            /*  PI    */
#define TRIG_3_PI_OVER_2    4.7123889803f            /*  3PI/2 */
#define TRIG_2_PI           6.2831853071f            /*  2PI   */
#define TRIG_ZERO           0.0f                     /*  zero   */
#define TRIG_ZERO_LIMIT     0.000001f                /* value below which numbers will be rounded to zero */
#define NEGATIVE_ONE        -1.0f
#define THIRTEEN            13u

/** These are the constants used in calculating Sin(). */
 /* constants used in calculating Sin()  */
#define SINE_COEFF_0        -0.000000007161714f      /* sine Coefficient #0 */
#define SINE_COEFF_1         1.0f                    /* sine Coefficient #1 */
#define SINE_COEFF_2        -0.0000075576f           /* sine Coefficient #2 */
#define SINE_COEFF_3        -0.166614f               /* sine Coefficient #3 */
#define SINE_COEFF_4        -0.0001978271f           /* sine Coefficient #4 */
#define SINE_COEFF_5         0.008771f               /* sine Coefficient #5 */
#define SINE_COEFF_6        -0.0006006538f           /* sine Coefficient #6 */
#define SINE_COEFF_7         0.0003188567f           /* sine Coefficient #7 */
#define SINE_COEFF_8        -0.0002720017f           /* sine Coefficient #8 */
#define SINE_COEFF_9         0.00008266765f          /* sine Coefficient #9 */
#define SINE_COEFF_10       -0.00001010888f          /* sine Coefficient #10 */

/** These are the constants used in calculating ArcTan(). */
 /* constants used in calculating ArcTan()  */
#define ARCTAN_COEFF_0      -0.0000005869951f        /* arctan Coefficient #1 */
#define ARCTAN_COEFF_1       1.000056f               /* arctan Coefficient #2 */
#define ARCTAN_COEFF_2      -0.001287f               /* arctan Coefficient #3 */
#define ARCTAN_COEFF_3      -0.320787f               /* arctan Coefficient #4 */
#define ARCTAN_COEFF_4      -0.063708f               /* arctan Coefficient #5 */
#define ARCTAN_COEFF_5       0.383474f               /* arctan Coefficient #6 */
#define ARCTAN_COEFF_6      -0.300610f               /* arctan Coefficient #7 */
#define ARCTAN_COEFF_7       0.100063f               /* arctan Coefficient #8 */
#define ARCTAN_COEFF_8      -0.011801f               /* arctan Coefficient #9 */

/** These are the constants used in calculating ArcSin() */
 /* constants used in calculating ArcSin()  */
#define ARCSINE_COEFF_0_A     -0.000000007161714f    /* arcsine coefficient #0 in Interval A */
#define ARCSINE_COEFF_1_A      1.000305f             /* arcsine coefficient #1 in Interval A */
#define ARCSINE_COEFF_2_A     -0.012890f             /* arcsine coefficient #2 in Interval A */
#define ARCSINE_COEFF_3_A      0.398032f             /* arcsine coefficient #3 in Interval A */
#define ARCSINE_COEFF_4_A     -2.178024f             /* arcsine coefficient #4 in Interval A */
#define ARCSINE_COEFF_5_A      11.864578f            /* arcsine coefficient #5 in Interval A */
#define ARCSINE_COEFF_6_A     -37.406385f            /* arcsine coefficient #6 in Interval A */
#define ARCSINE_COEFF_7_A      64.172492f            /* arcsine coefficient #7 in Interval A */
#define ARCSINE_COEFF_8_A     -33.018307f            /* arcsine coefficient #8 in Interval A */
#define ARCSINE_COEFF_9_A     -68.489041f            /* arcsine coefficient #9 in Interval A */
#define ARCSINE_COEFF_10_A     94.532203f            /* arcsine coefficient #10 in Interval A */
#define ARCSINE_COEFF_11_A     49.205398f            /* arcsine coefficient #11 in Interval A */
#define ARCSINE_COEFF_12_A    -145.091166f           /* arcsine coefficient #12 in Interval A */
#define ARCSINE_COEFF_13_A     48.422906f            /* arcsine coefficient #13 in Interval A */
#define ARCSINE_COEFF_14_A    -11.687058f            /* arcsine coefficient #14 in Interval A */
#define ARCSINE_COEFF_15_A     127.679010f           /* arcsine coefficient #15 in Interval A */
#define ARCSINE_COEFF_16_A    -146.669795f           /* arcsine coefficient #16 in Interval A */
#define ARCSINE_COEFF_17_A     48.730751f            /* arcsine coefficient #17 in Interval A */
#define ARCSINE_COEFF_0_B     -117.167283f           /* arcsine coefficient #0 in Interval B */
#define ARCSINE_COEFF_1_B      241.593385f           /* arcsine coefficient #1 in Interval B */
#define ARCSINE_COEFF_2_B      23.226450f            /* arcsine coefficient #2 in Interval B */
#define ARCSINE_COEFF_3_B     -50.637213f            /* arcsine coefficient #3 in Interval B */
#define ARCSINE_COEFF_4_B     -356.822393f           /* arcsine coefficient #4 in Interval B */
#define ARCSINE_COEFF_5_B      132.632710f           /* arcsine coefficient #5 in Interval B */
#define ARCSINE_COEFF_6_B     -18.345748f            /* arcsine coefficient #6 in Interval B */
#define ARCSINE_COEFF_7_B      350.315960f           /* arcsine coefficient #7 in Interval B */
#define ARCSINE_COEFF_8_B     -181.037298f           /* arcsine coefficient #8 in Interval B */
#define ARCSINE_COEFF_9_B      227.179559f           /* arcsine coefficient #9 in Interval B */
#define ARCSINE_COEFF_10_B    -296.739920f           /* arcsine coefficient #10 in Interval B */
#define ARCSINE_COEFF_11_B    -96.559073f            /* arcsine coefficient #11 in Interval B */
#define ARCSINE_COEFF_12_B     143.845840f           /* arcsine coefficient #12 in Interval B */
#define ARCSINE_COEFF_0_C      266.383599f           /* arcsine coefficient #0 in Interval C */
#define ARCSINE_COEFF_1_C     -398.216618f           /* arcsine coefficient #1 in Interval C */
#define ARCSINE_COEFF_2_C      159.909384f           /* arcsine coefficient #2 in Interval C */
#define ARCSINE_COEFF_3_C     -481.564931f           /* arcsine coefficient #3 in Interval C */
#define ARCSINE_COEFF_4_C      643.222644f           /* arcsine coefficient #4 in Interval C */
#define ARCSINE_COEFF_5_C     -602.608417f           /* arcsine coefficient #5 in Interval C */
#define ARCSINE_COEFF_6_C      431.340522f           /* arcsine coefficient #6 in Interval C */
#define ARCSINE_COEFF_7_C      317.953188f           /* arcsine coefficient #7 in Interval C */
#define ARCSINE_COEFF_8_C      267.411882f           /* arcsine coefficient #8 in Interval C */
#define ARCSINE_COEFF_9_C     -694.846853f           /* arcsine coefficient #9 in Interval C */
#define ARCSINE_COEFF_10_C     111.277111f           /* arcsine coefficient #10 in Interval C */
#define ARCSINE_COEFF_11_C    -385.640755f           /* arcsine coefficient #11 in Interval C */
#define ARCSINE_COEFF_12_C     366.887100f           /* arcsine coefficient #12 in Interval C */
#define ARCSINE_COEFF_0_D     -285.577262f           /* arcsine coefficient #0 in Interval D */
#define ARCSINE_COEFF_1_D     -1266.407324f          /* arcsine coefficient #1 in Interval D */
#define ARCSINE_COEFF_2_D      1999.667251f          /* arcsine coefficient #2 in Interval D */
#define ARCSINE_COEFF_3_D      2087.602378f          /* arcsine coefficient #3 in Interval D */
#define ARCSINE_COEFF_4_D     -669.734382f           /* arcsine coefficient #4 in Interval D */
#define ARCSINE_COEFF_5_D     -541.361019f           /* arcsine coefficient #5 in Interval D */
#define ARCSINE_COEFF_6_D     -889.099922f           /* arcsine coefficient #6 in Interval D */
#define ARCSINE_COEFF_7_D     -1090.098925f          /* arcsine coefficient #7 in Interval D */
#define ARCSINE_COEFF_8_D     -965.000979f           /* arcsine coefficient #8 in Interval D */
#define ARCSINE_COEFF_9_D      450.247578f           /* arcsine coefficient #9 in Interval D */
#define ARCSINE_COEFF_10_D    -3342.003808f          /* arcsine coefficient #0 in Interval D */
#define ARCSINE_COEFF_11_D     430.160931f           /* arcsine coefficient #1 in Interval D */
#define ARCSINE_COEFF_12_D     3264.335626f          /* arcsine coefficient #2 in Interval D */
#define ARCSINE_COEFF_13_D     2086.706953f          /* arcsine coefficient #3 in Interval D */
#define ARCSINE_COEFF_14_D     82.598222f            /* arcsine coefficient #4 in Interval D */
#define ARCSINE_COEFF_15_D     365.411304f           /* arcsine coefficient #5 in Interval D */
#define ARCSINE_COEFF_16_D    -1852.144692f          /* arcsine coefficient #6 in Interval D */
#define ARCSINE_COEFF_17_D     4006.564778f          /* arcsine coefficient #7 in Interval D */
#define ARCSINE_COEFF_18_D     853.675535f           /* arcsine coefficient #8 in Interval D */
#define ARCSINE_COEFF_19_D    -2620.173535f          /* arcsine coefficient #9 in Interval D */
#define ARCSINE_COEFF_20_D    -2174.012313f          /* arcsine coefficient #10 in Interval D */
#define ARCSINE_COEFF_21_D    -3101.6958854f         /* arcsine coefficient #11 in Interval D */
#define ARCSINE_COEFF_22_D    -394.938869f           /* arcsine coefficient #12 in Interval D */
#define ARCSINE_COEFF_23_D     3566.816515f          /* arcsine coefficient #12 in Interval D */
#define ARCSINE_COEFF_0_E      7887.541176f          /* arcsine coefficient #0 in Interval E */
#define ARCSINE_COEFF_1_E      783.992223f           /* arcsine coefficient #1 in Interval E */
#define ARCSINE_COEFF_2_E     -1868.306495f          /* arcsine coefficient #2 in Interval E */
#define ARCSINE_COEFF_3_E     -9762.407042f          /* arcsine coefficient #3 in Interval E */
#define ARCSINE_COEFF_4_E     -17520.575308f         /* arcsine coefficient #4 in Interval E */
#define ARCSINE_COEFF_5_E      20481.320519f         /* arcsine coefficient #5 in Interval E */


/* ArcSin has 5 intervals that have calculations (0.0, 0.9], [0.901, 0.96], [0.961, 0.98], [0.981, 0.99975],
   and [0.999751, 0.9999).  We'll call these Intervals A to E. */

#define ARCSIN_MAX_VALUE  99.0f
#define ARCSIN_INTERVAL_A_UPPER_LIMIT  0.90f
#define ARCSIN_INTERVAL_B_UPPER_LIMIT  0.96f
#define ARCSIN_INTERVAL_C_UPPER_LIMIT  0.98f
#define ARCSIN_INTERVAL_D_UPPER_LIMIT  0.99975f
#define ARCSIN_INTERVAL_E_UPPER_LIMIT  0.9999f



/* function declarations */
f32 f32_Sin( f32 f32InputValue ) ;     /* returns the sine value at f32InputValue radians */

f32 f32_Cos( f32 f32InputValue ) ;     /* returns the cosine value at f32InputValue radians */

f32 f32_Tan( f32 f32InputValue ) ;     /* returns the tangent value at f32InputValue radians */

f32 f32_ArcSin ( f32 f32InputValue ) ; /* returns the arcsin value at f32InputValue */

f32 f32_ArcTan2 ( f32 f32Numerator ,   /* returns the value of arctan2 (f32Numerator, f32Denominator) */
                 f32 f32Denominator ) ;

f32 f32_ArcTanInputsToAbsVal ( f32* pf32Numerator ,     /* changes inputs to absolute values and returns */
                               f32* pf32Denominator ) ; /* -1 if one of the inputs is negative, or 1 if */
                                                       /* neither or both are negative */
#endif  /*COM_TRIG_H*/

/*
** end of file
*/
