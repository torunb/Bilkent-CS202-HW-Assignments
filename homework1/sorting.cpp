/*
* Title: Sorting and Algorithm Efficiency
* Author: Utku Boran Torun
* ID: 21901898
* Section: 1
* Assignment: 1
* Description: Implementation of functions in header file
*/

#include "sorting.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 50000;

// HELPERS
void swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

void displayArray(const int *arr, const int size)
{
    for(int i = 0; i < size; i++)
    {
        if(i == size - 1)
            cout << arr[i];
        else
            cout << arr[i] << ", ";
    }
    cout << endl;
}

void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, const int size)
{
    for(int i = 0; i < size; i++)
    {
        int random = rand() % (size - 1) ;
        arr1[i] = random;
        arr2[i] = random;
        arr3[i] = random;
    }
}

void createAscendingArrays(int *&arr1, int *&arr2, int *&arr3, const int size)
{
    for(int i = 0; i < size; i++)
    {
        arr1[i] = i + 1;
        arr2[i] = i + 1;
        arr3[i] = i + 1;
    }
}

void createDescendingArrays(int *&arr1, int *&arr2, int *&arr3, const int size)
{
    int j = 0, k = 0, z = 0;
    for(int i = size - 1; i >= 0; i--)
    {
        arr1[j++] = i + size;
        arr2[k++] = i + size;
        arr3[z++] = i + size;
    }
}

// BUBBLE SORT
void bubbleSort(int *arr, const int size, int &compCount, int &moveCount)
{
    moveCount = 0;
    compCount = 0;
    bool sorted = false; 
   
	for (int pass = 1; (pass < size) && !sorted; ++pass) {  
        sorted = true;

        for (int index = 0; index < size-pass; ++index) {
            int nextIndex = index + 1;
            ++compCount;
            if (   arr[index] > arr[nextIndex]) {
                swap(arr[index], arr[nextIndex]);
                moveCount += 3;
                sorted = false; // signal exchange
            }
        }
    }
}

// MERGE SORT
void merge( int theArray[], int first, int mid, int last, int& compCount, int& moveCount) {
   
	int tempArray[MAX_SIZE]; 	// temporary array
   
	int first1 = first; 	// beginning of first subarray
    int last1 = mid; 		// end of first subarray
    int first2 = mid + 1;	// beginning of second subarray
    int last2 = last;		// end of second subarray
    int index = first1; // next available location in tempArray

    for ( ; (first1 <= last1) && (first2 <= last2); ++index) {
        if (++compCount && theArray[first1] < theArray[first2]) {  
            tempArray[index] = theArray[first1];
            moveCount++;
            ++first1;
        }
        else {  
            tempArray[index] = theArray[first2];
            moveCount++;
            ++first2;
        }
    }

    // finish off the first subarray, if necessary
    for (; first1 <= last1; ++first1, ++index){
        tempArray[index] = theArray[first1];
        moveCount++;
    }

    // finish off the second subarray, if necessary
    for (; first2 <= last2; ++first2, ++index){
        tempArray[index] = theArray[first2];
        moveCount++;
    }

    // copy the result back into the original array
    for (index = first; index <= last; ++index){
        theArray[index] = tempArray[index];
        moveCount++;
    }

}  // end merge



void helperMergeSort(int theArray[], int first, int last, int& compCount, int& moveCount)
{
    if (++compCount && first < last) {

        int mid = (first + last)/2; 	// index of midpoint

        helperMergeSort(theArray, first, mid, compCount, moveCount);

        helperMergeSort(theArray, mid+1, last, compCount, moveCount);

        // merge the two halves
        merge(theArray, first, mid, last, compCount, moveCount);
   }

}

void mergeSort( int *arr, const int size, int &compCount, int &moveCount) {
	helperMergeSort(arr, 0, size - 1, compCount, moveCount);
}





