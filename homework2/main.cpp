/**
* Title : Binary Search Trees
* Author : Utku Boran Torun
* ID: 21901898
* Section : 1
* Assignment : 2
* Description : Main function in order to test binary search tree functions
*/

#include "BST.h"
#include <iostream>

using namespace std;

void merge(BST& tree1, BST& tree2, int& nodeCount1, int& nodeCount2, BST*& newTree)
{
    nodeCount1 = 0, nodeCount2 = 0;
    BSTNode* root1 = tree1.getRoot();
    BSTNode* root2 = tree2.getRoot();
    tree1.countNumberOfNodes(root1, nodeCount1);
    tree2.countNumberOfNodes(root2, nodeCount2);

    int* arr1 = tree1.inorderTraversal(nodeCount1);
    int* arr2 = tree2.inorderTraversal(nodeCount2);

    int size = nodeCount1 + nodeCount2;

    int* all = new int[size];


    for(int i = 0; i < nodeCount1; i++)
    {
        all[i] = arr1[i];
    }

    int j = 0;
    for(int i = nodeCount1; i < size && j < nodeCount2; i++)
    {
        all[i] = arr2[j++];
    }


    for(int i = 0; i < size; i++)
    {
        newTree->insertItem(all[i]);
    }

}

BST* merge(const BST& tree1, const BST& tree2)
{
    BST tempTree1 = tree1;
    BST tempTree2 = tree2;


    int nodeCount1 = 0, nodeCount2 = 0;

    BST* newTree = new BST();
    merge(tempTree1, tempTree2, nodeCount1, nodeCount2, newTree);

    return newTree;
}

void displayArray(const int *arr, const int size) // for display of inorder traversal array
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

int main()
{
    BST myTree;
    int length = 0;

    myTree.insertItem(8);
    myTree.insertItem(4);
    myTree.insertItem(13);
    myTree.insertItem(3);
    myTree.insertItem(6);
    myTree.insertItem(12);
    myTree.insertItem(15);
    myTree.insertItem(1);
    myTree.insertItem(5);
    myTree.insertItem(10);
    myTree.insertItem(14);
    myTree.insertItem(2);
    myTree.insertItem(7);
    myTree.insertItem(9);

    cout << "-----------Initial BST-------------" << endl;
    myTree.displayTree();

    cout << endl;
    cout << endl;
    myTree.deleteItem(7);
    myTree.deleteItem(9);
    cout << "-----------After deletion of 7 and 9-------------" << endl;
    myTree.displayTree();

    cout << endl;
    cout << endl;

    cout << "-----------Retrieve Item Function (Retrieve 10, 14, 5, 15 and print it)-------------" << endl;
    BSTNode* retrieved = myTree.retrieveItem(10);
    BSTNode* retrieved2 = myTree.retrieveItem(14);
    BSTNode* retrieved3 = myTree.retrieveItem(5);
    BSTNode* retrieved4 = myTree.retrieveItem(15);


    cout << "Item of retrieved node: " << retrieved->getItem() << endl;
    cout << "Item of retrieved node: " << retrieved2->getItem() << endl;
    cout << "Item of retrieved node: " << retrieved3->getItem() << endl;
    cout << "Item of retrieved node: " << retrieved4->getItem() << endl;


    cout << endl;
    cout << endl;

    BST otherTree;
    otherTree.insertItem(16);
    otherTree.insertItem(7);
    otherTree.insertItem(11);
    otherTree.insertItem(9);
    
    

    cout << "-----------Inorder Traversal Function of Two Trees-------------" << endl;
    int* arr = myTree.inorderTraversal(length);
    cout << "My tree: ";
    displayArray(arr, length);
    int* arr2 = otherTree.inorderTraversal(length);
    cout<< "Other tree: ";
    displayArray(arr2, length);
    cout << endl;
    cout << endl;

    cout << "-----------HasSequence Function and nodes that are visited-------------" << endl;

    int seq[] = {1, 2, 3, 4, 5, 6};
    int seq2[] = {10, 12, 13, 15};
    int seq3[] = {10, 11, 12};

    myTree.hasSequence(seq, 6);
    myTree.hasSequence(seq2, 4);
    myTree.hasSequence(seq3, 3);

    cout << endl;
    cout << endl;

    cout << "-----------Count Nodes Below Level Function-------------" << endl;
    int level1 = 1, level2 = 2, level3 = 3;
    int nodeCount1 = myTree.countNodesBelowLevel(level1);
    int nodeCount2 = myTree.countNodesBelowLevel(level2);
    int nodeCount3 = myTree.countNodesBelowLevel(level3);

    cout << "Count nodes below level " << level1 << ": " << nodeCount1 << endl;
    cout << "Count nodes below level " << level2 << ": " << nodeCount2 << endl;
    cout << "Count nodes below level " << level3 << ": " << nodeCount3 << endl;

    cout << endl;
    cout << endl;

    cout << "-----------Merge Function-------------" << endl;
    

    cout << "The other tree that will be merged" << endl;
    otherTree.displayTree();

    BST* merged = merge(myTree, otherTree);
    cout << "After the merge: " << endl;
    merged->displayTree();

    cout << endl;
    cout << endl;

    return 0;
}