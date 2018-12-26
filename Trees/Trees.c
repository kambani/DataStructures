#include <ntstatus.h>
#include <stdio.h>
#include <stdlib.h>
#include "Trees.h"
#include "..\Stack\Stack.h"

NTSTATUS
TreeAdd(PTree Tree, ULONG Data)

/**
Adds a Node into the BST Tree
**/

{
	PNode pnew;
	PNode runner;
	PNode temp;
	if (Tree == NULL) {
		return STATUS_INVALID_PARAMETER;
	}

	pnew = (PNode)malloc(sizeof(Node));
	pnew->Data = Data;
	if (Tree->Root == NULL) {
		Tree->Root = pnew;
		return STATUS_SUCCESS;
	}

	runner = Tree->Root;
	temp = runner;
	while (runner != NULL) {
		temp = runner;
		if (Data >= runner->Data) {
			runner = runner->Right;
		}
		else {
			runner = runner->Left;
		}
	}

	if (Data >= temp->Data) {
		temp->Right = pnew;
	}
	else {
		temp->Left = pnew;
	}

	return STATUS_SUCCESS;
}

VOID
TreePrintPreOrder(PNode Node)

/**
Prints a Tree in PreOrder fashion given Root Node
**/

{
	if (Node == NULL) {
		return;
	}

	wprintf(L"%lu ", Node->Data);
	TreePrintPreOrder(Node->Left);
	TreePrintPreOrder(Node->Right);
}

VOID
TreePrintInOrder(PNode Node)

/**
Prints a Tree in Inorder given root node
**/

{
	if (Node == NULL) {
		return;
	}

	TreePrintInOrder(Node->Left);
	wprintf(L"%lu ", Node->Data);
	TreePrintInOrder(Node->Right);
}

VOID
TreePrintPostOrder(PNode Node)

/**
Prints a Tree in PostOrder given root node
**/

{
	if (Node == NULL) {
		return;
	}

	TreePrintInOrder(Node->Left);
	TreePrintInOrder(Node->Right);
	wprintf(L"%lu ", Node->Data);
}

ULONG
TreeGetCount(PNode Node)

/**
Gets the number of nodes in a Tree supplied by root node passed
**/

{
	ULONG LeftCount;
	ULONG RightCount;
	if (Node == NULL) {
		return 0;
	}

	LeftCount = TreeGetCount(Node->Left);
	RightCount = TreeGetCount(Node->Right);
	return (LeftCount + RightCount + 1);
}

ULONG
TreeGetHeight(PNode Node)

/**
Height of a tree is defined by number of edges
from root to the deepest leaf + 1
**/

{
	ULONG LeftHeight;
	ULONG RightHeight;
	if (Node == NULL) {
		return 1;
	}

	LeftHeight = TreeGetHeight(Node->Left);
	RightHeight = TreeGetHeight(Node->Right);
	return (LeftHeight > RightHeight) ? LeftHeight : RightHeight;
}

BOOLEAN
TreeCheckNodeExists(PTree Tree, PNode Node)

/**
This function checks if a Node exists in the supplied Tree
**/

{
	PNode temp;
	if (Node == NULL) {
		return FALSE;
	}

	temp = Tree->Root;
	while (temp != NULL) {
		if (Node->Data > temp->Data) {
			temp = temp->Right;
		}
		else if (Node->Data < temp->Data) {
			temp = temp->Left;
		}
		else {
			if (temp == Node) {

				//
				// Found our Node
				//

				return TRUE;
			}
			else {

				//
				// Seems like we have duplicates values
				// Since during inserttion we have added == Values
				// to the right, go right
				//

				temp = temp->Right;
			}
		}
	}
}

BOOLEAN
TreeCheckIfStrictlyBinaryTree(PNode Node)

/**
Given root node of a tree, check if the tree
is a strictly binary tree
**/

{
	BOOLEAN LeftSubTreeCheck;
	BOOLEAN RightSubTreeCheck;
	if (Node == NULL) {
		return FALSE;
	}

	LeftSubTreeCheck = TreeCheckIfStrictlyBinaryTree(Node->Left);
	RightSubTreeCheck = TreeCheckIfStrictlyBinaryTree(Node->Right);
	if (LeftSubTreeCheck == RightSubTreeCheck) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

VOID
TreePrintLeafNodes(PNode Node)

/**
Given a Root node of a Tree, prints all the leaf node
**/

{
	if (Node == NULL) {
		return;
	}

	if (Node->Left == NULL && Node->Right == NULL) {
		wprintf(L"%lu", Node->Data);
	}
	else {
		TreePrintLeafNodes(Node->Left);
		TreePrintLeafNodes(Node->Right);
	}
}

VOID
TreeSwap(PNode Node)

/**
Given a Root node of a Tree, swaps all the subtrees belonging to it
**/

{

	if (Node == NULL) {
		return;
	}

	PNode temp = Node->Right;
	Node->Right = Node->Left;
	Node->Left = temp;
	TreeSwap(Node->Left);
	TreeSwap(Node->Right);
}

ULONG
TreeCheckIfCompleteBinaryTree(PNode Node)

/**
Given the root node of the tree, it checks if this is a
complete binary tree. If yes, returns the height of the tree
else returns 0.
**/

{
	ULONG Left;
	ULONG Right;
	if (Node == NULL) {
		return 0;
	}

	if (Node->Right == NULL || Node->Left == NULL) {
		return 1;
	}
	else {
		Left = TreeCheckIfCompleteBinaryTree(Node->Left);
		Right = TreeCheckIfCompleteBinaryTree(Node->Right);
		return (Left == Right && Left != 0 && Right != 0) ? (Left + 1) : 0;
	}
}

VOID
TreePreOrderNonRecurssive(PNode Node)
/**
Prints a tree in preorder manner without recurrsion
**/

{
	/*SNode Stack;
	StackInitialize(&Stack);

	while (TRUE) {
		while (Node != NULL) {
			wprintf(L"%lu ", Node->Data);
			StackPushData(&Stack, )
		}
	}*/

	return;
}


