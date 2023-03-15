/*
* Title: Heaps and AVL Tree
* Author: Utku Boran Torun
* ID: 21901898
* Section: 1
* Assignment: 3
* Description: Heapsort function and main function to test our implementations
*/

#include "heap.h"
#include <iostream>
#include <fstream>

using namespace std;

void swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

void heapRebuild(int* arr, int root, int size, int& compCount)
{
	int child = (2 * root) + 1;

    if(child < size && ++compCount)
    {
        int rightChild = child + 1;

        if(rightChild < size && arr[rightChild] > arr[child] && ++compCount)
            child = rightChild;

        if(arr[root] < arr[child] && ++compCount)
        {
            int temp = arr[root];
            arr[root] = arr[child];
            arr[child] = temp;

            heapRebuild(arr, child, size, compCount);
        }
    }
}

void heapSort(int* arr, int n, int& compCount)
{
	for ( int index = (n/2) - 1;  index >= 0;  index-- )
		heapRebuild( arr, index, n, compCount);
		
	for ( int last = n-1;  last > 0;  last-- ) 
	{ 
		swap(arr[0], arr[last]);
		heapRebuild( arr, 0, last, compCount);
	}
}

void displayArray(const int *arr, const int size)
{
    for ( int i = 0; i < size; i++)
	{
		cout<< arr[i] << "\n";	
	}
}

int main()
{
    heap myHeap;
	int comparisonCount = 0, size = 0, num = 0;

    while( cin >> num )
	{
		myHeap.insert(num); 
		size++;
    }

	int* arr = new int[size];
	
	int j = size - 1;
	for (int i = 0; i < size; i++)
	{
		arr[i] = myHeap.items[j--];
		// alternatively -> arr[i] = myHeap.popMaximum();
	}

	heapSort(arr, size, comparisonCount);

	cout << "Sorted Array Items: " << endl;
	displayArray(arr, size);
	cout<< "Comp count of this file: " << comparisonCount;
    
	delete arr;
    return 0;
}