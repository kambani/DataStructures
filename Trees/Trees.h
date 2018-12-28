#pragma once
#include <windows.h>
#include "..\LinkedList\LinkedList.h"

typedef struct Node {
	LONG Data;
	struct Node* Right;
	struct Node* Left;

	//
	// Capability to Hook this Node into 
	// LinkedList/Queue or any other data structure
	// Application should take care of memory allocation
	// of Node in such special cases.
	//
	UCHAR Variable[1];

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

PNode
TreeFindCommonAncestor(PNode Root, PNode p, PNode q);

PNode
TreeFindNode(PTree Tree, LONG Data);

BOOLEAN
TreeCheckIfSubtree(PTree t1, PTree t2);

VOID
TreePrintPathWhichAddToSum(PTree Tree, LONG Sum);