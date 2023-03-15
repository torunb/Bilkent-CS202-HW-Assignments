/*
* Title: Heaps and AVL Tree
* Author: Utku Boran Torun
* ID: 21901898
* Section: 1
* Assignment: 3
* Description: Header file of heap data structure
*/

#ifndef __HEAP_H
#define __HEAP_H

const int MAX_HEAP = 10000;
class heap
{
public:
    heap(int newSize);
    heap();
    
    bool isEmpty() const; //
    void insert (const int& newItem); // 
    void heapDelete (int& rootItem); // 
    void heapRebuild(int root); //
    int maximum(); //
    int popMaximum(); // 

    ////////////////////////////
    void displayHeap();
    int getSize();
    ///////////////////////////


    void swap(int& x, int& y);

    int items[MAX_HEAP];

    int getCompCount();

private:
    int size;
    int compCount;
};

#endif