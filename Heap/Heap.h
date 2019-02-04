#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS

/**
Heap that takes HeapData as input
Wrap your struct around HeapData and you have a 
generics of this Heap!
See Examples for more details.
This Heap Library apart from conventional Heap APIs of
init add remove also contains extraneous APIs whose solution
requires heap to be used.
**/

typedef LONG HeapData;
typedef PLONG PHeapData;

typedef enum _Heap_Type {
	MinHeap = 0,
	MaxHeap
} Heap_Type, *PHeap_Type;

typedef struct _Heap {
	size_t size;
	PHeapData* Array;
	Heap_Type Type;
	LONG Index;
} Heap, *PHeap;

/************************HEAP BASIC APIS*****************************/

VOID
HeapInit(PHeap Heap, size_t size, Heap_Type Type);

NTSTATUS
HeapAdd(PHeap Heap, PHeapData Data);

VOID
HeapPrint(PHeap Heap);

PHeapData
HeapRemove(PHeap Heap);

VOID
HeapClear(PHeap Heap);

/************************BEGIN HEAP RELATED PROBLEMS*****************/

VOID
HeapSortTradeFilesIntoOne(const char* FilePaths, 
						  const char* OutputFilePath,
						  ULONG NumFiles, 
						  const char* Delimeter);