// QUICK SORT
void partition(int theArray[], int first, int last, int &pivotIndex, int &compCount, int &moveCount) {
    // Precondition: theArray[first..last] is an array; first <= last.
    // Postcondition: Partitions theArray[first..last] such that:
    //   S1 = theArray[first..pivotIndex-1] < pivot
    //   theArray[pivotIndex] == pivot
    //   S2 = theArray[pivotIndex+1..last] >= pivot
    
    // place pivot in theArray[first]
    //choosePivot(theArray, first, last);

    int pivot = theArray[first]; // copy pivot
    moveCount++;    
    // initially, everything but pivot is in unknown
    int lastS1 = first;           // index of last item in S1
    int firstUnknown = first + 1; // index of first item in unknown
    
        // move one item at a time until unknown region is empty
    for (   ; firstUnknown <= last; ++firstUnknown) {
        // Invariant: theArray[first+1..lastS1] < pivot
        //            theArray[lastS1+1..firstUnknown-1] >= pivot

        // move item from unknown to proper region
        if (++compCount && theArray[firstUnknown] < pivot) {  	// belongs to S1
            ++lastS1;
            swap(theArray[firstUnknown], theArray[lastS1]);
            moveCount += 3;
        }	// else belongs to S2
        //++compCount;
    }
    // place pivot in proper position and mark its location
    swap(theArray[first], theArray[lastS1]);
    moveCount += 3;
    pivotIndex = lastS1;
}



void quicksort(int theArray[], int first, int last, int &compCount, int &moveCount) {
// Precondition: theArray[first..last] is an array.
// Postcondition: theArray[first..last] is sorted.

	int pivotIndex;

    if (++compCount && first < last) {

        // create the partition: S1, pivot, S2
        partition(theArray, first, last, pivotIndex, compCount, moveCount);

        // sort regions S1 and S2
        quicksort(theArray, first, pivotIndex - 1, compCount, moveCount);
        quicksort(theArray, pivotIndex + 1, last, compCount, moveCount);
    }
}

void quickSort(int *arr, const int size, int &compCount, int &moveCount)
{
    quicksort(arr, 0, size - 1, compCount, moveCount);
}


////////////////////////////// PERFORMANCE ANALYSIS ///////////////////////////////////////////////////////////////

