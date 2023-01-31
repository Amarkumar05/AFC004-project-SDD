/* Filename: CircularBuffer.c
 * 
 * Author: Henry Gilbert
 * 
 * Date: 11 April 2022
 * 
 * Description: Source code to implement circular buffer data structure. 
 *
 ****Copyright 2022 Archangel Systems - All Rights Reserved. *****/


/**************  Included File(s) **************************/
#include "CircularBuffer.h"

/**************  Macro Definition(s) ***********************/
#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif


/**************  Function Definition(s) ********************/

/*
 * Function: cb_push
 * 
 * Description: Pushes a byte to the byte circular buffer, at the buffer's head pointer.  
 * 
 * Return: None
 * 
 * Requirement Implemented: INT1.0102.S.IOP.3.001
 */
void cb_push( circBuffer_t * const cb, /* Pointer to circular buffer struct*/
              const uint8_t data ) /* Input data to be pushed */
{
    size_t offset = cb->head + 1;
    if (offset >= cb->capacity)
    {
        offset = 0;
    }
    if (offset != cb->tail) /* Head-tail wraparound protection */
    {
        cb->data[cb->head] = data;
        cb->head = offset;
    }
    return;
}

/*
 * Function:  cb_pop
 * 
 * Description: Returns an 8bit value at the circular buffer's tail index. 
 *
 * Return: Data popped from the circular buffer's tail pointer. 
 * 
 * Requirement Implemented:  INT1.0102.S.IOP.3.002
 */
uint8_t cb_pop( circBuffer_t * const cb ) /* Pointer to circular buffer struct */
{
    uint8_t data;
    if (cb->head != cb->tail)
    {
        data = cb->data[cb->tail];
        cb->tail += 1;
        if (cb->tail >= cb->capacity)
        {
            cb->tail -= cb->capacity;
        }
    }
    else
    {
        data = 0; // Don't want this 
    }
    return data;
}

/* 
 * Function: cb_reset
 * 
 * Description: Sets circular buffer head and tail values to zero
 * 
 * Return: None
 * 
 * Requirement Implemented: INT1.0102.S.IOP.3.003
 */
void cb_reset( circBuffer_t * const cb ) /* Pointer to circular buffer struct */
{
    cb->head = 0;
    cb->tail = 0;
    return;
}

/*
 * Function: cb_peek
 * 
 * Description: Peeks at circular buffer's nth index 
 * 
 * Return: Value at the circular buffer's input index
 * 
 * Requirement Implemented:  INT1.0102.S.IOP.3.004
 */
uint8_t cb_peek( const circBuffer_t * const cb, /* Pointer to circular buffer struct */
                 const size_t offset ) /* Offset value to peek at */
{
    size_t idx = cb->tail + offset;
    if (idx >= cb->capacity)
    {
        idx -= cb->capacity;
    }
    return cb->data[idx];
}

/*
 * Function: cb_bytesUsed 
 * 
 * Description: Returns bytes used by circular buffer.  
 *              Accounts for head-tail wraparound. 
 * 
 * Return: None
 * 
 * Requirement Implemented: INT1.0102.S.IOP.3.005
 */
size_t cb_bytesUsed( const circBuffer_t * const cb ) /* Pointer to circular buffer struct */
{
    return (cb->head >= cb->tail) ? cb->head - cb->tail : cb->capacity - (cb->tail - cb->head);
}

/*
 * Function:  cb_advanceTail
 *
 * Description:  Advances tail by the specified amount of indices
 * 
 * Return: None
 * 
 * Requirement Implemented:  INT1.0102.S.IOP.3.006
 */
void cb_advanceTail( circBuffer_t * const cb, /* Pointer to circular buffer struct */
                     const size_t num )
{
    size_t maxAdvance;
    size_t advance;
    maxAdvance = (cb->tail > cb->head) ? cb->head + cb->capacity - cb->tail : cb->head - cb->tail;
    advance = min( num, maxAdvance );
    cb->tail += advance;
    if (cb->tail >= cb->capacity)
    {
        cb->tail -= cb->capacity;
    }
    return;
}

/*
 * Function:  cb_flushOut
 *
 * Description:  Flushes data out of circular buffer to destination buffer
 * 
 * Return: Number of bytes flushed out 
 * 
 * Requirement Implemented:  INT1.0102.S.IOP.3.007
 */
