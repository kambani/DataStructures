#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

VOID
HeapInit(PHeap Heap, size_t size, Heap_Type Type)

/**
Initializes Heap dynamically of given size
**/
{
	if (Heap == NULL) {
		return;
	}

	if (size <= 0) {
		return;
	}

	Heap->size = size;
	Heap->Array = malloc(sizeof(ULONG) * size);
	memset(Heap->Array, 0, size);
	Heap->Type = Type;
	Heap->Index = -1;
}

VOID
HeapPrint(PHeap Heap)

/**
**/

{
	if (Heap != NULL && Heap->size > 0) {
		for (unsigned int i = 0; i < Heap->size; i++) {
			wprintf(L"%d ", Heap->Array[i]);
		}
	}
}

NTSTATUS
HeapiAddMinHeap(PHeap Heap, LONG Data)

/**
Adds an element to the Min Heap
**/

{
	int i;
	if (Heap->size - 1 == Heap->Index) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	for (i = ++Heap->Index; i > 0; i = (i - 1) / 2) {
		if (Heap->Array[(i - 1) / 2] > Data) {
			Heap->Array[i] = Heap->Array[(i - 1) / 2];
		} else {
			break;
		}
	}

	Heap->Array[i] = Data;
	return STATUS_SUCCESS;
}

NTSTATUS
HeapiAddMaxHeap(PHeap Heap, LONG Data)

/**
Adds an element to the Max Heap
**/

{
	int i;
	if (Heap->size - 1 == Heap->Index) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	for (i = ++Heap->Index; i > 0; i = (i - 1) / 2) {
		if (Heap->Array[(i - 1) / 2] < Data) {
			Heap->Array[i] = Heap->Array[(i - 1) / 2];
		} else {
			break;
		}
	}

	Heap->Array[i] = Data;
	return STATUS_SUCCESS;
}

NTSTATUS
HeapAdd(PHeap Heap, LONG Data)

/**
Adds given element to the heap
**/

{
	if (Heap != NULL) {
		if (Heap->Type == MinHeap) {
			return HeapiAddMinHeap(Heap, Data);
		} else {
			return HeapiAddMaxHeap(Heap, Data);
		}
	}

	return STATUS_INVALID_PARAMETER;
}

LONG
HeapiRemoveMinHeap(PHeap Heap)

/**
Pops an element off a min heap
**/

{
	LONG ReturnValue;
	LONG LastValue;
	int i;

	if (Heap == NULL || Heap->Index == -1) {
		return LONG_MIN;
	}

	ReturnValue = Heap->Array[0];
	LastValue = Heap->Array[Heap->Index--];

	for (i = 1; i <= Heap->Index; i = 2 * i + 1) {
		if ((i + 1) <= Heap->Index && Heap->Array[i] > Heap->Array[i + 1]) {
			i++;
		}

		if (LastValue > Heap->Array[i]) {
			Heap->Array[(i - 1) / 2] = Heap->Array[i];
		} else {
			break;
		}
	}

	Heap->Array[(i - 1) / 2] = LastValue; 
	return ReturnValue;
}

LONG
HeapiRemoveMaxHeap(PHeap Heap)

/**
Pops an element off a max heap
**/

{
	LONG ReturnValue;
	LONG LastValue;
	int i;

	if (Heap == NULL || Heap->Index == -1) {
		return LONG_MIN;
	}

	ReturnValue = Heap->Array[0];
	LastValue = Heap->Array[Heap->Index--];

	for (i = 1; i <= Heap->Index; i = 2 * i + 1) {
		if ((i + 1) <= Heap->Index && Heap->Array[i] < Heap->Array[i + 1]) {
			i++;
		}

		if (LastValue < Heap->Array[i]) {
			Heap->Array[(i - 1) / 2] = Heap->Array[i];
		}
		else {
			break;
		}
	}

	Heap->Array[(i - 1) / 2] = LastValue;
	return ReturnValue;
}

LONG
HeapRemove(PHeap Heap)

{
	if (Heap != NULL) {
		if (Heap->Type == MinHeap) {
			return HeapiRemoveMinHeap(Heap);
		}
		else {
			return HeapiRemoveMaxHeap(Heap);
		}
	}

	return LONG_MIN;
}