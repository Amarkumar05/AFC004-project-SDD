/**
 *  @file COMHardwareResetConfiguration.c
 *  @brief This module contains a function to initialize all Hardware to a reset configuration.
 *
 *  @date 12May2006
 *  @author Stephen Hallacy
 *
 *  @par <b> Description: </b>
 *       - Configures all dsPIC peripherals to the default values after a reset.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *       - v_HardwareResetConfiguartion
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 12May2006 <td> <center>Draft</center>   <td> <center>SH</center> <td> Initial Draft
 *        <tr><td> 13Mar2007 <td>   <center>"</center>     <td> <center>SH</center> <td> CAR 323
 *        <tr><td> 11Mar2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR83-COM, PR_CR_017 and PR_CR_012
 *        <tr><td> 17Sep2008 <td>   <center>"</center>     <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 05Nov2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281- PR_CR_173
 *        <tr><td> 22Dec2008 <td>  <center> 1.2 </center>   <td> <center>JD</center> <td> ADHR315:PR_LLRBT_076
 *                                                                                                PR_LLRBT_115
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMHardwareResetConfiguration.c 6061 2008-12-23 16:15:03Z jayd $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

/**************  Include Files  ************************/
#include "COMHardwareResetConfiguration.h"

/**************  Module Level Function Prototypes  *****/


/**************  Module Level Variables  **************/


/**********  Constants, Enums, and Typedefs  ***********/



/***********  Global Variable Declarations  ************/

/**
 * @brief Initialize all Hardware to a reset configuration.
 *
 * @par <b> Detailed Description: </b>
 *  The following modules are initialized:
 *             - Internal A/D converter
 *              - SPI1
 *              - SPI2
 *              - UART 1 and UART 2
 *              - I2C
 *              - CAN
 *              - Input Capture Ports
 *              - Output Compare Ports
 *              - Change notification
 *   The registers accessed by this function are enumerated as follows:
 *   ADCON1   - Internal ADC Control Register 1 = 0x0000
 *   SPI1STAT - Serial Peripheral Interface 1 Status Register   = 0x0000
 *   SPI2STAT - Serial Peripheral Interface 2 Status Register   = 0x0000
 *   U1MODE   - UART 1 mode register = 0x0000
 *   U2MODE   - UART 2 mode register = 0x0000
 *   I2CCON   - I2C control register = 0x0000
 *   C1CTRL   - CAN module control register = 0x0100
 *   IC1CON   - Input capture port 1 control register = 0x0000
 *   IC2CON   - Input capture port 2 control register = 0x0000
 *   IC3CON   - Input capture port 3 control register = 0x0000
 *   IC4CON   - Input capture port 4 control register = 0x0000
 *   IC5CON   - Input capture port 5 control register = 0x0000
 *   IC6CON   - Input capture port 6 control register = 0x0000
 *   IC7CON   - Input capture port 7 control register = 0x0000
 *   IC8CON   - Input capture port 8 control register = 0x0000
 *   OC1CON   - Output compare port 1 control register = 0x0000
 *   OC2CON   - Output compare port 2 control register = 0x0000
 *   OC3CON   - Output compare port 3 control register = 0x0000
 *   OC4CON   - Output compare port 4 control register = 0x0000
 *   OC5CON   - Output compare port 5 control register = 0x0000
 *   OC6CON   - Output compare port 6 control register = 0x0000
 *   OC7CON   - Output compare port 7 control register = 0x0000
 *   OC8CON   - Output compare port 8 control register = 0x0000
 *   CNEN1    - Change notification interrupt register 1 = 0x0000
 *   CNEN2    - Change notification interrupt register 2 = 0x0000
 *   CNPU1    - Change notification pull up register 1 = 0xFFFF
 *   CNPU2    - Change notification pull up register 2 = 0xFFFF
 *   T1CON    - Timer 1 control register = 0x0000
 *   T2CON    - Timer 2 control register = 0x0000
 *   T3CON    - Timer 3 control register = 0x0000
 *   T4CON    - Timer 4 control register = 0x0000
 *   T5CON    - Timer 5 control register = 0x0000
 *   TRISB    - Port B bit direction set register = 0xFFFF
 *   TRISC    - Port C bit direction set register = 0xFFFF
 *   TRISD    - Port D bit direction set register = 0xFFFF
 *   TRISF    - Port F bit direction set register = 0xFFFF
 *   TRISG    - Port G bit direction set register = 0xFFFF
 *   RCON     -  Reset configuration register     = 0x0000
 *
 * @author Stephen Hallacy
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *			REL.0135.S.COM.16.001 \n
 *
 * @par <b> Parameters: </b> <br>
 *    <i> None </i> (void)
 */

