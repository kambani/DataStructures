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