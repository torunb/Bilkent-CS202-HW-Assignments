/*
* Title: Sorting and Algorithm Efficiency
* Author: Utku Boran Torun
* ID: 21901898
* Section: 1
* Assignment: 1
* Description: Main.cpp for testing algorithms that we implemented in sorting.cpp
*/

#include "sorting.h"
#include <iostream>

using namespace std;

int main()
{
    int compCount1 = 0, moveCount1 = 0;
    int compCount2 = 0, moveCount2 = 0;
    int compCount3 = 0, moveCount3 = 0;

    int arr1[] = {20, 15, 19, 26, 27, 17, 14, 22, 29, 11, 25, 28, 13, 21, 23, 16}; // size = 16
    int arr2[] = {20, 15, 19, 26, 27, 17, 14, 22, 29, 11, 25, 28, 13, 21, 23, 16};
    int arr3[] = {20, 15, 19, 26, 27, 17, 14, 22, 29, 11, 25, 28, 13, 21, 23, 16};

    cout << endl;
    cout << "--Bubble Sort Algorithm--" << endl;
    bubbleSort(arr1, 16, compCount1, moveCount1);
    displayArray(arr1, 16);
    cout << "Bubble sort comparison count: " << compCount1 << endl;
    cout << "Bubble sort move count: " << moveCount1 << endl;
    cout << endl;

    cout << "--Merge Sort Algorithm--" << endl;
    mergeSort(arr2, 16, compCount2, moveCount2);
    displayArray(arr2, 16);
    cout << "Merge sort comparison count: " << compCount2 << endl;
    cout << "Merge sort move count: " << moveCount2 << endl;
    cout << endl;

    cout << "--Quick Sort Algorithm--" << endl;
    quickSort(arr3, 16, compCount3, moveCount3);
    displayArray(arr3, 16);
    cout << "Quick sort comparison count: " << compCount3 << endl;
    cout << "Quick sort move count: " << moveCount3 << endl;
    cout << endl;

    performanceAnalysis();

    return 0;
}