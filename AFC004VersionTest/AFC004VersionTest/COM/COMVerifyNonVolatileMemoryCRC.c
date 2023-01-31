/**
 *  @file COMVerifyNonVolatileMemoryCRC.c
 *  @brief This file contains functions for verifying both the EEPROM's and Program memory's CRC.
 *
 *  @date 11Jun2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Description: </b>
 *       - CRC is computed in 40-byte blocks defined by the symbol MAXIMUM_BYTES_FOR_CRC
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *       - u8_VerifyProgramCRC - Verifies Program Memory CRC
 *       - u8_VerifyEepromCRC - Verifies EEPROM Memory CRC
 *       - u32_ComputeEEPROMCRC - Computes EEPROM Memory CRC
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 11Jun2006 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM, PR_CR_004 and PR_CR_032
 *        <tr><td> 16Sep2008 <td>   <center>"</center>     <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 02Dec2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *        <tr><td> 10Dec2008 <td>  <center> 1.2 </center>   <td> <center>JD</center> <td> ADHR280: PR_LLR_054
 *        <tr><td> 06Jan2009 <td>  <center> 1.3 </center>   <td> <center>JD</center> <td> ADHR315: PR_LLRBT_140
 *        <tr><td> 26Jan2009 <td>  <center> 1.4</center>    <td> <center>JD</center> <td> ADHR327: PR_LLR_COM_016
 *        <tr><td> 19Feb2009 <td>  <center> 1.5 </center>   <td> <center>KN</center> <td> ADHR343
 *        <tr><td> 02Mar2009 <td>  <center> 1.6 </center>   <td> <center>YC</center> <td> ADHR508
 *        <tr><td> 21Apr2009 <td>  <center> 1.7 </center>   <td> <center>KN</center> <td> ADHR698:PR_LLR_COM_027
 *        <tr><td> 27Apr2009 <td>  <center> 1.8 </center>   <td> <center>YC</center> <td> ADHR696:PR_LLRBT_140
 *        <tr><td> 06May2009 <td>  <center> 1.9 </center>   <td> <center>YC</center> <td> PR_LLR_054
 *        <tr><td> 27Jan2019 <td>  <center> 2.0 </center>   <td> <center>BA</center> <td> Updated verify prog. memory CRC function
 *                                                                                        to use passed addresses
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMVerifyNonVolatileMemoryCRC.c 6322 2009-05-06 14:54:27Z yijing $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008-2019.  Archangel Systems, Inc. </i> <BR>
 */

/**************  Include Files  ************************/
#include "COMVerifyNonVolatileMemoryCRC.h"
#include "COMDefines.h"
//#include "COMReadEEPROM.h"
#include "COMCRCModule.h"

#ifndef TIDSP
//#include "COMEEPROM.h"
#include "COMReadProgramMemory.h"
#endif

/**************  Module Level Function Prototypes  *****/

/**************  Module Level Variables  **************/


/**********  Constants, Enums, and Typedefs  ***********/


/***********  Global Variable Declarations  ************/

#ifndef TIDSP
/**
 * @brief Computes the CRC over the specified program memory range and compares result to a previously computed CRC value.
 *
 * @par <b> Detailed Description: </b>
 * Step 1: Get StartAddress, EndAddress., and initial CRC.
 * Step 2: Init ByteIndex, Address to zero.
 * Step 3: Init pointer to program instruction value to zero.
 * Step 4: Init a Done flag and a return value flag to zero.
 * Step 5: Init computed CRC value to zero
 * Step 6: IF EndAddress is greater than (StartAddress + 2), THEN go to Step 7. ELSE go to Step 17?
 * Step 7: IF Address is less than or equal to EndAddress, set ByteIndex to zero.
 * Step 8: IF ByteIndex is less than 40 bytes, THEN go to Step 9. ELSE go to Step 14.
 * Step 9. Read program memory, call function u32_ReadProgramMemory
 * Step 10. Store 4 bytes form program memory into ByteArray, and increase ByteIndex by 4.
 * Step 11. IF Address is equal to the EndAddress, THEN go to Step 12. ELSE go to Step 13
 * Step 12. Set the Done flag to True, THEN go to Step 14.
 * Step 13. Address is added to 2, THEN go to Step 8.
 * Step 14. Computed CRC value, call function u32_Calculate32BitCRC.
 * Step 15. IF Done flag is set True, THEN go to step 16. ELSE go to Step 7.
 * Step 16. If  computed CRC value is equal to initial CRC, THEN set the return  flag to success,ELSE goto next step
 * Step 17. Set the return  flag to FAILURE
 * Step 18. EXIT, and return the return flag.
 *
 * u32CRC = Previously Computed (On Host PC) CRC of Program memory that starts at address u32StartAddress and ends at
 * address u32EndAddress. The Value at the end address is included in the CRC computation.
 *
 * @author Stephen Hallacy, Brett Augsburger
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.7.003 \n
 *
 * @param [in] u32StartAddress   First Program Address in range of addresses to verify
 * @param [in] u32EndAddress     Last Program Address in range of addresses to verify
 * @param [in] u32CRCAddress     Address holding the previously computed CRC
 */
