/**
 *  @file COMDSPicNonVolatileMemRead.s
 *  @brief This file contains low level functions for doing the following:<BR>
 *         Reading a word from eeprom and Reading the upper and lower word from program memory.
 *
 *  @date 22Nov2005
 *
 *  @author Stephen Hallacy
 *
 *  @par <b> Description: </b>
 *     - Reads the Lower Word from the DSPics NonVolatile Memory.
 *     - Reads the Upper Word from the DSPics NonVolatile Memory.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _u16_ReadNonVolatileLowWord
 *     - _u16_ReadNonVolatileHighWord
 *
 *  @par <b> Change History: </b> <BR>
 *     This file is part of the compact math library for the dsPIC30.
 *     (c) Microchip Technology. 2003.
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 22Nov2005 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 16Sep2008  <td> <center>  "  </center>   <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 03Nov2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281: PR_CR_268
 *        <tr><td> 19Feb2009 <td>  <center> 1.2 </center>   <td> <center>KN</center> <td> ADHR343
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMDSPicNonVolatileMemRead.s 6187 2009-02-19 22:21:09Z karthikn $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

.text

.include "COMDSPicNonVolatileMemRead.inc"
	
;***********  Variable Declarations  ************


/**
 * @brief This function reads a single 16-bit value from Non-volatile memory.
 *
 * @par <b> Detailed Description: </b>
 *      - This function takes 1 parameter, the 32 bit Non-Volatile address.
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *	    REL.0135.S.COM.7.003.D02 \n		
 *
 * @par <b> Parameters: </b> <br>
 *    <i> None </i> (void)
 */

_u16_ReadNonVolatileLowWord:
   PUSH W4
   MOV W1,TBLPAG
   TBLRDL [W0],W4
   MOV W4,W0
   POP W4
   return



/**
 * @brief This function reads a single 16-bit value from Non-volatile memory.
 *
 * @par <b> Detailed Description: </b>
 *      - This function takes 1 parameter, the 32 bit Non-Volatile address.
 *      - Note: This function should only be used for program memory.
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *	    REL.0135.S.COM.7.003.D03 \n
 *
 * @par <b> Parameters: </b> <br> 
 *    <i> None </i> (void)
 */

_u16_ReadNonVolatileHighWord:
   PUSH W4
   MOV W1,TBLPAG
   TBLRDH [W0],W4
   MOV W4,W0
   POP W4
   return

;   END OF FILE (COMDSPicNonVolatileMemRead.s)
