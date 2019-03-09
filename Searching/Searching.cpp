#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include "Searching.h"


LONG
BinarySearch(PLONG Array, ULONG NumElements, LONG Element)

/**
Performs Simple binary search on the Array.
Returns position of the element in the array.
-1 on Element not found.
**/

{
	LONG Low;
	LONG High;
	LONG Mid;

	if (Array == NULL) {
		return -1;
	}

	Low = 0;
	High = NumElements - 1;

	while (Low <= High) {
		Mid = Low + (High - Low) / 2;
		if (Array[Mid] == Element) {
			return Mid;
		} else if (Array[Mid] > Element) {
			High = Mid - 1;
		} else {
			Low = Mid + 1;
		}
	}

	return -1;
}

LONG
FirstOccurrenceInSortedArray(PLONG Array, ULONG NumElements, LONG Element)

/**
Returns position of the element in the array.
-1 on Element not found.
**/

{
	LONG Low;
	LONG High;
	LONG Mid;
	LONG Index;

	if (Array == NULL) {
		return -1;
	}

	Low = 0;
	High = NumElements - 1;
	Index = -1;

	while (Low <= High) {
		Mid = Low + (High - Low) / 2;
		if (Array[Mid] == Element) {
			Index = Mid;
			High = Mid - 1;
		} else if (Array[Mid] > Element) {
			High = Mid - 1;
		} else {
			Low = Mid + 1;
		}
	}

	return Index;
}

LONG
FirstOccurenceGreaterThanKInSortedArray(PLONG Array, ULONG NumElements, LONG k)

/**
Finds the first occurrence of element greater than K 
in sorted array.
-1 On element not found
**/

{
	LONG Low;
	LONG High;
	LONG Mid;
	LONG Index;
	
	Low = 0;
	High = NumElements - 1;
	Index = -1;

	if (Array == NULL) {
		return -1;
	}

	while (Low <= High) {
		Mid = Low + (High - Low) / 2;
		if (Array[Mid] > k) {
			Index = Mid;
			High = Mid - 1;
		} else {
			Low = Mid + 1;
		}
	}

	return Index;
}

LONG
SearchSmallestInCyclicallySortedArray(PLONG Array, ULONG NumElements)

/**
Finds the smallest element in a cyclically sorted array.
All Elements have to be distinct.
**/

{
	LONG Low;
	LONG High;
	LONG Mid;
	LONG PrevNeighbor;
	LONG NextNeighbor;

	if (Array == NULL) {
		return -1;
	}

	Low = 0;
	High = NumElements - 1;

	while (Low <= High) {
		Mid = Low + (High - Low) / 2;
		PrevNeighbor = (Mid - 1) < 0 ? NumElements - 1 : Mid - 1;
		NextNeighbor = (Mid + 1) == NumElements ? 0 : Mid + 1;
		
		if (Array[PrevNeighbor] == Array[NextNeighbor]) {
			//
			// Case of 2 element Array
			//
			return Array[PrevNeighbor] < Array[Mid] ? 
				   PrevNeighbor : Mid;
		}

		if (Array[PrevNeighbor] > Array[Mid] &&
			Array[NextNeighbor] > Array[Mid]) {
			return Mid;
		}

		if (Array[Mid] > Array[High]) {
			Low = Mid + 1;
		}
		else {
			High = Mid - 1;
		}
	}

	return -1;
}

ULONG32
FindMissingIP32Bit(const char* FilePath)

/**
Takes a File of 32 bit IP addresses (in billions)
Finds the "first" potential IP Missing. Doesnt care for rest 
remaining entries.

32 bit IP Address means there will be 2^32 entries ~ 4 bil
= 4294967296
Lets say you have 4294967296 - 1 Entries, then find the missing entry.

Here is the logic:
If you have 2^32 entries. If you just consider upper 16 bits,
then they are 2^16 unique values, which is what Buckets below signifies.
Now 2^32 entries = 2^16 * (of these unique upper 2^16 values). Hence each
entry in the bucket below should fill upto exact 2^16 if there are 2^32 entries.
However, some ip/ips are missing hence one of the bucket/buckets will be < 2 ^16.

We gotta find that bucket.

Once you find that bucket, rescan the file and find all the entries that belong to
this bucket. The values will range from 0 to 2^16 as you know. Hence have a bit map
to indicate each of these values. for every value to find, set "valueth" bit in the
bit map. 

Now scan your bitmap. Find the bit i not set. Then i is the value of lower 16 bits.
return Upper16 bits appeneded with i to the user.

Returns -1 on errors and when no IP is missing.
**/

