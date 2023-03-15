/**
* Title : Binary Search Trees
* Author : Utku Boran Torun
* ID: 21901898
* Section : 1
* Assignment : 2
* Description : Header file for binary search tree node
*/

#ifndef __BSTNODE_H
#define __BSTNODE_H

#include <stdlib.h>
#include <stdio.h>


class BSTNode
{
public:
    BSTNode();
    ~BSTNode();
    BSTNode(const int& nodeItem, BSTNode* left = NULL, BSTNode* right = NULL):item(nodeItem), leftChildPtr(left), rightChildPtr(right){}
    
    int getItem();

private:
    int item;
    BSTNode* leftChildPtr;
    BSTNode* rightChildPtr;

    friend class BST;
};


#endif