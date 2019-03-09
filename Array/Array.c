#include <stdio.h>
#include <stdlib.h>
#include "Array.h"

VOID
ArrayLongestIncreasingSubArrayLength(PLONG Array, ULONG NumElements)

/**
Prints the length of the Longest Increasing Subarray
**/

{
    ULONG MaxLength;
    ULONG CurrentLength;

    MaxLength = 1;
    CurrentLength = 1;

    if (Array == NULL) {
        return;
    }

    for (unsigned int i = 0; i < NumElements - 1; i++) {
        if (Array[i] < Array[i + 1]) {
            CurrentLength++;
        } else {
            if (CurrentLength > MaxLength) {
                MaxLength = CurrentLength;
            }

            CurrentLength = 1;
        }
    }

    if (CurrentLength > MaxLength) {
        MaxLength = CurrentLength;
    }

    wprintf(L"Longest Increasing SubArray: %lu\n", MaxLength);
}