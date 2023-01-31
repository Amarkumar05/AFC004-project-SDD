/** @file COMVerifyNonVolatileMemoryCRC.h
 *  @brief Header file for COMVerifyNonVolatileMemoryCRC.c
 *
 *  @par <b> Description: </b>
 *     - CRC is computed in 40-byte blocks defined by the symbol MAXIMUM_BYTES_FOR_CRC
 *
 *  @date 14Jun2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 14Jun2006 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> PR_CR_032 and PR_CR_012
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 02Dec2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *        <tr><td> 26Jan2009 <td>  <center> 1.2</center>    <td> <center>JD</center> <td> ADHR327: PR_LLR_COM_016
 *        <tr><td> 19Feb2009 <td>  <center> 1.3 </center>   <td> <center>KN</center> <td> ADHR343
 *        <tr><td> 27Jan2019 <td>  <center> 2.0 </center>   <td> <center>BA</center> <td> Updated verify prog. memory CRC function
 *                                                                                        to use passed addresses
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMVerifyNonVolatileMemoryCRC.h 6187 2009-02-19 22:21:09Z karthikn $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006-2019.  Archangel Systems, Inc. </i> <BR>
 */

#ifndef COMVERIFYNONVOLATILEMEMORYCRC_H
#define COMVERIFYNONVOLATILEMEMORYCRC_H

#include "COMtypedefs.h"

#ifndef TIDSP

/**
 * This value represents the LOW WORD.
 */
#define LOW_WORD 0

/**
 * This value represents the HIGH WORD.
 */
#define HIGH_WORD 1
/**
 * This value represents Hexadecimal value 0x00000000.
 */
#define HEX_00000000  0x00000000

extern u16 u16_ReadNonVolatileLowWord ( u32 u32Address ) ; /* NonVolatile Memory Address */

#endif

/**
 * This value represents the maximum bytes for Cyclic redundancy check.
 */
#define MAXIMUM_BYTES_FOR_CRC 40

#define PROGRAM_MEM_ADDRESS_LIMIT 0x17FFE

#ifndef TIDSP

#define EEPROM_MEM_ADDRESS_LIMIT  0x7FFFFE

#else

#define EEPROM_MEM_ADDRESS_LIMIT  0x9004FFFE

#endif

/* Use this function to verify the CRC of the program memory */
u8 u8_VerifyProgramMemoryCRC ( u32 u32StartAddress, u32 u32EndAddress, u32 u32CRCAddress ) ;

u8 u8_VerifyEEPROMCRC ( u32 u32StartAddress, /* First EEPROM Address in range of addresses to verify */
                        u32 u32EndAddress, /* Last EEPROM Address in range of addresses to verify */
                        u32 u32CRC ) ; /* The computed CRC will be compared with this CRC */

u32 u32_ComputeEEPROMCRC ( u32 u32StartAddress, /* First EEPROM Address in range of addresses to verify */
                           u32 u32EndAddress ) ; /* Last EEPROM Address in range of addresses to verify */

#endif

/* End of COMVerifyNonVolatileMemoryCRC.h header file. */