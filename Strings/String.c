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

LONG
StringCharAt(__in const wchar_t* string, __in PCHAR character, BOOL fromLast) 

/**
Find the first occurance of a character in a given null terminated string
fromLast flag to be set true when one desires traversal to be done from the 
end of the string.
**/

{

	ULONG StringLength;
	if (string == NULL || character == NULL) {
		return -1;
	}

	StringLength = StringiGetLength(string);

	if (!fromLast) {
		for (int i = 0; string[i]; i++) {
			if (string[i] == *character) {
				return i;
			}
		}
	} else {
		for (int i = StringLength - 1; i >= 0; i--) {
			if (string[i] == *character) {
				return i;
			}
		}
	}

	return -1;
}

LONG
StringSubstringBoyerMoore(__in const wchar_t* string, __in const wchar_t* pattern)

/**
Uses BoyerMoore method to check if pattern appears in a string.
Returns the position if there is a match else -1.
Strings should be null terminated.
**/

{
	LONG i;
	LONG j;
	size_t PatternLength;
	size_t StringLength;

	if (string == NULL || pattern == NULL) {
		return -1;
	}

	PatternLength = StringiGetLength(pattern);
	StringLength = StringiGetLength(string);
	i = j = PatternLength - 1;
	while (i < StringLength) {
		while (j >= 0) {
			if (pattern[j] != string[i]) {
				break;
			}

			j--;
			i--;
		}

		if (j < 0) {
			return i + 1;
		}

		i = i + PatternLength - min(j, StringCharAt(pattern, &string[i], TRUE) + 1);
		j = PatternLength - 1;
	}

	return -1;
}

BOOLEAN
StringIsStringRotationOf(__in const wchar_t* ParentString, __in const wchar_t* String)

/**
Checks if given string is just a rotation of ParentString.
**/

{
	size_t Length;
	wchar_t* temp;
	if (ParentString == NULL || String == NULL) {
		return FALSE;
	}

	Length = StringiGetLength(ParentString);
	temp = (wchar_t*)malloc(2 * Length + 1);
	memcpy(temp, ParentString, Length * sizeof(wchar_t));
	memcpy((temp + Length), ParentString, Length * sizeof(wchar_t));
	temp[Length + Length + 1] = L"\o";

	return (StringSubstringBrutForce(ParentString, String)!= -1) ;
}

BOOLEAN
StringCheckIfAsciiStringsHaveIdenticalCharCount(__in const wchar_t* string1, __in const wchar_t* string2)

/**
Function checks if the strings have identical character count.
For Ascii strings only.
**/

{
	LONG CharacterCount[ASCII_CHARACTER_COUNT];
	memset(&CharacterCount, 0, sizeof(CharacterCount));

	if (string1 == NULL || string2 == NULL) {
		return FALSE;
	}

	if (StringiGetLength(string1) != StringiGetLength(string2)) {
		return FALSE;
	}

	for (int i = 0; string1[i]; i++) {
		CharacterCount[string1[i]]++;
	}

	for (int i = 0; string2[i]; i++) {
		if (--CharacterCount[string2[i]] < 0) {
			return FALSE;
		}
	}

	return TRUE;
}