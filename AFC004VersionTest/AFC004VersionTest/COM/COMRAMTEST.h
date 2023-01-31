/** @file COMRAMTEST.h
 *  @brief This file implements the RAM test.
 *
 *  @par <b> Description: </b>
 *     - This file implements the RAM test.
 *
 *  @date 06Jul2006
 *  @author Vamshi Gangumalla
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 06Jul2006 <td> <center>Draft</center>   <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 11Apr2008 <td> <center>Draft</center>   <td> <center>VG</center> <td> CAR332
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 20Nov2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMRAMTEST.h 6008 2008-12-09 23:01:49Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006.  Archangel Systems, Inc. </i> <BR>
 */

#ifndef   COMRAMTEST_H
   #define COMRAMTEST_H
/*   This function performs the Random Access Memory Test at boot.*/
/*****************************************************************
RAM test function works only when in programming mode for the ICD.
It doesn't work ( i.e. the function fails the memory test ) when in
debug mode, as a section of the RAM is used by the ICD to perform debug tasks.
******************************************************************/
   u16 u16_asmRAMTestResult (     /* Function to perform the RAM test. */
      u16 u16StartAddr ,       /* Start address of the RAM test. */
      u16 u16EndAddr ,         /* End address of the RAM test. */
      u16 u16TestWord1 ,       /* Ram Test Memory Write Word 1. */
      u16 u16ResultWord1 ,     /* Ram Test Memory Read Word 1. */
      u16 u16TestWord2 ,       /* Ram Test Memory Write Word 2. */
      u16 u16ResultWord2 ) ;  /* Ram Test Memory Read Word 2. */
#endif

/* End of COMRAMTest.h Module. */


