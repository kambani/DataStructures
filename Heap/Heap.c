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
	Heap->Array = malloc(sizeof(PHeapData) * size);
	memset(Heap->Array, 0, size);
	Heap->Type = Type;
	Heap->Index = -1;
}

VOID
HeapPrint(PHeap Heap)

/**
Prints the Heap
**/

{
	if (Heap != NULL && Heap->size > 0) {
		for (unsigned int i = 0; i < Heap->size; i++) {
			wprintf(L"%d ", *(Heap->Array[i]));
		}
	}
}

NTSTATUS
HeapiAddMinHeap(PHeap Heap, PHeapData Data)

/**
Adds an element to the Min Heap
**/

{
	int i;
	if (Heap->size - 1 == Heap->Index) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	for (i = ++Heap->Index; i > 0; i = (i - 1) / 2) {
		if (*(Heap->Array[(i - 1) / 2]) > *Data) {
			Heap->Array[i] = Heap->Array[(i - 1) / 2];
		} else {
			break;
		}
	}

	Heap->Array[i] = Data;
	return STATUS_SUCCESS;
}

NTSTATUS
HeapiAddMaxHeap(PHeap Heap, PHeapData Data)

/**
Adds an element to the Max Heap
**/

{
	int i;
	if (Heap->size - 1 == Heap->Index) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	for (i = ++Heap->Index; i > 0; i = (i - 1) / 2) {
		if (*(Heap->Array[(i - 1) / 2]) < *Data) {
			Heap->Array[i] = Heap->Array[(i - 1) / 2];
		} else {
			break;
		}
	}

	Heap->Array[i] = Data;
	return STATUS_SUCCESS;
}

NTSTATUS
HeapAdd(PHeap Heap, PHeapData Data)

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

PHeapData
HeapiRemoveMinHeap(PHeap Heap)

/**
Pops an element off a min heap
**/

{
	PHeapData ReturnValue;
	PHeapData LastValue;
	int i;

	if (Heap == NULL || Heap->Index == -1) {
		return NULL;
	}

	ReturnValue = Heap->Array[0];
	LastValue = Heap->Array[Heap->Index--];

	for (i = 1; i <= Heap->Index; i = 2 * i + 1) {
		if ((i + 1) <= Heap->Index && *(Heap->Array[i]) > *(Heap->Array[i + 1])) {
			i++;
		}

		if (*LastValue > *(Heap->Array[i])) {
			Heap->Array[(i - 1) / 2] = Heap->Array[i];
		} else {
			break;
		}
	}

	Heap->Array[(i - 1) / 2] = LastValue; 
	return ReturnValue;
}

PHeapData
HeapiRemoveMaxHeap(PHeap Heap)

/**
Pops an element off a max heap
**/

{
	PHeapData ReturnValue;
	PHeapData LastValue;
	int i;

	if (Heap == NULL || Heap->Index == -1) {
		return NULL;
	}

	ReturnValue = Heap->Array[0];
	LastValue = Heap->Array[Heap->Index--];

	for (i = 1; i <= Heap->Index; i = 2 * i + 1) {
		if ((i + 1) <= Heap->Index && *(Heap->Array[i]) < *(Heap->Array[i + 1])) {
			i++;
		}

		if (*LastValue < *(Heap->Array[i])) {
			Heap->Array[(i - 1) / 2] = Heap->Array[i];
		}
		else {
			break;
		}
	}

	Heap->Array[(i - 1) / 2] = LastValue;
	return ReturnValue;
}

PHeapData
HeapRemove(PHeap Heap)

/**
Removes an element from the heap
**/

{
	if (Heap != NULL) {
		if (Heap->Type == MinHeap) {
			return HeapiRemoveMinHeap(Heap);
		}
		else {
			return HeapiRemoveMaxHeap(Heap);
		}
	}

	return NULL;
}

VOID
HeapClear(PHeap Heap)

/**
Clears and frees the Heap.
Doesnt check if data is present.
**/

{
	free(Heap->Array);
	memset(Heap, 0, sizeof(Heap));
	return;
}


typedef struct _StockInfo {
	union {
		HeapData Data;
		LONG Time;
	};
	CHAR Symbol[10];
	ULONG Quantity;
	ULONG Price;
	ULONG FileIndex;
} StockInfo, *PStockInfo;

