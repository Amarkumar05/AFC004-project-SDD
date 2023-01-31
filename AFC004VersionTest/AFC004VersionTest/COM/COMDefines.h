/** @file COMDefines.h
 *  @brief This header file defines the common defines.
 *
 *  @par <b> Description: </b>
 *     - This header file defines the common defines.
 *
 *  @date 22Nov2006
 *  @author Vamshi Gangumalla
 *
 *  @par <b> Change History: </b> <BR>
 *     <table>
 *        <tr><td> <i> Date  <td> Release <td> Author <td> Description </i>
 *        <tr><td> 22Nov2006 <td> <center>Draft</center>   <td> <center>VG</center> <td> Initial Draft
 *        <tr><td> 21Feb2008 <td>   <center>"</center>     <td> <center>KN</center> <td> ADHR127
 *        <tr><td> 23Sep2008 <td>  <center> 1.0 </center>   <td> <center>JD</center> <td> Baseline Release
 *        <tr><td> 28Apr2009 <td>  <center> 1.1 </center>   <td> <center>YC</center> <td> ADHR703
 *        <tr><td> 29May2009 <td>  <center> 1.2 </center>   <td> <center>JD</center> <td> ADHR715
 *        <tr><td> 24Oct2014 <td>  <center> 1.3 </center>   <td> <center>YC</center> <td> ADHR943
 *        <tr><td> 19Apr2016 <td>  <center> 1.4 </center>   <td> <center>YC</center> <td> ADHR986: SW1.12

 *  </table>
 *  <BR>
 *
 *  @note $Id: COMDefines.h 7717 2016-05-23 19:29:02Z yijing $ <BR>
 *  @note
 *  <i> All rights reserved.  Copyright 2006.  Archangel Systems, Inc. </i> <BR>
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/

/* Conditional Include of the header file. */
#ifndef COMDEFINES_HEADER
   #define COMDEFINES_HEADER

