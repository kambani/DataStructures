// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" {
#include "..\LinkedList\LinkedList.h"
#include "..\Strings\String.h"
}

void
ExecuteLinkedListFunctions() {
	LNode Head;
	LinkedListInitialize(&Head);
	LinkedListAddData(&Head, 1u);
	LinkedListAddData(&Head, 2u);
	LinkedListAddData(&Head, 3u);
	LinkedListAddData(&Head, 1u);
	LinkedListAddData(&Head, 1u);
	LinkedListPrint(&Head);
	LinkedListPrintKthToLast(&Head, 4);
	LinkedListRemoveData(&Head, 2u);
	LinkedListRemoveDuplicates(&Head, TRUE);
	LinkedListReverseList(&Head, (&Head)->front->front->front);
	LinkedListPartitionAroundValue(&Head, 3u);
	LinkedListAddData(&Head, 6u);
	wprintf(L"%lu\n", LinkedListCheckIfPalindrome(&Head));
	LinkedListPrint(&Head);
}

void
ExecuteStringFunctions()
{
	const wchar_t* string = L"asdg;jfb!@^$#3240";
	wprintf(L"%lu\n", StringCheckIfAllCharactersUnique(string));

	wchar_t string2[20] = L"kaushal";
	StringReverse(string2, 0);
	wprintf(L"%ls\n", string2);

	const wchar_t* pattern = L"g;jfb!@";
	wprintf(L"%lu\n", StringSubstringBrutForce(string, pattern));
}

int main()
{
	//ExecuteLinkedListFunctions();
	//ExecuteStringFunctions();
	return 0;
}

