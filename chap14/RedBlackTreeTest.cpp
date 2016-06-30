//
// Created by yijun on 6/22/16.
//

#include <iostream>
#include <gtest/gtest.h>

#include "RedBlackTree.h"

TEST(RBTreeTest, RBTree) {
//    Interval array[] = {{15, 15}, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    Interval array[] = {{0, 3}, {6, 10}, {5, 8}, {8, 9}, {15, 23}, {16, 21}, {25, 30}, {17, 19}, {26, 26}, {19, 20}};
    std::vector<Interval> vec(array, array + sizeof(array) / sizeof(Interval));

    for (std::vector<Interval>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
        std::cout << (*iter).mLow << " " << (*iter).mHigh << std::endl;
    }

    RBTree *rbTree = new RBTree(vec);

    ASSERT_TRUE(rbTree != nullptr);

    std::cout << " before operating " << std::endl;
    rbTree->RBTreeBFSTraverse();

    Interval *interval1 = new Interval(0, 3);
    Interval *interval2 = new Interval(25, 30);

    RBTreeNode *p1 = rbTree->IntervalSearch(interval1);
    RBTreeNode *p2 = rbTree->IntervalSearch(interval2);

    std::cout << " p1 high " << p1->mInterval.mHigh
        << " p1 low " << p1->mInterval.mLow << std::endl;

    std::cout << " p2 high " << p2->mInterval.mHigh
        << " p2 low " << p2->mInterval.mLow << std::endl;

    rbTree->RBTreeMaximum();
    rbTree->RBTreeMinimum();

    RBTreeNode *p3 = rbTree->RBTreeInOrderSuccessor(p1);
    RBTreeNode *p4 = rbTree->RBTreeInOrderPredecessor(p1);
    RBTreeNode *p5 = rbTree->RBTreeInOrderSuccessor(p2);
    RBTreeNode *p6 = rbTree->RBTreeInOrderPredecessor(p2);

//    Interval *interval3 = new Interval(22, 28);
//    Interval *interval4 = new Interval(19, 25);

    Interval interval3 = Interval(22, 28);
    Interval interval4 = Interval(19, 25);

//    RBTreeNode *newNode1 = rbTree->IntervalSearch(&interval3);
//    RBTreeNode *newNode2 = rbTree->IntervalSearch(&interval4);

    RBTreeNode newNode1 = RBTreeNode(interval3);
    RBTreeNode newNode2 = RBTreeNode(interval4);

    std::cout << " newNode1 high " << newNode1.mInterval.mHigh
        << " newNode1 low " << newNode1.mInterval.mLow << std::endl;

    std::cout << " newNode2 high " << newNode2.mInterval.mHigh
        << " newNode2 low " << newNode2.mInterval.mLow << std::endl;

    rbTree->IntervalInsert(&newNode1);
    rbTree->IntervalInsert(&newNode2);

    std::cout << " after insert" << std::endl;
    rbTree->RBTreeBFSTraverse();


    rbTree->IntervalDelete(p1);
    rbTree->IntervalDelete(p2);

    std::cout << " after delete" << std::endl;
    rbTree->RBTreeBFSTraverse();

#if 0
    rbTree->IntervalDelete(&newNode1);
    rbTree->IntervalDelete(&newNode2);

    std::cout << " after delete" << std::endl;
    rbTree->RBTreeBFSTraverse();
#endif

}
