/**
 *  @file COMCRCModule.c
 *  @brief This file implements the 32 bit CRC Validation Module.
 *
 *  @date 18May2006
 *  @author Vamshi Gangumalla
 *
 *  @par <b> Description: </b>
 *     - This function creates the 32 bit CRC Remainder look up table.
 *     - This function calculates the 32 bit CRC using the CRC table.
 *     - This function loads the header and the CRC remainder key into the message.
 *     - This function verifies the header and the CRC remainder key of the message.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - v_Generate32BitCRCTable
 *     - u32_Calculate32BitCRC
 *     - v_LoadMessageHeaderAndCRCResult
 *     - u16_VerifyCRCofTheMessage
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 15May2006 <td> <center>Draft</center>   <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 10Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM
 *        <tr><td> 10Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> PR_CR_017
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> PR_CR_004
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> PR_CR_040
 *        <tr><td> 16Sep2008 <td>   <center>"</center>     <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 02Dec2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *        <tr><td> 10Dec2008 <td>  <center> 1.2 </center>   <td> <center>JD</center> <td> ADHR280: PR_LLR_044,PR_LLR_047
 *        <tr><td> 21Apr2009 <td>  <center> 1.3 </center>   <td> <center>YC</center> <td> ADHR696: PR_LLRBT_228
 *  </table>
 *  <br>
 *
 *  @note $Id: COMCRCModule.c 6284 2009-04-21 22:22:06Z yijing $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

/* Header file for the COM32BITCRC Module. */
   #include "COMCRCModule.h"

/*********************   Constant variables assignment header file.***********************/
/* This is the 32 bit CRC look up table for CRC remainder calculation function. */
   static u32 u32aCRCTable [ NUMBER_256 ] ; /**< File level variable. */


/**
 * @brief This function generates the lookup table for generating the Cyclical Redundancy Check ( CRC )
 *
 * @par <b> Detailed Description: </b>
 * CRC remainder is calculated for all the 256 combinations possible for a 'char data type' ( i.e. 8 bits ) data.
 * CRC is calculated by performing XOR on the CRC remainder for every occurrence of '1' in the CRC Stream of data.
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.7.005 \n
 *       REL.0135.S.DSP.8.009 \n
 *
 *
 * @param [in] u32CRCPolynomialKey 32-bit CRC polynomial key to generate CRC table
 */

void v_Generate32BitCRCTable ( u32 u32CRCPolynomialKey ) /* 32-bit CRC polynomial key to generate CRC table */
{
/* Variable to trace trough 8 bits of a character data type. */
   u16 u16BitTracer = ( u16 ) ZERO ;

/* Variable to trace trough the CRC look up table. */
   u16 u16CRCTableTracer = ( u16 ) ZERO ;

/* Variable for saving the calculated CRC remainder. */
   u32 u32CalculatedCRCRemainder = ( u32 ) ZERO ;

/* Loop for calculating the CRC remainder of all the possible combinations possible for a 8 bit data. */
   for ( u16CRCTableTracer = ( u16 ) ZERO ; u16CRCTableTracer <= ( u16 ) NUMBER_255 ; u16CRCTableTracer++ )
   {
/*    Initialize the CRC remainder to Zero. */
      u32CalculatedCRCRemainder = ( u32 ) ZERO ;

/*    Shift left CRC data by 24 bits to skip the preceeding 24 bits that would be Zeros and XOR with the CRC Remainder. */
      u32CalculatedCRCRemainder = ( ( u32 ) u16CRCTableTracer << ( u16 ) SHIFT_24 ) ^ u32CalculatedCRCRemainder ;

/*    Loop for calculating the CRC remainder by performing XOR on the remainder data for every occurrence of 1 in the 8 bits of
      data. */
      for ( u16BitTracer = ( u16 ) ONE ; u16BitTracer <= ( u16 ) EIGHT ; u16BitTracer++ )
      {
/*       Check wether the most significant byte of the 32 bit data is 1. */
         if ( ( u32CalculatedCRCRemainder & ( u32 ) MS_BIT ) != ( u32 ) ZERO )
         {
/*          If the most significant byte is 1, left shift the CRC remainder once and XOR the CRC remainder with the CRC key
            0x04C11DB7. */
            u32CalculatedCRCRemainder = ( u32CalculatedCRCRemainder << ( u16 ) ONE ) ^ u32CRCPolynomialKey ;
         }
         else
         {
/*          If the most significant byte is 0, left shift the CRC remainder by one. */
            u32CalculatedCRCRemainder = u32CalculatedCRCRemainder << ( u16 ) ONE ;
         }
      }
/*    Save the 32 bit CRC remainder generated in the CRC look up table. */
      u32aCRCTable  [  u16CRCTableTracer ]  = u32CalculatedCRCRemainder & ( u32 ) BIT8FF ;
   }

/* Return from the function v_Generate32BitCRCTable. */
   return;/** @return \a None (void) */
}
/* End v_Generate32BitCRCTable. */

