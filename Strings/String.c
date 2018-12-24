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


VOID
StringCompressStringCharacterAndCount(__in const wchar_t* string, wchar_t** compressed)

/**
Compresses a null terminated string in Character<Count> fashion.
new memory is allocated on the heap for the user.
User's responsiblity to free the memory after use
If it computes the compressed string is bigger in length than original
then it returns NULL in compressed
**/

{
	PCHAR Character;
	ULONG Count;
	ULONG CompressedLength;
	WCHAR CountString[100];
	ULONG StringLength;
	ULONG Index;
	wchar_t* Output;

	if (string == NULL) {
		return;
	}

	Character = &string[0];
	CompressedLength = 0;
	Count = 0;
	StringLength = 0;
	Index = 0;
	Output = *compressed;

	for (int i = 0; string[i]; i++) {
		if (string[i] == *Character) {
			Count++;
		} else {
			_i64tow(Count, CountString, 10);
			CompressedLength += StringiGetLength(CountString);
			CompressedLength += 1;
			Character = &string[i];
			Count = 1;
		}

		//
		// While we are here, lets also compute string length
		//
		StringLength++;
	}

	_i64tow(Count, CountString, 10);
	CompressedLength += StringiGetLength(CountString);
	CompressedLength += 1;
	wprintf(L"The compressed Length is: %d\n", CompressedLength);

	//
	// Now lets create a buffer of required size.
	//

	if (CompressedLength > StringLength) {
		Output = NULL;
		return;
	} else {
		// One extra for the null terminator.
		Output = malloc((sizeof(wchar_t) * CompressedLength) + sizeof(wchar_t));
		Count = 0;
	}

	Character = &string[0];
	for (int i = 0; string[i]; i++) {
		if (string[i] == *Character) {
			Count++;
		}
		else {
			_i64tow(Count, CountString, 10);
			Output[Index++] = *Character;
			CompressedLength = StringiGetLength(CountString);
			wcscpy(&Output[Index], &CountString[0]);
			Index += CompressedLength;
			Character = &string[i];
			Count = 1;
		}
	}

	_i64tow(Count, CountString, 10);
	Output[Index++] = *Character;
	CompressedLength = StringiGetLength(CountString);
	wcscpy(&Output[Index], &CountString[0]);

	*compressed = Output;
}

VOID
Stringitoa_w(__out wchar_t* string, __in LONG number, ULONG base)

/**
Converts a given number with a base into wide char string.
Negative numbers supported for base 10 only.
**/
 
{
	ULONG Remainder;
	ULONG Index;
	BOOLEAN IsNegative;

	Index = 0;
	IsNegative = FALSE;
	if (string == NULL || base < 0) {
		return;
	}

	//
	// Negative numbers only supported for Decimal number
	//
	if (number < 0 && base == 10) {
		IsNegative = TRUE;
		number = -1 * number;
	}

	do {
		Remainder = number % base;
		string[Index++] = (Remainder >= 10)? 'A' + (Remainder - 10): Remainder + '0';
		number = number / base;
	} while (number != 0);

	if (IsNegative == TRUE) {
		string[Index++] = '-';
	}

	string[Index] = '\0';
	StringReverse(string, StringiGetLength(string));
}

LONG
Stringatoi_w(__in wchar_t* string)

/**
Standard C atoi function.
**/

{
	LONG ReturnValue = 0;
	ULONG Index = 0;
	BOOLEAN IsNegative = FALSE;
	if (string == NULL) {
		return;
	}

	if (string[Index] == '-') {
		IsNegative = TRUE;
		Index++;
	}

	for (int i = Index; string[i]; i++) {
		ReturnValue = ReturnValue * 10 + string[i] - '0';
	}

	if (IsNegative == TRUE) {
		ReturnValue = -1 * ReturnValue;
	}

	return ReturnValue;
}

VOID
StringReplace(__in wchar_t* string, __in PUCHAR character, __in const wchar_t* pattern)

/**
Replaces a given character in string with given pattern.
Assume string has extra space in the end if needed
**/

{
	ULONG CharacterCount = 0;
	ULONG PatternCount = 0;
	ULONG SpaceNeeded = 0;
	LONG Index = 0;
	LONG Index2 = 0;
	LONG PatternIndex = 0;

	if (string == NULL || character == NULL || pattern == NULL) {
		return NULL;
	}

	for (Index; string[Index]; Index++) {
		if (string[Index] == *character) {
			CharacterCount++;
		}
	}

	for (Index2; pattern[Index2]; Index2++) {
		PatternCount++;
	}

	SpaceNeeded = CharacterCount * PatternCount - CharacterCount;
	Index2 = Index + SpaceNeeded;
	PatternIndex = PatternCount - 1;
	for (Index; Index >=0; Index--)
	{
		if (string[Index] != *character) {
			string[Index2--] = string[Index];
		} else {
			while (PatternIndex >= 0) {
				string[Index2--] = pattern[PatternIndex--];
			}

			PatternIndex = PatternCount - 1;
		}
	}
}