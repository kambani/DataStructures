#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"

VOID
SortiMerge(PLONG Array, ULONG Low, ULONG High)

/**
Simple Merge function
Ascending order.
**/

{
    PULONG TempArray;
    size_t TempArraySize;
    ULONG Mid;
    ULONG i;
    ULONG j;
    ULONG Index;
    
    TempArraySize = (High - Low + 1);
    TempArray = (PULONG)malloc(sizeof(LONG) * TempArraySize);
    Mid = (Low + High) / 2;
    Index = 0;

    for (i = Low, j = Mid + 1; i <= Mid && j <= High;) {
        TempArray[Index++] = Array[i] < Array[j] ? Array[i++] : Array[j++];
    }

    while (i <= Mid) {
        TempArray[Index++] = Array[i++];
    }

    while (j <= High) {
        TempArray[Index++] = Array[j++];
    }

    memcpy(Array + Low, TempArray, sizeof(LONG) * TempArraySize);
    free(TempArray);
}

VOID
SortMergeSort(PLONG Array, ULONG Low, ULONG High)

/**
Simple Merge sort
**/

{
    ULONG Mid;
    if (Low < High) {
        Mid = Low + ((High - Low) / 2);
        SortMergeSort(Array, Low, Mid);
        SortMergeSort(Array, Mid + 1, High);
        SortiMerge(Array, Low, High);
    }
}

VOID
SortiMergeInversion(PLONG Array, ULONG Low, ULONG High, PULONG InversionCount)

/**
Merge for Inversion Count.
**/

{
    PULONG TempArray;
    size_t TempArraySize;
    ULONG Mid;
    ULONG i;
    ULONG j;
    ULONG Index;

    TempArraySize = (High - Low + 1);
    TempArray = (PULONG)malloc(sizeof(LONG) * TempArraySize);
    Mid = (Low + High) / 2;
    Index = 0;

    for (i = Low, j = Mid + 1; i <= Mid && j <= High;) {
        if (Array[i] < Array[j]) {
            TempArray[Index++] = Array[i++];
        } else {
            TempArray[Index++] = Array[j++];
            *InversionCount = *InversionCount + (Mid - i + 1);
        }
    }

    while (i <= Mid) {
        TempArray[Index++] = Array[i++];
    }

    while (j <= High) {
        TempArray[Index++] = Array[j++];
    }

    memcpy(Array + Low, TempArray, sizeof(LONG) * TempArraySize);
    free(TempArray);
}

VOID
SortCountInversions(PLONG Array, ULONG Low, ULONG High, PULONG InversionCount)

/**
Given an array, counts the number of inversion.
An Inversion is defined as i < j and a[i] > a[j].
**/

{
    ULONG Mid;

    if (Low < High) {
        Mid = Low + ((High - Low) / 2);
        SortCountInversions(Array, Low, Mid, InversionCount);
        SortCountInversions(Array, Mid + 1, High, InversionCount);
        SortiMergeInversion(Array, Low, High, InversionCount);
    }
}

PSkyline
SortiSkylineMergeStripes(PSkyline SkylineLeft, PSkyline SkylineRight)

/**
Merge function for skyline problem.
**/

{
    ULONG Height1;
    ULONG Height2;
    ULONG Index;
    ULONG MaxHeight;
    ULONG i;
    ULONG j;
    PSkyline NewSkyline;
    PBuildingStripe NewStripe;

    Height1 = 0;
    Height2 = 0;
    Index = 0;
    MaxHeight = 0;
    NewSkyline = (PSkyline)malloc(sizeof(Skyline));
    NewSkyline->Count = SkylineLeft->Count + SkylineRight->Count;
    NewSkyline->Stripes = (PBuildingStripe*)malloc(sizeof(PBuildingStripe) * NewSkyline->Count);

    for (i = 0, j = 0; i < SkylineLeft->Count 
        && j < SkylineRight->Count;) 
    {
        NewStripe = (PBuildingStripe)malloc(sizeof(BuildingStripe));
        if (SkylineLeft->Stripes[i]->XCordinate < SkylineRight->Stripes[j]->XCordinate) {
            NewStripe->XCordinate = SkylineLeft->Stripes[i]->XCordinate;
            Height1 = SkylineLeft->Stripes[i]->YCordinate;
            i++;
        } else {
            NewStripe->XCordinate = SkylineRight->Stripes[j]->XCordinate;
            Height2 = SkylineRight->Stripes[j]->YCordinate;
            j++;
        }

        MaxHeight = max(Height1, Height2);
        NewStripe->YCordinate = MaxHeight;
        NewSkyline->Stripes[Index++] = NewStripe;
    }

    while (i < SkylineLeft->Count) {
        NewStripe = (PBuildingStripe)malloc(sizeof(BuildingStripe));
        NewStripe->XCordinate = SkylineLeft->Stripes[i]->XCordinate;
        NewStripe->YCordinate = SkylineLeft->Stripes[i]->YCordinate;
        NewSkyline->Stripes[Index++] = NewStripe;
        i++;
    }

    while (j < SkylineRight->Count) {
        NewStripe = (PBuildingStripe)malloc(sizeof(BuildingStripe));
        NewStripe->XCordinate = SkylineRight->Stripes[j]->XCordinate;
        NewStripe->YCordinate = SkylineRight->Stripes[j]->YCordinate;
        NewSkyline->Stripes[Index++] = NewStripe;
        j++;
    }

    return NewSkyline;
}

PSkyline
SortSkyLine(PBuilding Buildings, ULONG Low, ULONG High)

/**
Skyline problem. Given buildings defined by struct Building
Plot the Skyline.

N.B. TODO
Do not add consecutive Stripes with same height. Only add the first in such cases.
Add that check

**/

{
    ULONG Mid;
    PBuildingStripe LeftStripe;
    PBuildingStripe RightStripe;
    PSkyline NewSkyline;
    PSkyline SkylineLeft;
    PSkyline SkylineRight;

    NewSkyline = NULL;

    if (Low == High) {
        LeftStripe = (PBuildingStripe)malloc(sizeof(BuildingStripe));
        LeftStripe->XCordinate = Buildings[Low].Left;
        LeftStripe->YCordinate = Buildings[Low].Height;

        RightStripe = (PBuildingStripe)malloc(sizeof(BuildingStripe));
        RightStripe->XCordinate = Buildings[Low].Right;
        RightStripe->YCordinate = 0;

        //
        // Create a Skyline
        //
        NewSkyline = (PSkyline)malloc(sizeof(Skyline));
        NewSkyline->Count = 2;
        NewSkyline->Stripes = (PBuildingStripe*)malloc(sizeof(PBuildingStripe) * NewSkyline->Count);
        NewSkyline->Stripes[0] = LeftStripe;
        NewSkyline->Stripes[1] = RightStripe;

        return NewSkyline;

    } else if (Low < High) {
        Mid = Low + ((High - Low) / 2);
        SkylineLeft = SortSkyLine(Buildings, Low, Mid);
        SkylineRight = SortSkyLine(Buildings, Mid + 1, High);
        NewSkyline = SortiSkylineMergeStripes(SkylineLeft, SkylineRight);

        //
        // We now have a new merged Skyline
        // Free Left and Right Skylines
        //
        free(SkylineLeft->Stripes);
        free(SkylineLeft);
        free(SkylineRight->Stripes);
        free(SkylineRight);
    }

    return NewSkyline;
}