#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS

typedef struct _Graph {
	PULONG* matrix;
	ULONG RowCount;
	ULONG ColumnCount;
} Graph, *PGraph;

typedef struct _Edge {
	ULONG Src;
	ULONG Dst;
	ULONG Weight;
} Edge, *PEdge;

NTSTATUS
GraphInitMatrix(PGraph Graph, ULONG NumElements, BOOLEAN GeneratePseudoRandomNumber);

VOID
GraphPrint(PGraph Graph);

VOID
GraphZeroRowColumnof0Element(PGraph Graph);

VOID
GraphRotate90DegreeRight(PGraph graph);

VOID
GraphDFS(PGraph graph, ULONG S, BOOLEAN *vector);

VOID
GraphMinSpanningTreePrims(PGraph Graph);

VOID
GraphMinSpanningTreeKruskals(PGraph Graph);

BOOLEAN
GraphDetectHamiltonianCycle(PGraph Graph, ULONG StartVertex);