#define MAX_STOCK_FILE_LINE_SIZE 100
#define MAX_FILE_PATHS_SIZE 1000

VOID
HeapSortTradeFilesIntoOne(const char* FilePaths,
						  const char* OutputFilePath,
						  ULONG NumFiles,
						  const char* Delimeter)

/**
Function takes as input delimeter separated filepaths
Each of those File contains stock trade information of format
<TimeInMilliseconds>,<Symbol>,<quantity>,<price>
It reads the information across all the files, sorts them
as per the TimeInMilliseconds and spits the data into file pointed by 
OutputFile
**/

{
	PCHAR FilePath;
	FILE** Files;
	FILE* OutputFile;
	ULONG Index;
	Heap Heap;
	CHAR Line[MAX_STOCK_FILE_LINE_SIZE];
	PStockInfo Stockinfo;
	PCHAR Data;
	PHeapData temp;
	ULONG PreviousFileIndex;
	CHAR FilePathsNonConst[MAX_FILE_PATHS_SIZE];

	Files = malloc(sizeof(FILE) * NumFiles);
	OutputFile = fopen(OutputFilePath, "a");
	HeapInit(&Heap, NumFiles, MinHeap);
	strcpy(&FilePathsNonConst[0], &FilePaths[0]);
	Index = 0;

	//
	// Open all the input files
	//
	FilePath = strtok(&FilePathsNonConst[0], Delimeter);
	while (FilePath != NULL) {
		Files[Index++] = fopen(FilePath, "r");
		FilePath = strtok(NULL, Delimeter);
	}

	//
	// Populate the Heap with first lines of all the files
	//
	for (unsigned int i = 0; i < NumFiles; i++) {

		//
		// Read the first Line
		//
		if (fgets(&Line[0], MAX_STOCK_FILE_LINE_SIZE, Files[i]) != NULL) {

			//
			// Populate into struct
			//
			Stockinfo = malloc(sizeof(StockInfo));
			Data = strtok(&Line[0], ",");
			if (Data != NULL) {
				Stockinfo->Time = atoi(Data);
				Stockinfo->FileIndex = i;
			}
			else {

				//
				// Fata. Has to have Time because thats what feeds 
				// into the heap.
				//
				goto error;
			}

			//
			// No Null check needed. I dont care if rest fields
			// are NULL
			//
			strcpy(&Stockinfo->Symbol[0], strtok(NULL, ","));
			Stockinfo->Quantity = atoi(strtok(NULL, ","));
			Stockinfo->Price = atoi(strtok(NULL, ","));

			HeapAdd(&Heap, &Stockinfo->Time);
		}
	}

	//
	// Pop one out from the heap.
	// Write to the output file
	// Input another line from the file to 
	// which the popped one belonged to.
	//
	while (TRUE) {
		temp = HeapRemove(&Heap);
		if (temp != NULL) {
			Stockinfo = CONTAINING_RECORD(temp, StockInfo, Time);
			fprintf(OutputFile, "%d,%s,%d,%d\n", Stockinfo->Time,
											   Stockinfo->Symbol,
											   Stockinfo->Quantity,
											   Stockinfo->Price);
			PreviousFileIndex = Stockinfo->FileIndex;
			memset(Stockinfo, 0, sizeof(StockInfo));
			
			//
			// Lets get another input for the heap
			//
			if (fgets(&Line[0], MAX_STOCK_FILE_LINE_SIZE, Files[PreviousFileIndex]) != NULL) {

				//
				// Populate into struct
				//
				Data = strtok(&Line[0], ",");
				if (Data != NULL) {
					Stockinfo->Time = atoi(Data);
					Stockinfo->FileIndex = PreviousFileIndex;
				}
				else {

					//
					// Fatal. Has to have Time because thats what feeds 
					// into the heap.
					//
					goto error;
				}

				//
				// No Null check needed. I dont care if rest fields
				// are NULL
				//
				strcpy(&Stockinfo->Symbol[0], strtok(NULL, ","));
				Stockinfo->Quantity = atoi(strtok(NULL, ","));
				Stockinfo->Price = atoi(strtok(NULL, ","));

				HeapAdd(&Heap, &Stockinfo->Time);
			}
		} else {
			break;
		}
	}


error:
	for (unsigned int i = 0; i < NumFiles; i++) {
		fclose(Files[i]);
		fclose(OutputFile);
	}
	HeapClear(&Heap);
}