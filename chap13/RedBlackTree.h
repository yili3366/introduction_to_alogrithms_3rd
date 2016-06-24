//
// Created by yijun on 6/22/16.
//

#ifndef CHAP13_REDBLACKTREE_H
#define CHAP13_REDBLACKTREE_H

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

struct RBTreeNode {
    friend class RBTree;
    int mKey;
    Color mColor; //
    RBTreeNode *mLeftChild;
    RBTreeNode *mRightChild;
    RBTreeNode *mParent;

    RBTreeNode();
    RBTreeNode(RBTreeNode *node);
    RBTreeNode(int key, Color flag = kRed,
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

    RBTreeNode *IterativeRBTreeSearch(RBTreeNode *node, int key) const;
    RBTreeNode *RBTreeSearch(RBTreeNode *node, int key) const;

    RBTreeNode *RBTreeMaximum(RBTreeNode *node) const;
    RBTreeNode *RBTreeMinimum(RBTreeNode *node) const;
public:
    RBTree(const std::vector<int> &A);
    ~RBTree();

    void RBInsert(RBTreeNode *z);
    void RBDelete(RBTreeNode *z);

    void PreOrderTreeWalk(RBTreeNode *root) const;
    void InOrderTreeWalk(RBTreeNode *root) const;
    void PostOrderTreeWalk(RBTreeNode *root) const;

    void PreOrderTreeWalk() const;
    void InOrderTreeWalk() const;
    void PostOrderTreeWalk() const;

    RBTreeNode *IterativeRBTreeSearch(int key) const;
    RBTreeNode *RBTreeSearch(int key) const;

    RBTreeNode *RBTreeMaximum() const;
    RBTreeNode *RBTreeMinimum() const;

    RBTreeNode *RBTreeInOrderPredecessor(RBTreeNode *node) const;
    RBTreeNode *RBTreeInOrderSuccessor(RBTreeNode *node) const;

    void RBTreeBFSTraverse(RBTreeNode *node);
    void RBTreeBFSTraverse();
};

#endif //CHAP13_REDBLACKTREE_H