void v_HardwareResetConfiguartion ( void )
{
   /*******************************************************************

     This function sets all the hardware to a Reset configuration by

     1. Disabling the following:
           a. Internal ADC Module.
           b. SPI1 and SPI2 Modules.
           c. UART 1 and UART 2 Modules.
           d. I2C Module.
           e. CAN Bus Module.
           f. All Input Capture Ports (IC1-IC8).
           g. Output Compare Channels (OC1-OC2).
           h. All Change Notification Interrupts (CN0-CN23).

      2. Enabling Pull-ups on all Change Notification Ports (CN0-CN23).

      3. Stopping Timers 1 through 5.

      4. Making all I/O Ports Input Ports.

      5. Clearing the RCON Register (Reset Control Register).

    *******************************************************************/

   /* Disable the Internal ADC module. */
   ADCON1 = ZERO ;

   /* Disable the SPI1 module. */
   SPI1STAT = ZERO ;

   /* Disable the SPI2 module. */
   SPI2STAT = ZERO ;

   /* Disable the UART1 module. */
   U1MODE = ZERO ;

   /* Disable the UART2 module. */
   U2MODE = ZERO ;

   /*Disable the I2C Module. */
   I2CCON = ZERO ;

   /*Disable the CAN Module */
   C1CTRL = HEX_0100 ;

   /* Disable Input Capture Port 7 through 8. */
   IC1CON = ZERO ;
   IC2CON = ZERO ;
   IC3CON = ZERO ;
   IC4CON = ZERO ;
   IC5CON = ZERO ;
   IC6CON = ZERO ;
   IC7CON = ZERO ;
   IC8CON = ZERO ;

   /* Disable Output Compare Channels. */
   OC1CON = ZERO ;
   OC2CON = ZERO ;
   OC3CON = ZERO ;
   OC4CON = ZERO ;
   OC5CON = ZERO ;
   OC6CON = ZERO ;
   OC7CON = ZERO ;
   OC8CON = ZERO ;

   /* Disable Change Notification Interrupts on CN0 though CN15. */
   CNEN1 = ZERO ;

   /* Disable Change Notification Interrupts on CN16 though CN23. */
   CNEN2 = ZERO ;

   /* Enable Pull-ups on Change Notification Ports 0 through 15. */
   CNPU1 = HEX_FFFF ;

   /* Enable Pull-ups on Change Notification Ports 16 through 23. */
   CNPU2 = HEX_FFFF ;

   /* Stop all Timers. */
   T1CON = ZERO ;
   T2CON = ZERO ;
   T3CON = ZERO ;
   T4CON = ZERO ;
   T5CON = ZERO ;

   /* Make all ports input ports. */
   TRISB = HEX_FFFF ;
   TRISC = HEX_FFFF ;
   TRISD = HEX_FFFF ;
   TRISF = HEX_FFFF ;
   TRISG = HEX_FFFF ;

   /* Disable Watch Dog Timeouts (SWDTEN = 0) and Clears all Reset Flags. */
   /* WARNING: this setting will not disable the Watchdog Timer if the FWDTEN Configuration Bit is set. */
   RCON = ZERO ;

   return ; /** @return \a None (void) */

}

/*
** end of file
*/

