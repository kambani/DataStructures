#pragma once
#include <windows.h>

#define WORD_SIZE 64
#define ASCII_CHARACTER_COUNT 256

BOOLEAN
StringCheckIfAllCharactersUnique(__in const wchar_t* string);

VOID
StringReverse(__in wchar_t* string, __in_opt size_t size);

LONG
StringSubstringBrutForce(__in const wchar_t* string1, __in const wchar_t* string2);

BOOLEAN
StringIsStringRotationOf(__in const wchar_t* ParentString, __in const wchar_t* String);

LONG
StringCharAt(__in const wchar_t* string, __in PCHAR character, BOOL fromLast);

LONG
StringSubstringBoyerMoore(__in const wchar_t* string, __in const wchar_t* pattern);

BOOLEAN
StringCheckIfAsciiStringsHaveIdenticalCharCount(__in const wchar_t* string1, __in const wchar_t* string2);


