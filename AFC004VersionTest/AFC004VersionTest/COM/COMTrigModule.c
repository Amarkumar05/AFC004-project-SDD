/**
 *  @file COMTrigModule.c
 *  @brief Provides the trigonometric functions: Sine, Cosine, Tangent, ArcSine, ArcCosine, and ArcTangent
 *
 *  @date 02Aug2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Description: </b>
 *     - Polynomial approximations are used to calculate the values.
 *
 *  @par <b> Table of Contents: </b>
 *   The following functions are defined in this file:
 *     - f32_Sin - returns the sine value at f32InputValue radians
 *     - f32_Cos - returns the cosine value at f32InputValue radians
 *     - f32_Tan - returns the tangent value at f32InputValue radians
 *     - f32_ArcSin - returns the arcsin value at f32InputValue
 *     - f32_ArcTan2 -  returns the value of arctan2
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 02Aug2006 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 03Aug2006 <td>   <center>"</center>     <td> <center>SH</center> <td> Changed basic types to typedefs. Moved
 *                                                                                       absolute value calculation of ArcTan
 *                                                                                       inputs to its own function. reformatted
 *                                                                                       to meet new coding standards.
 *        <tr><td> 17Jan2007 <td>   <center>"</center>     <td> <center>SH</center> <td> 1. Made f32_Tan() Arrays to constant
 *                                                                                          Module Level Arrays.<BR>
 *                                                                                       2. (NOW)  s16 s16Counter = 0; (WAS)
 *                                                                                          u16 u16Counter = 0;
 *                                                                                          (NOW)  s16 s16CounterMax = 0; (WAS)
 *                                                                                          u16 u16CounterMax = 0;<BR>
 *                                                                                       3. Changed all instance of u16Counter and
 *                                                                                          u16CounterMax to s16Counter and
 *                                                                                          u16CounterMax respectively.
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM and PR_CR_004
 *        <tr><td> 25Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM and PR_LLT_COM_018
 *        <tr><td> 16Sep2008 <td>   <center>"</center>     <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 03Nov2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281: PR_CR_253;
 *        <tr><td> 26Jan2009 <td>  <center> 1.2</center>    <td> <center>JD</center> <td> ADHR327: PR_LLR_COM_021
 *        <tr><td> 13Feb2009 <td>  <center> 1.3</center>    <td> <center>YC</center> <td> ADHR340: PR_CR_315, deleted the function
 *                                                                                        "f32_ArcTanInputsToAbsVa"
 *        <tr><td> 29May2009 <td>  <center> 1.4</center>    <td> <center>JD</center> <td> ADHR715
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMTrigModule.c 6360 2009-05-29 18:37:40Z jayd $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

/*
**  Include Files  =============================================================
*/
#include "COMTrigModule.h"



/* Interval bounds */
static const f32 f32aInterval [ 13 ] = { 0.0f , 1.00f , 1.35f , 1.46f , 1.536f , 1.554f , 1.564f , 1.566f ,
                                      1.568f , 1.569f , 1.5699f , 1.5704f , 1.57065f } ;
 /**< File level variable. */
/* Number of coefficients in the calculation in each Interval */
static const u16 u16aMaxCoefficients [ 13 ] = { 8 , 8 , 8 , 8 , 8 , 10 , 10 , 10 , 10 , 10 , 10 , 10 , 8 } ;
                                                                                       /**< File level variable. */

