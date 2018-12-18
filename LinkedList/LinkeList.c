#include <ntstatus.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

NTSTATUS
LinkedListInitialize(PLNode Head)

/**
Initializes a supplied LNode has the head of the linkedlist
**/

{
	if (Head == NULL) {
		return STATUS_UNSUCCESSFUL;
	}

	Head->front = Head;
	Head->rear = Head;
	Head->Count = 0;
	
	return STATUS_SUCCESS;
}

NTSTATUS
LinkedListAddNode(PLNode Head, PLNode Node)

/**
Given a head node of the linked list, adds the supplied
Node to the rear of the LinkedList
**/

{
	if (Head == NULL || Node == NULL) {
		return STATUS_UNSUCCESSFUL;
	}

	Node->front = Head->rear->front;	
	Head->rear->front = Node;
	Head->rear = Node;
	Head->Count++;
	return STATUS_SUCCESS;
}

NTSTATUS
LinkedListAddData(PLNode Head, ULONG Data)

/**
Given a head node of the linked list, API creates LNode memory for 
the supplied data and adds the LNode to the rear of the LinkedList.
Memory for the LNode has to be destroyed by the API during the removal
**/

{
	PLNode pnew = (PLNode)malloc(sizeof(PLNode));
	pnew->Data = Data;
	NTSTATUS Status;
	if (Head == NULL) {
		return STATUS_UNSUCCESSFUL;
	}

	Status = LinkedListAddNode(Head, pnew);
	if (Status != STATUS_SUCCESS) {
		free(pnew);
	}

	return Status;
}

NTSTATUS
LinkedListRemoveNode(PLNode Head, PLNode Node)

/**
Removes a supplied LNode from the Linkedlist. 
Memory of the LNode will not be freed by the API
**/

{
	PLNode Runner;
	PLNode temp;
	if (Head == NULL || Head->rear == Head->front) {
		return STATUS_UNSUCCESSFUL;
	}

	temp = Head->front;
	Runner = Head;
	while (temp != NULL) {
		if (temp->Data == Node->Data) {
			Runner->front = temp->front;
			if (Runner->front == Head) {
				//
				// Last Node got deleted
				// Update the rear
				//
				Head->rear = Runner;
			}
			
			Head->Count--; 
			return STATUS_SUCCESS;
		}

		Runner = temp;
		temp = temp->front;
	}

	return STATUS_UNSUCCESSFUL;
}

NTSTATUS
LinkedListRemoveData(PLNode Head, ULONG Data)

/**
Removes the first LNode that represents the Data from the Linkedlist.
Memory of the LNode will be freed by the API
**/

{
	PLNode Runner;
	if (Head == NULL || Head->front == Head) {
		return STATUS_UNSUCCESSFUL;
	}

	Runner = Head;
	while (Runner->front != Head) {
		if (Runner->front->Data == Data) {
			Runner->front = Runner->front->front;
			if (Runner->front == Head) {
				//
				// Last Node got deleted
				// Update the rear
				//
				Head->rear = Runner;
			}

			Head->Count--;
			return STATUS_SUCCESS;
		}

		Runner = Runner->front;
	}

	return STATUS_UNSUCCESSFUL;
}

VOID
LinkedListPrint(PLNode Head)

/**
Prints a given list
**/

{
	PLNode temp;
	if (Head == NULL) {
		wprintf(L"Invalid list\n");
		return;
	} else if (Head->front == Head) {
		wprintf(L"List is empty\n");
		return;
	}

	temp = Head->front;
	while (temp != Head) {
		wprintf(L"%lu->", temp->Data);
		temp = temp->front;
	}

	wprintf(L"\n");
}

VOID
LinkedListRemoveDuplicates(PLNode Head, BOOLEAN FreeMemory)

/**
Removes Duplicate from the List in O(n^2) Manner
**/

{
	PLNode Runner;
	PLNode Slow;
	ULONG Original;
	PLNode temp;
	if (Head == NULL) {
		return;
	}

	Slow = Head->front;
	while (Slow != Head) {
		Original = Slow->Data;
		Runner = Slow;
		while (Runner->front != Head) {
			if (Runner->front->Data == Original) {
				temp = Runner->front;
				Runner->front = Runner->front->front;
				Head->Count--;
				if (FreeMemory == TRUE) {
					free(temp);
				}
			} else {
				Runner = Runner->front;
			}
		}

		Slow = Slow->front;
	}
}

VOID
LinkedListPrintKthToLast(PLNode Head, USHORT K)

/**
Prints the Kth Last elemtent of a list pointed by Head
**/

{
	PLNode SlowRunner;
	PLNode FastRunner;

	if (Head == NULL || (USHORT)-1 == Head->Count) {
		return;
	}

	SlowRunner = FastRunner = Head;

	//
	// Give the fast runner the lead.
	//
	while (K > 0)
	{
		FastRunner = FastRunner->front;
		K--;
	}

	while (FastRunner != Head) {
		SlowRunner = SlowRunner->front;
		FastRunner = FastRunner->front;
	}

	if (SlowRunner != Head) {
		wprintf(L"%d\n", SlowRunner->Data);
	}
}

