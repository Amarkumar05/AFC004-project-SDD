/**
 *  @file COMIIRFilter.c
 *  @brief Contains IIR filtering functions.
 *
 *  @date 26Jun2006
 *  @author Karthik Narayanan
 *
 *  @par <b> Description: </b>
 *      - This module needs external instantiations of IIR filter structs.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - f32_IIRFilter
 *     - v_IIRReset
 *     - v_IIRPreload
 *     - v_IIRSetup
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 26Jun2006 <td> <center>Draft</center>   <td> <center>KN</center> <td> Initial Draft
 *        <tr><td> 10Jul2006 <td>   <center>"</center>     <td> <center>KN</center> <td> Replaced literals with symbols.
 *        <tr><td> 15Jan2007 <td>   <center>"</center>     <td> <center>KN</center> <td> Replaced literals with symbols.
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM,PR_CR_017 and PR_CR_004
 *        <tr><td> 17Sep2008 <td>   <center>"</center>     <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 31Oct2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281: PR_CR_175
 *        <tr><td> 10Dec2008 <td>  <center> 1.2 </center>   <td> <center>JD</center> <td> ADHR280: PR_LLR_061,PR_LLR_062,
 *                                                                                                 PR_LLR_063,PR_LLR_083
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMIIRFilter.h 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

/**************  Include Files  ************************/
#include "COMIIRFilter.h"
#include "COMDefines.h"

/*
 **  Local Constants, Enums, Typedefs, and Prototypes  ==========================
 */

/**
 * @brief This function implements an IIR filter.
 *
 * @par <b> Detailed Description: </b>
 *  Implements y(k) = K2*x(k) + K1*y(k-1)
 *
 * @author Karthik Narayanan
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.15.001 \n
 *       REL.0135.S.DSP.16.001 \n
 *
 *
 * @param [in] f32Input  input value to be filtered
 * @param [out] *psIIRstruct_ptr  pointer to the filter struct
 */


f32 f32_IIRFilter ( f32 f32Input ,                    /* input value to be filtered */
                sIIR_struct *psIIRstruct_ptr )   /* pointer to the filter struct */
{
   f32 f32ReturnValue = ZEROF ; /* filtered output */


   if ( psIIRstruct_ptr->u8Preload == PRELOAD_FLAG_SET )
   {
      v_IIRPreload ( f32Input ,              /* value to be loaded into previous output */
                    psIIRstruct_ptr ) ;     /* pointer to the IIR struct */
   }
   else
   {}

    /**
    Implement filter
    **/
    /*f32ReturnValue = input ;
    f32ReturnValue += psIIRstruct_ptr->Coef * psIIRstruct_ptr->PastOutput ;
    f32ReturnValue *= psIIRstruct_ptr->Gain ;*/

   f32ReturnValue = ( psIIRstruct_ptr->f32K2 * f32Input ) + ( psIIRstruct_ptr->f32K1 * psIIRstruct_ptr->f32PastOutput ) ;

    /**
    Rotate PastValues buffer
    **/
   psIIRstruct_ptr->f32PastOutput = f32ReturnValue ;

   return f32ReturnValue ;/** @return \a f32ReturnValue - f32 indicating the filtered value */

}  /* end f32_IIRFilter() */

/**
 * @brief This function initializes the filter coefficients of the I order IIR filter.
 *
 * @par <b> Detailed Description: </b>
 *  Coefficient1 is the scaling on the previous output and Coefficient2 is the scaling on the input.
 *
 * @author Karthik Narayanan
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.15.001.D01 \n
 *       REL.0135.S.DSP.16.001.D03 \n
 *
 * @param [out] *psIIRstruct_ptr  pointer to the IIR struct
 * @param [in] f32Coefficient1  Feedback coefficient K1
 * @param [in] f32Coefficient2  Input coefficient K2
 */

void v_IIRSetup ( sIIR_struct *psIIRstruct_ptr ,  /* pointer to the IIR struct */
                  f32 f32Coefficient1 ,           /* Feedback coefficient K1 */
                  f32 f32Coefficient2 )          /* Input coefficient K2 */
{
   psIIRstruct_ptr->f32K1 = f32Coefficient1 ;
   psIIRstruct_ptr->f32K2 = f32Coefficient2 ;

   return ;/** @return \a None (void) */

}  /* end v_IIRSetup() */

/**
 * @brief This function clears the IIR filter history.
 *
 * @par <b> Detailed Description: </b>
 *  Sets the filter history to zero and the preload flag to 1.
 *
 * @author Karthik Narayanan
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.15.001.D02 \n
 *       REL.0135.S.DSP.16.001.D01 \n
 *
 * @param [out] *psIIRstruct_ptr  pointer to the IIR struct
 */

void v_IIRReset ( sIIR_struct *psIIRstruct_ptr ) /* pointer to the IIR struct */
{

   psIIRstruct_ptr->f32PastOutput = ZEROF ;
   psIIRstruct_ptr->u8Preload = ( u8 ) PRELOAD_FLAG_SET ;

   return ;/** @return \a None (void) */

}  /* end v_IIRReset() */

/**
 * @brief This function pre-loads the IIR filter history.
 *
 * @par <b> Detailed Description: </b>
 *  Sets the filter history to the input value and the preload flag to 0.
 *
 * @author Karthik Narayanan
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.15.001.D03 \n
 *       REL.0135.S.DSP.16.001.D02 \n
 *
 * @param [in] f32Val  value to be loaded into previous output
 * @param [out] *psIIRstruct_ptr  pointer to the IIR struct
 */

void v_IIRPreload ( f32 f32Val ,                    /* value to be loaded into previous output */
                    sIIR_struct *psIIRstruct_ptr ) /* pointer to the IIR struct */
{

   psIIRstruct_ptr->f32PastOutput = f32Val ;
   psIIRstruct_ptr->u8Preload = PRELOAD_FLAG_CLEAR ;

   return ;/** @return \a None (void) */

}  /* end v_IIRPreload() */



/*
** end of file
*/

