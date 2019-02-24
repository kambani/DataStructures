#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define MAX_EDGE_WEIGHT 64

NTSTATUS
GraphInitMatrix(PGraph Graph, ULONG NumElements, BOOLEAN GeneratePseudoRandomNumber)

/**
Initializes Graph as a matrix.
Generates random values if GeneratePseudoRandomNumber is TRUE.
**/

{
	if (Graph == NULL || NumElements == 0) {
		return STATUS_UNSUCCESSFUL;
	}

	Graph->matrix = (PULONG*)malloc(sizeof(PULONG) * NumElements);
	for (unsigned int i = 0; i < NumElements; i++) {
		Graph->matrix[i] = (PULONG)malloc(sizeof(ULONG) * NumElements);
	}

	if (GeneratePseudoRandomNumber == TRUE) {
		for (unsigned int i = 0; i < NumElements; i++) {
			for (unsigned int j = 0; j < NumElements; j++) {
				if (j > i) {
					Graph->matrix[i][j] = rand() % MAX_EDGE_WEIGHT;
					Graph->matrix[j][i] = Graph->matrix[i][j];
				} else if (i == j) {
					Graph->matrix[i][j] = ULONG_MAX;
				}
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
	
	for (unsigned int i = 0; i < Graph->RowCount; i++) {
		for (unsigned int j = 0; j < Graph->ColumnCount; j++) {
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
	for (unsigned int i = 0; i < Graph->RowCount; i++) {
		for (unsigned int j = 0; j < Graph->ColumnCount; j++) {
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
	for (unsigned int i = 0; i < Graph->RowCount; i++) {
		for (unsigned int j = 0; j < Graph->ColumnCount; j++) {
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

		for (unsigned int i = First; i < Last; i++) {
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
	wprintf(L"%c", 'a' + S);
	for (unsigned int i = 0; i < graph->RowCount; i++) {
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

VOID
GraphMinSpanningTreePrims(PGraph Graph)

/**
Prints Min spannning tree for a given graph.
**/

{
	ULONG Count;
	PULONG DistanceArray;
	ULONG i;
	ULONG Minimum;
	ULONG NumElements;
	PULONG PreviousArray;
	ULONG SelectedNode;
	PBOOLEAN VisitedArray;

	if (Graph == NULL) {
		return;
	}

	Count = 0;
	NumElements = Graph->RowCount;
	DistanceArray = malloc(sizeof(ULONG) * NumElements);
	i = 0;
	Minimum = ULONG_MAX;
	PreviousArray = malloc(sizeof(ULONG) * NumElements);
	VisitedArray = malloc(sizeof(BOOLEAN) * NumElements);

	for (i = 0; i < NumElements; i++) {
		DistanceArray[i] = ULONG_MAX;
		PreviousArray[i] = ULONG_MAX;
		VisitedArray[i] = FALSE;
	}

	DistanceArray[0] = 0;
	SelectedNode = 0;
	VisitedArray[0] = TRUE;

	while (Count < NumElements) {
		//
		// Update the Distance Array
		//
		for (i = 0; i < NumElements; i++) {
			if (Graph->matrix[SelectedNode][i] < DistanceArray[i] &&
				VisitedArray[i] == FALSE) {
				DistanceArray[i] = Graph->matrix[SelectedNode][i];
				PreviousArray[i] = SelectedNode;
			}
		}

		//
		// Find the next candidate for Selected Node
		//
		for (i = 0; i < NumElements; i++) {
			if (DistanceArray[i] < Minimum && VisitedArray[i] == FALSE) {
				Minimum = DistanceArray[i];
				SelectedNode = i;
			}
		}

		VisitedArray[SelectedNode] = TRUE;
		Count++;
	}

	//
	// Print Min Spanning Tree
	//
	for (i = 1; i < NumElements; i++) {
		wprintf(L"%c-%c %lu\n", (65 + PreviousArray[i]), 
							  (65 + i),
							  DistanceArray[i]);
	}
}

LONG
Find(PLONG ParentArray, LONG Candidate) 

{
	if (ParentArray[Candidate] == -1)
		return Candidate;
	Find(ParentArray, ParentArray[Candidate]);
}

VOID
Union(PLONG ParentArray, LONG Parent, LONG Child) 

{
	LONG ParentSet;
	LONG ChildSet;

	ParentSet = Find(ParentArray, Parent);
	ChildSet = Find(ParentArray, Child);

	if (ParentSet != ChildSet) {
		ParentArray[ChildSet] = ParentSet;
	}
}

VOID
GraphMinSpanningTreeKruskals(PGraph Graph)

/**
Minimum Spanning Tree using Kruskals.
**/

{
	PEdge Edges;
	ULONG NumEdges;
	ULONG i;
	ULONG j;
	ULONG Count;
	PLONG ParentArray;
	ULONG Src;
	ULONG Dst;
	Edge Temp;
	LONG SrcSet;
	LONG DstSet;

	if (Graph == NULL) {
		return;
	}

	//
	// We will consider AB and BA as separate edges
	// when populating edges.
	// Kruskals will anyways discard cycles.
	//
	NumEdges = (Graph->RowCount * (Graph->RowCount - 1)) / 2;
	Edges = malloc(sizeof(Edge) * NumEdges);
	memset(Edges, 0, sizeof(Edge) * NumEdges);
	ParentArray = malloc(sizeof(LONG) * NumEdges);
	Count = 0;

	for (i = 0; i < NumEdges; i++) {
		ParentArray[i] = -1;
	}

	for (i = 0; i < Graph->RowCount; i++) {
		for (j = i + 1; j < Graph->RowCount; j++) {
			if (Graph->matrix[i][j] != ULONG_MAX) {
				Edges[Count].Src = i;
				Edges[Count].Dst = j;
				Edges[Count].Weight = Graph->matrix[i][j];
				Count++;
			}
		}
	}

	//ASSERT(Count == (NumEdges - 1));

	//
	// Sort the Edges using simple bubble sort
	//
	for (i = 0; i < NumEdges - 1; i++) {
		for (j = 0; j < NumEdges - i - 1; j++) {
			if (Edges[j].Weight > Edges[j + 1].Weight) {
				//
				// Deep copy! Should have played with pointers
				// NVM.
				//
				Temp = Edges[j];
				Edges[j] = Edges[j + 1];
				Edges[j + 1] = Temp;
			}
		}
	}

	//
	// Start the Union-Find process
	// https://www.geeksforgeeks.org/union-find/
	//

	for (i = 0; i < NumEdges; i++) {
		Src = Edges[i].Src;
		Dst = Edges[i].Dst;
		SrcSet = Find(ParentArray, Src);
		DstSet = Find(ParentArray, Dst);

		if (SrcSet == DstSet) {
			//
			// Cycle. Skip
			//
			continue;
		} else {
			//
			// Print and Add to union
			// Lets keep destination as parent.
			//
			wprintf(L"%c-%c %d\n", (65 + Src), (65 + Dst), Edges[i].Weight);
			Union(ParentArray, Dst, Src);
		}
	}
}