/**
* Title : Binary Search Trees
* Author : Utku Boran Torun
* ID: 21901898
* Section : 1
* Assignment : 2
* Description : Implementation for binary search tree node
*/

#include "BSTNode.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

BSTNode:: BSTNode(){}

BSTNode:: ~BSTNode(){}


int BSTNode:: getItem()
{
    return this->item;
}