/*
* Title: Heaps and AVL Tree
* Author: Utku Boran Torun
* ID: 21901898
* Section: 1
* Assignment: 3
* Description: Implementation of heap data structure
*/

#include "heap.h"
#include <iostream>

using namespace std;

void heap:: swap(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

heap:: heap(int newSize)
{
    size = newSize;
    compCount = 0;
}

heap:: heap()
{
    size = 0;
    compCount = 0;
}

bool heap:: isEmpty() const
{
    return size == 0;
}

int heap:: getSize()
{
    return size;
}

void heap:: insert(const int& newItem)
{
    if(size >= MAX_HEAP)
    {
        cout << "Heap is full" << endl;
        return;
    }

    items[size] = newItem;

    int place = size;
    int parent = (size - 1) / 2;

    while( place > 0  && items[place] > items [parent] && ++compCount )
    {
        int temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

        place = parent;
        parent = (place - 1) / 2;
    }
    ++size;
}

void heap:: heapDelete(int& rootItem)
{
    if(isEmpty())
    {
        cout << "Heap is empty, you cannot delete item" << endl;
        return;
    }
    else
    {
        rootItem = items[0];
        items[0] = items[--size];
        heapRebuild(0);
    }
}

void heap:: heapRebuild(int root)
{
    int child = (2 * root) + 1;

    if(child < size && ++compCount)
    {
        int rightChild = child + 1;

        if(rightChild < size && items[rightChild] > items[child] && ++compCount)
            child = rightChild;

        if(items[root] < items[child] && ++compCount)
        {
            int temp = items[root];
            items[root] = items[child];
            items[child] = temp;

            heapRebuild(child);
        }
    }
}

int heap:: maximum()
{
    return items[0];
}

int heap:: popMaximum()
{
    int temp = items[0];

    for(int i = 0; i < size - 1; i++)
    {
        items[i] = items[i + 1];
    }
    --size;
    heapRebuild(0);
    return temp;
}


void heap:: displayHeap()
{
    for(int i = 0; i < size; i++)
    {
        if(i == size - 1)
            cout << items[i];
        else
            cout << items[i] << ", ";
    }
    cout << endl;
}

int heap:: getCompCount()
{
    return compCount;
}
