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

VOID
ArrayStockMarketBuySellNTimes(PULONG Array, ULONG NumElements)

/**
Maximize profit out of the given stock prices.
Unlike some solutions on the internet, were the transactions are 
limited to N, here N = Max times. IF N is provided then we will
have to store all the transactions, sort them and then pick the max out of it.
In internet they all go through DP.
**/

{
    ULONG Buy;
    ULONG Sell;
    ULONG MaxProfit;

    if (Array == NULL) {
        return;
    }

    Buy = Array[0];
    MaxProfit = 0;

    for (unsigned int i = 1; i < NumElements - 1; i++) {

        if (Array[i - 1] < Array[i] && Array[i + 1] < Array[i]) {
            //
            // Reached the Peak. Realise the profits
            //
            MaxProfit += Array[i] - Buy;
            Sell = Array[i];
            wprintf(L"Buy: %d. Sell: %d\n", Buy, Sell);
            continue;
        }
        //{ 12, 14, 17, 10, 14, 13, 12, 15 };
        if (Array[i - 1] > Array[i] && Array[i + 1] > Array[i]) {
            //
            // Time to update the buy.
            //
            Buy = Array[i];
        }
    }

    //
    // Check the last element if we can sell
    //
    if (Array[NumElements - 1] > Buy) {
        MaxProfit += Array[NumElements - 1] - Buy;
        Sell = Array[NumElements - 1];
        wprintf(L"Buy: %d. Sell: %d\n", Buy, Sell);
    }

    wprintf(L"Max Profit is: %d\n", MaxProfit);
}


PLONG
ArrayLongestIncreasingsubsequence(__in PLONG Array, __in ULONG NumElements, __out PULONG SubArrayLen)

/**
Longest Increasing Subsequence. Returns in a newly formed array
**/

{
    PULONG LIArray;
    ULONG i;
    LONG j;
    ULONG MaxIndex;
    ULONG MaxLen;
    LONG Prev;
    ULONG PrevIndex;
    PLONG NewArray;

    if (Array == NULL) {
        return;
    }

    MaxIndex = 0;
    MaxLen = 0;
    LIArray = malloc(sizeof(ULONG) * NumElements);
    for (i = 0; i < NumElements; i++) {
        LIArray[i] = 1;
    }

    for (i = 1; i < NumElements; i++) {
        for (j = 0; j < i; j++) {
            if (Array[j] < Array[i]) {
                LIArray[i] = max(LIArray[i], (LIArray[j] + 1));
                if (LIArray[i] > MaxLen) {
                    MaxLen = LIArray[i];
                    MaxIndex = i;
                }
            }
        }
    }

    *SubArrayLen = MaxLen;
    Prev = Array[MaxIndex];
    PrevIndex = MaxIndex;
    NewArray = malloc(sizeof(LONG) * MaxLen);

    MaxLen = MaxLen - 1;
    NewArray[MaxLen--] = Prev;
    for (j = MaxIndex - 1; j >= 0; j--) {
        if (Array[j] < Prev && ((LIArray[PrevIndex] - LIArray[j]) == 1)) {
            NewArray[MaxLen--] = Array[j];
            Prev = Array[j];
            PrevIndex = j;
        }
    }

    return NewArray;
}

LONG
ArrayMaxSubArraySum(__in PLONG Array, __in ULONG NumElements)

/**
Max SubArray Sum via Kadane's
**/

{
    LONG CurrentSum;
    LONG MaxSum;
 
    if (Array == NULL) {
        return LONG_MIN;
    }

    CurrentSum = Array[0];
    MaxSum = Array[0];

    for (unsigned int i = 1; i < NumElements; i++) {
        CurrentSum = max(Array[i], Array[i] + CurrentSum);
        MaxSum = max(MaxSum, CurrentSum);
    }

    return CurrentSum;
}

LONG
ArrayMaxSubArraySumCircular(__in PLONG Array, __in ULONG NumElements)

/**
Max SubArray Sum when circular boundries are allowed
Geek for Geeks for more details.
MaxSubArray (if we have to go circular/Wrapping) = 
Sum of All elements - SubArraySum of non wrapping
**/

{
    LONG SubArraySumLinear;
    LONG SubArraySumNonParticipating;
    LONG TotalSum;

    if (Array == NULL) {
        return LONG_MIN;
    }

    TotalSum = LONG_MIN;
    SubArraySumLinear = ArrayMaxSubArraySum(Array, NumElements);

    //
    // Find the SubArray Sum of non Wrapping elements.
    // now the reason we have to wrap is because there are alot of
    // negative elements in between. So lets take subarray sum of them,
    // by reversing the sign of all. 
    // and while we there, also calculate the total
    //

    for (unsigned int i = 0; i < NumElements; i++) {
        TotalSum += Array[i];
        Array[i] = -Array[i];
    }

    SubArraySumNonParticipating = ArrayMaxSubArraySum(Array, NumElements);

    //
    // Either its the LinearSubArraySum or Sum - SubArraySum of Non Participating elements (Wrapping case)
    //

    return max((SubArraySumNonParticipating + TotalSum), SubArraySumLinear);
}