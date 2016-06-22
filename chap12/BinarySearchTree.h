//
// Created by yijun on 6/21/16.
//

#ifndef CHAP12_BINARYSEARCHTREE_H
#define CHAP12_BINARYSEARCHTREE_H

#include <iostream>
#include <vector>

enum Error {
    kSuccess = 0,
    kAllocateError = 1,
};

struct BinaryNode {
//    BinaryNode();
    BinaryNode(int key,
               BinaryNode *parent = nullptr,
               BinaryNode *leftChild = nullptr,
               BinaryNode *rightChild = nullptr);

    BinaryNode *mLeftChild;
    BinaryNode *mRightChild;
    BinaryNode *mParent;

    int mKey;
//    char *mValue;
};

class BinarySearchTree {
private:
    void Transplant(BinaryNode *u, BinaryNode *v);
    BinaryNode *TreeMaximum(BinaryNode *node) const;
    BinaryNode *TreeMinimum(BinaryNode *node) const;

    void InorderTreeWalk(BinaryNode *node) const;
    void PreorderTreeWalk(BinaryNode *node) const;
    void PostorderTreeWalk(BinaryNode *node) const;

    BinaryNode *IterativeTreeSearch(BinaryNode *node, int key) const;
    BinaryNode *TreeSearch(BinaryNode *node, int key) const;
    void Clear(BinaryNode *node);

    BinaryNode *mRoot;

public:
    BinarySearchTree();
    BinarySearchTree(const std::vector<int> &A);
    ~BinarySearchTree();


    void InorderTreeWalk() const;
    void PreorderTreeWalk() const;
    void PostorderTreeWalk() const;


    BinaryNode *IterativeTreeSearch(int key) const;
    BinaryNode *TreeSearch(int key) const;

    BinaryNode *TreeMaximum() const;
    BinaryNode *TreeMinimum() const;

    void TreeInsert(BinaryNode *insertNode);
    void TreeDelete(BinaryNode *deleteNode);

    BinaryNode *TreePredecessor(BinaryNode *node) const;
    BinaryNode *TreeSuccessor(BinaryNode *node) const;
};

#endif //CHAP12_BINARYSEARCHTREE_H
