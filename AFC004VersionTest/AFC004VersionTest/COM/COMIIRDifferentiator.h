/* Filename: COMIIRDifferentiator.h
 *
 * Author: Henry Gilbert
 * 
 * Date: 2 August 2022
 * 
 * Description: Public interface to IIR differentiator functions and type declaration
 * 
 * All Rights Reserved. Copyright Archangel Systems 2022
 *
 */

#ifndef _COMIIRDIFFERENTIATOR_H
#define _COMIIRDIFFERENTIATOR_H

/**************  Included File(s) **************************/
#include <stdint.h>


/**************  Macro Definition(s) ***********************/
#define DIFF_PRELOAD_FLAG_SET   1         
#define DIFF_PRELOAD_FLAG_CLEAR 0         

/**************  Type Definition(s) ************************/
typedef struct
{
    /* Configurable settings */
    struct
    {
        /* Base configuration */
        float k1;
        float k2;
        float samplingRate_Hz;
        
        /* Limited differentiation limits and deltas*/
        float upperLimit;
        float lowerLimit;
        float upperDelta;
        float lowerDelta;
    } config;

    /* Updated based on differentiated values */
    float pastOutputOfDiff;
    float pastInputOfDiff;
    uint8_t preloadValue;

} IIRDiff_Filter;


/**************  Function Prototype(s) *********************/
void IIRDifferentiatorSetup(IIRDiff_Filter * const IIRDiff,
        const float K1,
        const float samplingRate,
        const float upperLimit,
        const float lowerLimit,
        const float upperDelta,
        const float lowerDelta);

void IIRDifferentiatorReset(IIRDiff_Filter * const IIRDiff);

void IIRDifferentiatorPreload(const float preloadValue,
        IIRDiff_Filter * const IIRDiff);

float IIR_Differentiator_Limited(const float input,
        IIRDiff_Filter * const IIRDiff);

#endif
/* End of COMIIRDifferentiator.h header file. */