{
	FILE* File;
	ULONG32 Buckets[1 << 16] = {0};
	CHAR IpAddressString[32];
	ULONG32 IpAddress;
	ULONG Index;
	ULONG Lower16;
	ULONG32 LowerBitMap;
	ULONG32 Mask;

	if (FilePath == NULL) {
		return -1;
	}

	File = fopen(FilePath, "r");

	//
	// Fill up 
	//
	while (TRUE) {
		if (fgets(IpAddressString, 100, File) != NULL) {
			IpAddress = atoi(IpAddressString);
			Buckets[IpAddress >> 16]++;
		}
		else {
			break;
		}
	}

	//
	// Find the first bucket that is not completely filled.
	// Sure their might be many, but we just returning first
	// missing entry that should have been present.
	//
	for (Index = 0; Index < (1 << 16); Index++) {
		if (Buckets[Index] < (1 << 16)) {
			fseek(File, 0, SEEK_SET);
			LowerBitMap = 0;
			Mask = 0;

			//
			// Rescan the file, find all entries that fits 
			// into this bucket. Extract the lower 16 value of these entries.
			// In the bitmap, set the bitNumber which is = to this lower 16 value
			//
			while (fgets(IpAddressString, 100, File) != NULL) {
				IpAddress = atoi(IpAddressString);
				if ((IpAddress >> 16) == Index) {
					Mask = 1 << 16;
					Mask = Mask - 1;
					Lower16 = IpAddress & Mask;
					LowerBitMap = LowerBitMap | (1 << Lower16);
				}
			}

			//
			// Close the file
			//
			fclose(File);

			//
			// Now scan the Lower16 bit map and find the bit not set.
			// Had it been set at that bit location then, what would have been
			// its value (provided all other bit locations are 0). That value is the 
			// lower 16 value of the entry missing for this bucket. Upper 16 you already
			// know. Merge them and you have your missing entry.
			//
			for (unsigned int i = 0; i < (1 << 16); i++) {
				if ((LowerBitMap & (1 << i)) > 0) {
					return (Index << 16) | i;
				}
			}
		}
	}

	return -1;
}

LONG
BinarySearchInArrayOfUnknownLen(std::vector<int> Array, LONG k)

/**
Binary Search in an Array of unknown Length
Array has to be sorted else output is unknown
Array has to be in the form of vector because C/C++
does not throw exception on Out of Bounds error.
**/

{
	LONG p;
	LONG Low;
	LONG High;
	LONG Mid;
	LONG Index;

	p = 0;
	Index = 0;

	//
	// Probe the End of the Array.
	//
	while (TRUE) {
		try
		{
			Index = (1 << p) - 1;
			if (Array.at(Index) > k) {
				break;
			}
			else if (Array[Index] == k) {
				return Index;
			}
		}
		catch (exception &e)
		{
			UNREFERENCED_PARAMETER(e);
			break;
		}

		++p;
	}

	//
	// Now we have jumped 2^p -1 in every cycle and have reached a point
	// where K < Array[2^p -1]. Now K will be > Array[2^(p-1) -1], Why? Because else 
	// we would have exited from then while loop in previous round
	// Eg. If the element was at position 8 in a array of length 10
	// We'd go 0, 3, 7, 15 break
	// Now search from 8 (2^(p-1)) to 14 ((2 ^ p) - 2) where p = 4
	//
	Low = ((1 << (p - 1)));
	High = Index - 1; //i.e (2 ^ p) - 2;

	while (Low <= High) {
		try {
			Mid = Low + (High - Low) / 2;
			if (Array.at(Mid) == k) {
				return Mid;
			} else if (Array.at(Mid) > k) {
				High = Mid - 1;
			} else {
				Low = Mid + 1;
			}
		} catch (exception &e)
		{
			UNREFERENCED_PARAMETER(e);

			//
			// This is the Case where High
			// was way beyond the bounds of the Array
			// in the probing phase.
			// We have to keep going to left
			//
			High = Mid - 1;
		}
	}

	return -1;
}

