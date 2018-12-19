#include <ntstatus.h>
#include <stdio.h>
#include <stdlib.h>
#include "String.h"

BOOLEAN
StringCheckIfAllCharactersUnique(__in const wchar_t* string)

/**
Checks if a given string has all characters unique.
Operates on a wide char unicode string.
Currently compatible on 64 bit machines only.
**/

{
	ULONG64 Mask;
	typedef struct _BitMap {
		ULONG64 First;
		ULONG64 Second;
		ULONG64 Third;
		ULONG64 Fourth;
	} BitMap;

	BitMap bm = { 0 };

	for (int i = 0; string[i]; i++) {
		Mask = 1UI64 << (string[i] % WORD_SIZE);

		switch (string[i] / WORD_SIZE) {
		case 0:
			if ((bm.First & Mask) != 0) {
				return FALSE;
			} else {
				bm.First |= Mask;
			}

			break;
		case 1:
			if ((bm.Second & Mask) != 0) {
				return FALSE;
			} else {
				bm.Second |= Mask;
			}

			break;
		case 2:
			if ((bm.Third & Mask) != 0) {
				return FALSE;
			} else {
				bm.Third |= Mask;
			}

			break;
		case 3:
			if ((bm.Fourth & Mask) != 0) {
				return FALSE;
			} else {
				bm.Fourth |= Mask;
			}
			break;
		}
	}

	return TRUE;
}

size_t
StringiGetLength(__in const wchar_t* string)

/**
calculates the length of a string.
String expected to end with null terminator.
**/

{
	size_t size = 0;
	if (string == NULL) {
		return (ULONG)-1;
	}

	for (int i = 0; string[i]; i++) {
		size++;
	}

	return size;
}

VOID
StringReverse(__in wchar_t* string, __in_opt size_t size)

/**
Reverses a string in place.
Size to be passed if the string is not null terminated.
**/

{
	wchar_t* temp;
	if (string == NULL) {
		return;
	}

	if (size <= 0) {
		size = StringiGetLength(string);
	}

	size--;
	for (int i = 0; i <= size/2; i++) {
		temp = string[i];
		string[i] = string[size - i];
		string[size - i] = temp;
	}
}

LONG
StringSubstringBrutForce(__in const wchar_t* string, __in const wchar_t* pattern)

/**
Uses brut force method to check if pattern appears in a string.
Returns the position if there is a match else -1.
Strings should be null terminated.
**/

{
	int j;
	size_t PatternLength;

	if (string == NULL || pattern == NULL) {
		return -1;
	}

	//
	// Since usually patterns are of resonable size 
	// than input string we try to avoid taking length of string
	// and just work with length of pattern
	//
	j = 0;
	PatternLength = StringiGetLength(pattern);

	for (int i = 0; string[i + PatternLength -1]; i++) {
		for (j = 0; pattern[j]; j++) {
			if (string[i + j] != pattern[j]) {
				break;
			}
		}

		if (!pattern[j]) {
			return i;
		}
	}

	return -1;
}