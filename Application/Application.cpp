// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" {
#include "..\LinkedList\LinkedList.h"
#include "..\Strings\String.h"
#include "..\GraphMatrix\Graph.h"
#include "..\Trees\Trees.h"
#include "..\Heap\Heap.h"
}

void
ExecuteLinkedListFunctions() {
	LNode Head;
	LNode Head2;
	LNode Head3;
	LNode Head4;
	LNode Head5;
	LNode Head6;
	LNode Head7;
	PLNode NewHead;

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

	LinkedListInitialize(&Head2);
	LinkedListAddData(&Head2, 4u);
	LinkedListAddData(&Head2, 5u);
	LinkedListAddData(&Head2, 6u);

	LinkedListInitialize(&Head3);
	LinkedListAddData(&Head3, 7u);
	LinkedListAddData(&Head3, 8u);
	LinkedListAddData(&Head3, 9u);

	LinkedListPrint(&Head2);
	LinkedListPrint(&Head3);

	LinkedListMergeSortedLists(&Head2, &Head3, &NewHead);
	LinkedListPrint(NewHead);

	LinkedListInitialize(&Head4);
	LinkedListAddData(&Head4, 0u);
	LinkedListAddData(&Head4, 1u);
	LinkedListAddData(&Head4, 2u);
	LinkedListAddData(&Head4, 3u);
	LinkedListAddData(&Head4, 4u);
	LinkedListAddData(&Head4, 5u);
	LinkedListEvenOddMerge(&Head4);
	LinkedListPrint(&Head4);

	LinkedListInitialize(&Head5);
	LinkedListAddData(&Head5, 0u);
	LinkedListAddData(&Head5, 1u);
	LinkedListAddData(&Head5, 2u);
	LinkedListAddData(&Head5, 3u);
	LinkedListAddData(&Head5, 4u);

	LinkedListInitialize(&Head6);
	LinkedListAddData(&Head6, 6u);
	LinkedListAddData(&Head6, 7u);
	LinkedListAddData(&Head6, 8u);
	
	//Make a Linear Loop
	// 6->7->8->
	//         |
	//   0->1->2->3->4
	Head6.rear->front = Head5.front->front->front;
	PLNode OverlappedNode = LinkedListDetectOverlap(&Head5, &Head6);
	wprintf(L"%d\n", OverlappedNode->Data);

	LinkedListInitialize(&Head7);
	LinkedListAddData(&Head7, 0u);
	LinkedListAddData(&Head7, 1u);
	LinkedListAddData(&Head7, 2u);
	LinkedListAddData(&Head7, 3u);
	LinkedListAddData(&Head7, 4u);
	LinkedListZip(&Head7);
	LinkedListPrint(&Head7);
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

void
ExecuteTreeFunctions()
{
	Tree Tree1;
	memset(&Tree1, 0, sizeof(Tree));
	TreeAdd(&Tree1, 7);
	TreeAdd(&Tree1, 4);
	TreeAdd(&Tree1, 12);
	TreeAdd(&Tree1, 2);
	TreeAdd(&Tree1, 6);
	TreeAdd(&Tree1, 9);
	TreeAdd(&Tree1, 19);
	TreeAdd(&Tree1, 3);
	TreeAdd(&Tree1, 5);
	TreeAdd(&Tree1, 8);
	TreeAdd(&Tree1, 11);
	TreeAdd(&Tree1, 15);
	TreeAdd(&Tree1, 20);
	TreePrintInorderWithParentPointer(&Tree1);
	TreePrintInOrder(Tree1.Root);
	wprintf(L"\n");
	TreePrintPreOrder(Tree1.Root);

	wprintf(L"\n");
	TreeMorrisTraversal(&Tree1);
	TreePrintExterior(&Tree1);

	Tree Tree2;
	memset(&Tree2, 0, sizeof(Tree));
	TreeAdd(&Tree2, 12);
	TreeAdd(&Tree2, 9);
	TreeAdd(&Tree2, 19);
	TreeAdd(&Tree2, 8);
	TreeAdd(&Tree2, 11);
	TreeAdd(&Tree2, 15);
	TreeAdd(&Tree2, 20);
	wprintf(L"Subtree: %d\n", TreeCheckIfSubtree(&Tree1, &Tree2));

	TreePrintPreOrder(Tree1.Root);
	wprintf(L"%lu\n", TreeCheckIfBST(&Tree1));

	TreePrintPathWhichAddToSum(&Tree1, 11);

	PNode find = TreeFindNode(&Tree1, 9);
	PNode find2 = TreeFindNode(&Tree1, 20);
	PNode CommanAncestor = TreeFindCommonAncestor(Tree1.Root, find, find2);
	if (CommanAncestor != NULL) {
		wprintf(L"Comman Ancestor %d\n", CommanAncestor->Data);
	} else {
		wprintf(L"No Comman Ancestor\n");
	}

	PLNode Heads;
	ULONG Count;
	TreeLinkAtLevels(&Tree1, &Heads, &Count);
	for (int i = 0; i < Count; i++) {
		LinkedListPrint(&Heads[i]);
	}

	PTree Tree3;
	ULONG array[] = { 1, 2, 3, 4, 5 };
	TreemakeMinHeightTreeFromSortedArray(&Tree3, array, 5);
	TreePrintPreOrder(Tree3->Root);

	Tree Tree4;
	memset(&Tree4, 0, sizeof(Tree));
	TreeAdd(&Tree4, 10);
	TreeAdd(&Tree4, 12);
	TreeAdd(&Tree4, 5);
	TreeAdd(&Tree4, 6);
	TreeAdd(&Tree4, 7);
	TreeAdd(&Tree4, 4);
	TreePrintExterior(&Tree4);

	PTree NewTree;
	ULONG Inorder[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 19, 20 };
	ULONG Preorder[13] = { 7, 4, 2, 3, 6, 5, 12, 9, 8, 11, 19, 15, 20 };
	TreeConstructFromPreAndInorder(Inorder, 13, Preorder, 13, &NewTree);
	TreePrintInOrder(NewTree->Root);
}

VOID
ExecuteHeapFunctions()
{
	//Heap heap;
	//HeapData HeapData[8] = { 15, 7, 2, 9, 11, 4, 3, 12 };
	//HeapInit(&heap, 8, MinHeap);
	//HeapAdd(&heap, &HeapData[0]);
	//HeapAdd(&heap, &HeapData[1]);
	//HeapAdd(&heap, &HeapData[2]);
	//HeapAdd(&heap, &HeapData[3]);
	//HeapAdd(&heap, &HeapData[4]);
	//HeapAdd(&heap, &HeapData[5]);
	//HeapAdd(&heap, &HeapData[6]);
	//HeapAdd(&heap, &HeapData[7]);
	//HeapPrint(&heap);
	//wprintf(L"\n%d", *HeapRemove(&heap));
	//wprintf(L"\n%d", *HeapRemove(&heap));
	//wprintf(L"\n%d", *HeapRemove(&heap));
	//wprintf(L"\n%d", *HeapRemove(&heap));
	//wprintf(L"\n%d", *HeapRemove(&heap));
	//wprintf(L"\n%d", *HeapRemove(&heap));
	//wprintf(L"\n%d", *HeapRemove(&heap));
	//wprintf(L"\n%d", *HeapRemove(&heap));
	//wprintf(L"\n%d", *HeapRemove(&heap));

	HeapSortTradeFilesIntoOne("C:\\temp\\stocks1.txt,C:\\temp\\stocks2.txt",
							  "C:\\temp\\stocksoutput.txt",
							  2,
							  ",");
}

int main()
{
	//ExecuteLinkedListFunctions();
	//ExecuteStringFunctions();
	//ExecuteGraphFunctions();
	//ExecuteTreeFunctions();
	ExecuteHeapFunctions();
	return 0;
}

