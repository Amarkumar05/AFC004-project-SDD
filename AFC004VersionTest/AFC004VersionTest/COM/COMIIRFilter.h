/** @file COMIIRFilter.h
 *  @brief Contains prototypes of IIR filtering functions.
 *
 *  @par <b> Description: </b>
 *     - Implements a I-order IIR filter.
 *
 *  @date 26Jun2006
 *  @author Karthik Narayanan
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 26Jun2006 <td> <center>Draft</center>   <td> <center>KN</center> <td> Initial Draft
 *        <tr><td> 15Jan2007 <td>   <center>"</center>     <td> <center>KN</center> <td> Added defines PRELOAD_FLAG_SET and
 *                                                                                       PRELOAD_FLAG_CLEAR.
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM, PR_CR_032 and PR_CR_012
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 31Oct2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281: PR_CR_175
 *  </table>
 *  <BR>
 *  @note $Id: COMIIRFilter.h 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006.  Archangel Systems, Inc. </i> <BR>
 */

#ifndef _COMIIRFILTER_H
#define _COMIIRFILTER_H

/*
 *  Include Files  =============================================================
 */
#include "COMtypedefs.h"

/*
 *  DEFINE I ORDER IIR FILTER
 */
    /**
     * @brief I ORDER IIR FILTER
     */
typedef struct
{
 /**   @brief f32K1 description
 *   @par \b Usage:
 *      Filter coefficient 1.
 *   @par \b Units:
 *      Float
 *   @par <b>Valid Data Range:</b>
 *      <table>
 *         <tr><td> \a Minimum <td> 0.0
 *         <tr><td> \a Maximum <td> 1.0
 *         <tr><td> \a Initial \a Value <td> 0.0
 */
   f32   f32K1 ;          /* Filter coefficient 1 */
 /**   @brief f32K2 description
 *   @par \b Usage:
 *      Filter coefficient 2.
 *   @par \b Units:
 *      Float
 *   @par <b>Valid Data Range:</b>
 *      <table>
 *         <tr><td> \a Minimum <td> 0.0
 *         <tr><td> \a Maximum <td> 1.0
 *         <tr><td> \a Initial \a Value <td> 0.0
 */
   f32   f32K2 ;           /* Filter coefficient 2 */
 /**   @brief f32PastOutput description
 *   @par \b Usage:
 *      Filter history.
 *   @par \b Units:
 *      Float
 *   @par <b>Valid Data Range:</b>
 *      <table>
 *         <tr><td> \a Minimum <td>
 *         <tr><td> \a Maximum <td>
 *         <tr><td> \a Initial \a Value <td> 0.0
 */
   f32   f32PastOutput ;  /* Filter history */
 /**   @brief u8Preload description
 *   @par \b Usage:
 *      Variable to decide when to preload
 *   @par \b Units:
 *      Unsigned Integer
 *   @par <b>Valid Data Range:</b>
 *      <table>
 *         <tr><td> \a Minimum <td> 0
 *         <tr><td> \a Maximum <td> 1
 *         <tr><td> \a Initial \a Value <td> 0
 */
   u8    u8Preload ;      /* Variable to decide preload */

} sIIR_struct ;

   /*
    * This value represents the set value for preload variable.
    */
#define PRELOAD_FLAG_SET   1
   /*
    * This value represents the clear value for preload variable.
    */
#define PRELOAD_FLAG_CLEAR 0

 /*
  *  Function Prototypes  =======================================================
  */
 f32 f32_IIRFilter ( f32 f32Input ,                    /* input value to be filtered */
                     sIIR_struct *psIIRstruct_ptr ) ;  /* pointer to the filter struct */

 void v_IIRSetup ( sIIR_struct *psIIRstruct_ptr ,      /* pointer to the filter struct */
                   f32 f32Coefficient1 ,               /* filter coefficient K1 */
                   f32 f32Coefficient2 ) ;             /* filter coefficient K2 */

 void v_IIRReset ( sIIR_struct *psIIRstruct_ptr ) ;    /* pointer to the filter struct */

 void v_IIRPreload ( f32 f32Val ,                      /* value to be loaded into previous output */
                     sIIR_struct *psIIRstruct_ptr ) ;  /* pointer to the filter struct */


#endif /* _COMIIRFILTER_H */

/*
 * end of file
 */

