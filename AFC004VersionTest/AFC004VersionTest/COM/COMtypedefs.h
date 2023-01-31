/** @file COMtypedefs.h
 *  @brief This file assigns Alias for the compiler defined data types.
 *
 *  @par <b> Description: </b>
 *       None
 *
 *  @date 15may2006
 *  @author Vamshi Gangumalla
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 15May2006 <td> <center>Draft</center>   <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 05Dec2008 <td>  <center> 1.0 </center>   <td> <center>YC</center> <td> Baseline Release
 *                                                                                        (ADHR281: Code review,duplicate name)
 *        <tr><td> 27Jan2019 <td>  <center> 1.1 </center>   <td> <center>BA</center> <td> Extended to include more types
 *     </table>
 *  <BR>
 *
 *  @note $Id: COMtypedefs.h 6017 2008-12-10 15:20:12Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2005-2019.  Archangel Systems, Inc. </i> <BR>
 */

/* Alias for compiler specific data types defined in MPLAB C 30 compiler. */
#ifndef COMTYPEDEFS_H
#define COMTYPEDEFS_H

/* Specify an extension for GCC based compilers */
#if defined(__GNUC__)
#define __EXTENSION __extension__
#else
#define __EXTENSION
#endif

#if !defined(__PACKED)
#define __PACKED
#endif

/*    Char Data types are defined with alias here. */
typedef signed char s8 ;
typedef unsigned char u8 ;     

/*    Integer data types are defined with alias here. */
typedef signed int s16 ;
typedef unsigned int u16 ;

/*    Long integer data types are defined with alias here. */
typedef signed long s32 ;
typedef unsigned long u32 ;

/*    floating point data types are defined with alias here. */
typedef float f32 ;
typedef long double f64 ;

__EXTENSION typedef unsigned long long u64 ;

typedef union
{
   u8 Val ;

   struct
   {
      __EXTENSION u8 b0 : 1 ;
      __EXTENSION u8 b1 : 1 ;
      __EXTENSION u8 b2 : 1 ;
      __EXTENSION u8 b3 : 1 ;
      __EXTENSION u8 b4 : 1 ;
      __EXTENSION u8 b5 : 1 ;
      __EXTENSION u8 b6 : 1 ;
      __EXTENSION u8 b7 : 1 ;
   } bits ;
} u8_val, u8_bits ;

typedef union
{
   u16 Val ;
   u8 v[2] __PACKED ;

   struct __PACKED
   {
      u8 LB ;
      u8 HB ;
   } byte ;

   struct __PACKED
   {
      __EXTENSION u8 b0 : 1 ;
      __EXTENSION u8 b1 : 1 ;
      __EXTENSION u8 b2 : 1 ;
      __EXTENSION u8 b3 : 1 ;
      __EXTENSION u8 b4 : 1 ;
      __EXTENSION u8 b5 : 1 ;
      __EXTENSION u8 b6 : 1 ;
      __EXTENSION u8 b7 : 1 ;
      __EXTENSION u8 b8 : 1 ;
      __EXTENSION u8 b9 : 1 ;
      __EXTENSION u8 b10 : 1 ;
      __EXTENSION u8 b11 : 1 ;
      __EXTENSION u8 b12 : 1 ;
      __EXTENSION u8 b13 : 1 ;
      __EXTENSION u8 b14 : 1 ;
      __EXTENSION u8 b15 : 1 ;
   } bits ;
} u16_val, u16_bits ;

typedef union
{
   u32 Val ;
   u16 w[2] __PACKED ;
   u8 v[4] __PACKED ;

   struct __PACKED
   {
      u16 LW ;
      u16 HW ;
   } word ;

   struct __PACKED
   {
      u8 LB ;
      u8 HB ;
      u8 UB ;
      u8 MB ;
   } byte ;

   struct __PACKED
   {
      u16_val low ;
      u16_val high ;
   } wordUnion ;

   struct __PACKED
   {
      __EXTENSION u8 b0 : 1 ;
      __EXTENSION u8 b1 : 1 ;
      __EXTENSION u8 b2 : 1 ;
      __EXTENSION u8 b3 : 1 ;
      __EXTENSION u8 b4 : 1 ;
      __EXTENSION u8 b5 : 1 ;
      __EXTENSION u8 b6 : 1 ;
      __EXTENSION u8 b7 : 1 ;
      __EXTENSION u8 b8 : 1 ;
      __EXTENSION u8 b9 : 1 ;
      __EXTENSION u8 b10 : 1 ;
      __EXTENSION u8 b11 : 1 ;
      __EXTENSION u8 b12 : 1 ;
      __EXTENSION u8 b13 : 1 ;
      __EXTENSION u8 b14 : 1 ;
      __EXTENSION u8 b15 : 1 ;
      __EXTENSION u8 b16 : 1 ;
      __EXTENSION u8 b17 : 1 ;
      __EXTENSION u8 b18 : 1 ;
      __EXTENSION u8 b19 : 1 ;
      __EXTENSION u8 b20 : 1 ;
      __EXTENSION u8 b21 : 1 ;
      __EXTENSION u8 b22 : 1 ;
      __EXTENSION u8 b23 : 1 ;
      __EXTENSION u8 b24 : 1 ;
      __EXTENSION u8 b25 : 1 ;
      __EXTENSION u8 b26 : 1 ;
      __EXTENSION u8 b27 : 1 ;
      __EXTENSION u8 b28 : 1 ;
      __EXTENSION u8 b29 : 1 ;
      __EXTENSION u8 b30 : 1 ;
      __EXTENSION u8 b31 : 1 ;
   } bits ;
} u32_val ;