VOID
FindMinAndMaxInArray(PLONG Array, ULONG NumElements)

/**
Find Min and Max simultanously in an Array
**/

{
	LONG Min;
	LONG Max;
	ULONG Index;
	LONG CurrentMin;
	LONG CurrentMax;

	Index = 0;
	if (Array == NULL || NumElements < 2) {
		return;
	}

	Min = Array[Index] < Array[Index + 1] ? Array[Index] : Array[++Index];
	Max = Index == 0 ? Array[++Index] : Array[0];

	Index++;
	for (; Index < NumElements - 1; Index = Index + 2) {
		CurrentMin = Array[Index] < Array[Index + 1] ? Array[Index] : Array[Index + 1];
		CurrentMax = Array[Index] > Array[Index + 1] ? Array[Index] : Array[Index + 1];

		if (CurrentMin < Min) {
			Min = CurrentMin;
		}

		if (CurrentMax > Max) {
			Max = CurrentMax;
		}
	}
	
	if (NumElements % 2 == 1) {
		//
		// Odd Number of elements
		// we have missed the last one
		//
		Min = Array[NumElements - 1] < Min ? Array[NumElements - 1] : Min;
		Max = Array[NumElements - 1] > Max ? Array[NumElements - 1] : Max;
	}

	wprintf(L"Min: %d. Max: %d", Min, Max);
}

unsigned int rand_interval(unsigned int min, unsigned int max)
{
	int r;
	const unsigned int range = 1 + max - min;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;

	/* Create equal size buckets all in a row, then fire randomly towards
	 * the buckets until you land in one of them. All buckets are equally
	 * likely. If you land off the end of the line of buckets, try again. */
	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}

LONG
iPartitionArray(PLONG Array, LONG Low, LONG High, LONG Pivot)

{
	LONG PivotValue;
	LONG Index;
	LONG temp;

	PivotValue = Array[Pivot];
	Array[Pivot] = Array[High];
	Array[High] = PivotValue;
	Index = Low;

	for (int i = Low; i < High; i++) {
		if (Array[i] > PivotValue) {
			temp = Array[i];
			Array[i] = Array[Index];
			Array[Index++] = temp;
		}
	}

	temp = Array[High];
	Array[High] = Array[Index];
	Array[Index] = temp;

	return Index;
}

LONG
FindKLargest(PLONG Array, ULONG NumElements, ULONG k)

/**
Finds the Kth largest element in a random array
**/

{
	LONG Low;
	LONG High;
	LONG p;

	if (Array == NULL) {
		return LONG_MIN;
	}

	Low = 0;
	High = NumElements - 1;

	while (Low <= High) {
		p = iPartitionArray(Array, Low, High, rand_interval(Low, High));
		if (p == k - 1) {
			return Array[p];
		} else if (p > k - 1) {
			High = p - 1;
		} else {
			Low = p + 1;
		}
	}

	return -1;
}

LONG
FindKthSmallestFromTwoSortedArray(PLONG Array1, ULONG NumElements1, PLONG Array2, ULONG NumElements2, ULONG K)

/**
Given two sorted arrays, find the kth smallest array.
**/

{
	ULONG Step;
	ULONG Index1;
	ULONG Index2;
	ULONG StepArray1;
	ULONG StepArray2;

	Index1 = 0;
	Index2 = 0;
	Step = 0;

	while ((Index1 + Index2) < K - 1) {
		Step = (K - Index1 - Index2) / 2;
		StepArray1 = Index1 + Step;
		StepArray2 = Index2 + Step;

		if ((StepArray1 - 1 < NumElements1) && 
			(StepArray2 - 1 >= NumElements2 || Array1[StepArray1 - 1] < Array2[StepArray2 - 1])) {
			Index1 = StepArray1;
		} else {
			Index2 = StepArray2;
		}
	}

	if ((Index1 < NumElements1) &&
		(Index2 >= NumElements2 || Array1[Index1] < Array2[Index2])) {
		return Array1[Index1];
	} else {
		return Array2[Index2];
	}
}

