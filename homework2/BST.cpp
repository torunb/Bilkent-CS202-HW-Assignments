/**
* Title : Binary Search Trees
* Author : Utku Boran Torun
* ID: 21901898
* Section : 1
* Assignment : 2
* Description : Implementation for binary search tree
*/

#include "BST.h"

#include <iostream>

using namespace std;

const int MAX_INT = 500;
const int defaultTab = 6;


BST:: BST(): root(NULL)
{

}

BST:: ~BST()
{

}

BST:: BST(BST*& tree)
{
    copyTree(tree->root);
}

void BST:: copyTree(BSTNode*& treePtr)
{
    if(treePtr != NULL)
    {
        BSTNode* newNode = new BSTNode(treePtr->item, NULL, NULL);
        copyTree(treePtr->leftChildPtr);
        this->insertItem(treePtr->item);
        copyTree(treePtr->leftChildPtr);
    }
}

bool BST:: isEmpty() const
{
    return root == NULL;
}

void BST:: displayTree(BSTNode*& treePtr)
{
    if(treePtr == NULL)
    {
        return;
    }
    else
    {
        cout << treePtr->item << ", ";
        displayTree(treePtr->leftChildPtr);
        displayTree(treePtr->rightChildPtr);
    }
}

void BST:: displayTree()
{
    displayTree(root);
}

void BST:: inserter(BSTNode*& treePtr, int newItem)
{
    if(treePtr == NULL)
    {
        treePtr = new BSTNode(newItem, NULL, NULL);
    }
    else if (newItem < treePtr->item)
    {
        inserter(treePtr->leftChildPtr, newItem);
    }
    else
    {
        inserter(treePtr->rightChildPtr, newItem);
    }
    
}

void BST:: insertItem(int key)
{
    inserter(root, key);
}

void BST:: processLeftMost(BSTNode*& nodePtr, int& key)
{
    if(nodePtr->leftChildPtr == NULL)
    {
        key = nodePtr->item;
        BSTNode* delPtr = nodePtr;
        nodePtr = nodePtr->rightChildPtr;
        delPtr->rightChildPtr = NULL;
        delete delPtr;
    }

    else
        processLeftMost(nodePtr->leftChildPtr, key);
}

void BST:: deleteNodeItem(BSTNode*& nodePtr)
{
    BSTNode* delPtr;
    int temp;

    if ( (nodePtr->leftChildPtr == NULL) && (nodePtr->rightChildPtr == NULL) ) 
    {   
		delete nodePtr;
		nodePtr = NULL;
    }

    else if (nodePtr->leftChildPtr == NULL)
    {
		delPtr = nodePtr;
		nodePtr = nodePtr->rightChildPtr;
		delPtr->rightChildPtr = NULL; 
		delete delPtr;
	}

    else if(nodePtr->rightChildPtr == NULL)
    {
        delPtr = nodePtr;
        nodePtr = nodePtr->leftChildPtr;
        delPtr->leftChildPtr = NULL;
        delete delPtr;
    }
    else
    {
        processLeftMost(nodePtr->rightChildPtr, temp);
        nodePtr->item = temp;
    }

}

void BST:: deleteItem(BSTNode*& treePtr, int key)
{
    if(treePtr == NULL)
        return;

    else if (key == treePtr->item)
        deleteNodeItem(treePtr);

    else if(key < treePtr->item)
        deleteItem(treePtr->leftChildPtr, key);
        
    else
        deleteItem(treePtr->rightChildPtr, key);
}

void BST:: deleteItem(int key)
{
    deleteItem(root, key);
}

BSTNode* BST:: retrieveSequenceHelper(BSTNode*& treePtr, int key)
{
    if(treePtr == NULL)
    {
        cout << endl;
        return NULL;
    }
    else if(key == treePtr->item)
    {
        cout << treePtr->item << ", ";
        return treePtr;
    }
    else if(key < treePtr->item)
    {
        cout << treePtr->item << ", ";
        return retrieveSequenceHelper(treePtr->leftChildPtr, key);
    }
    else
    {
        cout << treePtr->item << ", ";
        return retrieveSequenceHelper(treePtr->rightChildPtr, key);
    }
}

BSTNode* BST:: retrieveHelper(BSTNode*& treePtr, int key)
{
    if(treePtr == NULL)
    {
        return NULL;
    }
    else if(key == treePtr->item)
    {
        return treePtr;
    }
    else if(key < treePtr->item)
    {
        return retrieveHelper(treePtr->leftChildPtr, key);
    }
    else
    {
        return retrieveHelper(treePtr->rightChildPtr, key);
    }
    
}