typedef union
{
   u64 Val ;
   u32 d[2] __PACKED ;
   u16 w[4] __PACKED ;
   u8 v[8] __PACKED ;

   struct __PACKED
   {
      u32 LD ;
      u32 HD ;
   } dword ;

   struct __PACKED
   {
      u16 LW ;
      u16 HW ;
      u16 UW ;
      u16 MW ;
   } word ;

   struct __PACKED
   {
      __EXTENSION u8 b0 : 1 ;
      __EXTENSION u8 b1 : 1 ;
      __EXTENSION u8 b2 : 1 ;
      __EXTENSION u8 b3 : 1 ;
      __EXTENSION u8 b4 : 1 ;
      __EXTENSION u8 b5 : 1 ;
      __EXTENSION u8 b6 : 1 ;
      __EXTENSION u8 b7 : 1 ;
      __EXTENSION u8 b8 : 1 ;
      __EXTENSION u8 b9 : 1 ;
      __EXTENSION u8 b10 : 1 ;
      __EXTENSION u8 b11 : 1 ;
      __EXTENSION u8 b12 : 1 ;
      __EXTENSION u8 b13 : 1 ;
      __EXTENSION u8 b14 : 1 ;
      __EXTENSION u8 b15 : 1 ;
      __EXTENSION u8 b16 : 1 ;
      __EXTENSION u8 b17 : 1 ;
      __EXTENSION u8 b18 : 1 ;
      __EXTENSION u8 b19 : 1 ;
      __EXTENSION u8 b20 : 1 ;
      __EXTENSION u8 b21 : 1 ;
      __EXTENSION u8 b22 : 1 ;
      __EXTENSION u8 b23 : 1 ;
      __EXTENSION u8 b24 : 1 ;
      __EXTENSION u8 b25 : 1 ;
      __EXTENSION u8 b26 : 1 ;
      __EXTENSION u8 b27 : 1 ;
      __EXTENSION u8 b28 : 1 ;
      __EXTENSION u8 b29 : 1 ;
      __EXTENSION u8 b30 : 1 ;
      __EXTENSION u8 b31 : 1 ;
      __EXTENSION u8 b32 : 1 ;
      __EXTENSION u8 b33 : 1 ;
      __EXTENSION u8 b34 : 1 ;
      __EXTENSION u8 b35 : 1 ;
      __EXTENSION u8 b36 : 1 ;
      __EXTENSION u8 b37 : 1 ;
      __EXTENSION u8 b38 : 1 ;
      __EXTENSION u8 b39 : 1 ;
      __EXTENSION u8 b40 : 1 ;
      __EXTENSION u8 b41 : 1 ;
      __EXTENSION u8 b42 : 1 ;
      __EXTENSION u8 b43 : 1 ;
      __EXTENSION u8 b44 : 1 ;
      __EXTENSION u8 b45 : 1 ;
      __EXTENSION u8 b46 : 1 ;
      __EXTENSION u8 b47 : 1 ;
      __EXTENSION u8 b48 : 1 ;
      __EXTENSION u8 b49 : 1 ;
      __EXTENSION u8 b50 : 1 ;
      __EXTENSION u8 b51 : 1 ;
      __EXTENSION u8 b52 : 1 ;
      __EXTENSION u8 b53 : 1 ;
      __EXTENSION u8 b54 : 1 ;
      __EXTENSION u8 b55 : 1 ;
      __EXTENSION u8 b56 : 1 ;
      __EXTENSION u8 b57 : 1 ;
      __EXTENSION u8 b58 : 1 ;
      __EXTENSION u8 b59 : 1 ;
      __EXTENSION u8 b60 : 1 ;
      __EXTENSION u8 b61 : 1 ;
      __EXTENSION u8 b62 : 1 ;
      __EXTENSION u8 b63 : 1 ;
   } bits ;
} u64_val ;

#endif

/* End of COMtypedefs.h header file. */