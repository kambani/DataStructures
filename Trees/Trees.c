#include <stdio.h>
#include <stdlib.h>
#include "Trees.h"
#include "..\Stack\Stack.h"

NTSTATUS
TreeAdd(PTree Tree, LONG Data)

/**
Adds a Node into the BST Tree. Memory for the Node is 
allocated from the heap. 
**/

{
	PNode pnew;
	PNode runner;
	PNode temp;
	if (Tree == NULL) {
		return STATUS_INVALID_PARAMETER;
	}

	pnew = (PNode)malloc(sizeof(Node));
	memset(pnew, 0, sizeof(Node));
	pnew->Data = Data;
	if (Tree->Root == NULL) {
		Tree->Root = pnew;
		pnew->Parent = NULL;
		Tree->Count++;
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

	//
	// Link to Parent
	//
	pnew->Parent = temp;

	Tree->Count++;
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
		return 0;
	}

	LeftHeight = TreeGetHeight(Node->Left);
	RightHeight = TreeGetHeight(Node->Right);
	return (LeftHeight > RightHeight) ? LeftHeight + 1 : RightHeight + 1;
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

	return FALSE;
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

LONG
TreeiComputeHeightifBalanced(PNode Node)

/**
This functions gives you the height of the tree,
if the tree is balanced
**/

{
	LONG LeftHeight;
	LONG RightHeight;
	ULONG Diff;

	if (Node == NULL) {
		return 0;
	}

	LeftHeight = TreeiComputeHeightifBalanced(Node->Left);
	if (LeftHeight == -1) {
		return -1;
	}

	RightHeight = TreeiComputeHeightifBalanced(Node->Right);
	if (RightHeight == -1) {
		return -1;
	}

	Diff = abs(LeftHeight - RightHeight);
	if (Diff > 1) {
		return -1;
	} else {
		return (LeftHeight > RightHeight) ? LeftHeight + 1 : RightHeight + 1;
	}
}

BOOLEAN
TreeCheckIfBalanced(PNode Node)

/**
Height of 2 subtrees never differs by 1
**/

{
	if (TreeiComputeHeightifBalanced(Node) == -1) {
		return FALSE;
	} else {
		return TRUE;
	}
}

VOID
TreeiMakeTreeFromSortedArray(PTree Tree, PULONG Array, LONG Start, LONG End) 

/**
Internal for TreemakeMinHeightTreeFromSortedArray
**/

{
	ULONG Middle;

	if (Start <= End) {
		Middle = (Start + End) / 2;
		TreeAdd(Tree, Array[Middle]);
		TreeiMakeTreeFromSortedArray(Tree, Array, Start, Middle - 1);
		TreeiMakeTreeFromSortedArray(Tree, Array, Middle + 1, End);
	}
}

NTSTATUS
TreemakeMinHeightTreeFromSortedArray(PTree *Tree, PULONG Array, ULONG Length)

/**
Creates a Min Height Tree from a sorted array.
**/

{
	
	NTSTATUS Status;
	PTree TreeLocal;
	
	TreeLocal = *Tree;
	Status = STATUS_SUCCESS;

	if (Array == NULL || Length <= 0) {
		TreeLocal = NULL;
		Status = STATUS_UNSUCCESSFUL;
		goto Done;
	}

	TreeLocal = (PTree)malloc(sizeof(Tree));
	memset(TreeLocal, 0, sizeof(Tree));
	TreeiMakeTreeFromSortedArray(TreeLocal, Array, 0, Length - 1);
	
Done: 
	*Tree = TreeLocal;
	return Status;
}

BOOLEAN
TreeiCheckBst(PNode Node, LONG Min, LONG Max)

/**
Checks if a Tree is a BST.
**/

{
	if (Node == NULL) {
		return TRUE;
	}

	//
	// Condition should be in accordance to what you have 
	// during the Add operation. Currently we have allowed
	// All > and = root to go to right.
	//
	if ((Node->Data < Min) || (Node->Data >= Max)) {
		return FALSE;
	}

	return TreeiCheckBst(Node->Left, Min, Node->Data) &&
		   TreeiCheckBst(Node->Right, Node->Data, Max);
}

BOOLEAN
TreeCheckIfBST(PTree tree) 

/**
Wrapper API for TreeiCheckBst.
**/

{
	if (tree == NULL || tree->Root == NULL) {
		return FALSE;
	}

	return TreeiCheckBst(tree->Root, LONG_MIN, LONG_MAX);
}

VOID
TreeiLinkLevels(PNode Node, PLNode HeadsArray, ULONG Level)

/**
Links all the levels of a Tree
**/

{
	LNode Head;
	if (Node == NULL) {
		return;
	}

	Head = HeadsArray[Level];

	//
	// TODO: Try hooking the PNode to 
	// LinkedList rather than creating new LNode
	// and copying the data over.
	//
	LinkedListAddData(&Head, Node->Data);

	TreeiLinkLevels(Node->Left, HeadsArray, Level + 1);
	TreeiLinkLevels(Node->Right, HeadsArray, Level + 1);
}

VOID
TreeLinkAtLevels(PTree Tree, PLNode* Heads, PULONG Count)

/**
Joins all the nodes at the same level for a Tree.
Returns Array of LinkedList heads. Count of array also given back to the user
**/

{
	ULONG Levels;
	PLNode HeadsArray;
	if (Tree == NULL || Tree->Root == NULL) {
		return;
	}

	Levels = TreeGetHeight(Tree->Root);
	HeadsArray = (PLNode)malloc(sizeof(LNode) * Levels);
	memset(HeadsArray, 0, sizeof(LNode) * Levels);
	for (ULONG i = 0; i < Levels; i++) {
		LinkedListInitialize(&HeadsArray[i]);
	}

	TreeiLinkLevels(Tree->Root, HeadsArray, 0);

	*Count = Levels;
	*Heads = HeadsArray;
}

BOOLEAN
TreeiCheckIfContains(PNode Root, PNode Node)

/**
Checks if Root of a given tree contains the given Node
**/

{
	if (Root == NULL) {
		return FALSE;
	}

	if (Root->Data == Node->Data) {
		return TRUE;
	}

	return TreeiCheckIfContains(Root->Left, Node) ||
		   TreeiCheckIfContains(Root->Right, Node);
}

PNode
TreeFindCommonAncestor(PNode Root, PNode p, PNode q)

/**
Finds the command ancestor between Node p and q of Given Tree
**/

{
	BOOLEAN PExistsOnLeft;
	BOOLEAN QExistsOnLeft;

	if (Root == NULL || p == NULL || q == NULL) {
		return NULL;
	}

	PExistsOnLeft = TreeiCheckIfContains(Root->Left, p);
	QExistsOnLeft = TreeiCheckIfContains(Root->Left, q);

	if (PExistsOnLeft != QExistsOnLeft) {
		return Root;
	}

	return (PExistsOnLeft == TRUE) ? TreeFindCommonAncestor(Root->Left, p, q) : 
								     TreeFindCommonAncestor(Root->Right, p, q);
}

PNode
TreeFindNode(PTree Tree, LONG Data)

/**
Finds the first Node which matches the given 
Data
**/

{
	PNode Runner;
	if (Tree == NULL || Tree->Root == NULL) {
		return NULL;
	}

	Runner = Tree->Root;
	while (Runner != NULL && Runner->Data != Data) {
		if (Runner->Data > Data) {
			Runner = Runner->Left;
		}
		else {
			Runner = Runner->Right;
		}
	}

	return Runner;
}

BOOLEAN
TreeiMatchTrees(PNode root1, PNode root2, PULONG MatchCount)

/**
Checks is Trees represented by root1 and root2 are same
**/

{
	if (root1 == NULL && root2 == NULL) {
		return TRUE;
	}

	if (root1 == NULL) {

		//
		// We reached end of Tree1 while matching
		// and Tree2 seems to stil have nodes in that 
		// direction
		//
		return FALSE;
	}
	
	if (root2 == NULL) {

		//
		// We have reached the end of Tree2 
		// on this side. But provided we have
		// reached here with match count != 0
		// this certainly is candidate for a subtree
		// from this side of the tree. Return TRUE
		//
		if (MatchCount != 0) {
			return TRUE;
		} else {
			return FALSE;
		}
	}

	if (root1->Data != root2->Data) {
		return FALSE;
	}

	(*MatchCount)++;
	return TreeiMatchTrees(root1->Left, root2->Left, MatchCount) &&
		   TreeiMatchTrees(root1->Right, root2->Right, MatchCount);
}

BOOLEAN
TreeiCheckIfSubTree(PNode root1, PNode root2)

/**
Internal for TreeCheckIfSubtree. 
**/

{
	ULONG MatchCount;

	MatchCount = 0;
	if (root1 == NULL) {
		return FALSE;
	}

	if (root1->Data == root2->Data) {
		if (TreeiMatchTrees(root1, root2, &MatchCount) == TRUE) {
			return TRUE;
		}
	}
		
	return TreeiCheckIfSubTree(root1->Left, root2) ||
		   TreeiCheckIfSubTree(root1->Right, root2);
}

BOOLEAN
TreeCheckIfSubtree(PTree t1, PTree t2)

/**
Check if t2 is a subtree of t1
**/

{
	if (t1 == NULL || t2 == NULL || 
		t1->Root == NULL || t2->Root == NULL) {
		return FALSE;
	}

	return TreeiCheckIfSubTree(t1->Root, t2->Root);
}

VOID
TreeiPrintArray(PLONG Array, ULONG Start, ULONG End)

/**
Internal for TreeiPrintPathWhichAddToSum.
**/

{
	for (unsigned int i = Start; i <= End; i++) {
		wprintf(L"%d->", Array[i]);
	}

	wprintf(L"\n");
}

VOID
TreeiPrintPathWhichAddToSum(PNode Node, PLONG Array, ULONG Level, PLONG Sum)

/**
Internal of TreePrintPathWhichAddToSum.
**/

{
	LONG SumLocal;
	if (Node == NULL) {
		return; 
	}

	SumLocal = 0;
	Array[Level] = Node->Data;
	for (int i = Level; i >= 0; i--) {
		SumLocal += Array[i];
		if (SumLocal == *Sum) {
			TreeiPrintArray(Array, i, Level);
		}
	}

	TreeiPrintPathWhichAddToSum(Node->Left, Array, Level + 1, Sum);
	TreeiPrintPathWhichAddToSum(Node->Right, Array, Level + 1, Sum);
}

VOID
TreePrintPathWhichAddToSum(PTree Tree, LONG Sum)

/**
Given a Tree, this function prints all the paths
whose sum matches the given sum.
**/

{
	ULONG Levels;
	PLONG Array;
	if (Tree == NULL || Tree->Root == NULL) {
		return;
	}

	Levels = TreeGetHeight(Tree->Root);
	Array = (PLONG)malloc(sizeof(LONG) * Levels);
	memset(Array, 0, sizeof(LONG) * Levels);
	TreeiPrintPathWhichAddToSum(Tree->Root, Array, 0, &Sum);
}

VOID
TreeMorrisTraversal(PTree Tree)

/**
Inorder Traversal of a tree without using o(h)
stack space which usually happens in recursive traversal or
other iterative solution
**/

{
	PNode Node;
	PNode pre;
	if (Tree == NULL || Tree->Root == NULL) {
		return;
	}

	Node = Tree->Root;

	while (Node != NULL) {
		if (Node->Left) {
			pre = Node->Left;
			while (pre->Right != NULL && pre->Right != Node) {
				pre = pre->Right;
			}

			if (pre->Right == NULL) {
				//
				// Make new Link.
				//
				pre->Right = Node;
				Node = Node->Left;
			} else {
				//
				// Link Exists, break it.
				//
				wprintf(L"%d ", Node->Data);
				pre->Right = NULL;
				Node = Node->Right;
			}
		} else {
			wprintf(L"%d ", Node->Data);
			Node = Node->Right;
		}
	}

	wprintf(L"\n");
}

BOOLEAN
TreeiCheckSymmetry(PNode Node1, PNode Node2)

/**
Internal to TreeCheckIfSymmetric
**/

{
	if (Node1 == NULL && Node2 == NULL) {
		return TRUE;
	}

	if (Node1 == NULL || Node2 == NULL) {
		return FALSE;
	}

	if (Node1->Data == Node2->Data) {
		return TreeiCheckSymmetry(Node1->Left, Node2->Right) &&
			   TreeiCheckSymmetry(Node1->Right, Node2->Left);
	} else {
		return FALSE;
	}
}

BOOLEAN
TreeCheckIfSymmetric(PTree Tree)

/**
Checks if Tree is symmetric
**/

{
	if (Tree != NULL || Tree->Root != NULL) {
		return TreeiCheckSymmetry(Tree->Root->Left, 
								  Tree->Root->Right);
	} else {
		return FALSE;
	}
}

VOID
TreePrintInorderWithParentPointer(PTree Tree)

/**
Prints the tree inorder manner when pointer to parent
exists
**/

{
	PNode Current;
	PNode Prev;
	PNode Next;
	if (Tree == NULL || Tree->Root == NULL) {
		return;
	}

	Current = Tree->Root;
	Prev = NULL;
	Next = NULL;
	while (Current != NULL) {
		if (Prev == NULL || Prev->Right == Current
			|| Prev->Left == Current) {
			if (Current->Left != NULL) {
				Next = Current->Left;
			} else {
				wprintf(L"%d ", Current->Data);
				Next = Current->Right ? Current->Right : Current->Parent;
			}
		} else if (Current->Left == Prev) {
			wprintf(L"%d ", Current->Data);
			Next = Current->Right ? Current->Right : Current->Parent;
		} else {
			Next = Current->Parent;
		}

		Prev = Current;
		Current = Next;
	}

	wprintf(L"\n");
}

VOID
TreeiPrintLeftExterior(PNode Root, BOOLEAN isBoundry)

/**
Prints the Left exterior of a Tree in 
clock wise fashion given Root of the node
**/

{
	if (Root == NULL) {
		return;
	}

	if (isBoundry == TRUE || 
		(Root->Left == NULL && Root->Right == NULL)) {
		wprintf(L"%d ", Root->Data);
	}

	TreeiPrintLeftExterior(Root->Left, isBoundry);
	TreeiPrintLeftExterior(Root->Right, isBoundry && Root->Left == NULL);
}

VOID
TreeiPrintRightExterior(PNode Root, BOOLEAN isBoundry)

/**
Prints the Right exterior of a Tree in
clock wise fashion given Root of the node
**/

{
	if (Root == NULL) {
		return;
	}
	
	TreeiPrintRightExterior(Root->Left, isBoundry && Root->Right == NULL);
	TreeiPrintRightExterior(Root->Right, isBoundry);
	if (isBoundry == TRUE ||
		(Root->Left == NULL && Root->Right == NULL)) {
		wprintf(L"%d ", Root->Data);
	}
}

VOID
TreePrintExterior(PTree Tree)

/**
Prints the exterior of a Tree
**/

{
	if (Tree != NULL && Tree->Root != NULL) {
		wprintf(L"%d ", Tree->Root->Data);
		TreeiPrintLeftExterior(Tree->Root->Left, TRUE);
		TreeiPrintRightExterior(Tree->Root->Right, TRUE);
	}

	wprintf(L"\n");
}