/* Coefficients used to calculate tan() */
static const f32 f32aTanCoefficients [ 13 ] [ 11 ] =
   { {  0.00001491028f , 0.998691f     , 0.027428f      , 0.093539f      , 1.073381f      ,
       -2.547659f     , 3.801754f     , -2.841215f     , 0.951448f      , 0.0f           ,
        0.0f },
     {  316.563434f    , -1168.307442f , 1180.148984f   , 607.928054f    , -1779.378518f  ,
        658.252754f    , 616.869617f   , -556.810836f   , 126.291552f    , 0.0f           ,
        0.0f },
     {  871.099632f    , -1035.291252f , 1920.704092f   , -3680.383299f  , 1528.690797f   ,
        428.856499f    , 1145.207475f  , -1572.214738f  , 453.301387f    , 0.0f           ,
        0.0f },
     { 391585.345138f , -427894.003923f, -172814.721013f, 220312.252046f , 46722.086257f  ,
       -29782.883808f , 15363.931379f , -37597.271727f , 13756.424956f  , 0.0f           ,
        0.0f },
     { -623947.748650f, 281355.831490f, 210458.604108f , -83112.859031f , 217196.935144f ,
       -83750.328960f , -88416.179754f, 6269.163377f   , 17370.809928f  , 0.0f           ,
        0.0f },
     { -11237338.35f  , 2892103.881277f, 7077427.515207f, 1152473.060731f, -3637546.139905f,
        892013.459815f , 1401107.455346f, -1612085.499134f, -17406.772833f , 376023.685779f ,
       -64241.177305f } ,
     {  300531.291529f , 168149.713631f, 72404.304705f  , -15969.960205f , -70256.288468f ,
       -52620.274706f , -20680.805274f, -14653.528631f , 6767.060442f   , 5828.952512f   ,
        3458.577746f },
     { 26540482.5f    , -17352790.0f  , -8108246.439993f, 7179492.806458f, -2652385.703541f,
      -513308.466730f, 1789811.212502f, -1026274.548135f, 315900.435510f , 136617.714245f ,
      -91607.711930f },
     { -11857218.25f  , 5590519.465659f, 8603226.383351f, 878347.357058f , 388042.546124f ,
       -1822239.345670f, -312861.570549f, -726111.939882f, -177080.575519f, 20736.180463f  ,
        226325.663617f },
     { 48471118.5f    , -15548890.0f  , 1320977.404180f, 9456493.132551f, -11610150.0f   ,
       4418316.882146f, -683972.164312f, -2217507.709860f, -1729140.642613f, -197653.170466f,
       1122667.618308f },
     { 157137350.0f   , 665625100.0f  , -435493600.0f  , 89380840.0f    , -130997200.0f  ,
       126677.242207f , 40913110.0f   , 9230747.948486f, -26259340.0f   , -20803840.0f   ,
       18302780.0f },
     { 3827755100.0f  , 3493285000.0f , -895957700.0f  , -1688728000.0f , 399480700.0f   ,
      -361275700.0f  , -23369990.0f  , -277656100.0f  , -5647688.869029f, -1343041.943007f,
       83691690.0f },
     { 534166100.0f   , 135949500.0f  , -271744000.0f  , 240770700.0f   , -191080800.0f  ,
      -133775100.0f  , 15936180.0f   , 61538090.0f    , -6993031.894470f, 0.0f           ,
       0.0f } } ;  /**< File level variable. */

/**
 * @brief This function calculates sine.
 *
 * @par <b> Detailed Description: </b>
 *     Uses a polynomial approximation to calculate the return value
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       INT1.0102.S.IMU.4.015 \n
 *          INT1.0102.S.DSP.7.015 \n
 *
 * @param [in] f32InputValue  Input value
 */

f32 f32_Sin ( f32 f32InputValue ) /* input value */
{
   f32 f32SineValue = ( f32 ) ZERO ;  /* sine result */
   f32 f32Negator = ( f32 ) ONE ;   /* negation product */

   /* get input s16o the range 0..2PI*/
   while ( f32InputValue < ZERO )
   {
      f32InputValue += TRIG_2_PI ;
   }
   while ( f32InputValue > TRIG_2_PI )
   {
      f32InputValue -= TRIG_2_PI ;
   }

   /* get input s16o the range 0..pi/2*/
   if ( f32InputValue > TRIG_PI )  /* result should be negative */
   {
      f32InputValue -= TRIG_PI ; /* get input s16o range 0..pi */
      f32Negator = NEGATIVE_ONE ;   /* make f32Negator negative */
   }
   else
   { }

   if ( f32InputValue > TRIG_PI_OVER_2 ) /* if f32InputValue in range pi/2..pi */
   {
      /* reflect input s16o range 0..pi/2 */
      f32InputValue = f32InputValue - TRIG_PI_OVER_2 ;
      f32InputValue = TRIG_PI_OVER_2 - f32InputValue ;
   }
   else
   { }

   f32SineValue = ( SINE_COEFF_0 + f32InputValue *
                  ( SINE_COEFF_1 + f32InputValue *
                  ( SINE_COEFF_2 + f32InputValue *
                  ( SINE_COEFF_3 + f32InputValue *
                  ( SINE_COEFF_4 + f32InputValue *
                  ( SINE_COEFF_5 + f32InputValue *
                  ( SINE_COEFF_6 + f32InputValue *
                  ( SINE_COEFF_7 + f32InputValue *
                  ( SINE_COEFF_8 + f32InputValue *
                  ( SINE_COEFF_9 + f32InputValue *
                  ( SINE_COEFF_10 ) ) ) ) ) ) ) ) ) ) ) ;

   /* convert to negative when needed */
   f32SineValue *= f32Negator ;

   return ( f32SineValue ) ;
   /** @return \a f32SineValue - Returns the Sine value of f32InputValue. */
} /* end Sin() */

