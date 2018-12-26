#include <ntstatus.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

NTSTATUS
GraphInitMatrix(PGraph Graph, ULONG NumElements, BOOLEAN GeneratePseudoRandomNumber)

/**
Initializes Graph as a matrix.
Generates random values if GeneratePseudoRandomNumber is TRUE.
**/

{
	PULONG Row;
	if (Graph == NULL || NumElements == 0) {
		return STATUS_UNSUCCESSFUL;
	}

	Graph->matrix = (PULONG*)malloc(sizeof(PULONG) * NumElements);
	for (int i = 0; i < NumElements; i++) {
		Graph->matrix[i] = (PULONG)malloc(sizeof(ULONG) * NumElements);
	}

	if (GeneratePseudoRandomNumber == TRUE) {
		for (int i = 0; i < NumElements; i++) {
			for (int j = 0; j < NumElements; j++) {
				Graph->matrix[i][j] = rand();
			}
		}
	}

	Graph->RowCount = NumElements;
	Graph->ColumnCount = NumElements;

	return STATUS_SUCCESS;
}

VOID
GraphPrint(PGraph Graph)

/**
Prints the graph.
**/

{
	if (Graph == NULL) {
		return;
	}
	
	for (int i = 0; i < Graph->RowCount; i++) {
		for (int j = 0; j < Graph->ColumnCount; j++) {
			wprintf(L"%lu ", Graph->matrix[i][j]);
		}
		wprintf(L"\n");
	}
}

VOID
GraphZeroRowColumnof0Element(PGraph Graph)

/**
If we encounter an element which is 0 in the matrix
then zero out the corresponding row and column.
Solved using bit map approach. Hence currently supported for
max 64 * 64 Matrix only
**/

{
	ULONG64 ZeroRows = 0;
	ULONG64 ZeroColumns = 0;
	ULONG64 Mask = 0;

	if (Graph == NULL || Graph->matrix == NULL || 
		Graph->ColumnCount > 64 || Graph->RowCount > 64) {
		return;
	}

	//
	// Mark Columns and Rows that need to be 0d out.
	//
	for (int i = 0; i < Graph->RowCount; i++) {
		for (int j = 0; j < Graph->ColumnCount; j++) {
			if (Graph->matrix[i][j] == 0) {
				Mask = 1 << i;
				ZeroRows |= Mask;
				Mask = 1 << j;
				ZeroColumns |= Mask;
			}
		}
	}

	//
	// Zero out
	//
	for (int i = 0; i < Graph->RowCount; i++) {
		for (int j = 0; j < Graph->ColumnCount; j++) {
			if (((ZeroRows & (1 << i)) != 0) || ((ZeroColumns & (1 << j)) != 0)) {
				Graph->matrix[i][j] = 0;
			}
		}
	}
}

VOID
GraphRotate90DegreeRight(PGraph graph) 

/**
Rotates the Matrix by 90 degrees to right
**/

{
	ULONG Layer;
	ULONG First;
	ULONG Last;
	ULONG Offset;
	ULONG temp;
	if (graph == NULL || graph->matrix == NULL) {
		return;
	}

	for (Layer = 0; Layer < graph->RowCount / 2; Layer++) {
		First = Layer;
		Last = graph->RowCount - 1 - Layer;

		for (int i = First; i < Last; i++) {
			Offset = i - First;

			//
			// Remove Top
			//
			temp = graph->matrix[First][i];

			//
			// Left to Top
			//
			graph->matrix[First][i] = graph->matrix[Last - Offset][First];

			//
			// Bottom to Left
			//
			graph->matrix[Last - Offset][First] = graph->matrix[Last][Last - Offset];

			//
			// Right to Bottom
			//
			graph->matrix[Last][Offset] = graph->matrix[i][Last];

			//
			// top to right
			//
			graph->matrix[i][Last] = temp;
		}
	}
}

VOID
GraphDFS(PGraph graph, ULONG S, BOOLEAN *vector) 

/**
Traverse the graph in dfs
**/

{
	vector[S] = TRUE;
	for (int i = 0; i < graph->RowCount; i++) {
		if (graph->matrix[S][i] != 0 && vector[S] == FALSE) {
			GraphDFS(graph, S, vector);
		}
	}
}

VOID
GraphBFS(PGraph graph)

/**
Traverse the graph in bfs
**/

{

}