/**
 * @brief This function calculates the 32 bit CRC remainder.
 *
 * @par <b> Detailed Description: </b>
 * This function calculates the CRC remainder using the 32 bit CRC remainder look up table.
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.14.002 \n
 *       REL.0135.S.COM.14.004 \n
 *
 * @param [out] *u8paCRCCalculationMessage CRC calculation Message
 * @param [in] u16StartPositionOfCRC Start Index position of CRC calculation Message
 * @param [in] u16StopPositionOfCRC CRC remainder for initilizing the CRC calculator
 * @param [in] u32InitilizeCRCRemainder CRC remainder for initilizing the CRC calculator
 */

u32 u32_Calculate32BitCRC (          /*   CRC remainder calculation function. */
      u8 *u8paCRCCalculationMessage , /*   CRC calculation Message. */
      u16 u16StartPositionOfCRC ,     /*   Start Index position of CRC calculation Message. */
      u16 u16StopPositionOfCRC ,      /*   End Index position of CRC calculation Message. */
      u32 u32InitilizeCRCRemainder ) /*   CRC remainder for initilizing the CRC calculator. */
{

/* This variable is used to trace the length of the CRC Message. */
   u16 u16MessageTracer = ( u16 ) ZERO ;

/* This variable is used to create the CRC member to be looked up in the CRC Table. */
   u32 u32CRCMember = ( u32 ) ZERO ;

/* Temporary variable for the CRC Remainder calculation. */
   u32 u32CalculatedCRCRemainder = u32InitilizeCRCRemainder ;

/* Loop for performs the CRC of the members in the Message starting with the start position and ending with the end position. */
   for ( u16MessageTracer = u16StartPositionOfCRC ; u16MessageTracer <= u16StopPositionOfCRC ; u16MessageTracer++ )
   {
/*    First calculate the index of the CRC look up table by performing XOR of the most significant bytes of the CRC table with
      the input data. */
      u32CRCMember = ( ( u32CalculatedCRCRemainder >> ( u16 ) SHIFT_24 ) ^
                       ( u32 ) u8paCRCCalculationMessage [ u16MessageTracer ] ) & ( u32 ) BIT2FF ;

/*    Then calculate the CRC remainder by performing XOR on the most significant byte of the CRC remainder with the data from the
      CRC look up table. */
      u32CalculatedCRCRemainder = ( ( u32CalculatedCRCRemainder << ( u16 ) SHIFT_8 ) ^
                                      u32aCRCTable [ u32CRCMember ] ) & ( u32 ) BIT8FF ;
   }

/* Return the calculated CRC remainder of the Message. */
   return ( u32CalculatedCRCRemainder ) ;
   /** @return \a u32CalculatedCRCRemainder - Return the calculated CRC remainder of the Message. */
}
/* End u32_Calculate32BitCRC. */


/**
 * @brief This function generates and loads the Header and CRC remainder bytes into the transmission.
 *
 * @par <b> Detailed Description: </b>
 * This function saves the Header OxFF in the first 6 bytes of the Message buffer and loads the CRC remainder in to
 * the last 4 bytes of the Message.
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.14.001 \n
 *       REL.0135.S.DSP.15.001
 *
 * @param [out] u8paCRCCalculationMessage The CRC calculation Message.
 * @param [in] u16LengthOfCRCMessageMinusOne  The length of CRC Message.
 * @param [in] u8HeaderByte Message Header Byte.
 * @param [in] u16HeaderSize Message Header Size.
 */
