#pragma once
#include <windows.h>

typedef struct SNode {
	union {
		ULONG Data;
		ULONG Count;
	};

	struct SNode* Next;
} SNode, *PSNode;

NTSTATUS
StackInitialize(PSNode Node);

NTSTATUS
StackPush(PSNode RootNode, PSNode Node);

NTSTATUS
StackPushData(PSNode RootNode, ULONG Data);

PSNode
StackPop(PSNode RootNode);

ULONG
StackPopData(PSNode RootNode);