/* Pound Defines for Numbers. */
   /* unsigned integers */
   /**
    * Integer zero.
    * This value represents zero as an unsigned integer.
    */
   #define ZERO  0U
   /**
    * Integer ONE.
    * This value represents one as an unsigned integer.
    */
   #define ONE   1U
   /**
    * Integer TWO.
    * This value represents two as an unsigned integer.
    */
   #define TWO   2U
   /**
    * Integer THREE.
    * This value represents three as an unsigned integer.
    */
   #define THREE 3U
   /**
    * Integer FOUR.
    * This value represents four as an unsigned integer.
    */
   #define FOUR  4U
   /**
    * Integer FIVE.
    * This value represents five as an unsigned integer.
    */
   #define FIVE  5U
   /**
    * Integer SIX.
    * This value represents six as an unsigned integer.
    */
   #define SIX   6U
   /**
    * Integer SEVEN.
    * This value represents seven as an unsigned integer.
    */
   #define SEVEN 7U
   /**
    * Integer Eight.
    * This value represents eight as an unsigned integer.
    */
   #define EIGHT 8U
   /**
    * Integer NINE.
    * This value represents nine as an unsigned integer.
    */
   #define NINE  9U

   /* signed integers */
   /**
    * Integer zeros.
    * This value represents zero as a signed integer.
    */
   #define ZEROS 0

   /* floats */
   /**
    * Float zero.
    * This value represents zero as a floating point number.
    */
   #define ZEROF     0.0f
   /* floats */
   /**
    * Float zero limit.
    * This value represents value below this number will be rounded to zero.
    */
   #define ZERO_LIMIT     0.000000001f
   /**
    * Float half.
    * This value represents half as a floating point number.
    */
   #define ONE_HALF  0.5f
   /**
    * Float One.
    * This value represents one as a floating point number.
    */
   #define ONEF      1.0f

   /* Pound Defines for True/False. */
   /**
     * Boolean true.
     * This value represents a Boolean true condition.
     */
   #define TRUE  ONE
   /**
     * Boolean false.
     * This value represents a Boolean false condition.
     */
   #define FALSE ZERO

   /* Pound Defines for Yes/No. */
   /**
     * Boolean Yes.
     * This value represents a Boolean true condition.
     */
   #define YES ONE
      /**
       * Boolean NO.
       * This value represents a Boolean false condition.
       */
   #define NO  ZERO

   /* Pound Defines for Good/Bad. */
   /**
     * Boolean GOOD
     * This value represents a Boolean true condition.
     */
   #define GOOD ONE
   /**
     * Boolean BAD
     * This value represents a Boolean false condition.
     */
   #define BAD  ZERO

   /* Pound Defines for Sucess/Failure. */
   /**
    * Boolean Success
    * This value represents a Boolean true condition.
    */
   #define SUCCESS GOOD
   /**
    * Boolean Failure.
    * This value represents a Boolean false condition.
    */
   #define FAILURE BAD

   /* Pound Defines for On/Off. */
   /**
    * Boolean ON
    * This value represents a Boolean true condition.
    */
   #define ON  ONE
   /**
     * Boolean OFF
     * This value represents a Boolean false condition.
     */
   #define OFF ZERO

   /* Pound Defines for Set/Clear. */
   /**
     * Boolean SET
     * This value represents a Boolean True condition.
     */
   #define SET   ONE
   /**
     * Boolean CLEAR
     * This value represents a Boolean false condition.
     */
   #define CLEAR ZERO

   /* Pound Defines for Size of compiler defined data types. */
   /**
     * Size of compiler
     * This value represents a total number of bytes in Float.
     */
   #define NUMBER_OF_BYTES_PER_FLOAT 4U
   /**
     * Size of compiler
     * This value represents a total number of bytes in Integer.
     */
   #define NUMBER_OF_BYTES_PER_INT   2U
   /**
     * Size of compiler
     * This value represents a total number of bytes in Character.
     */
   #define NUMBER_OF_BYTES_PER_CHAR  1U
   /**
     * Size of compiler
     * This value represents Number of 16 Bit float in 32 Bit float.
     */
   #define NUMBER_OF_U16_PER_F32     2U
   /**
     * Size of compiler
     * This value represents Number of 8 Bit float in 32 Bit float.
     */
   #define NUMBER_OF_U8_PER_F32      4U
   /**
     * Size of compiler
     * This value represents Number of 16 Bit Integer in 32 Bit Integer.
     */
   #define NUMBER_OF_U8_PER_U16      2U
   /**
     * Size of compiler
     * This value represents Number of 8 Bit Integer in 32 Bit Integer.
     */
   #define NUMBER_OF_U8_PER_U32      4U

   /* Pound defines for the Persistance fault monitering. */
   /**
     * Persistance Fault monitering
     * This value represents transmit buffer overflow.
     */
   #define TRANSMIT_BUFFER_OVERFLOW    0U
   /**
     * Persistance Fault monitering
     * This value represents FLASP solution compare.
     */
   #define FLASP_SOLUTIONS_COMPARE     1U
   /**
     * Persistance Fault monitering
     * This value represents SPI communication timeout.
     */
   #define SPI_COMMUNICATION_TIMEOUT   2U
   /**
     * Persistance Fault monitering
     * This value represents Communication message received.
     */
   #define COMMUNICATION_MESSAGE_RECEIVED 3U

   /* Pound defines for calculating complement of a number. */
   /**
     * Complement of a number
     * This value represents for the hexadecimal number 2FF.
     */
   #define BIT2FF  0xFFU
   /**
     * Complement of a number
     * This value represents for the hexadecimal number 4FF.
     */
   #define BIT4FF  0xFFFFU
   /**
     * Complement of a number
     * This value represents for the hexadecimal number 8FF.
     */
   #define BIT8FF  0xFFFFFFFFU
   /**
     * Complement of a number
     * This value represents for the hexadecimal number 16FF.
     */
   #define BIT16FF 0xFFFFFFFFFFFFFFFFU

   /* Pound Defines for bit Mask. */
   /**
    * These are the unsigned hexadecimal numbers used for bit Mask.
    */
   #define BITMASK_0x00  0x00
   #define BITMASK_0x01  0x01U
   #define BITMASK_0x02  0x02U
   #define BITMASK_0x03  0x03U
   #define BITMASK_0x04  0x04U
   #define BITMASK_0x05  0x05U
   #define BITMASK_0x06  0x06U
   #define BITMASK_0x07  0x07U
   #define BITMASK_0x08  0x08U
   #define BITMASK_0x09  0x09U
   #define BITMASK_0x0A  0x0AU
   #define BITMASK_0x0B  0x0BU
   #define BITMASK_0x0C  0x0CU
   #define BITMASK_0x0D  0x0DU
   #define BITMASK_0x0E  0x0EU
   #define BITMASK_0x0F  0x0FU
   #define BITMASK_0x10  0x10U
   #define BITMASK_0x11  0x11U
   #define BITMASK_0x12  0x12U
   #define BITMASK_0x13  0x13U
   #define BITMASK_0x14  0x14U
   #define BITMASK_0x15  0x15U
   #define BITMASK_0x16  0x16U
   #define BITMASK_0x17  0x17U
   #define BITMASK_0x18  0x18U
   #define BITMASK_0x19  0x19U
   #define BITMASK_0x1A  0x1AU
   #define BITMASK_0x1B  0x1BU
   #define BITMASK_0x1C  0x1CU
   #define BITMASK_0x1D  0x1DU
   #define BITMASK_0x1E  0x1EU
   #define BITMASK_0x1F  0x1FU
   #define BITMASK_0x20  0x20U

   /* Pound Defines for Logical Shifts. */
   /**
    * These are the unsigned integer values used for Shifting the data.
    */
   #define SHIFT_0    0U
   #define SHIFT_1    1U
   #define SHIFT_2    2U
   #define SHIFT_3    3U
   #define SHIFT_4    4U
   #define SHIFT_5    5U
   #define SHIFT_6    6U
   #define SHIFT_7    7U
   #define SHIFT_8    8U
   #define SHIFT_9    9U
   #define SHIFT_10   10U
   #define SHIFT_11   11U
   #define SHIFT_12   12U
   #define SHIFT_13   13U
   #define SHIFT_14   14U
   #define SHIFT_15   15U
   #define SHIFT_16   16U
   #define SHIFT_17   17U
   #define SHIFT_18   18U
   #define SHIFT_19   19U
   #define SHIFT_20   20U
   #define SHIFT_21   21U
   #define SHIFT_22   22U
   #define SHIFT_23   23U
   #define SHIFT_24   24U
   #define SHIFT_25   25U
   #define SHIFT_26   26U
   #define SHIFT_27   27U
   #define SHIFT_28   28U
   #define SHIFT_29   29U
   #define SHIFT_30   30U
   #define SHIFT_31   31U
   #define SHIFT_32   32U

   /* Pound Defines for Array Index. */
   /**
    * These are the unsigned integer numbers used to avoid magic numbers.
    */
   #define NUMBER_0    0U
   #define NUMBER_1    1U
   #define NUMBER_2    2U
   #define NUMBER_3    3U
   #define NUMBER_4    4U
   #define NUMBER_5    5U
   #define NUMBER_6    6U
   #define NUMBER_7    7U
   #define NUMBER_8    8U
   #define NUMBER_9    9U
   #define NUMBER_10   10U
   #define NUMBER_11   11U
   #define NUMBER_12   12U
   #define NUMBER_13   13U
   #define NUMBER_14   14U
   #define NUMBER_15   15U
   #define NUMBER_16   16U
   #define NUMBER_17   17U
   #define NUMBER_18   18U
   #define NUMBER_19   19U
   #define NUMBER_20   20U
   #define NUMBER_21   21U
   #define NUMBER_22   22U
   #define NUMBER_23   23U
   #define NUMBER_24   24U
   #define NUMBER_25   25U
   #define NUMBER_26   26U
   #define NUMBER_27   27U
   #define NUMBER_28   28U
   #define NUMBER_29   29U
   #define NUMBER_30   30U
   #define NUMBER_31   31U
   #define NUMBER_32   32U
   #define NUMBER_33   33U
   #define NUMBER_34   34U
   #define NUMBER_35   35U
   #define NUMBER_36   36U
   #define NUMBER_37   37U
   #define NUMBER_38   38U
   #define NUMBER_39   39U
   #define NUMBER_40   40U
   #define NUMBER_41   41U
   #define NUMBER_42   42U
   #define NUMBER_43   43U
   #define NUMBER_44   44U
   #define NUMBER_45   45U
   #define NUMBER_46   46U
   #define NUMBER_47   47U
   #define NUMBER_48   48U
   #define NUMBER_49   49U
   #define NUMBER_50   50U
   #define NUMBER_51   51U
   #define NUMBER_52   52U
   #define NUMBER_53   53U
   #define NUMBER_54   54U
   #define NUMBER_55   55U
   #define NUMBER_56   56U
   #define NUMBER_57   57U
   #define NUMBER_58   58U
   #define NUMBER_59   59U
   #define NUMBER_60   60U
   #define NUMBER_61   61U
   #define NUMBER_62   62U
   #define NUMBER_63   63U
   #define NUMBER_64   64U
   #define NUMBER_65   65U
   #define NUMBER_66   66U
   #define NUMBER_67   67U
   #define NUMBER_68   68U
   #define NUMBER_69   69U
   #define NUMBER_70   70U
   #define NUMBER_71   71U
   #define NUMBER_72   72U
   #define NUMBER_73   73U
   #define NUMBER_74   74U
   #define NUMBER_75   75U
   #define NUMBER_76   76U
   #define NUMBER_77   77U
   #define NUMBER_78   78U
   #define NUMBER_79   79U
   #define NUMBER_80   80U
   #define NUMBER_81   81U
   #define NUMBER_82   82U
   #define NUMBER_83   83U
   #define NUMBER_84   84U
   #define NUMBER_85   85U
   #define NUMBER_86   86U
   #define NUMBER_87   87U
   #define NUMBER_88   88U
   #define NUMBER_89   89U
   #define NUMBER_90   90U
   #define NUMBER_91   91U
   #define NUMBER_92   92U
   #define NUMBER_93   93U
   #define NUMBER_94   94U
   #define NUMBER_95   95U
   #define NUMBER_96   96U
   #define NUMBER_97   97U
   #define NUMBER_98   98U
   #define NUMBER_99   99U
   #define NUMBER_100  100U
   #define NUMBER_101  101U
   #define NUMBER_102  102U
   #define NUMBER_103  103U
   #define NUMBER_104  104U
   #define NUMBER_105  105U
   #define NUMBER_106  106U
   #define NUMBER_107  107U
   #define NUMBER_108  108U
   #define NUMBER_109  109U
   #define NUMBER_110  110U
   #define NUMBER_111  111U
   #define NUMBER_112  112U
   #define NUMBER_113  113U
   #define NUMBER_114  114U
   #define NUMBER_115  115U
   #define NUMBER_116  116U
   #define NUMBER_117  117U
   #define NUMBER_118  118U
   #define NUMBER_119  119U
   #define NUMBER_120  120U
   #define NUMBER_121  121U
   #define NUMBER_122  122U
   #define NUMBER_123  123U
   #define NUMBER_124  124U
   #define NUMBER_125  125U
   #define NUMBER_126  126U
   #define NUMBER_127  127U
   #define NUMBER_128  128U
   #define NUMBER_129  129U
   #define NUMBER_130  130U
   #define NUMBER_131  131U
   #define NUMBER_132  132U
   #define NUMBER_133  133U
   #define NUMBER_134  134U
   #define NUMBER_135  135U
   #define NUMBER_136  136U
   #define NUMBER_137  137U
   #define NUMBER_138  138U
   #define NUMBER_139  139U
   #define NUMBER_140  140U
   #define NUMBER_141  141U
   #define NUMBER_142  142U
   #define NUMBER_143  143U
   #define NUMBER_144  144U
   #define NUMBER_145  145U
   #define NUMBER_146  146U
   #define NUMBER_147  147U
   #define NUMBER_148  148U
   #define NUMBER_149  149U
   #define NUMBER_150  150U
   #define NUMBER_154  154U
   #define NUMBER_158  158U
   #define NUMBER_162  162U
   #define NUMBER_166  166U
   #define NUMBER_255  255U
   #define NUMBER_256  256U
   #define NUMBER_500  500U

   /**
    * This value represents unsigned integer one as a row.
    */
   #define ONE_ROW       1u
   /**
    * This value represents unsigned integer one as a column.
    */
   #define ONE_COLUMN    1u
   /**
    * This value represents unsigned integer one as VALID.
    */
   #define VALID         1u
   /**
    * This value represents unsigned integer zero as a INVALID.
    */
   #define INVALID         0
   /**
    * This value represents Floating point zero.
    */
   #define F32_ZERO ZEROF

   /**
    * This value represents Hexadecimal value FFFF.
    */
   #define HEX_FFFF 0xFFFF

   /**
    * This value represents Hexadecimal value 0100.
    */
   #define HEX_0100 0x0100


/* End of COMDefines.h Module. */
#endif

