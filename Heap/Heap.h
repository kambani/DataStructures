#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS

/**
Array Implementation of Heap
Currently Heap will store elements of type
Integer. No complex Objects
**/

typedef enum _Heap_Type {
	MinHeap = 0,
	MaxHeap
} Heap_Type, *PHeap_Type;

typedef struct _Heap {
	size_t size;
	PLONG Array;
	Heap_Type Type;
	LONG Index;
} Heap, *PHeap;

VOID
HeapInit(PHeap Heap, size_t size, Heap_Type Type);

NTSTATUS
HeapAdd(PHeap Heap, LONG Data);

VOID
HeapPrint(PHeap Heap);

LONG
HeapRemove(PHeap Heap);
