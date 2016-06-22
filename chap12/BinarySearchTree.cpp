//
// Created by yijun on 6/21/16.
//

#include "BinarySearchTree.h"

#include <iostream>
#include <vector>

//BinaryNode::BinaryNode() {
//}

BinaryNode::BinaryNode(int key,
                       BinaryNode *parent,
                       BinaryNode *leftChild,
                       BinaryNode *rigthChild) :
    mKey(key), mParent(parent), mLeftChild(leftChild), mRightChild(rigthChild) {
}

BinarySearchTree::BinarySearchTree() : mRoot(nullptr) {
}

BinarySearchTree::BinarySearchTree(const std::vector<int> &A) {
    mRoot = nullptr;

    for (int i = 0; i < A.size(); ++i) {
        BinaryNode *newNode = new BinaryNode(A[i]);
        if (newNode == nullptr) {
            std::runtime_error("allcate error!");
            exit(kAllocateError);
        }
        TreeInsert(new BinaryNode(A[i]));
    }

    mRoot->mParent = nullptr;
}

void BinarySearchTree::Clear(BinaryNode *node) {
    while (node != nullptr) {
        Clear(node->mLeftChild);
        Clear(node->mRightChild);
        BinaryNode *tmp = node;
        node = nullptr;
        delete tmp;
    }
}

BinarySearchTree::~BinarySearchTree() {
    Clear(mRoot);
}

void BinarySearchTree::InorderTreeWalk() const {
    InorderTreeWalk(mRoot);
    std::cout << std::endl;
}

void BinarySearchTree::InorderTreeWalk(BinaryNode *node) const {
    if (node != nullptr) {
        InorderTreeWalk(node->mLeftChild);
        std::cout << node->mKey << " ";
        InorderTreeWalk(node->mRightChild);
    }
}

void BinarySearchTree::PreorderTreeWalk() const {
    PreorderTreeWalk(mRoot);
    std::cout << std::endl;
}

void BinarySearchTree::PreorderTreeWalk(BinaryNode *node) const {
    if (node != nullptr) {
        std::cout << node->mKey << " ";
        InorderTreeWalk(node->mLeftChild);
        InorderTreeWalk(node->mRightChild);
    }
}

void BinarySearchTree::PostorderTreeWalk() const {
    PostorderTreeWalk(mRoot);
    std::cout << std::endl;
}

void BinarySearchTree::PostorderTreeWalk(BinaryNode *node) const {
    if (node != nullptr) {
        InorderTreeWalk(node->mLeftChild);
        InorderTreeWalk(node->mRightChild);
        std::cout << node->mKey << " ";
    }
}

BinaryNode *BinarySearchTree::IterativeTreeSearch(int key) const {
    BinaryNode *p = IterativeTreeSearch(mRoot, key);
    if (p != nullptr) {
        std::cout << " find key " << p->mKey << std::endl;
    } else {
        std::cout << " no find key " << key << std::endl;
    }

    return p;
}
BinaryNode *BinarySearchTree::IterativeTreeSearch(BinaryNode *node, int key) const {
    while (node != nullptr && key != node->mKey) {
        if (key < node->mKey)
            node = node->mLeftChild;
        else if (key > node->mKey)
            node = node->mRightChild;
    }
    return node;
}

BinaryNode *BinarySearchTree::TreeSearch(int key) const {
    BinaryNode *p = TreeSearch(mRoot, key);
    if (p != nullptr) {
        std::cout << " find key " << p->mKey << std::endl;
    } else {
        std::cout << " no find key " << key << std::endl;
    }

    return p;
}

BinaryNode *BinarySearchTree::TreeSearch(BinaryNode *node, int key) const {
    if (node == nullptr || node->mKey == key) {
        return node;
    }

    if (key < node->mKey) {
        return TreeSearch(node->mLeftChild, key);
    } else {
        return TreeSearch(node->mRightChild, key);
    }
}

BinaryNode *BinarySearchTree::TreeMaximum() const {
    BinaryNode *p = TreeMaximum(mRoot);
    std::cout << " tree maximum: " << p->mKey << std::endl;
    return p;
}

BinaryNode *BinarySearchTree::TreeMaximum(BinaryNode *node) const {
    while (node != nullptr && node->mRightChild != nullptr) {
        node = node->mRightChild;
    }
    return node;
}

BinaryNode *BinarySearchTree::TreeMinimum() const {
    BinaryNode *p = TreeMinimum(mRoot);
    std::cout << " tree minimum: " << p->mKey << std::endl;
    return p;
}

BinaryNode *BinarySearchTree::TreeMinimum(BinaryNode *node) const {
    while (node != nullptr && node->mLeftChild != nullptr) {
        node = node->mLeftChild;
    }
    return node;
}

BinaryNode *BinarySearchTree::TreePredecessor(BinaryNode *node) const {
    if (node->mLeftChild != nullptr) {
        return TreeMaximum(node);
    }

    BinaryNode *predecessorNode = node->mParent;

    while (predecessorNode != nullptr && node == predecessorNode->mLeftChild) {
        node = predecessorNode;
        predecessorNode = predecessorNode->mParent;
    }

    return predecessorNode;
}

BinaryNode *BinarySearchTree::TreeSuccessor(BinaryNode *node) const {
    if (node->mRightChild != nullptr) {
        return TreeMinimum(node);
    }

    BinaryNode *successorNode = node->mParent;

    while (successorNode != nullptr && node == successorNode->mRightChild) {
        node = successorNode;
        successorNode = successorNode->mParent;
    }

    return successorNode;
}

void BinarySearchTree::TreeInsert(BinaryNode *insertNode) {
    BinaryNode *pNode = nullptr;
    BinaryNode *root = mRoot;

    while (root != nullptr) {
        pNode = root;
        if (insertNode->mKey < root->mKey) {
            root = root->mLeftChild;
        } else {
            root = root->mRightChild;
        }
    }

    insertNode->mParent = pNode;

    if (pNode == nullptr) {
         mRoot = insertNode;
    } else if (insertNode->mKey < pNode->mKey) {
        pNode->mLeftChild = insertNode;
    } else {
        pNode->mRightChild = insertNode;
    }
}

void BinarySearchTree::Transplant(BinaryNode *u, BinaryNode *v) {
    if (u->mParent == nullptr) {
        mRoot = v;
    } else if (u == u->mParent->mLeftChild) {
        u->mParent->mLeftChild = v;
    } else {
        u->mParent->mRightChild = v;
    }

    if (v != nullptr) {
        v->mParent = u->mParent;
    }
}

void BinarySearchTree::TreeDelete(BinaryNode *deleteNode) {
    BinaryNode *successorOfDeletedNode;

    if (deleteNode->mLeftChild == nullptr) {
        Transplant(deleteNode, deleteNode->mRightChild);
    } else if (deleteNode->mRightChild == nullptr) {
        Transplant(deleteNode, deleteNode->mLeftChild);
    } else {
        successorOfDeletedNode = TreeMinimum(deleteNode->mRightChild);
        if (successorOfDeletedNode->mParent != deleteNode) {
            Transplant(successorOfDeletedNode, successorOfDeletedNode->mRightChild);
            successorOfDeletedNode->mRightChild = deleteNode->mRightChild;
            successorOfDeletedNode->mRightChild->mParent = successorOfDeletedNode;
        }
        Transplant(deleteNode, successorOfDeletedNode);
        successorOfDeletedNode->mLeftChild = deleteNode->mLeftChild;
        successorOfDeletedNode->mLeftChild->mParent = successorOfDeletedNode;
    }
}