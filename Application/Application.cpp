// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" {
#include "..\LinkedList\LinkedList.h"
}



int main()
{
	LNode Head;
	LinkedListInitialize(&Head);
	LinkedListAddData(&Head, 1u);
	LinkedListAddData(&Head, 2u);
	LinkedListAddData(&Head, 3u);
	LinkedListAddData(&Head, 1u);
	LinkedListAddData(&Head, 1u);
	LinkedListPrint(&Head);
	//LinkedListPrintKthToLast(&Head, 4);
	//LinkedListRemoveData(&Head, 2u);
	//LinkedListRemoveDuplicates(&Head, TRUE);
	//LinkedListReverseList(&Head, (&Head)->front->front->front);
	//LinkedListPartitionAroundValue(&Head, 3u);
	//LinkedListAddData(&Head, 6u);
	wprintf(L"%lu\n", LinkedListCheckIfPalindrome(&Head));
	LinkedListPrint(&Head);
	return 0;
}