/**
 * @brief This function calculates cosine.
 *
 * @par <b> Detailed Description: </b>
 *     Uses the fact that cos(x) = sin(x + pi/2) and calls the sine function
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       INT1.0102.S.IMU.4.015 \n
 *          INT1.0102.S.DSP.7.015 \n
 *
 * @param [in] f32InputValue  input value
 */

f32 f32_Cos ( f32 f32InputValue ) /* input value */
{
   f32 f32CosineValue = ( f32 ) ZERO ; /* cosine result */
   f32 f32InputToSin = f32InputValue + ( f32 ) TRIG_PI_OVER_2 ;  /* input + pi/2 */

   /*  cos(x) = sin(x + pi/2) */
   f32CosineValue = f32_Sin ( f32InputToSin ) ;

   return f32CosineValue ;
   /** @return \a f32CosineValue - cosine of f32InputValue radians. */
} /* end Cos() */

/**
 * @brief This function calculates tangent.
 *
 * @par <b> Detailed Description: </b>
 *     Uses a polynomial approximation to get the tangent value.
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       INT1.0102.S.IMU.4.015 \n
 *          INT1.0102.S.DSP.7.015 \n
 *
 * @param [in] f32InputValue  input value
 */

f32 f32_Tan ( f32 f32InputValue ) /* input value */
{
   f32 f32TangentValue = ( f32 ) ZERO ;  /* the result */
   f32 f32Negator = ( f32 ) ONE ;      /* used to negate the result when necessary */
   u16 u16LowerIndex = ( u16 ) ZERO ;      /* lower index into Interval array */
   u16 u16UpperIndex = ( u16 ) THIRTEEN  ;     /* upper index into Interval array */
   u16 u16CurrentIndex = ( u16 ) ZERO ;    /* used to locate the correct Interval to use  */
   s16 s16Counter = ( s16 ) ZERO ;         /* for loop counter */
   s16 s16CounterMax = ( s16 ) ZERO ;      /* the number of times to execute the for loop */

   /* validate input*/
   while ( f32InputValue < -TRIG_PI_OVER_2 )
   {
      f32InputValue =  f32InputValue + TRIG_PI  ;
   }
   while ( f32InputValue > TRIG_PI_OVER_2 )
   {
      f32InputValue = ( f32InputValue - TRIG_PI ) ;
   }

   /* make a positive value out of negative input*/
   if ( f32InputValue < ZERO )
   {
      f32InputValue *= NEGATIVE_ONE  ;
      f32Negator = NEGATIVE_ONE  ;
   }
   else
   { }

   if ( ( f32InputValue < TRIG_ZERO_LIMIT ) )
   {
      f32TangentValue = ( f32 ) ZERO ;
   }
   else
   {
      /* Find the correct Interval via bisection */
      while ( u16UpperIndex - u16LowerIndex > ONE )
      {
         u16CurrentIndex = ( u16UpperIndex + u16LowerIndex ) >> ( u16 ) ONE ;

         if ( f32InputValue > f32aInterval [ u16CurrentIndex ] )
         {
            u16LowerIndex = u16CurrentIndex ;
         }
         else
         {
            u16UpperIndex = u16CurrentIndex ;
         }
      }

      /* Evaluate the polynomial for this Interval */
      s16CounterMax = u16aMaxCoefficients [ u16LowerIndex ] ;

      f32TangentValue = f32aTanCoefficients [ u16LowerIndex ] [ s16CounterMax ] ;

      for ( s16Counter = s16CounterMax - ( s16 ) ONE ; s16Counter >= ( s16 ) ZERO ; s16Counter-- )
      {
         f32TangentValue = f32TangentValue * f32InputValue + f32aTanCoefficients [ u16LowerIndex ] [ s16Counter ] ;
      }
   }

   f32TangentValue *= f32Negator ;

   return ( f32TangentValue ) ;
   /** @return \a f32TangentValue - Tangent of f32InputValue radians. */
} /* end Tan() */

