/**
* Title : Binary Search Trees
* Author : Utku Boran Torun
* ID: 21901898
* Section : 1
* Assignment : 2
* Description : Header file for binary search tree
*/

#ifndef __BST_H
#define __BST_H

#include "BSTNode.h"

class BST
{
public:
    BST();
    ~BST();

    BST(BST*& tree);

    bool isEmpty() const; //
    void insertItem(int key); //
    void deleteItem(int key); // 
    BSTNode* retrieveItem(int key); // 
    int* inorderTraversal(int& length); //
    bool hasSequence(int* seq, int length);
    int countNodesBelowLevel(int level);

    // insert helpers
    void inserter(BSTNode*& treePtr, int newItem);

    // delete helpers
    void deleteItem(BSTNode*& treePtr, int key);
    void deleteNodeItem(BSTNode*& nodePtr);
    void processLeftMost(BSTNode*& nodePtr, int& key);

    // retrieve helpers
    BSTNode* retrieveHelper(BSTNode*& treePtr, int key);
    BSTNode* retrieveSequenceHelper(BSTNode*& treePtr, int key);
    BSTNode* retrieveSequenceItem(int key);

    // inorder traversal helper
    void helperInorder(BSTNode*& treePtr, int& nodeCount, int*& arr, int& i);
    void helperInorderForLevel(BSTNode*& treePtr, int& nodeCount);

    // print function
    void displayTree(BSTNode*& treePtr);
    void displayTree();
    
    // below helpers
    void countNumberOfNodes(BSTNode*& treePtr, int& nodeCount);
    void countNumberOfNodesBiggerThanTwo(BSTNode*& treePtr, int& nodeCount);
    void numberOfNodesHelper(BSTNode*& treePtr, int& level, int& nodeCount);
    void countNumberOfNodes();
    void countNumberOfNodesDiff(BSTNode* treePtr, int& nodeCount);


    // copy functiom
    void copyTree(BSTNode*& treePtr);

    // get root
    BSTNode* getRoot();

private:
    BSTNode* root;

};

#endif