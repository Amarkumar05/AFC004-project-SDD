///** @file COMEEPROM.h
// *  @brief Header file for COM EEPROM
// *
// *  @par <b> Description: </b> 
// *       - Contains different module's EEPROM h file.
// *
// *  @date 08Dec2008
// *  @author Yijing Chen
// *
// *  @par <b> Change History: </b> <BR>
// *     <table>
// *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
// *        <tr><td> 05Dec2008 <td>  <center> 1.0 </center>   <td> <center>YC</center> <td> Baseline Release 
// *                                                                                        (ADHR281: Code review,duplicate name)
// *        <tr><td> 13Feb2009 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR340:PR_CR_331
// *        <tr><td> 27Jan2019 <td>  <center> 2.0 </center>   <td> <center>BA</center> <td> Improved
// *     </table>
// *  <BR>
// *
// *  @note $Id: COMEEPROM.h 6176 2009-02-13 22:37:52Z yijing $ <BR>
// *  @note
// *  <i> All rights reserved.  Copyright 2005-2019.  Archangel Systems, Inc. </i> <BR>
// */
//
//#ifndef    COMEEPROM_H
//#define COMEEPROM_H
//
//#if defined DSP
//#include <DSPEEPROMMap.h>
//
//#elif defined(__dsPIC30F6012__) || defined(__dsPIC30F6012A__) || defined(__dsPIC30F6014A__)
///* EEPROM Start Address. */
//#define EEPROM_START_ADDRESS              0x007FF000
//
///* EEPROM CRC Address Offset. */
//#define EEPROM_CRC_LOW_WORD_ADDR_OFFSET   0x00000FFE
//
///* EEPROM End Address. */
//#define EEPROM_END_ADDRESS                0x007FFFFE
//
//#else 
//#error "must define DSP or a supported dsPIC30F"
//
//#endif
//
//#endif
//
///* End of COMEEPROM.h header file. */