BSTNode* BST:: retrieveSequenceItem(int key)
{
    return retrieveSequenceHelper(root, key);
}

BSTNode* BST:: retrieveItem(int key)
{
    return retrieveHelper(root, key);
}

void BST:: helperInorder(BSTNode*& treePtr, int& nodeCount, int*& arr, int& i)
{
    if(treePtr != NULL)
    {
        nodeCount++;
        helperInorder(treePtr->leftChildPtr, nodeCount, arr, i);
        arr[i++] = treePtr->item;
        helperInorder(treePtr->rightChildPtr, nodeCount, arr, i);
    }
}

int* BST:: inorderTraversal(int& length)
{
    cout << endl;
    int i = 0, nodeCount = 0;

    int* arr = new int[MAX_INT];

    helperInorder(root, nodeCount, arr, i);
    length = nodeCount;
    int* arr1 = new int[length];

    
    for(int j = 0; j < length; j++)
    {
        arr1[j] = arr[j];
    }
    
    delete arr;
    return arr1;
}

void BST:: helperInorderForLevel(BSTNode*& treePtr, int& nodeCount)
{
    if(treePtr != NULL)
    {
        nodeCount++;
        helperInorderForLevel(treePtr->leftChildPtr, nodeCount);
        helperInorderForLevel(treePtr->rightChildPtr, nodeCount);
    }
}
void BST:: countNumberOfNodes(BSTNode*& treePtr, int& nodeCount)
{
    if(treePtr == NULL)
    {
        return;
    }
    else
    {
        countNumberOfNodes(treePtr->leftChildPtr, nodeCount);
        nodeCount++;
        countNumberOfNodes(treePtr->rightChildPtr, nodeCount);
    }
}

void BST:: countNumberOfNodesBiggerThanTwo(BSTNode*& treePtr, int& nodeCount)
{
    if(treePtr == NULL)
    {
        return;
    }
    else
    {
        countNumberOfNodes(treePtr->leftChildPtr, nodeCount);
        nodeCount++;
        countNumberOfNodes(treePtr->rightChildPtr, nodeCount);
    }
}

void BST:: countNumberOfNodes()
{
    int nodeCount = 0;
    countNumberOfNodes(root, nodeCount);
    cout << "Number of nodes: " << nodeCount << endl;
}

void BST:: numberOfNodesHelper(BSTNode*& treePtr, int& level, int& nodeCount)
{
    BSTNode* temp = treePtr;
    BSTNode* temp2 = treePtr;

    if(level == 1)
    {
        countNumberOfNodes(root, nodeCount);
    }
    else if(level == 2)
    {
        temp = temp->leftChildPtr;
        temp2 = temp2->rightChildPtr;
        countNumberOfNodes(temp, nodeCount);
        countNumberOfNodes(temp2, nodeCount);
    }
    else if(level == 3)
    {
        for(int i = 1; i < level - 1; i++)
        {
            temp = temp->leftChildPtr;
            temp2 = temp2->rightChildPtr;
        }

        countNumberOfNodesBiggerThanTwo(temp, nodeCount);
        nodeCount--;
        countNumberOfNodesBiggerThanTwo(temp2, nodeCount);
        nodeCount--;
    }
    else
    {
        for(int i = 1; i < level - 1; i++)
        {
            temp = temp->leftChildPtr;
            temp2 = temp2->rightChildPtr;
        }
        countNumberOfNodesBiggerThanTwo(temp, nodeCount);
        countNumberOfNodesBiggerThanTwo(temp2, nodeCount);
    }
}

int BST::countNodesBelowLevel(int level)
{
    int nodeCount = 0;

    numberOfNodesHelper(root, level, nodeCount);
    return nodeCount;
}


BSTNode* BST:: getRoot()
{
    return root;
}

// bool BST:: hasSequence(int* seq, int length)
// {
//     bool hasSequence = false;

// }


bool BST::hasSequence(int* seq, int length)
{
    bool hasSequence = true;

    for(int i = 0; i < length; i++)
    {
        BSTNode* checker = retrieveSequenceItem(seq[i]);
        if(checker == NULL)
        {
            hasSequence = false;
            cout << "Has not sequence" << endl;
            return hasSequence;
        }
    }

    if(length == 4)
    {
        for(int i = length - 1; i >= 0; i--)
        {
            BSTNode* checker = retrieveSequenceItem(seq[length - 1] - 1);
            if(checker != NULL)
            {
                hasSequence = false;
                cout << "Has not sequence" << endl;
                return hasSequence;
            }
        }
    }
    cout << "Has sequence" << endl;
    return hasSequence;
}