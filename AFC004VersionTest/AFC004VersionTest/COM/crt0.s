/**
 *  @file crt0.s
 *  @brief This file contains low level functions for doing the following:<BR>
 *         Takes control at device reset
 *
 *  @date 
 *
 *  @author 
 *
 *  @par <b> Description: </b>
 *     - initialize stack and stack limit register
 *     - initialize PSV window if __const_length > 0
 *     - process the data initialization template
 *     - call the user's _main entry point
 *     - Copy data from program memory to data memory; 
 *
 *  @par <b> Table of Contents: </b>
 *     The following functions are defined in this file:
 *     - _resetPRI
 *     - _psv_init
 *     - _data_init
 *     - _main
 *     - _memcpypd3
 *
 *  @par <b> Change History: </b> <BR>
 *     This file is part of the compact math library for the dsPIC30. 
 *     (c) Microchip Technology. 2003.
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td>   <td> <center>Draft</center>   <td> <center>  </center> <td> Initial Draft
 *        <tr><td> 16Sep2008  <td> <center>  "  </center>   <td> <center>JD</center> <td> ADHR259
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 09Dec2008 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR281
 *        <tr><td> 13Feb2009 <td>  <center> 1.2 </center>   <td> <center>YC</center> <td> ADHR340:PR_CR_322
 *        <tr><td> 27Jan2019 <td>  <center> 1.3 </center>   <td> <center>BA</center> <td> Changed to .init section
 *  </table>
 *  <BR>
 *
 *  @note $Id: crt0.s 6176 2009-02-13 22:37:52Z yijing $ <BR>
 *  @note <i> All rights reserved.  Copyright 2008-2019.  Archangel Systems, Inc. </i> <BR>
 */
;; C Run-time startup module for dsPIC30 C compiler.
;; (c) Copyright 2002,2004 Microchip Technology, All rights reserved
;;
;; Primary version, with data initialization support.
;; The linker loads this version when the --data-init
;; option is selected.
;; 
;; See file crt1.s for the alternate version without
;; data initialization support.
;; 
;; Entry __reset takes control at device reset and
;; performs the following:
;;
;;  1. initialize stack and stack limit register
;;  2. initialize PSV window if __const_length > 0
;;  3. process the data initialization template
;;  4. call the user's _main entry point
;; Supports the zero-parameter form of main() by default.
;; If the symbol __ARGV is defined, supports the two-parameter
;; form of main().
;;
;; Un-comment the following line to define symbol __ARGV:
;;      .equiv __ARGV,1
;; 
        .equ __30F2010, 1   
        .include "p30f2010.inc"

        .section .init,code

        .global __resetPRI
        .ifdef __C30ELF
        .type   __resetPRI,@function
        .endif
        

;/**
; * @brief This function takes control at device reset.
; *
; * @par <b> Detailed Description: </b>
; *     - Initialize stack, PSV, and data registers used:  w0
; *\verbatim
; *
; *   Inputs (defined by user or linker):
; *      __SP_init
; *      __SPLIM_init
; *
; *   Outputs:
; *      (does not return - resets the processor)
; *
; *   Calls:
; *      __psv_init
; *      __data_init
; *      _main or __main
; *\endverbatim
; * @author 
; *
; * @par <b> Requirement(s) Implemented: </b> <BR>
; *	     REL.0135.S.COM.16.001.D01 \n	
; *
; * @par <b> Parameters: </b> <br> 
; *    <i> None </i> (void)
; */

__resetPRI:     
        .weak   __reset
        .ifdef __C30ELF
        .type   __reset,@function
        .endif
__reset:

        mov      #__SP_init,w15    ; initialize w15
        mov      #__SPLIM_init,w0  ; 
        mov      w0,_SPLIM         ; initialize SPLIM
        nop                        ; wait 1 cycle

        rcall    __psv_init        ; initialize PSV
        rcall    __data_init       ; initialize data
                                   ;  clears w0, so ARGC = 0

        .ifdef __ARGV
          rcall  __main            ; call two-parameter main() setup
        .else
          call  _main              ; call user's main()
        .endif

        .pword 0xDA4000            ; halt the simulator
        reset                      ; reset the processor


;/**
; * @brief This function Initialize PSV window if _constlen > 0.
; *
; * @par <b> Detailed Description: </b>
; *     - Registers used:  w0
; *\verbatim
; *
; *      Inputs (defined by linker):
; *      __const_length
; *      __const_psvpage
; *
; *      Outputs:
; *      (none)
; *
; *\endverbatim
; * @author 
; *
; * @par <b> Requirement(s) Implemented: </b> <BR>
; *	     REL.0135.S.COM.16.001.D01 \n
; *
; * @par <b> Parameters: </b> <br> 
; *    <i> None </i> (void)
; */
        .weak __psv_init
__psv_init:

        bclr     _CORCON,#PSV        ; disable PSV (default)
        mov      #__const_length,w0  ; 
        cp0      w0                  ; test length of constants
        bra      z,1f                ; br if zero

        mov      #__const_psvpage,w0 ; 
        mov      w0,_PSVPAG          ; PSVPAG = psvpage(constants)
        bset     _CORCON,#PSV        ; enable PSV

1:      return                       ;  and exit


