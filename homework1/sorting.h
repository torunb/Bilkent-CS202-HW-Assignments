/*
* Title: Sorting and Algorithm Efficiency
* Author: Utku Boran Torun
* ID: 21901898
* Section: 1
* Assignment: 1
* Description: Header file that contains sorting alghoritms and random array functions
*/

#ifndef __SORTING_H
#define __SORTING_H

#include <cstdlib>

void bubbleSort(int *arr, const int size, int &compCount, int &moveCount);
void mergeSort(int *arr, const int size, int &compCount, int &moveCount);
void quickSort(int *arr, const int size, int &compCount, int &moveCount);

void displayArray(const int *arr, const int size);
void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
void createAscendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
void createDescendingArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);

void performanceAnalysis();






#endif