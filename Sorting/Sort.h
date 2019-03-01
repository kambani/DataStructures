#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windows.h>
#undef WIN32_NO_STATUS
#include <vector>

using namespace std;

//
// Structs related to Skyline problem
//
typedef struct _Building {
    ULONG Left;
    ULONG Height;
    ULONG Right;
} Building, *PBuilding;

typedef struct _BuildingStripe {
    ULONG XCordinate;
    ULONG YCordinate;
} BuildingStripe, *PBuildingStripe;

typedef struct _Skyline {
    PBuildingStripe *Stripes;
    ULONG Count;
}Skyline, *PSkyline;

VOID
SortMergeSort(PLONG Array, ULONG Low, ULONG High);

VOID
SortCountInversions(PLONG Array, ULONG Low, ULONG High, PULONG InversionCount);

PSkyline
SortSkyLine(PBuilding Buildings, ULONG Low, ULONG High);