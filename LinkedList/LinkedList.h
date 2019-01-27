#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS

//
//  H->1->2->3->4->            
//  |             | 
//  ---------------
// N.B. The last Node points back to Head.
// On Empty LL, Head front and rear pointers
// point to Head itself
//

typedef struct LNode {
	struct LNode *front;
	struct LNode *rear;
	union {
		ULONG Count;
		ULONG Data;
	};
} LNode, *PLNode;

NTSTATUS
LinkedListInitialize(PLNode Head);

NTSTATUS
LinkedListAddNode(PLNode Head, PLNode Node);

NTSTATUS
LinkedListAddData(PLNode Head, ULONG Data);

PLNode
LinkedListRemoveNode(PLNode head, PLNode Node);

NTSTATUS
LinkedListRemoveData(PLNode Head, ULONG Data);

VOID
LinkedListPrint(PLNode head);

VOID
LinkedListRemoveDuplicates(PLNode Head, BOOLEAN FreeMemory);

VOID
LinkedListPrintKthToLast(PLNode Head, USHORT K);

VOID
LinkedListReverseList(PLNode Head, PLNode till);

VOID
LinkedListReverseListInBetween(PLNode from, PLNode till);

VOID
LinkedListPartitionAroundValue(PLNode Head, ULONG K);

BOOLEAN
LinkedListCheckIfPalindrome(PLNode Head);

PLNode
LinkedListFindMiddle(PLNode Head);

PLNode
LinkedListFindLoop(PLNode Head);

VOID
LinkedListMergeSortedLists(PLNode Head1, PLNode Head2, PLNode* Head);

LONG
LinkedListMedianCircularSortedList(PLNode Head, PLNode ArbitraryNode);

VOID
LinkedListEvenOddMerge(PLNode Head);

PLNode
LinkedListDetectOverlap(PLNode Head1, PLNode Head2);

VOID
LinkedListZip(PLNode Head);