LONG
FindTheMissingElementInASequence(PLONG Array, ULONG N, ULONG NumElements)

/**
Given an array of length N-1 and Number N, find the element missing from 
range 1 to N
**/

{
	ULONG XOR1;
	ULONG XORArray;
	unsigned int i;

	if (NumElements != N - 1) {
		return LONG_MIN;
	}

	for (i = 1; i <= N; i++) {
		XOR1 = XOR1 ^ i;
	}

	for (i = 0; i < NumElements; i++) {
		XORArray = XORArray ^ Array[i];
	}

	//
	// Missing element.
	//
	return XOR1 ^ XORArray;
}

VOID
FindTheMisingAndRepeatingElement(PLONG Array, ULONG N, ULONG NumElements)

/**
Note: It doesnt matter in what order you xor. A XOR B XOR C = C XOR A XOR B
Hence you can club all xoring in one loop for this problem

Given an array of length N and Number N, find the element missing and the element 
repeating from range 1 to N.

Take XOR of array and (1 to N range). The output will be a number which has bits set
where the missing and repeating elements have their bits set.

Now find the first bit set from LSB from the above output.

Now XOR all elements from array and (1 to N range) which has that first bit set from LSB.
Output will be either missing element or the repeating element.
**/

{
	LONG XORArrayAndRange;
	LONG Mask;
	LONG MissingOrRepeatingElement;
	LONG FirstBitSet;

	FirstBitSet = 0;
	XORArrayAndRange = 0;
	Mask = 0;
	MissingOrRepeatingElement = 0;

	if (NumElements != N) {
		return;
	}

	//
	// XOR all elements in array and the range.
	//
	for (unsigned int i = 1; i <= N; i++) {
		XORArrayAndRange ^= i;
		XORArrayAndRange ^= Array[i - 1];
	}
	
	//
	// Find the first bit set from LSB.
	//
	Mask = ~(XORArrayAndRange - 1);
	FirstBitSet = XORArrayAndRange & Mask;

	//
	// XOR all the elements with the above bit set
	//
	for (unsigned int i = 1; i <= N; i++) {
		if (((FirstBitSet & i) > 0)) {
			MissingOrRepeatingElement ^= i;
		}

		if (((FirstBitSet & Array[i - 1]) > 0)) {
			MissingOrRepeatingElement ^= Array[i - 1];
		}
	}

	for (unsigned int i = 0; i < NumElements; i++) {
		if (Array[i] == MissingOrRepeatingElement) {
			wprintf(L"The repeating element is: %d\n", Array[i]);
			wprintf(L"The missing element is: %d\n", Array[i] ^ XORArrayAndRange);
			return;
		}
	}

	wprintf(L"The repeating element is: %d\n", MissingOrRepeatingElement ^ XORArrayAndRange);
	wprintf(L"The missing element is: %d\n", MissingOrRepeatingElement);
}

VOID
SearchArrayWithCloseEntries(PLONG Array, ULONG NumElements, LONG K)

/**
Find position of an element k if it exists.
The Array is a Close entry Array meaning difference between consecutive
elements is no more than 1
**/

{
	ULONG i = 0;
	if (Array == NULL) {
		return;
	}

	while (i < NumElements) {
		if (Array[i] != K) {
			i = i + abs((K - Array[i]));
		}

		if (Array[i] == K) {
			wprintf(L"%d ", i);
			i++;
		}
	}
}

LONG
FindMoreThanHalfRepeatingNumberInLargeArray(PLONG Array, ULONG NumElements)

/**
Given a very large array/stream how would you find most recurring element.
Provided important condition that the most recurring element occurs for more than
half the length of the array/stream
O(1) Space and only Single pass allowed
**/

{
	ULONG Count;
	ULONG i;
	LONG Candidate;

	Candidate = LONG_MIN;
	Count = 0;
	i = 0;

	while (i < NumElements) {
		if (Count == 0) {
			Candidate = Array[i];
			Count = 1;
		} else if (Candidate != Array[i]) {
			Count--;
		} else {
			Count++;
		}
	}

	return Candidate;
}