void v_LoadMessageHeaderAndCRCResult (
   u8 *u8paCRCCalculationMessage ,                /* The CRC calculation Message.*/
   u16 u16LengthOfCRCMessageMinusOne ,            /* The  length of CRC Message. */
   u8  u8HeaderByte ,                             /* Message Header Byte. */
   u16 u16HeaderSize )                           /* Message Header Size. */
{
/*   Temporary variable to extract 8 bits from the CRC 32 remainder. */
   u32 u32CRC8BitRemainder = ( u32 ) ZERO ;

/*   This Temporary variable is used in the header byte assigning for loop. */
   u16 u16MessageCounter = ( u16 ) ZERO ;

/*   This variable stores the CRC remainder calculated by the CRC calculation function. */
   u32 u32CalculatedCRCRemainder  = ( u32 ) ZERO ;

/*   For loop to load the 6 header bytes into the message buffer. */
   for ( u16MessageCounter = ( u16 ) ZERO ; u16MessageCounter < u16HeaderSize ; u16MessageCounter++ )
   {
   /*   Load OxFF header byte into the message buffer.*/
      u8paCRCCalculationMessage [ u16MessageCounter ]  = u8HeaderByte ;
   }

/* Calculate the CRC remainder and save it in the last 4 bytes of the message buffer. */
   u32CalculatedCRCRemainder = u32_Calculate32BitCRC (                /* CRC calculating funion. */
                                  u8paCRCCalculationMessage ,          /* Message on which CRC is being computed*/
                                  u16HeaderSize ,                      /* No of Header bytes in the Message. */
                                  ( u16LengthOfCRCMessageMinusOne - ( u16 ) NUMBER_4 ) ,
                                                                      /* Length of Message on which CRC is being computed. */
                                  u32CalculatedCRCRemainder ) ;       /* The remainder returned of the */

/* Split the CRC remainder into 4 bytes and load them into the last 4 bytes of the message buffer. */
/* Most Significant Byte being extracted. */
   u32CRC8BitRemainder = ( u32CalculatedCRCRemainder >> ( u16 ) SHIFT_24 ) & ( u32 ) BIT2FF ;
   u8paCRCCalculationMessage [ u16LengthOfCRCMessageMinusOne - ( u16 ) NUMBER_3 ]  = ( u8 ) u32CRC8BitRemainder ;
/* 2nd Most Significant Byte being extracted. */
   u32CRC8BitRemainder = ( u32CalculatedCRCRemainder >> ( u16 ) SHIFT_16 ) & ( u32 ) BIT2FF ;
   u8paCRCCalculationMessage [ u16LengthOfCRCMessageMinusOne - ( u16 ) NUMBER_2 ]  = ( u8 ) u32CRC8BitRemainder ;
/* 3rd Most Significant Byte being extracted. */
   u32CRC8BitRemainder = ( u32CalculatedCRCRemainder >>  ( u16 ) SHIFT_8 ) & ( u32 ) BIT2FF ;
   u8paCRCCalculationMessage [ u16LengthOfCRCMessageMinusOne - ( u16 ) NUMBER_1 ]  = ( u8 ) u32CRC8BitRemainder ;
/* 4th Most Significant Byte being extracted. */
   u32CRC8BitRemainder = ( u32CalculatedCRCRemainder >>  ( u16 ) SHIFT_0 ) & ( u32 ) BIT2FF ;
   u8paCRCCalculationMessage [ u16LengthOfCRCMessageMinusOne - ( u16 ) NUMBER_0 ]  = ( u8 ) u32CRC8BitRemainder ;

/*   Return from the v_LoadMessageHeaderAndCRCResult function. */
   return ;/** @return \a None (void) */
}
/* End v_LoadMessageHeaderAndCRCResult. */


/**
 * @brief This function is used to verify the header and CRC of the received bytes.
 *
 * @par <b> Detailed Description: </b>
 * This function first checks for the 6 header bytes and then calculates and checks the CRC of the received message
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *       REL.0135.S.COM.9.001 \n
 *       REL.0135.S.COM.9.002 \n
 *       REL.0135.S.DSP.10.001 \n
 *       REL.0135.S.DSP.10.002 \n
 *
 * @param [out] *u8paCRCCalculationMessage The CRC calculation Message.
 * @param [in] u16LengthOfCRCMessageMinusOne  The length of CRC Message.
 */

u16 u16_VerifyCRCofTheMessage ( u8 *u8paCRCCalculationMessage ,       /* The CRC calculation Message.*/
                                u16 u16LengthOfCRCMessageMinusOne )  /* The  length of CRC Message. */
{
/*   This variable is used to save the results of the CRC and Header checks. */
   u16 u16CRCErrorFlag = ( u16 ) ZERO ;

/*   This variable stores the CRC remainder calculated by the CRC calculation function. */
   u32 u32CalculatedCRCRemainder = ( u32 ) ZERO ;

/*   Call the CRC remainder calculating function to check for the message validity. */
   u32CalculatedCRCRemainder = u32_Calculate32BitCRC (                          /* Function to calculate the CRC of the Message. */
                                  &u8paCRCCalculationMessage  [ ( u16 ) ZERO ] , /* The CRC calculation Message. */
                                  ( u16 ) NUMBER_6 ,                              /* The CRC calculation start byte number. */
                                  u16LengthOfCRCMessageMinusOne ,                 /* The CRC calculation end byte number.*/
                                  u32CalculatedCRCRemainder ) ;                  /* The CRC remainder initilization. */

/*   Check for the successful validation CRC remainder of the message. */
   if ( u32CalculatedCRCRemainder == ( u32 ) ZERO )
   {
/*    Assert the header fault flag. */
      u16CRCErrorFlag = ( u16 ) GOOD ;
   }
   else
   {
      u16CRCErrorFlag = ( u16 ) BAD ;
   }
/* Return the header and CRC validation flag. */
   return ( u16CRCErrorFlag ) ;/** @return \a u16CRCErrorFlag - Return the header and CRC validation flag */
}
/* End u16_VerifyCRCofTheMessage. */

/* End of COMCRCModule.c Module. */

