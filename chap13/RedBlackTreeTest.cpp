//
// Created by yijun on 6/22/16.
//

#include <iostream>
#include <gtest/gtest.h>

#include "RedBlackTree.h"

TEST(RBTreeTest, RBTree) {
    int array[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    std::vector<int> vec(array, array + sizeof(array) / sizeof(int));
    RBTree *rbTree = new RBTree(vec);

    ASSERT_TRUE(rbTree != nullptr);

    std::cout << " before operating " << std::endl;
    rbTree->InOrderTreeWalk();

//    rbTree->PostOrderTreeWalk();
//    rbTree->PreOrderTreeWalk();

    RBTreeNode* p1 = rbTree->RBTreeSearch(6);
    RBTreeNode* p2 = rbTree->IterativeRBTreeSearch(7);
    rbTree->RBTreeMaximum();
    rbTree->RBTreeMinimum();

#if 1
    RBTreeNode *p3 = rbTree->RBTreeInOrderSuccessor(p1);
    RBTreeNode *p4 = rbTree->RBTreeInOrderPredecessor(p1);
    RBTreeNode *p5 = rbTree->RBTreeInOrderSuccessor(p2);
    RBTreeNode *p6 = rbTree->RBTreeInOrderPredecessor(p2);

#endif
    RBTreeNode *newNode1 = new RBTreeNode(14);
    RBTreeNode *newNode2 = new RBTreeNode(19);

    rbTree->RBInsert(newNode1);
    rbTree->RBInsert(newNode2);

    rbTree->RBDelete(p1);
    rbTree->RBDelete(p2);

#if 1
    rbTree->RBDelete(newNode1);
    rbTree->RBDelete(newNode2);

#endif

    std::cout << " after operating" << std::endl;
    rbTree->InOrderTreeWalk();
}
