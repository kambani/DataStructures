#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include "Graph.h"

using namespace std;
#define MAX_EDGE_WEIGHT 64
#define INVALID_MATRIX_ENTRY ULONG_MAX

NTSTATUS
GraphInitMatrix(PGraph Graph, ULONG NumElements, BOOLEAN GeneratePseudoRandomNumber)

/**
Initializes Graph as a matrix.
Generates random values if GeneratePseudoRandomNumber is TRUE.
**/

{
    ULONG Input;

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
					Graph->matrix[i][j] = INVALID_MATRIX_ENTRY;
				}
			}
		}
	} else {
        //
        // Take Input from user
        //

        for (unsigned int i = 0; i < NumElements; i++) {
            for (unsigned int j = 0; j < NumElements; j++) {
                if (i == j) {
                    Graph->matrix[i][j] = INVALID_MATRIX_ENTRY;
                } else {
                    wprintf(L"Enter Input for [%c][%c]\n", (65 + i), (65 + j));
                    cin >> Input;
                    if (Input == 0) {
                        //
                        // We do not want zero weight edge
                        //
                        Graph->matrix[i][j] = INVALID_MATRIX_ENTRY;
                    } else {
                        Graph->matrix[i][j] = Input;
                    }
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
O(N ^ 2). Because we visit N * N vertices even if 
they are connected or not.
Can be improved to O(V + E) if used adjacency list.
**/

{
	vector[S] = TRUE;
	wprintf(L"%c", 'a' + S);
	for (unsigned int i = 0; i < graph->RowCount; i++) {
		if (graph->matrix[S][i] != INVALID_MATRIX_ENTRY && vector[S] == FALSE) {
			GraphDFS(graph, S, vector);
		}
	}
}

VOID
GraphBFS(PGraph graph)

/**
Breadth First Search.
O(N ^ 2). For Adjacency matrix.
O(V + E) for AL.
**/

{
    ULONG NumElements;
    PBOOLEAN Visited;
    ULONG Vertex;
    queue<unsigned int> Queue;

    if (graph == NULL) {
        return;
    }

    NumElements = graph->RowCount;
    Visited = (PBOOLEAN)malloc(sizeof(BOOLEAN) * NumElements);
    memset(Visited, 0, NumElements);
    Vertex = 0;
    Queue.push(Vertex);
    Visited[Vertex] = TRUE;

    while (Queue.empty() == FALSE) {
        Vertex = Queue.front();
        Queue.pop();
        for (unsigned int i = 0; i < NumElements; i++) {
            if (graph->matrix[Vertex][i] != INVALID_MATRIX_ENTRY && Visited[i] != TRUE) {
                wprintf(L"%lu ", i);
                Visited[i] = TRUE;
                Queue.push(i);
            }
        }
    }
}


VOID
GraphMinSpanningTreePrims(PGraph Graph)

/**
Prints Min spannning tree for a given graph.
O(V ^ 2).
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
	DistanceArray = (PULONG)malloc(sizeof(ULONG) * NumElements);
	i = 0;
	Minimum = ULONG_MAX;
	PreviousArray = (PULONG)malloc(sizeof(ULONG) * NumElements);
	VisitedArray = (PBOOLEAN)malloc(sizeof(BOOLEAN) * NumElements);

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
O(ELogE) = To Sort the edges.
 O(VLogV) = Union Find implemented here can take O(LogV) or worst case O(V)
 Total = O(ELogE) +  O(VLogV) 
 |E| >= |V| - 1
 Hence  O(ELogE) = O(VLogV)
 Total =  O(ELogE) +  O(ELogE) = O(ELogE)
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
	Edges = (PEdge)malloc(sizeof(Edge) * NumEdges);
	memset(Edges, 0, sizeof(Edge) * NumEdges);
	ParentArray = (PLONG)malloc(sizeof(LONG) * NumEdges);
	Count = 0;

	for (i = 0; i < NumEdges; i++) {
		ParentArray[i] = -1;
	}

	for (i = 0; i < Graph->RowCount; i++) {
		for (j = i + 1; j < Graph->RowCount; j++) {
			if (Graph->matrix[i][j] != INVALID_MATRIX_ENTRY) {
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
    // Ideally should be sorted via nlogn approach.
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

BOOLEAN
GraphiCheckHamiltonian(PLONG Array, ULONG NumElements, ULONG Vertex, ULONG Neighbor)

{
    for (unsigned int i = 0; i < NumElements; i++) {
        if (Array[i] == Neighbor || Array[Neighbor] == Vertex) {
            return FALSE;
        }
    }

    return TRUE;
}

BOOLEAN
GraphiHamiltonian(PLONG Array, ULONG Vertex, PGraph Graph, ULONG StartVertex)

/**
Internal driver for GraphDetectHamiltonianCycle.
**/

{
    ULONG i;
    BOOLEAN Continue;

    Continue = FALSE;

    //
    // Base case
    //
    for (i = 0; i < Graph->ColumnCount; i++) {
        if (Array[i] == -1) {
            Continue = TRUE;
            break;
        }
    }
    if (Continue == FALSE) {
        if (Array[Graph->ColumnCount - 1] == StartVertex) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    
    for (i = 0; i < Graph->ColumnCount; i++) {
        if (Graph->matrix[Vertex][i] != INVALID_MATRIX_ENTRY) {
            if (GraphiCheckHamiltonian(Array, Graph->RowCount, Vertex, i) == TRUE) {
                Array[Vertex] = i;
                if (GraphiHamiltonian(Array, i, Graph, StartVertex) == FALSE) {
                    //
                    // BackTrack
                    //
                    Array[Vertex] = -1;
                } else {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

BOOLEAN
GraphDetectHamiltonianCycle(PGraph Graph, ULONG StartVertex)

/**
Determine if a graph contains Hamiltonian Cycle
**/

{
    ULONG i;
    ULONG NumElements;
    ULONG Vertex;
    PLONG Array;
    BOOLEAN ReturnValue;

    if (Graph == NULL) {
        return FALSE;
    }

    NumElements = Graph->RowCount;
    Array = (PLONG)malloc(sizeof(LONG) * NumElements);
    for (i = 0; i < NumElements; i++) {
        Array[i] = -1;
    }

    ReturnValue = GraphiHamiltonian(Array, 0, Graph, StartVertex);
    if (ReturnValue == TRUE) {
        wprintf(L"%d->", StartVertex);
        for (i = 0; i < NumElements; i++) {
            wprintf(L"%d->", Array[i]);
        }
        wprintf(L"\n");
    }

    free(Array);

    return ReturnValue;
}