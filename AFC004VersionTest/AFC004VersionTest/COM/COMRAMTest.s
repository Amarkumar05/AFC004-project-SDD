/**
 *  @file COMRAMTest.s
 *  @brief This file implements the RAM test.
 *
 *  @date 06Jul2006
 *
 *  @author Vamshi Gangumalla.
 *
 *  @par <b> Description: </b>
 *     - This function performs the Random Access Memory Test at boot.
 *       RAM test function works only when in programming mode for 
 *       the ICD. It doesn't work ( i.e. the function fails the memory 
 *       test ) when in debug mode, as a section of the RAM is used by 
 *       the ICD to perform debug tasks.
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _u16_asmRAMTestResult
 *
 *  @par <b> Change History: </b> <BR>
 *     This file is part of the compact math library for the dsPIC30. 
 *     (c) Microchip Technology. 2003.
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 06Jul2006 <td> <center>Draft</center> <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 11Apr2007 <td> <center> " </center>   <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 16Sep2008  <td> <center>  "  </center>   <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 10Dec2008 <td>  <center> 1.1 </center>   <td> <center>JD</center> <td> ADHR280: PR_LLR_055
 *  </table>
 *  <BR>
 *
 *  @note $Id: COMRAMTest.s 6023 2008-12-10 20:50:49Z jayd $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008.  Archangel Systems, Inc. </i> <BR>
 */

/*   Header file to include the processor defined labels. */
 .IFDEF __30F6012A
    .include "p30f6012A.inc"
 .ENDIF
 
 .IFDEF __30F6012
    .include "p30f6012.inc"
 .ENDIF
 
 .IFDEF __30F6014A
    .include "p30f6014A.inc"
 .ENDIF


 .equiv TEST_FAIL , 0x0000        ; RAM Test Failure value.
 .equiv TEST_PASS , 0x0001        ; RAM Test Sucess value.
 .equiv WORD_SIZE , 0x0002        ; RAM Test Memory word size.
         
/*   Prototyping the assembly function to be called using C language construct.
   u16 u16_asmRAMTestResult ( u16 u16StartAddr, u16 u16EndAddr ) ;
   The assembly function can be now called using the above construct.   */
.global _u16_asmRAMTestResult

/*   Assembly directive for specifying the function to be saved in the code section. */
.section .text


/**
 * @brief This function performs the Random Access Memory Test at boot.
 *
 * @par <b> Detailed Description: </b>
 *   - This function performs the following steps in order to test the non volatile memory: 
 *       - Loads test data for the Test Memory Location. 
 *       - Copies and saves the data in the Test Memory Location. 
 *       - Writes the test data into the Test Memory Location. 
 *       - Reads the data from the Test Memory Location. 
 *       - Performs Exclusive OR to verify the read and write operation on the Test Memory Location. 
 *       - Writes the result of the test 0x0000 into the Test Memory Location. 
 *       - Copies back the data into the Test Memory Location. 
 *       - Saves the result of the test in the register. 
 *       - Checks for Zero which indicates successful memory test. 
 *       - Copies the literal value into the register. 
 *       - Increments the pointer of the Test Memory Location. 
 *       - Returns a success if all the memory write-read operations are done successfully else returns a failure.
 *
 * @author Vamshi Gangumalla
 *
 * @par <b> Requirement(s) Implemented: </b> <BR>
 *	    REL.0135.S.COM.8.001 \n
 *	    REL.0135.S.COM.8.002 \n		
 *
 * @par <b> Parameters: </b> <br> 
 *    <i> None </i> (void)
 */
; RAM test function works only when in programming mode for the ICD.
; It doesn't work when in debug mode, as a section of the RAM is used 
; by the ICD to perform debug tasks.

_u16_asmRAMTestResult:          ; Function to implement the RAM boot up test.
                                ; W0 = u16StartAddr         Start address of the RAM test.
                                ; W1 = u16EndAddr           End address of the RAM test.
                                ; W2 = u16TestWord1         Ram Test Memory Write Word 1.
                                ; W3 = u16ResultWord1       Ram Test Memory Read Word 1.
                                ; W4 = u16TestWord2         Ram Test Memory Write Word 2.
                                ; W5 = u16ResultWord2       Ram Test Memory Read Word 2.

   MOV W2, W9                   ; Move the Test Data 1 into Resgister W9.
   MOV W3, W10                  ; Move the Test Result 1 into Resgister W10.
   MOV W4, W11                  ; Move the Test Data 2 into Resgister W11.
   MOV W5, W12                  ; Move the Test Result 2 into Resgister W12.
   MOV W0, W3                   ; Load the Ram Test starting memory Address into Register W3. 
   CLR W7                       ; Clear the register for saving the status of the memory check.   
   
   RAMTEST: 
      MOV W9 , W4               ; Load test data for the Test Memory Location.
      MOV [ W3 ] , W8           ; Copy and save the data in the Test Memory Location.
      MOV W4 , [ W3 ]           ; Write the test data into the Test Memory Location.
      MOV [ W3 ] , W5           ; Read the data from the Test Memory Location.
      XOR W10 , W5 , W6         ; Perform Exclusive OR to verify the read and write operation on the Test Memory Location.
      MOV W6 , [ W3 ]           ; Write the result of the test 0x0000 into the Test Memory Location.
      IOR W6 , W7 , W7          ; Save the result of the test in the register.

      MOV W11, W4               ; Load test data for the Test Memory Location.
      MOV W4, [ W3 ]            ; Write the test data into the Test Memory Location.   
      MOV [ W3 ] , W5           ; Read the data from the Test Memory Location.   
      XOR W12 , W5 , W6         ; Perform Exclusive OR to verify the read and write operation on the Test Memory Location.
      MOV W6 , [ W3 ]           ; Write the result of the test 0x0000 into the Test Memory Location.      
      MOV W8 , [ W3 ]           ; Copy back the data into the Test Memory Location.
      IOR W6 , W7 , W7          ; Save the result of the test in the register.
      BRA NZ , TESTFAIL         ; Check for Zero which indicates successful memory test.

      MOV #WORD_SIZE , W8       ; Copy the literal value into register.
      ADD W8 , W3 , W3          ; Increment the pointer of the Test Memory Location.   
      XOR W3 , W1 , W8          ; Check weather the Test Memory Location is the last memory location.
      BRA NZ , RAMTEST          ; If no jump to the continue memory test loop.

      MOV #TEST_PASS , W0       ; Return RAM Memory Test Successful.
      RETURN

   TESTFAIL: 
      MOV #TEST_FAIL , W0       ; Return RAM Memory Test Fail.
      RETURN                    ; Return from the function.

.end                            ; End of the Assembly file.