/**
 * @brief This function calculates arctangent {atan2(y, x)}.
 *
 * @par <b> Detailed Description: </b>
 *     Uses a polynomial approximation to get the arctangent value.
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       INT1.0102.S.IMU.4.015 \n
 *          INT1.0102.S.DSP.7.015 \n
 *
 * @param [in] f32Numerator  Numerator argument
 * @param [in] f32Denominator  Denominator argument
 */

f32 f32_ArcTan2 ( f32 f32Numerator,     /* numerator argument */
                  f32 f32Denominator )  /* denominator argument */
{
   f32 f32ArcTan = ZEROF ;                   /* arctan result */
   f32 f32InputValue = ZEROF ;               /* numnerator/denominator */
   f32 f32AbsNumerator = f32Numerator ;     /* absolute value of numerator */
   f32 f32AbsDenominator = f32Denominator ; /* absolute value of numerator */
   f32 f32Negator = ONEF ; /* negation product */

   /* get the absolute values of the inputs */
   if ( f32AbsNumerator < TRIG_ZERO )
   {
      f32AbsNumerator = -f32AbsNumerator ;
      f32Negator = NEGATIVE_ONE  ;
   } /* else numerator positive, so no change */
   else
   { }

   if ( f32AbsDenominator < TRIG_ZERO )
   {
      f32AbsDenominator = -f32AbsDenominator ;
      f32Negator *= NEGATIVE_ONE  ;
   }/* else denominator positive, so no change */
   else
   { }

   /* Handle special cases */
   if ( f32AbsNumerator < TRIG_ZERO_LIMIT ) /* numerator zero */
   {
      if ( f32Denominator < TRIG_ZERO ) /* negative denominator */
      {
         f32ArcTan = -TRIG_PI ;
      }
      else /* positive or zero denominator */
      {
         f32ArcTan = TRIG_ZERO ;
      }
   }
   else if ( f32AbsDenominator < TRIG_ZERO_LIMIT ) /* denominator zero */
   {
      if ( f32Numerator < TRIG_ZERO ) /* negative numerator */
      {
         f32ArcTan = -TRIG_PI_OVER_2 ;
      }
      else
      {
         f32ArcTan = TRIG_PI_OVER_2 ;
      }
   }
   else /* calculate f32ArcTan */
   {
      /* select the algorithm to use based on numerator:denominator ratio*/
      if ( f32AbsNumerator < f32AbsDenominator )
      {
         /* change inputs to a single value*/
         f32InputValue = f32AbsNumerator / f32AbsDenominator ;

         f32ArcTan = ( ARCTAN_COEFF_0 + f32InputValue *
                     ( ARCTAN_COEFF_1 + f32InputValue *
                     ( ARCTAN_COEFF_2 + f32InputValue *
                     ( ARCTAN_COEFF_3 + f32InputValue *
                     ( ARCTAN_COEFF_4 + f32InputValue *
                     ( ARCTAN_COEFF_5 + f32InputValue *
                     ( ARCTAN_COEFF_6 + f32InputValue *
                     ( ARCTAN_COEFF_7 + f32InputValue *
                     ( ARCTAN_COEFF_8 ) ) ) ) ) ) ) ) ) ;

         /* handle negative input*/
         f32ArcTan *= f32Negator ;
      }
      else
      {
         /* change inputs to a single value */
         f32InputValue = f32AbsDenominator / f32AbsNumerator ;

         if ( f32InputValue < TRIG_ZERO_LIMIT )
         {
            f32ArcTan = TRIG_ZERO ;
         }
         else
         {
            f32ArcTan = ( ARCTAN_COEFF_0 + f32InputValue *
                        ( ARCTAN_COEFF_1 + f32InputValue *
                        ( ARCTAN_COEFF_2 + f32InputValue *
                        ( ARCTAN_COEFF_3 + f32InputValue *
                        ( ARCTAN_COEFF_4 + f32InputValue *
                        ( ARCTAN_COEFF_5 + f32InputValue *
                        ( ARCTAN_COEFF_6 + f32InputValue *
                        ( ARCTAN_COEFF_7 + f32InputValue *
                        ( ARCTAN_COEFF_8 ) ) ) ) ) ) ) ) ) ;
          }

          f32ArcTan = TRIG_PI_OVER_2 - f32ArcTan ;

          /* handle negative input*/
          f32ArcTan *= f32Negator ;
      }

      /* adjust return value to indicate the correct quadrant*/
      if ( f32Denominator < TRIG_ZERO ) /* quadrant II & III : add or subtract 180 degrees*/
      {
         if ( f32Numerator < TRIG_ZERO )
         {
            f32ArcTan -= TRIG_PI ;
         }
         else
         {
            f32ArcTan += TRIG_PI ;
         }
      }
      /* quadrant IV : add 360 degrees already taken care of with the f32Negator*/
      else
      { }
   }

   return ( f32ArcTan ) ;
   /** @return \a f32ArcTan - Arctangent (atan2) of the given inputs */
} /* end ArcTan() */



