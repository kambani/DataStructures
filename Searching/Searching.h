#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS
#include <iostream>
#include <vector>

LONG
BinarySearch(PLONG Array, ULONG NumElements, LONG Element);

LONG
FirstOccurrenceInSortedArray(PLONG Array, ULONG NumElements, LONG Element);

LONG
FirstOccurenceGreaterThanKInSortedArray(PLONG Array, ULONG NumElements, LONG k);

LONG
SearchSmallestInCyclicallySortedArray(PLONG Array, ULONG NumElements);

ULONG32
FindMissingIP32Bit(const char* FilePath);

LONG
BinarySearchInArrayOfUnknownLen(std::vector<int> Array, LONG k);

VOID
FindMinAndMaxInArray(PLONG Array, ULONG NumElements);

LONG
FindKLargest(PLONG Array, ULONG NumElements, ULONG k);

LONG
FindKthSmallestFromTwoSortedArray(PLONG Array1, ULONG NumElements1, PLONG Array2, ULONG NumElements2, ULONG K);

LONG
FindTheMissingElementInASequence(PLONG Array, ULONG N, ULONG NumElements);

VOID
FindTheMisingAndRepeatingElement(PLONG Array, ULONG N, ULONG NumElements);

VOID
SearchArrayWithCloseEntries(PLONG Array, ULONG NumElements, LONG K);

LONG
FindMoreThanHalfRepeatingNumberInLargeArray(PLONG Array, ULONG NumElements);