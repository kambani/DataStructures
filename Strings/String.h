#pragma once
#include <windows.h>

#define WORD_SIZE 64

BOOLEAN
StringCheckIfAllCharactersUnique(__in const wchar_t* string);

VOID
StringReverse(__in wchar_t* string, __in_opt size_t size);

LONG
StringSubstringBrutForce(__in const wchar_t* string1, __in const wchar_t* string2);


