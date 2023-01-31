/* Filename: COMIIRDifferentiator.c
 *
 * Date: 2 August 2022
 * 
 * Author: Henry Gilbert
 * 
 * Description: Implementation of IIR Differentiator data structure. 
 * 
 * All Rights Reserved. Copyright Archangel Systems 2022
 */


/**************  Included File(s) **************************/
#include "COMIIRDifferentiator.h"
#include <stddef.h>

/**************  Function Definition(s) ********************/

/* Function: IIRDifferentiatorSetup
 *
 * Description: Setups an IIR differentiator instance based on an 
 *      input K1 coefficient value and the desired sampling rate. 
 * 
 * Return: None (void)
 * 
 * Requirement Implemented: REL.0104.S.IOP.8.001
 */
void IIRDifferentiatorSetup(IIRDiff_Filter * const IIRDiff,
                            const float K1,
                            const float samplingRate,
                            const float upperLimit,
                            const float lowerLimit,
                            const float upperDelta,
                            const float lowerDelta)
{
    if(NULL == IIRDiff)
    {
        return;
    }

    IIRDiff->config.k1 = K1;
    IIRDiff->config.k2 = 1.00f - K1;
    IIRDiff->config.samplingRate_Hz = samplingRate;
    IIRDiff->config.upperDelta = upperDelta;
    IIRDiff->config.lowerDelta = lowerDelta;
    IIRDiff->config.upperLimit = upperLimit;
    IIRDiff->config.lowerLimit = lowerLimit;
    return;
}

/* Function: IIRDifferentiatorReset
 *
 * Description: Reset an IIR differentiator instance's past output and 
 *      past input to zero. 
 * 
 * Return: None (void)
 * 
 * Requirement Implemented: REL.0104.S.IOP.8.002
 */
void IIRDifferentiatorReset(IIRDiff_Filter * const IIRDiff)
{
    IIRDiff->pastOutputOfDiff = 0.0f;
    IIRDiff->pastInputOfDiff = 0.0f;
    IIRDiff->preloadValue = DIFF_PRELOAD_FLAG_SET;
    return;
}

/* Function: IIRDifferentiatorPreload
 *
 * Description: Preloads an IIR Differentiator instance. 
 * 
 * Return: None (void)
 * 
 * Requirement Implemented: REL.0104.S.IOP.8.003
 */
void IIRDifferentiatorPreload(const float preloadValue,
                              IIRDiff_Filter * const IIRDiff)
{
    /* set the past input of the filter to the preload value */
    IIRDiff->pastInputOfDiff = preloadValue;
    IIRDiff->pastOutputOfDiff = 0.0f;
    IIRDiff->preloadValue = DIFF_PRELOAD_FLAG_CLEAR;
    return;
}

/* Function: IIR_Differentiator_Limited
 *
 * Description: Performs an IIRDifferentiation and limits the value to
 *      between -180 and +180. Used for rollover transitions. 
 * 
 * Return: Filtered output value 
 * 
 * Requirement Implemented: REL.0104.S.IOP.8.004
 */
float IIR_Differentiator_Limited(const float input,
                                 IIRDiff_Filter * const IIRDiff)
{
    float filteredOutput;
    float valueToAdd;

    if(IIRDiff->preloadValue == DIFF_PRELOAD_FLAG_SET)
    {
        IIRDifferentiatorPreload(input,
                                 IIRDiff);
    }

    /* Implement filter K2-Gain, K1 - coef    */
    valueToAdd = input - IIRDiff->pastInputOfDiff;

    /* If input is more than +180.0 , subtract 360 until it becomes < 180 */
    while( valueToAdd > IIRDiff->config.upperLimit )
    {
        valueToAdd += IIRDiff->config.lowerDelta;
    }

    /* If input is less than -180.0 , add 360 until it becomes > 180.0 */
    while( valueToAdd < IIRDiff->config.lowerLimit )
    {
        valueToAdd += IIRDiff->config.upperDelta;
    }

    /* Implement filter */
    filteredOutput = IIRDiff->config.k2 * IIRDiff->config.samplingRate_Hz * valueToAdd
            + IIRDiff->config.k1 * IIRDiff->pastOutputOfDiff;

    /* Rotate past values */
    IIRDiff->pastOutputOfDiff = filteredOutput;
    IIRDiff->pastInputOfDiff = input;

    return filteredOutput;
}

/* End of COMIIRDifferentiator.c source file. */
