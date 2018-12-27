#pragma once
#include <windows.h>
#include "..\LinkedList\LinkedList.h"

typedef struct Node {
	LONG Data;
	struct Node* Right;
	struct Node* Left;
} Node, *PNode;

typedef struct Tree {
	PNode Root;
	ULONG Count;
} Tree, *PTree;

NTSTATUS
TreeAdd(PTree Tree, LONG Data);

VOID
TreePrintPreOrder(PNode Node);

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

BOOLEAN
TreeCheckIfAlmostCompleteBinaryTree(PNode Node);

NTSTATUS
TreemakeMinHeightTreeFromSortedArray(PTree *Tree, PULONG Array, ULONG Length);

BOOLEAN
TreeCheckIfBST(PTree Tree);

VOID
TreeLinkAtLevels(PTree Tree, PLNode* Heads, PULONG Count);
