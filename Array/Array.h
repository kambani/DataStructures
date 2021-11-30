#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>


VOID
ArrayLongestIncreasingSubArrayLength(PLONG Array, ULONG NumElements);

VOID
ArrayStockMarketBuySellNTimes(PULONG Array, ULONG NumElements);

PLONG
ArrayLongestIncreasingsubsequence(__in PLONG Array, __in ULONG NumElements, __out PULONG SubArrayLen);

LONG
ArrayMaxSubArraySum(__in PLONG Array, __in ULONG NumElements);

LONG
ArrayMaxSubArraySumCircular(__in PLONG Array, __in ULONG NumElements);