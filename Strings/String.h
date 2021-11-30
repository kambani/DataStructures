#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS

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

VOID
StringCompressStringCharacterAndCount(__in const wchar_t* string, wchar_t** compressed);

VOID
Stringitoa_w(__out wchar_t* string, __in LONG number, ULONG base);

LONG
Stringatoi_w(__in const wchar_t* string);

VOID
StringReplace(__in wchar_t* string, __in PUCHAR character, __in const wchar_t* pattern);

ULONG
StringLevenshteinDistance(__in const char* string1, __in const char* string2);