u8 u8_VerifyProgramMemoryCRC ( u32 u32StartAddress, u32 u32EndAddress, u32 u32CRCAddress )
{
   u32 u32CurrentAddress ; /* Holds the working program memory address */
   u16 u16BufferIndex ; /* index for u8aBuffer */
   u32_val u32ProgramInstructionValue ; /* Value at the current memory address being accessed */
   u8 u8aBuffer[MAXIMUM_BYTES_FOR_CRC] ; /* Buffer for read program data */
   u32 u32ComputedCRC = ZERO ; /* Holds the computed CRC */
   u8 u8ReturnValue = ZERO ; /* pass/fail return value */
   u32_val u32StoredCRC; /* Holds the stored CRC */

   /* Initialize working address to specified start address */
   u32CurrentAddress = u32StartAddress ;

   /* Compute CRC over address range u32StartAddress to u32EndAddress. This calculation is performed piecewise. */
   while ( u32CurrentAddress <= u32EndAddress )
   {
      u16BufferIndex = ZERO ;

      /* Fill buffer up to maximum or end address if reached */
      while ( ( u16BufferIndex < MAXIMUM_BYTES_FOR_CRC ) && ( u32CurrentAddress <= u32EndAddress ) )
      {
         /* Read Program Memory */
         u32ProgramInstructionValue.Val = u32_ReadProgramMemory ( u32CurrentAddress ) ;

         /* Copy to buffer */
         u8aBuffer[u16BufferIndex++] = u32ProgramInstructionValue.v[0] ;
         u8aBuffer[u16BufferIndex++] = u32ProgramInstructionValue.v[1] ;
         u8aBuffer[u16BufferIndex++] = u32ProgramInstructionValue.v[2] ;
         u8aBuffer[u16BufferIndex++] = u32ProgramInstructionValue.v[3] ;

         u32CurrentAddress += TWO ;
      }
      /* Calculate CRC for this packet of data. CRC calculation from previous packet is carried over. */
      u32ComputedCRC = u32_Calculate32BitCRC ( u8aBuffer, ZERO, u16BufferIndex - ONE, u32ComputedCRC ) ;
   } /* End while ( u32Address <= u32EndAddress ) */
   
   u32StoredCRC.word.LW = u16_ReadNonVolatileLowWord ( u32CRCAddress ) ;
   u32StoredCRC.word.HW = u16_ReadNonVolatileLowWord ( u32CRCAddress + 2 ) ;

   /* Compare CRC value to previously computed 32-bit CRC stored in program memory */
   if ( u32ComputedCRC == u32StoredCRC.Val )
   {
      u8ReturnValue = SUCCESS ;
   }
   else
   {
      u8ReturnValue = FAILURE ;
   }

   return u8ReturnValue ;
   /** @return \a SUCCESS if Program CRC equals u32CRC. Otherwise, Returns FAILURE. */
} /* end u8_VerifyProgramCRC */

#endif

/**
 * @brief To Determine if the u32ProgramCRC equals the EEPROM CRC.
 *
 * @par <b> Detailed Description: </b>
 * Step 1: Get StartAddress, EndAddress and the initial CRC.
 * Step 2: Init ReturnValue to zero.
 * Step 3: Init computed CRC value to zero.
 * Step 4: To compute EEPROM CRC, call function u32_ComputeEEPROMCRC.
 * Step 5: Compare computed CRC with initial CRC.
 * Step 6: SUCCESS if the computed EEPROM CRC equals initial CRC. Otherwise, Returns FAILURE
 * Step 7. EXIT, and return the ReturnValue value.
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.7.004 \n
 *       REL.0135.S.DSP.15.003 \n
 *       REL.0135.S.DSP.15.004 \n
 *
 * @param [in] u32StartAddress  First EEPROM Address in range of addresses to verify
 * @param [in] u32EndAddress  Last EEPROM Address in range of addresses to verify
 * @param [in] u32CRC  The computed CRC will be compared with this CRC
 */

