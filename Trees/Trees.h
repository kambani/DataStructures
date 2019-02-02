#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS
#include "..\LinkedList\LinkedList.h"

typedef struct Node {
	LONG Data;
	struct Node* Right;
	struct Node* Left;

	union {
		struct Node* Parent;
		PLNode LNode;
	};

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
TreeCheckIfBalanced(PNode Node);

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

VOID
TreeMorrisTraversal(PTree Tree);

BOOLEAN
TreeCheckIfSymmetric(PTree Tree);

VOID
TreePrintInorderWithParentPointer(PTree Tree);

VOID
TreePrintExterior(PTree Tree);

VOID
TreeConstructFromPreAndInorder(PULONG Inorder, ULONG InorderSize,
							   PULONG Preorder, ULONG PreorderSize,
							   PTree* Tree);