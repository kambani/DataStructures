// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" {
#include "..\LinkedList\LinkedList.h"
#include "..\Strings\String.h"
#include "..\GraphMatrix\Graph.h"
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

	string = L"kaushal";
	pattern = L"sha";
	wprintf(L"%lu\n", StringIsStringRotationOf(string, pattern));

	CHAR character = 'k';
	wprintf(L"%d\n", StringCharAt(string, &character, FALSE));

	wprintf(L"%d.\n", StringSubstringBoyerMoore(string, pattern));

	const wchar_t* string3 = L"kaushaz";
	wprintf(L"%d\n", StringCheckIfAsciiStringsHaveIdenticalCharCount(string, string3));

	const wchar_t* string4 = L"aaaabbbb";
	wchar_t* output;
	StringCompressStringCharacterAndCount(string4, &output);
	wprintf(L"Compressed string is %ls\n", output);
	free(output);

	wchar_t temp[20];
	Stringitoa_w(temp, 0, 10);
	wprintf(L"%ls\n", temp);

	const wchar_t* string5 = L"-123";
	printf("%d\n", Stringatoi_w(string5));

	WCHAR string6[100] = L"kaushal is the best";
	UCHAR character2 = ' ';
	const wchar_t* pattern2 = L"160";
	StringReplace(string6, &character2, pattern2);
	wprintf(L"%ls", string6);
}

void
ExecuteGraphFunctions()
{
	NTSTATUS Status;
	Graph graph;
	Status = GraphInitMatrix(&graph, 3, TRUE);
	GraphPrint(&graph);

	GraphRotate90DegreeRight(&graph);
	GraphPrint(&graph);

	graph.matrix[0][1] = 0;
	GraphPrint(&graph); 
	GraphZeroRowColumnof0Element(&graph);
	GraphPrint(&graph);
}

int main()
{
	//ExecuteLinkedListFunctions();
	//ExecuteStringFunctions();
	//ExecuteGraphFunctions();
	return 0;
}