//u8 u8_VerifyEEPROMCRC ( u32 u32StartAddress, /* First EEPROM Address in range of addresses to verify */
//                        u32 u32EndAddress, /* Last EEPROM Address in range of addresses to verify */
//                        u32 u32CRC ) /* The computed CRC will be compared with this CRC */
//{
//   u8 u8ReturnValue = FAILURE ; /* pass/fail return value */
//
//   if ( u32_ComputeEEPROMCRC ( u32StartAddress, u32EndAddress ) == u32CRC )
//   {
//      u8ReturnValue = SUCCESS ;
//   }
//   else
//   {
//      u8ReturnValue = FAILURE ;
//   }
//
//   return u8ReturnValue ;
//   /** @return \a u8ReturnValue - SUCCESS if the EEPROM CRC equals u32CRC. Otherwise, Returns FAILURE. */
//} /* end u8_VerifyEEPROMCRC */

/**
 * @brief Computes EEPROM CRC.
 *
 * @par <b> Detailed Description: </b>
 * Computes the CRC of the 16-bit sequence between the addresses by reading 40-byte blocks.
 * Detailed Description:
 * Step 1: Get StartAddress and EndAddress.
 * Step 2: Init ByteIndex, Address to zero.
 * Step 3: Init pointer to program instruction value to zero.
 * Step 4: Init computed CRC value to zero.
 * Step 5: IF Address is less than or equal to EndAddress, THEN set ByteIndex to zero. ELSE go to Step 12
 * Step 6: IF ByteIndex is less than 40 bytes, THEN go to Step 7. ELSE go to Step 11.
 * Step 7. Read the 16-bit value from EEPROM at current working address.
 * Step 8. Copy the 16-bit data from previous step byte-wise into ByteArray, and increase ByteIndex by 2.
 * Step 9. IF Address is greater than or equal to EndAddress, THEN go to Step 11. ELSE go to Step 10
 * Step 10. Increment Address by 2, THEN go to Step 6.
 * Step 11. Call u32_Calculate32BitCRC to perform CRC calculations for data currently in buffer, THEN go to step 5.
 * Step 12. Return the computed CRC value and exit function. *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.7.004.D01 \n
 *       REL.0135.S.DSP.15.003.D01
 *
 * @param [in] u32StartAddress  First EEPROM Address in range of addresses to verify
 * @param [in] u32EndAddress  Last EEPROM Address in range of addresses to verify
 */
//u32 u32_ComputeEEPROMCRC ( u32 u32StartAddress, /* First EEPROM Address in range of addresses to verify */
//                           u32 u32EndAddress ) /* Last EEPROM Address in range of addresses to verify */
//{
//   u32 u32CurrentAddress ; /* Holds the working EEPROM address */
//   u16 u16BufferIndex ; /* index for u8aBuffer */
//   u16_val u16EepromValue ; /* Value at the current memory address being accessed */
//   u8 u8aBuffer [ MAXIMUM_BYTES_FOR_CRC ] ; /* Buffer for read program data */
//   u32 u32ComputedCRC = ZERO ; /* Holds the computed CRC */
//
//   /* Initialize working address to specified start address */
//   u32CurrentAddress = u32StartAddress ;
//
//   /* Compute CRC over address range u32StartAddress to u32EndAddress. This calculation is performed piecewise. */
//   while ( u32CurrentAddress <= u32EndAddress )
//   {
//      u16BufferIndex = ZERO ;
//
//      /* Fill buffer up to maximum or stop at end address if reached */
//      while ( ( u16BufferIndex < MAXIMUM_BYTES_FOR_CRC ) && ( u32CurrentAddress <= u32EndAddress ) )
//      {
//         /* Read EEPROM */
//         u16EepromValue.Val = u16_ReadEEPROM ( u32CurrentAddress ) ;
//
//         /* Copy to buffer */
//         u8aBuffer [ u16BufferIndex++ ] = u16EepromValue.v[0] ;
//         u8aBuffer [ u16BufferIndex++ ] = u16EepromValue.v[1] ;
//
//         u32CurrentAddress += TWO ;
//      }
//      /* Calculate CRC for this packet of data. CRC calculation from previous packet is carried over. */
//      u32ComputedCRC = u32_Calculate32BitCRC ( u8aBuffer, ZERO, u16BufferIndex - ONE, u32ComputedCRC ) ;
//   }
//
//   return u32ComputedCRC ;
//   /** @return \a u32ComputedCRC - Return the 32-bit EEPROM CRC */
//} /* end u32_ComputeEEPROMCRC */

/* End of COMVerifyNonVolatileMemoryCRC.c */