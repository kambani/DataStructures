#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

NTSTATUS
StackInitialize(PSNode Node)

/**
Initializes a Stack node into Root Node
**/

{
	if (Node == NULL) {
		return STATUS_UNSUCCESSFUL;
	}

	Node->Count = 0;
	Node->Next = Node;

	return STATUS_SUCCESS;
}

NTSTATUS
StackPush(PSNode RootNode, PSNode Node)

/**
Pushes a supplied Node into the stack
**/

{
	if (RootNode == NULL || Node == NULL) {
		return STATUS_UNSUCCESSFUL;
	}

	Node->Next = RootNode->Next;
	RootNode->Next = Node;
	RootNode->Count++;

	return STATUS_SUCCESS;
}

NTSTATUS
StackPushData(PSNode RootNode, ULONG Data)

/**
This API pushes a given ULONG data into stack
Mindwell memory is created by the API on the heap
**/

{
	PSNode pnew;
	if (RootNode == NULL) {
		return STATUS_SUCCESS;
	}

	pnew = (PSNode)malloc(sizeof(SNode));
	pnew->Next = RootNode->Next;
	RootNode->Next = pnew;
	RootNode->Count++;
}

PSNode
StackPop(PSNode RootNode)

/**
Pops a SNode from the stack. To be used in conjunction
with StackPush. Does not free the memory since its a user
supplied SNode
**/

{
	PSNode ReturnValue = NULL;
	if (RootNode == NULL) {
		return ReturnValue;
	}

	if (RootNode->Next == RootNode) {
		return ReturnValue;
	}
	else {
		ReturnValue = RootNode->Next;
		RootNode->Next = RootNode->Next->Next;
		RootNode->Count--;
		return ReturnValue;
	}
}

ULONG
StackPopData(PSNode RootNode)

/**
This API pops a ULONG data from the stack.
To be used in conjunction with StackPushData.
SNode memory is freed by thte API.
**/

{
	ULONG ReturnValue;
	PSNode RemoveNode;
	if (RootNode == NULL || RootNode->Next == RootNode) {
		//
		// Stack is empty
		//
		ReturnValue = (ULONG)-1;
	}

	RemoveNode = RootNode->Next;
	ReturnValue = RemoveNode->Data;
	RootNode->Next = RootNode->Next->Next;
	free(RemoveNode);
	return ReturnValue;
}