VOID
LinkedListReverseList(PLNode Head, PLNode till)

/**
Reverses the list with updated head untill the "till" node
N.B. Original List is modified
**/

{
	PLNode Current;
	PLNode Prev;
	PLNode Next;
	if (Head == NULL) {
		return;
	}

	Current = Head->front;
	Prev = till;
	Next = NULL;

	//
	// If reversing the entire list then we know that the 
	// first element is going to the last element. 
	// Update the rear already
	//

	if (till == Head) {
		Head->rear = Head->front;
	}

	while (Current != till) {
		Next = Current->front;
		Current->front = Prev;
		Prev = Current;
		Current = Next;
	}

	Head->front = Prev;
}

VOID
LinkedListPartitionAroundValue(PLNode Head, ULONG pivot)

/**
Partitions the list around the pivot value
such that Nodes with value <= are to the left of the pivot
and > to the right.
N.B. Original List is modified
**/

{
	PLNode LowStart;
	PLNode LowEnd;
	PLNode HighStart;
	PLNode HighEnd;
	PLNode temp;

	if (Head == NULL) {
		return;
	}

	temp = Head;
	LowStart = LowEnd = HighStart = HighEnd = NULL;

	while (temp->front != Head) {
		if (temp->front->Data <= pivot) {
			//
			// Send Left
			//
			if (LowStart == NULL) {
				LowStart = temp->front;
			} else {
				LowEnd->front = temp->front;
			}

			LowEnd = temp->front;
		} else {
			//
			// Send Right
			//
			if (HighStart == NULL) {
				HighStart = temp->front;
			} else {
				HighEnd->front = temp->front;
			}

			HighEnd = temp->front;
		}

		temp->front = temp->front->front;
	}

	//
	// Merge Everything
	//

	if (LowEnd != NULL) {
		LowEnd->front = HighStart;
		Head->front = LowStart;

		if (HighEnd != NULL) {
			Head->rear = HighEnd;
		} else {
			Head->rear = LowEnd;
		}
	} else {
		Head->front = HighStart;
		Head->rear = HighEnd;
	}
}

PLNode
LinkedListFindMiddle(PLNode Head)

/**
Returns a PLNode which represents the middle of the 
list.
N.B. In case of even number of Nodes, where 2 nodes are potential middle
candidates, it returns the second middle number candidate.
**/

{
	PLNode Runner;
	PLNode SlowRunner;
	if (Head == NULL) {
		return NULL;
	}

	SlowRunner = Runner = Head->front;
	while (Runner != Head && Runner->front != Head) {
		SlowRunner = SlowRunner->front;
		Runner = Runner->front->front;
	}

	return SlowRunner;
}

BOOLEAN
LinkedListCheckIfPalindrome(PLNode Head)

/**
Checks if a given LinkedList represented by Head is a palindrome.
**/

{
	PLNode Middle;
	PLNode TopHalf;
	PLNode BottomHalf;
	BOOLEAN ReturnValue;

	ReturnValue	= FALSE;
	Middle = NULL;
	if (Head == NULL) {
		ReturnValue = FALSE;
		goto done;
	}

	Middle = LinkedListFindMiddle(Head);
	LinkedListReverseList(Head, Middle);
	TopHalf = Head->front;

	if (Head->Count % 2 != 0)
	{
		BottomHalf = Middle->front;
	} else {
		BottomHalf = Middle;
	}

	while (TopHalf != Middle || BottomHalf != Head) {
		if (TopHalf->Data != BottomHalf->Data) {
			ReturnValue = FALSE;
			goto done;
		}

		TopHalf = TopHalf->front;
		BottomHalf = BottomHalf->front;
	}

	if (TopHalf == Middle && BottomHalf == Head) {
		ReturnValue = TRUE;
		goto done;
	}

done:
	//
	// Reconstruct the original list
	//
	if (Middle != NULL) {
		LinkedListReverseList(Head, Middle);
	}

	return ReturnValue;
}

PLNode
LinkedListFindLoop(PLNode Head)

{
	PLNode SlowRunner;
	PLNode FastRunner;
	if (Head == NULL) {
		return NULL;
	}

	SlowRunner = FastRunner = Head->front;
	while (FastRunner != NULL && FastRunner->front != NULL) {
		SlowRunner = SlowRunner->front;
		FastRunner = FastRunner->front->front;

		if (SlowRunner == FastRunner) {
			break;
		}
	}

	if (FastRunner == NULL || FastRunner->front == NULL) {
		//
		// No Loop
		//
		return NULL;
	}

	//
	// Reset the slow
	//
	SlowRunner = Head->front;

	while (SlowRunner != FastRunner) {
		SlowRunner = SlowRunner->front;
		FastRunner = FastRunner->front;
	}

	return SlowRunner;
}