/**
 * @brief This function calculates arcsine.
 *
 * @par <b> Detailed Description: </b>
 *     Uses a polynomial approximation to get the arcsine value.
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       INT1.0102.S.IMU.4.015 \n
 *          INT1.0102.S.DSP.7.015 \n
 *
 * @param [in] f32InputValue  input value
 */

f32 f32_ArcSin ( f32 f32InputValue ) /* input value */
{
   f32 f32ArcSinValue = ZEROF ;    /* the arcsine value to return  */
   f32 f32Negator = ONEF ;  /* used to make return negative when input is negative*/

   /* Validate input */
   if (( f32InputValue < NEGATIVE_ONE  ) || ( f32InputValue > ONE ))
   {
      f32ArcSinValue = ARCSIN_MAX_VALUE ;
   }
    /* calculate arcsine */
   else
   {
      /* take care of negative input*/
      if ( f32InputValue < TRIG_ZERO )
      {
         f32Negator = NEGATIVE_ONE ;
         f32InputValue = -f32InputValue ;
      }
      else
      { }

      if ( f32InputValue < ARCSIN_INTERVAL_B_UPPER_LIMIT )
      {
         if ( f32InputValue < ARCSIN_INTERVAL_A_UPPER_LIMIT ) /* Interval A: asin (0.0 to 0.9)*/
         {
            f32ArcSinValue = ( ARCSINE_COEFF_0_A + f32InputValue *
                             ( ARCSINE_COEFF_1_A + f32InputValue *
                             ( ARCSINE_COEFF_2_A + f32InputValue *
                             ( ARCSINE_COEFF_3_A + f32InputValue *
                             ( ARCSINE_COEFF_4_A + f32InputValue *
                             ( ARCSINE_COEFF_5_A + f32InputValue *
                             ( ARCSINE_COEFF_6_A + f32InputValue *
                             ( ARCSINE_COEFF_7_A + f32InputValue *
                             ( ARCSINE_COEFF_8_A + f32InputValue *
                             ( ARCSINE_COEFF_9_A + f32InputValue *
                             ( ARCSINE_COEFF_10_A + f32InputValue *
                             ( ARCSINE_COEFF_11_A + f32InputValue *
                             ( ARCSINE_COEFF_12_A + f32InputValue *
                             ( ARCSINE_COEFF_13_A + f32InputValue *
                             ( ARCSINE_COEFF_14_A + f32InputValue *
                             ( ARCSINE_COEFF_15_A + f32InputValue *
                             ( ARCSINE_COEFF_16_A + f32InputValue *
                             ( ARCSINE_COEFF_17_A ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ;
         }
         else /* Interval B: asin (0.91 to 0.96)*/
         {
            f32ArcSinValue = ( ARCSINE_COEFF_0_B + f32InputValue *
                             ( ARCSINE_COEFF_1_B + f32InputValue *
                             ( ARCSINE_COEFF_2_B + f32InputValue *
                             ( ARCSINE_COEFF_3_B + f32InputValue *
                             ( ARCSINE_COEFF_4_B + f32InputValue *
                             ( ARCSINE_COEFF_5_B + f32InputValue *
                             ( ARCSINE_COEFF_6_B + f32InputValue *
                             ( ARCSINE_COEFF_7_B + f32InputValue *
                             ( ARCSINE_COEFF_8_B + f32InputValue *
                             ( ARCSINE_COEFF_9_B + f32InputValue *
                             ( ARCSINE_COEFF_10_B + f32InputValue *
                             ( ARCSINE_COEFF_11_B + f32InputValue *
                             ( ARCSINE_COEFF_12_B ) ) ) ) ) ) ) ) ) ) ) ) ) ;
         }
      }
      else
      {
         if ( f32InputValue < ARCSIN_INTERVAL_D_UPPER_LIMIT )
         {
            if ( f32InputValue < ARCSIN_INTERVAL_C_UPPER_LIMIT ) /* Interval C: asin (0.961 to 0.98)*/
            {
               f32ArcSinValue = ( ARCSINE_COEFF_0_C + f32InputValue *
                                ( ARCSINE_COEFF_1_C + f32InputValue *
                                ( ARCSINE_COEFF_2_C + f32InputValue *
                                ( ARCSINE_COEFF_3_C + f32InputValue *
                                ( ARCSINE_COEFF_4_C + f32InputValue *
                                ( ARCSINE_COEFF_5_C + f32InputValue *
                                ( ARCSINE_COEFF_6_C + f32InputValue *
                                ( ARCSINE_COEFF_7_C + f32InputValue *
                                ( ARCSINE_COEFF_8_C + f32InputValue *
                                ( ARCSINE_COEFF_9_C + f32InputValue *
                                ( ARCSINE_COEFF_10_C + f32InputValue *
                                ( ARCSINE_COEFF_11_C + f32InputValue *
                                ( ARCSINE_COEFF_12_C ) ) ) ) ) ) ) ) ) ) ) ) ) ;
            }
            else /* Interval D: asin (0.981 to 0.9975)*/
            {
               f32ArcSinValue = ( ARCSINE_COEFF_0_D + f32InputValue *
                                ( ARCSINE_COEFF_1_D + f32InputValue *
                                ( ARCSINE_COEFF_2_D + f32InputValue *
                                ( ARCSINE_COEFF_3_D + f32InputValue *
                                ( ARCSINE_COEFF_4_D + f32InputValue *
                                ( ARCSINE_COEFF_5_D + f32InputValue *
                                ( ARCSINE_COEFF_6_D + f32InputValue *
                                ( ARCSINE_COEFF_7_D + f32InputValue *
                                ( ARCSINE_COEFF_8_D + f32InputValue *
                                ( ARCSINE_COEFF_9_D + f32InputValue *
                                ( ARCSINE_COEFF_10_D + f32InputValue *
                                ( ARCSINE_COEFF_11_D + f32InputValue *
                                ( ARCSINE_COEFF_12_D + f32InputValue *
                                ( ARCSINE_COEFF_13_D + f32InputValue *
                                ( ARCSINE_COEFF_14_D + f32InputValue *
                                ( ARCSINE_COEFF_15_D + f32InputValue *
                                ( ARCSINE_COEFF_16_D + f32InputValue *
                                ( ARCSINE_COEFF_17_D + f32InputValue *
                                ( ARCSINE_COEFF_18_D + f32InputValue *
                                ( ARCSINE_COEFF_19_D + f32InputValue *
                                ( ARCSINE_COEFF_20_D + f32InputValue *
                                ( ARCSINE_COEFF_21_D + f32InputValue *
                                ( ARCSINE_COEFF_22_D + f32InputValue *
                                ( ARCSINE_COEFF_23_D ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ;
            }
         }
         else
         {
            if ( f32InputValue < ARCSIN_INTERVAL_E_UPPER_LIMIT ) /* Interval E: asin (0.9976 to 0.9999)*/
            {
               f32ArcSinValue = ( ARCSINE_COEFF_0_E + f32InputValue *
                                ( ARCSINE_COEFF_1_E + f32InputValue *
                                ( ARCSINE_COEFF_2_E + f32InputValue *
                                ( ARCSINE_COEFF_3_E + f32InputValue *
                                ( ARCSINE_COEFF_4_E + f32InputValue *
                                ( ARCSINE_COEFF_5_E ) ) ) ) ) ) ;
            }
            else
            {
               /* close to 1, so make it pi/2*/
               f32ArcSinValue = TRIG_PI_OVER_2 ;
            }
         }
      }

      /* multiply by f32Negator to handle negative input*/
      f32ArcSinValue *= f32Negator ;
   }

   return ( f32ArcSinValue ) ;
   /** @return \a f32ArcSinValue - ArcSine of f32InputValue. */
} /* end ArcSin() */

/* end of file */
