;/**
; * @brief This function Process data init template.
; *
; * @par <b> Detailed Description: </b>
; *     - Registers used:  w0 w1 w2 w3 w4 w5
; *     - The template is null-terminated, with records in the following format:
; *\verbatim
; * struct data_record 
; * {
; *   char *dst;        /* destination address  */
; *   int  len;         /* length in bytes      */
; *   int  format;      /* format code          */
; *   char dat[0];      /* variable length data */
; * };
; *  
; *      Inputs (defined by linker):
; *      __dinit_tbloffset
; *      __dinit_tblpage
; *
; *      Outputs:
; *      (none)
; *
; *      Calls:
; *      __memcpypd3
; *\endverbatim
; * @author 
; *
; * @par <b> Requirement(s) Implemented: </b> <BR>
; *	     REL.0135.S.COM.16.001.D01 \n
; *
; * @par <b> Parameters: </b> <br> 
; *    <i> None </i> (void)
; */        
        .weak __data_init
__data_init:

        .equiv   FMT_CLEAR,0    ;  format codes
        .equiv   FMT_COPY2,1    ; 
        .equiv   FMT_COPY3,2    ; 

        mov      #__dinit_tbloffset,w0 ; w0,w1 = template
        mov      #__dinit_tblpage,w1   ;
        bra      4f                    ; br to continue

1:      add      w0,#2,w0       ; template+=2
        addc     w1,#0,w1       ; 
        mov      w1,_TBLPAG     ; TBLPAG = tblpage(template)

        tblrdl.w [w0],w3        ; w3 = len 
        add      w0,#2,w0       ; template+=2
        addc     w1,#0,w1       ; 
        mov      w1,_TBLPAG     ; TBLPAG = tblpage(template)

        tblrdl.w [w0],w5        ; w5 = format
        add      w0,#2,w0       ; template+=2
        addc     w1,#0,w1       ; 
        clr      w4             ; upper = FALSE (default)

        cp       w5,#FMT_CLEAR  ; test format
        bra      nz,2f          ; br if not FMT_CLEAR

        ;; FMT_CLEAR - clear destination memory
        dec      w3,w3          ; decrement & test len
        bra      n,4f           ; br if negative

        repeat   w3             ; 
        clr.b    [w2++]         ; clear memory      
        bra      4f             ; br to continue

        ;; FMT_COPY2, FMT_COPY3 - copy bytes
2:      cp       w5,#FMT_COPY2  ; test format
        bra      z,3f           ; br if FMT_COPY2

        setm     w4             ; upper = TRUE

3:      rcall    __memcpypd3    ; copy 2 or 3 bytes

4:      mov      w1,_TBLPAG     ; TBLPAG = tblpage(template)
        tblrdl.w [w0],w2        ; w2 = next dst      
        cp0      w2             ; 
        bra      nz,1b          ; loop on non-zero dst

        retlw    #0,w0          ; exit (clears ARGC also)


;/**
; * @brief This function Copy data from program memory to data memory.
; *
; * @par <b> Detailed Description: </b>
; *     - Registers used:  w0 w1 w2 w3 w4 w 
; *\verbatim
; *
; *      Inputs
; *      w0,w1 = source address   (24 bits)
; *      w2 = destination address (16 bits)
; *      w3 = number of bytes (even or odd)
; *      w4 = upper byte flag   (0 = false)
; *
; *      Outputs:
; *      w0,w1 = next source address (24 bits)
; *
; *\endverbatim
; * @author 
; *
; * @par <b> Requirement(s) Implemented: </b> <BR>
; *	     REL.0135.S.COM.16.001.D01 \n
; *
; *
; * @par <b> Parameters: </b> <br> 
; *    <i> None </i> (void)
; */
__memcpypd3:

1:      mov      w1,_TBLPAG     ; TBLPAG = tblpage(src)
        mov      w0,w5          ; w5 =   tbloffset(src)
        add      w0,#2,w0       ; src+=2
        addc     w1,#0,w1       ;

        tblrdl.b [w5++],[w2++]  ; dst++ = lo byte
        dec      w3,w3          ; num--
        bra      z,2f           ; br if done

        tblrdl.b [w5--],[w2++]  ; dst++ = hi byte
        dec      w3,w3          ; num--
        bra      z,2f           ; br if done

        cp0      w4             ; test upper flag
        bra      z,1b           ; br if false

        tblrdh.b [w5],[w2++]    ; dst++ = upper byte
        dec      w3,w3          ; num--
        bra      nz,1b          ; br if not done

2:      return                  ; exit


;/**
; * @brief This function Initialize a stack frame to support the two-parameter form of main()
; *
; * @par <b> Detailed Description: </b>
; *     - Registers used:  w0 w1
; *\verbatim
; *
; *      Inputs (defined by user or linker):
; *      (none)
; *
; *      Outputs:
; *      (none)
; *
; *      Calls:
; *      _main
; *\endverbatim
; * @author 
; *
; * @par <b> Requirement(s) Implemented: </b> <BR>
; *	     REL.0135.S.COM.16.001.D01 \n
; *
; *
; */
        .ifdef __ARGV        
__main:

        lnk      #6             ; construct frame

        mov      #0,w0          ; store a null terminator
        mov.b    w0,[w15-6]     ;  for program name

        sub      w15,#6,w1
        mov      w1,[w15-4]     ; argv[0] = &pgmname             
        mov      w0,[w15-2]     ; argv[1] = 0

        mov      #1,w0          ; w0 = argc
        sub      w15,#4,w1      ; w1 = &argv
        call    _main           ; call the user's main()

        ulnk                    ; destroy frame
        return                  ;  and exit
        .endif

        .end

