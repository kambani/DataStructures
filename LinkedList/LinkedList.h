#pragma once
#include <windows.h>

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

NTSTATUS
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
LinkedListPartitionAroundValue(PLNode Head, ULONG K);

BOOLEAN
LinkedListCheckIfPalindrome(PLNode Head);

PLNode
LinkedListFindMiddle(PLNode Head);

PLNode
LinkedListFindLoop(PLNode Head);