void randomAnalysis(int& compCount, int& moveCount)
{
    cout << "---------------------------------------------------------------" << endl;
    cout << "Random Array Bubble Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    double duration = 0;

    int size1 = 4000, size2 = 8000, size3 = 12000, size4 = 16000, size5 = 20000, size6 = 24000, size7 = 28000, size8 = 32000, size9 = 36000, size10 = 40000;
    
    int* arr1 = new int[size1];
    int* arr2 = new int[size1];
    int* arr3 = new int[size1];

    
    createRandomArrays(arr1, arr2, arr3, size1);
    clock_t startTime1 = clock();
    bubbleSort(arr1, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime1 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;
    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    createRandomArrays(arr1, arr2, arr3, size2);
    clock_t startTime2 = clock();
    bubbleSort(arr1, size2, compCount, moveCount);
    duration = 1000 * double( clock() - startTime2 ) / CLOCKS_PER_SEC;

    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    createRandomArrays(arr1, arr2, arr3, size3);
    clock_t startTime3 = clock();
    bubbleSort(arr1, size3, compCount, moveCount);
    duration = 1000 * double( clock() - startTime3 ) / CLOCKS_PER_SEC;

    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    createRandomArrays(arr1, arr2, arr3, size4);
    clock_t startTime4 = clock();
    bubbleSort(arr1, size4, compCount, moveCount);
    duration = 1000 * double( clock() - startTime4 ) / CLOCKS_PER_SEC;

    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    createRandomArrays(arr1, arr2, arr3, size5);
    clock_t startTime5 = clock();
    bubbleSort(arr1, size5, compCount, moveCount);
    duration = 1000 * double( clock() - startTime5 ) / CLOCKS_PER_SEC;

    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    createRandomArrays(arr1, arr2, arr3, size6);
    clock_t startTime6 = clock();
    bubbleSort(arr1, size6, compCount, moveCount);
    duration = 1000 * double( clock() - startTime6 ) / CLOCKS_PER_SEC;

    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    createRandomArrays(arr1, arr2, arr3, size7);
    clock_t startTime7 = clock();
    bubbleSort(arr1, size7, compCount, moveCount);
    duration = 1000 * double( clock() - startTime7 ) / CLOCKS_PER_SEC;

    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    createRandomArrays(arr1, arr2, arr3, size8);
    clock_t startTime8 = clock();
    bubbleSort(arr1, size8, compCount, moveCount);
    duration = 1000 * double( clock() - startTime8 ) / CLOCKS_PER_SEC;

    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    createRandomArrays(arr1, arr2, arr3, size9);
    clock_t startTime9 = clock();
    bubbleSort(arr1, size9, compCount, moveCount);
    duration = 1000 * double( clock() - startTime9 ) / CLOCKS_PER_SEC;

    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    createRandomArrays(arr1, arr2, arr3, size10);
    clock_t startTime10 = clock();
    bubbleSort(arr1, size10, compCount, moveCount);
    duration = 1000 * double( clock() - startTime10 ) / CLOCKS_PER_SEC;

    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    cout << "---------------------------------------------------------------" << endl;
    cout << "Random Array Merge Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size1];
    arr2 = new int[size1];
    arr3 = new int[size1];

    
    createRandomArrays(arr1, arr2, arr3, size1);
    clock_t startTime11 = clock();
    mergeSort(arr2, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime11 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    
    createRandomArrays(arr1, arr2, arr3, size2);
    clock_t startTime12 = clock();
    mergeSort(arr2, size2, compCount, moveCount);

    duration = 1000 * double( clock() - startTime12 ) / CLOCKS_PER_SEC;
    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    
    createRandomArrays(arr1, arr2, arr3, size3);
    clock_t startTime13 = clock();
    mergeSort(arr2, size3, compCount, moveCount);

    duration = 1000 * double( clock() - startTime13 ) / CLOCKS_PER_SEC;
    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    
    createRandomArrays(arr1, arr2, arr3, size4);
    clock_t startTime14 = clock();
    mergeSort(arr2, size4, compCount, moveCount);

    duration = 1000 * double( clock() - startTime14 ) / CLOCKS_PER_SEC;
    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    
    createRandomArrays(arr1, arr2, arr3, size5);
    clock_t startTime15 = clock();
    mergeSort(arr2, size5, compCount, moveCount);

    duration = 1000 * double( clock() - startTime15 ) / CLOCKS_PER_SEC;
    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    
    createRandomArrays(arr1, arr2, arr3, size6);
    clock_t startTime16 = clock();
    mergeSort(arr2, size6, compCount, moveCount);

    duration = 1000 * double( clock() - startTime16 ) / CLOCKS_PER_SEC;
    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;

    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    
    createRandomArrays(arr1, arr2, arr3, size7);
    clock_t startTime17 = clock();
    mergeSort(arr2, size7, compCount, moveCount);

    duration = 1000 * double( clock() - startTime17 ) / CLOCKS_PER_SEC;
    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    
    createRandomArrays(arr1, arr2, arr3, size8);
    clock_t startTime18 = clock();
    mergeSort(arr2, size8, compCount, moveCount);

    duration = 1000 * double( clock() - startTime18 ) / CLOCKS_PER_SEC;
    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    
    createRandomArrays(arr1, arr2, arr3, size9);
    clock_t startTime19 = clock();
    mergeSort(arr2, size9, compCount, moveCount);

    duration = 1000 * double( clock() - startTime19 ) / CLOCKS_PER_SEC;
    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    
    createRandomArrays(arr1, arr2, arr3, size10);
    clock_t startTime20 = clock();
    mergeSort(arr2, size10, compCount, moveCount);

    duration = 1000 * double( clock() - startTime20 ) / CLOCKS_PER_SEC;
    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    cout << "---------------------------------------------------------------" << endl;
    cout << "Random Array Quick Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size1];
    arr2 = new int[size1];
    arr3 = new int[size1];

    
    createRandomArrays(arr1, arr2, arr3, size1);
    clock_t startTime21 = clock();
    quickSort(arr3, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime21 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    
    createRandomArrays(arr1, arr2, arr3, size2);
    clock_t startTime22 = clock();
    quickSort(arr3, size2, compCount, moveCount);

    duration = 1000 * double( clock() - startTime22 ) / CLOCKS_PER_SEC;
    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    
    createRandomArrays(arr1, arr2, arr3, size3);
    clock_t startTime23 = clock();
    quickSort(arr3, size3, compCount, moveCount);

    duration = 1000 * double( clock() - startTime23 ) / CLOCKS_PER_SEC;
    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    
    createRandomArrays(arr1, arr2, arr3, size4);
    clock_t startTime24 = clock();
    quickSort(arr3, size4, compCount, moveCount);

    duration = 1000 * double( clock() - startTime24 ) / CLOCKS_PER_SEC;
    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    
    createRandomArrays(arr1, arr2, arr3, size5);
    clock_t startTime25 = clock();
    quickSort(arr3, size5, compCount, moveCount);

    duration = 1000 * double( clock() - startTime25 ) / CLOCKS_PER_SEC;
    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    
    createRandomArrays(arr1, arr2, arr3, size6);
    clock_t startTime26 = clock();
    quickSort(arr3, size6, compCount, moveCount);

    duration = 1000 * double( clock() - startTime26 ) / CLOCKS_PER_SEC;
    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;

    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    
    createRandomArrays(arr1, arr2, arr3, size7);
    clock_t startTime27 = clock();
    quickSort(arr3, size7, compCount, moveCount);

    duration = 1000 * double( clock() - startTime27 ) / CLOCKS_PER_SEC;
    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    
    createRandomArrays(arr1, arr2, arr3, size8);
    clock_t startTime28 = clock();
    quickSort(arr3, size8, compCount, moveCount);

    duration = 1000 * double( clock() - startTime28 ) / CLOCKS_PER_SEC;
    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    
    createRandomArrays(arr1, arr2, arr3, size9);
    clock_t startTime29 = clock();
    quickSort(arr3, size9, compCount, moveCount);

    duration = 1000 * double( clock() - startTime29 ) / CLOCKS_PER_SEC;
    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    
    createRandomArrays(arr1, arr2, arr3, size10);
    clock_t startTime30 = clock();
    quickSort(arr3, size10, compCount, moveCount);

    duration = 1000 * double( clock() - startTime30 ) / CLOCKS_PER_SEC;
    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;
}

void ascendingAnalysis(int& compCount, int& moveCount)
{
    cout << "---------------------------------------------------------------" << endl;
    cout << "Ascending Array Bubble Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    double duration = 0;

    int size1 = 4000, size2 = 8000, size3 = 12000, size4 = 16000, size5 = 20000, size6 = 24000, size7 = 28000, size8 = 32000, size9 = 36000, size10 = 40000;
    
    int* arr1 = new int[size1];
    int* arr2 = new int[size1];
    int* arr3 = new int[size1];

    
    createAscendingArrays(arr1, arr2, arr3, size1);
    clock_t startTime1 = clock();
    bubbleSort(arr1, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime1 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;
    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    createAscendingArrays(arr1, arr2, arr3, size2);
    clock_t startTime2 = clock();
    bubbleSort(arr1, size2, compCount, moveCount);
    duration = 1000 * double( clock() - startTime2 ) / CLOCKS_PER_SEC;

    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    createAscendingArrays(arr1, arr2, arr3, size3);
    clock_t startTime3 = clock();
    bubbleSort(arr1, size3, compCount, moveCount);
    duration = 1000 * double( clock() - startTime3 ) / CLOCKS_PER_SEC;

    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    createAscendingArrays(arr1, arr2, arr3, size4);
    clock_t startTime4 = clock();
    bubbleSort(arr1, size4, compCount, moveCount);
    duration = 1000 * double( clock() - startTime4 ) / CLOCKS_PER_SEC;

    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    createAscendingArrays(arr1, arr2, arr3, size5);
    clock_t startTime5 = clock();
    bubbleSort(arr1, size5, compCount, moveCount);
    duration = 1000 * double( clock() - startTime5 ) / CLOCKS_PER_SEC;

    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    createAscendingArrays(arr1, arr2, arr3, size6);
    clock_t startTime6 = clock();
    bubbleSort(arr1, size6, compCount, moveCount);
    duration = 1000 * double( clock() - startTime6 ) / CLOCKS_PER_SEC;

    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    createAscendingArrays(arr1, arr2, arr3, size7);
    clock_t startTime7 = clock();
    bubbleSort(arr1, size7, compCount, moveCount);
    duration = 1000 * double( clock() - startTime7 ) / CLOCKS_PER_SEC;

    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    createAscendingArrays(arr1, arr2, arr3, size8);
    clock_t startTime8 = clock();
    bubbleSort(arr1, size8, compCount, moveCount);
    duration = 1000 * double( clock() - startTime8 ) / CLOCKS_PER_SEC;

    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    createAscendingArrays(arr1, arr2, arr3, size9);
    clock_t startTime9 = clock();
    bubbleSort(arr1, size9, compCount, moveCount);
    duration = 1000 * double( clock() - startTime9 ) / CLOCKS_PER_SEC;

    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    createAscendingArrays(arr1, arr2, arr3, size10);
    clock_t startTime10 = clock();
    bubbleSort(arr1, size10, compCount, moveCount);
    duration = 1000 * double( clock() - startTime10 ) / CLOCKS_PER_SEC;

    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    cout << "---------------------------------------------------------------" << endl;
    cout << "Ascending Array Merge Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size1];
    arr2 = new int[size1];
    arr3 = new int[size1];

    
    createAscendingArrays(arr1, arr2, arr3, size1);
    clock_t startTime11 = clock();
    mergeSort(arr2, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime11 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    
    createAscendingArrays(arr1, arr2, arr3, size2);
    clock_t startTime12 = clock();
    mergeSort(arr2, size2, compCount, moveCount);

    duration = 1000 * double( clock() - startTime12 ) / CLOCKS_PER_SEC;
    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    
    createAscendingArrays(arr1, arr2, arr3, size3);
    clock_t startTime13 = clock();
    mergeSort(arr2, size3, compCount, moveCount);

    duration = 1000 * double( clock() - startTime13 ) / CLOCKS_PER_SEC;
    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    
    createAscendingArrays(arr1, arr2, arr3, size4);
    clock_t startTime14 = clock();
    mergeSort(arr2, size4, compCount, moveCount);

    duration = 1000 * double( clock() - startTime14 ) / CLOCKS_PER_SEC;
    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    
    createAscendingArrays(arr1, arr2, arr3, size5);
    clock_t startTime15 = clock();
    mergeSort(arr2, size5, compCount, moveCount);

    duration = 1000 * double( clock() - startTime15 ) / CLOCKS_PER_SEC;
    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    
    createAscendingArrays(arr1, arr2, arr3, size6);
    clock_t startTime16 = clock();
    mergeSort(arr2, size6, compCount, moveCount);

    duration = 1000 * double( clock() - startTime16 ) / CLOCKS_PER_SEC;
    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;

    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    
    createAscendingArrays(arr1, arr2, arr3, size7);
    clock_t startTime17 = clock();
    mergeSort(arr2, size7, compCount, moveCount);

    duration = 1000 * double( clock() - startTime17 ) / CLOCKS_PER_SEC;
    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    
    createAscendingArrays(arr1, arr2, arr3, size8);
    clock_t startTime18 = clock();
    mergeSort(arr2, size8, compCount, moveCount);

    duration = 1000 * double( clock() - startTime18 ) / CLOCKS_PER_SEC;
    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    
    createAscendingArrays(arr1, arr2, arr3, size9);
    clock_t startTime19 = clock();
    mergeSort(arr2, size9, compCount, moveCount);

    duration = 1000 * double( clock() - startTime19 ) / CLOCKS_PER_SEC;
    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    
    createAscendingArrays(arr1, arr2, arr3, size10);
    clock_t startTime20 = clock();
    mergeSort(arr2, size10, compCount, moveCount);

    duration = 1000 * double( clock() - startTime20 ) / CLOCKS_PER_SEC;
    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    cout << "---------------------------------------------------------------" << endl;
    cout << "Ascending Array Quick Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size1];
    arr2 = new int[size1];
    arr3 = new int[size1];

    
    createAscendingArrays(arr1, arr2, arr3, size1);
    clock_t startTime21 = clock();
    quickSort(arr3, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime21 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    
    createAscendingArrays(arr1, arr2, arr3, size2);
    clock_t startTime22 = clock();
    quickSort(arr3, size2, compCount, moveCount);

    duration = 1000 * double( clock() - startTime22 ) / CLOCKS_PER_SEC;
    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    
    createAscendingArrays(arr1, arr2, arr3, size3);
    clock_t startTime23 = clock();
    quickSort(arr3, size3, compCount, moveCount);

    duration = 1000 * double( clock() - startTime23 ) / CLOCKS_PER_SEC;
    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    
    createAscendingArrays(arr1, arr2, arr3, size4);
    clock_t startTime24 = clock();
    quickSort(arr3, size4, compCount, moveCount);

    duration = 1000 * double( clock() - startTime24 ) / CLOCKS_PER_SEC;
    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    
    createAscendingArrays(arr1, arr2, arr3, size5);
    clock_t startTime25 = clock();
    quickSort(arr3, size5, compCount, moveCount);

    duration = 1000 * double( clock() - startTime25 ) / CLOCKS_PER_SEC;
    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    
    createAscendingArrays(arr1, arr2, arr3, size6);
    clock_t startTime26 = clock();
    quickSort(arr3, size6, compCount, moveCount);

    duration = 1000 * double( clock() - startTime26 ) / CLOCKS_PER_SEC;
    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;

    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    
    createAscendingArrays(arr1, arr2, arr3, size7);
    clock_t startTime27 = clock();
    quickSort(arr3, size7, compCount, moveCount);

    duration = 1000 * double( clock() - startTime27 ) / CLOCKS_PER_SEC;
    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    
    createAscendingArrays(arr1, arr2, arr3, size8);
    clock_t startTime28 = clock();
    quickSort(arr3, size8, compCount, moveCount);

    duration = 1000 * double( clock() - startTime28 ) / CLOCKS_PER_SEC;
    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    
    createAscendingArrays(arr1, arr2, arr3, size9);
    clock_t startTime29 = clock();
    quickSort(arr3, size9, compCount, moveCount);

    duration = 1000 * double( clock() - startTime29 ) / CLOCKS_PER_SEC;
    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    
    createAscendingArrays(arr1, arr2, arr3, size10);
    clock_t startTime30 = clock();
    quickSort(arr3, size10, compCount, moveCount);

    duration = 1000 * double( clock() - startTime30 ) / CLOCKS_PER_SEC;
    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;
}

void descendingAnalysis(int& compCount, int& moveCount)
{
    cout << "---------------------------------------------------------------" << endl;
    cout << "Descending Array Bubble Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    double duration = 0;

    int size1 = 4000, size2 = 8000, size3 = 12000, size4 = 16000, size5 = 20000, size6 = 24000, size7 = 28000, size8 = 32000, size9 = 36000, size10 = 40000;
    
    int* arr1 = new int[size1];
    int* arr2 = new int[size1];
    int* arr3 = new int[size1];

    
    createDescendingArrays(arr1, arr2, arr3, size1);
    clock_t startTime1 = clock();
    bubbleSort(arr1, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime1 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;
    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    createDescendingArrays(arr1, arr2, arr3, size2);
    clock_t startTime2 = clock();
    bubbleSort(arr1, size2, compCount, moveCount);
    duration = 1000 * double( clock() - startTime2 ) / CLOCKS_PER_SEC;

    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    createDescendingArrays(arr1, arr2, arr3, size3);
    clock_t startTime3 = clock();
    bubbleSort(arr1, size3, compCount, moveCount);
    duration = 1000 * double( clock() - startTime3 ) / CLOCKS_PER_SEC;

    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    createDescendingArrays(arr1, arr2, arr3, size4);
    clock_t startTime4 = clock();
    bubbleSort(arr1, size4, compCount, moveCount);
    duration = 1000 * double( clock() - startTime4 ) / CLOCKS_PER_SEC;

    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    createDescendingArrays(arr1, arr2, arr3, size5);
    clock_t startTime5 = clock();
    bubbleSort(arr1, size5, compCount, moveCount);
    duration = 1000 * double( clock() - startTime5 ) / CLOCKS_PER_SEC;

    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    createDescendingArrays(arr1, arr2, arr3, size6);
    clock_t startTime6 = clock();
    bubbleSort(arr1, size6, compCount, moveCount);
    duration = 1000 * double( clock() - startTime6 ) / CLOCKS_PER_SEC;

    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    createDescendingArrays(arr1, arr2, arr3, size7);
    clock_t startTime7 = clock();
    bubbleSort(arr1, size7, compCount, moveCount);
    duration = 1000 * double( clock() - startTime7 ) / CLOCKS_PER_SEC;

    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    createDescendingArrays(arr1, arr2, arr3, size8);
    clock_t startTime8 = clock();
    bubbleSort(arr1, size8, compCount, moveCount);
    duration = 1000 * double( clock() - startTime8 ) / CLOCKS_PER_SEC;

    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    createDescendingArrays(arr1, arr2, arr3, size9);
    clock_t startTime9 = clock();
    bubbleSort(arr1, size9, compCount, moveCount);
    duration = 1000 * double( clock() - startTime9 ) / CLOCKS_PER_SEC;

    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;
    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    createDescendingArrays(arr1, arr2, arr3, size10);
    clock_t startTime10 = clock();
    bubbleSort(arr1, size10, compCount, moveCount);
    duration = 1000 * double( clock() - startTime10 ) / CLOCKS_PER_SEC;

    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    cout << "---------------------------------------------------------------" << endl;
    cout << "Descending Array Merge Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size1];
    arr2 = new int[size1];
    arr3 = new int[size1];

    
    createDescendingArrays(arr1, arr2, arr3, size1);
    clock_t startTime11 = clock();
    mergeSort(arr2, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime11 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    
    createDescendingArrays(arr1, arr2, arr3, size2);
    clock_t startTime12 = clock();
    mergeSort(arr2, size2, compCount, moveCount);

    duration = 1000 * double( clock() - startTime12 ) / CLOCKS_PER_SEC;
    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    
    createDescendingArrays(arr1, arr2, arr3, size3);
    clock_t startTime13 = clock();
    mergeSort(arr2, size3, compCount, moveCount);

    duration = 1000 * double( clock() - startTime13 ) / CLOCKS_PER_SEC;
    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    
    createDescendingArrays(arr1, arr2, arr3, size4);
    clock_t startTime14 = clock();
    mergeSort(arr2, size4, compCount, moveCount);

    duration = 1000 * double( clock() - startTime14 ) / CLOCKS_PER_SEC;
    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    
    createDescendingArrays(arr1, arr2, arr3, size5);
    clock_t startTime15 = clock();
    mergeSort(arr2, size5, compCount, moveCount);

    duration = 1000 * double( clock() - startTime15 ) / CLOCKS_PER_SEC;
    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    
    createDescendingArrays(arr1, arr2, arr3, size6);
    clock_t startTime16 = clock();
    mergeSort(arr2, size6, compCount, moveCount);

    duration = 1000 * double( clock() - startTime16 ) / CLOCKS_PER_SEC;
    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;

    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    
    createDescendingArrays(arr1, arr2, arr3, size7);
    clock_t startTime17 = clock();
    mergeSort(arr2, size7, compCount, moveCount);

    duration = 1000 * double( clock() - startTime17 ) / CLOCKS_PER_SEC;
    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    
    createDescendingArrays(arr1, arr2, arr3, size8);
    clock_t startTime18 = clock();
    mergeSort(arr2, size8, compCount, moveCount);

    duration = 1000 * double( clock() - startTime18 ) / CLOCKS_PER_SEC;
    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    
    createDescendingArrays(arr1, arr2, arr3, size9);
    clock_t startTime19 = clock();
    mergeSort(arr2, size9, compCount, moveCount);

    duration = 1000 * double( clock() - startTime19 ) / CLOCKS_PER_SEC;
    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    
    createDescendingArrays(arr1, arr2, arr3, size10);
    clock_t startTime20 = clock();
    mergeSort(arr2, size10, compCount, moveCount);

    duration = 1000 * double( clock() - startTime20 ) / CLOCKS_PER_SEC;
    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    cout << "---------------------------------------------------------------" << endl;
    cout << "Descending Array Quick Sort Analysis" << endl;
    cout << "Array Size        Elapsed Time        compCount       moveCount" << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size1];
    arr2 = new int[size1];
    arr3 = new int[size1];

    
    createDescendingArrays(arr1, arr2, arr3, size1);
    clock_t startTime21 = clock();
    quickSort(arr3, size1, compCount, moveCount);

    duration = 1000 * double( clock() - startTime21 ) / CLOCKS_PER_SEC;
    cout << size1 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size2];
    arr2 = new int[size2];
    arr3 = new int[size2];

    
    createDescendingArrays(arr1, arr2, arr3, size2);
    clock_t startTime22 = clock();
    quickSort(arr3, size2, compCount, moveCount);

    duration = 1000 * double( clock() - startTime22 ) / CLOCKS_PER_SEC;
    cout << size2 << "              " << duration << " ms               " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size3];
    arr2 = new int[size3];
    arr3 = new int[size3];

    
    createDescendingArrays(arr1, arr2, arr3, size3);
    clock_t startTime23 = clock();
    quickSort(arr3, size3, compCount, moveCount);

    duration = 1000 * double( clock() - startTime23 ) / CLOCKS_PER_SEC;
    cout << size3 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size4];
    arr2 = new int[size4];
    arr3 = new int[size4];

    
    createDescendingArrays(arr1, arr2, arr3, size4);
    clock_t startTime24 = clock();
    quickSort(arr3, size4, compCount, moveCount);

    duration = 1000 * double( clock() - startTime24 ) / CLOCKS_PER_SEC;
    cout << size4 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size5];
    arr2 = new int[size5];
    arr3 = new int[size5];

    
    createDescendingArrays(arr1, arr2, arr3, size5);
    clock_t startTime25 = clock();
    quickSort(arr3, size5, compCount, moveCount);

    duration = 1000 * double( clock() - startTime25 ) / CLOCKS_PER_SEC;
    cout << size5 << "             " << duration << " ms              " << compCount << "          " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size6];
    arr2 = new int[size6];
    arr3 = new int[size6];

    
    createDescendingArrays(arr1, arr2, arr3, size6);
    clock_t startTime26 = clock();
    quickSort(arr3, size6, compCount, moveCount);

    duration = 1000 * double( clock() - startTime26 ) / CLOCKS_PER_SEC;
    cout << size6 << "             " << duration << " ms             " << compCount << "          " << moveCount << endl;


    compCount = 0;
    moveCount = 0;

    arr1 = new int[size7];
    arr2 = new int[size7];
    arr3 = new int[size7];

    
    createDescendingArrays(arr1, arr2, arr3, size7);
    clock_t startTime27 = clock();
    quickSort(arr3, size7, compCount, moveCount);

    duration = 1000 * double( clock() - startTime27 ) / CLOCKS_PER_SEC;
    cout << size7 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size8];
    arr2 = new int[size8];
    arr3 = new int[size8];

    
    createDescendingArrays(arr1, arr2, arr3, size8);
    clock_t startTime28 = clock();
    quickSort(arr3, size8, compCount, moveCount);

    duration = 1000 * double( clock() - startTime28 ) / CLOCKS_PER_SEC;
    cout << size8 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size9];
    arr2 = new int[size9];
    arr3 = new int[size9];

    
    createDescendingArrays(arr1, arr2, arr3, size9);
    clock_t startTime29 = clock();
    quickSort(arr3, size9, compCount, moveCount);

    duration = 1000 * double( clock() - startTime29 ) / CLOCKS_PER_SEC;
    cout << size9 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;

    compCount = 0;
    moveCount = 0;

    arr1 = new int[size10];
    arr2 = new int[size10];
    arr3 = new int[size10];

    
    createDescendingArrays(arr1, arr2, arr3, size10);
    clock_t startTime30 = clock();
    quickSort(arr3, size10, compCount, moveCount);

    duration = 1000 * double( clock() - startTime30 ) / CLOCKS_PER_SEC;
    cout << size10 << "             " << duration << " ms             " << compCount << "         " << moveCount << endl;
}

void performanceAnalysis()
{
    int comp1 = 0, mov1 = 0;
    int comp2 = 0, mov2 = 0;
    int comp3 = 0, mov3 = 0;
    randomAnalysis(comp1, mov1);
    ascendingAnalysis(comp2, mov2);
    descendingAnalysis(comp3, mov3);
}

