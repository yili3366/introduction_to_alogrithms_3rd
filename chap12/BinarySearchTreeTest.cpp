//
// Created by yijun on 6/21/16.
//

#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#include "BinarySearchTree.h"

TEST(BinarySearchTreeTest, BinarySearchTree) {

    int array[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    std::vector<int> vec(array, array + sizeof(array) / sizeof(int));

    BinarySearchTree *binarySearchTree = new BinarySearchTree(vec);

    ASSERT_TRUE(binarySearchTree != nullptr);

    binarySearchTree->InorderTreeWalk();

    BinaryNode *p1 = binarySearchTree->TreeSearch(6);
    BinaryNode *p2 = binarySearchTree->IterativeTreeSearch(7);
    binarySearchTree->TreeMaximum();
    binarySearchTree->TreeMinimum();
    BinaryNode *p3 = binarySearchTree->TreeSuccessor(p1);
    BinaryNode *p4 = binarySearchTree->TreePredecessor(p1);
    BinaryNode *p5 = binarySearchTree->TreeSuccessor(p2);
    BinaryNode *p6 = binarySearchTree->TreePredecessor(p2);

    BinaryNode *newNode1 = new BinaryNode(14);
    BinaryNode *newNode2 = new BinaryNode(19);

    binarySearchTree->TreeInsert(newNode1);
    binarySearchTree->TreeInsert(newNode2);

    binarySearchTree->TreeDelete(newNode1);
    binarySearchTree->TreeDelete(newNode2);

    binarySearchTree->TreeDelete(p1);
    binarySearchTree->TreeDelete(p2);
}

