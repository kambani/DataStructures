#pragma once
#include <windows.h>

typedef struct Node {
	ULONG Data;
	struct Node* Right;
	struct Node* Left;
} Node, *PNode;

typedef struct Tree {
	PNode Root;
	ULONG Count;
} Tree, *PTree;

NTSTATUS
TreeAdd(PTree Tree, ULONG Data);

VOID
TreePrintPreOrder(PTree Tree);

VOID
TreePrintPostOrder(PNode Node);

VOID
TreePrintInOrder(PNode Node);

ULONG
TreeGetHeight(PNode Node);

BOOLEAN
TreeCheckNodeExists(PTree Tree, PNode Node);

BOOLEAN
TreeCheckIfStrictlyBinaryTree(PNode Node);

VOID
TreePrintLeafNodes(PNode Node);

VOID
TreeSwap(PNode Node);

ULONG
TreeCheckIfCompleteBinaryTree(PNode Node);

VOID
TreePreOrderNonRecurssive(PNode Node);

//VOID
//TreeCheckIfAlmostCompleteBinaryTree()