size_t cb_flushOut( circBuffer_t * const cb, /* Pointer to circular buffer struct */
                    uint8_t * const destBuff, /* Buffer to store data to */
                    const size_t numBytesToFlush )
{
    /* Sanity checks */
    if ((cb == NULL) ||
            (cb->data == NULL) ||
            (numBytesToFlush > cb->capacity)) // todo test this 
    {
        /* Error! Invalid inputs */
        return 0;
    }

    if ((cb->head > cb->capacity) ||
            (cb->tail > cb->capacity))
    {
        /* Error! Unexpected buffer parameters */
        cb_reset( cb );
        return 0;
    }

    size_t sz = cb_bytesUsed( cb );
    if (0 == sz)
    {
        return 0;
    }
    size_t contiguous = min( cb->capacity - cb->tail, sz );
    size_t wrapped = sz - contiguous; // Equals zero if no wrap around

    uint8_t* cbAddr = cb->data + cb->tail;
    size_t maxCount = min( contiguous, numBytesToFlush );
    size_t count;
    for (count = 0; count < maxCount; count++)
    {
        destBuff[count] = cbAddr[count];
    }

    size_t written = maxCount;
    cb_advanceTail( cb, maxCount );

    /* Exit if failed to write everything tried to write, or if there's nothing left to write. */
    if (written != contiguous || wrapped == 0)
    {
        return written;
    }

    maxCount = min( wrapped, numBytesToFlush - contiguous );
    cbAddr = cb->data;
    for (count = 0; count < maxCount; count++)
    {
        destBuff[count + contiguous] = cbAddr[count];
    }

    written += maxCount;
    cb_advanceTail( cb, maxCount );

    return written;
}

/*
 * Function:  cb_flushIn
 *
 * Description:  Flushes data into circular buffer from a source buffer
 * 
 * Return: Number of bytes flushed in
 * 
 * Requirement Implemented:  INT1.0102.S.IOP.3.008
 */
size_t cb_flushIn( circBuffer_t * const cb, /* Pointer to circular buffer struct */
                   uint8_t * const srcBuff, /* Buffer to read data from */
                   const size_t numBytesToFlush ) /* Number of bytes to flush in */
{
    /* Sanity checks */
    if ((cb == NULL) ||
            (cb->data == NULL))
    {
        /* Error! Invalid inputs */
        return 0;
    }

    if ((cb->head > cb->capacity) ||
            (cb->tail > cb->capacity))
    {
        /* Error! Unexpected buffer parameters */
        cb_reset( cb );
        return 0;
    }

    size_t numBytesReadIntoCB;

    /* If "head" < "tail" then there is just one block of buffer available to be written to. */
    if (cb->head < cb->tail)
    {
        /* Read in every available byte, up to "bytesFree" bytes, starting at "head". */
        numBytesReadIntoCB = min( cb->tail - cb->head - 1, numBytesToFlush );
        uint8_t* cbAddr = cb->data + cb->head;

        size_t idx;
        for (idx = 0; idx < numBytesReadIntoCB; idx++)
        {
            cbAddr[idx] = srcBuff[idx];
        }

        cb->head += numBytesReadIntoCB;
    }
    else
    { /* cb->head >= cb->tail */
        size_t blockSize = cb->capacity - cb->head;
        if (cb->tail == 0) /* Don't read into last buffer position if "tail" is at 0 position */
            blockSize--;

        numBytesReadIntoCB = min( blockSize, numBytesToFlush );
        uint8_t* cbAddr = cb->data + cb->head;

        size_t idx;
        for (idx = 0; idx < numBytesReadIntoCB; idx++)
        {
            cbAddr[idx] = srcBuff[idx];
        }

        cb->head += numBytesReadIntoCB;

        if (cb->head >= cb->capacity)
        { /* Added > condition just to be safe */
            cb->head = 0; /* Wrapped around the buffer */

            /* Try to read more starting at beginning of buffer */
            if (cb->tail != 0)
            { /* "tail" shouldn't normally be 0 at this point but just to be safe */
                size_t numBytesToRead2ndStep = min( cb->tail - 1, numBytesToFlush - numBytesReadIntoCB );

                uint8_t* cbAddr = cb->data;

                size_t idx;
                for (idx = 0; idx < numBytesToRead2ndStep; idx++)
                {
                    cbAddr[idx] = srcBuff[idx + numBytesReadIntoCB];
                }

                numBytesReadIntoCB += numBytesToRead2ndStep;
                cb->head += numBytesToRead2ndStep;
            }
        }
    }
    return numBytesReadIntoCB;
}
/* end CircularBuffer.c */
