//
// Created by yijun on 6/22/16.
//

#ifndef CHAP14_REDBLACKTREE_H
#define CHAP14_REDBLACKTREE_H

#include <iostream>
#include <vector>

enum Color {
    kRed = 0,
    kBlack = 1
};

enum Error {
    kSuccess = 0,
    kAllocateError = 1,
};

struct Interval {
    int mLow;
    int mHigh;
    Interval(int low = -1, int high = -1);
};

struct RBTreeNode {
    friend class RBTree;
    int mKey;
    Color mColor; //
    RBTreeNode *mLeftChild;
    RBTreeNode *mRightChild;
    RBTreeNode *mParent;

//    int mSize;

    Interval mInterval; // for interval tree
    int mMax; // for interval tree

    RBTreeNode();
    RBTreeNode(Interval interval, Color color = kBlack,
               RBTreeNode *parent = nullptr, RBTreeNode *leftChild = nullptr,
               RBTreeNode *rightChild = nullptr);
};

class RBTree {
private:

    RBTreeNode *mRoot;
    RBTreeNode *mNilNode;

    void RBInsertFixUp(RBTreeNode *z);
    void RBDeleteFixUp(RBTreeNode *x);
    void RBTransplant(RBTreeNode *u, RBTreeNode *v);

    void ClearRBTree(RBTreeNode *node);

    void LeftRotate(RBTreeNode *x);
    void RightRotate(RBTreeNode *y);

    RBTreeNode *RBTreeMaximum(RBTreeNode *node) const;
    RBTreeNode *RBTreeMinimum(RBTreeNode *node) const;

    int GetMax(int a, int b, int c);

public:
    RBTree(const std::vector<Interval> &A);
    ~RBTree();

    void PreOrderTreeWalk(RBTreeNode *root) const;
    void InOrderTreeWalk(RBTreeNode *root) const;
    void PostOrderTreeWalk(RBTreeNode *root) const;

    void PreOrderTreeWalk() const;
    void InOrderTreeWalk() const;
    void PostOrderTreeWalk() const;

    RBTreeNode *RBTreeMaximum() const;
    RBTreeNode *RBTreeMinimum() const;

    RBTreeNode *RBTreeInOrderPredecessor(RBTreeNode *node) const;
    RBTreeNode *RBTreeInOrderSuccessor(RBTreeNode *node) const;

    void RBTreeBFSTraverse(RBTreeNode *node);
    void RBTreeBFSTraverse();

//    RBTreeNode *OSSelect(RBTreeNode *x, int i);
//    int OSRank(RBTreeNode *x);

    bool RBTreeOverlap(Interval *i, Interval *j);
    bool RBTreeLeft(Interval *i, Interval *j);
    bool RBTreeRight(Interval *i, Interval *j);

    RBTreeNode *IntervalSearch(Interval *i);
    RBTreeNode *IntervalInsert(RBTreeNode* z);
    void IntervalDelete(RBTreeNode* z);
    RBTreeNode* GetNilNode() const;
};

#endif //CHAP14_REDBLACKTREE_H
