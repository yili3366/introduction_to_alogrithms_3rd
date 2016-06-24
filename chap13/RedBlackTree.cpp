//
// Created by yijun on 6/22/16.
//

#include "RedBlackTree.h"

RBTreeNode::RBTreeNode() :
    mKey(-1), mColor(kRed), mLeftChild(nullptr), mRightChild(nullptr), mParent(nullptr) {
}

RBTreeNode::RBTreeNode(RBTreeNode *node) :
    mKey(node->mKey), mColor(node->mColor), mLeftChild(node->mLeftChild),
    mRightChild(node->mRightChild), mParent(node->mParent) {
}

RBTreeNode::RBTreeNode(int key, Color flag,
                       RBTreeNode *parent, RBTreeNode *leftChild, RBTreeNode *rightChild) :
    mKey(key), mColor(flag), mLeftChild(leftChild), mRightChild(rightChild), mParent(parent) {
}

RBTree::RBTree(const std::vector<int> &A) : mNilNode(new RBTreeNode()) {
    mNilNode->mColor = kBlack;
    mNilNode->mKey = -1;
    mNilNode->mLeftChild = nullptr;
    mNilNode->mRightChild = nullptr;
    mNilNode->mParent = nullptr;
    mRoot = mNilNode;

    for (int i = 0; i < A.size(); i++) {
        RBTreeNode *rbTreeNode = new RBTreeNode(A[i]);
        if (rbTreeNode == nullptr) {
            std::runtime_error("allcate error!");
            exit(kAllocateError);
        }
        RBInsert(rbTreeNode);
    }

    mRoot->mParent = mNilNode;
}

RBTree::~RBTree() {
    ClearRBTree(mRoot);
}

void RBTree::LeftRotate(RBTreeNode *x) {
    RBTreeNode *y;

    if (x->mRightChild == mNilNode) {
        std::cout << "can't left rotate" << std::endl;
        return;
    }

    y = x->mRightChild;
    x->mRightChild = y->mLeftChild;

    if (y->mLeftChild != mNilNode) {
        y->mLeftChild->mParent = x;
    }

    y->mParent = x->mParent;

    if (x->mParent == mNilNode) {
        mRoot = y;
    } else if (x->mParent->mLeftChild == x) {
        x->mParent->mLeftChild = y;
    } else {
        x->mParent->mRightChild = y;
    }

    y->mLeftChild = x;
    x->mParent = y;
}

void RBTree::RightRotate(RBTreeNode *y) {
    RBTreeNode *x;

    if (y->mLeftChild == mNilNode) {
        std::cout << "can't right rotate!" << std::endl;
        return;
    }
    x = y->mLeftChild;
    y->mLeftChild = x->mRightChild;
    if (x->mRightChild != mNilNode) {
        x->mRightChild->mParent = y;
    }

    x->mParent = y->mParent;

    if (y->mParent == mNilNode) {
        mRoot = x;
    } else if (y->mParent->mRightChild == y) {
        y->mParent->mRightChild = x;
    } else {
        y->mParent->mLeftChild = x;
    }

    y->mParent = x;
    x->mRightChild = y;
}

void RBTree::RBInsert(RBTreeNode *z) {
    RBTreeNode *y = mNilNode;
    RBTreeNode *x = mRoot;

    while (x != mNilNode) {
        y = x;
        if (z->mKey < x->mKey) {
            x = x->mLeftChild;
        } else {
            x = x->mRightChild;
        }
    }

    z->mParent = y;
    if (y == mNilNode) {
        mRoot = z;
    } else if (z->mKey < y->mKey) {
        y->mLeftChild = z;
    } else {
        y->mRightChild = z;
    }

    z->mLeftChild = mNilNode;
    z->mRightChild = mNilNode;
    z->mColor = kRed;

    RBInsertFixUp(z);
}

void RBTree::RBInsertFixUp(RBTreeNode *z) {
    RBTreeNode *y;

    while (z->mParent->mColor == kRed) {
        if (z->mParent == z->mParent->mParent->mLeftChild) {
            y = z->mParent->mParent->mRightChild;
            if (y->mColor == kRed) {
                z->mParent->mColor = kBlack;
                y->mColor = kBlack;
                z->mParent->mParent->mColor = kRed;
                z = z->mParent->mParent;
            } else {
                if (z == z->mParent->mRightChild) {
                    z = z->mParent;
                    LeftRotate(z);
                }
                z->mParent->mColor = kBlack;
                z->mParent->mParent->mColor = kRed;
                RightRotate(z->mParent->mParent);
            }
        } else if (z->mParent == z->mParent->mParent->mRightChild) {
            y = z->mParent->mParent->mLeftChild;
            if (y->mColor == kRed) {
                z->mParent->mColor = kBlack;
                y->mColor = kBlack;
                z->mParent->mParent->mColor = kRed;
                z = z->mParent->mParent;
            } else {
                if (z == z->mParent->mLeftChild) {
                    z = z->mParent;
                    RightRotate(z);
                }
                z->mParent->mColor = kBlack;
                z->mParent->mParent->mColor = kRed;
                LeftRotate(z->mParent->mParent);
            }
        }
    }
    mRoot->mColor = kBlack;
}

void RBTree::RBTransplant(RBTreeNode *u, RBTreeNode *v) {
    if (u->mParent == mNilNode) {
        mRoot = v;
    } else if (u == u->mParent->mLeftChild) {
        u->mParent->mLeftChild = v;
    } else {
        u->mParent->mRightChild = v;
    }

    v->mParent = u->mParent;
}

void RBTree::RBDeleteFixUp(RBTreeNode *x) {
    RBTreeNode *w;
    while (x != mRoot && x->mColor == kBlack) {
        if (x == x->mParent->mLeftChild) {
            w = x->mParent->mRightChild;
            if (w->mColor == kRed) {
                w->mColor = kBlack;
                x->mParent->mColor = kRed;
                LeftRotate(x->mParent);
                w = x->mParent->mRightChild;
            }

            if (w->mLeftChild->mColor == kBlack && w->mRightChild->mColor == kBlack) {
                w->mColor == kRed;
                x = x->mParent;
            } else {
                if (w->mRightChild->mColor == kBlack) {
                    w->mLeftChild->mColor = kBlack;
                    w->mColor = kRed;
                    RightRotate(w);
                    w = x->mParent->mRightChild;
                }
                w->mColor = x->mParent->mColor;
                x->mParent->mColor = kBlack;
                w->mRightChild->mColor = kBlack;
                LeftRotate(x->mParent);
                x = mRoot;
            }
        } else {
            w = x->mParent->mLeftChild;
            if (w->mColor == kRed) {
                w->mColor = kBlack;
                x->mParent->mColor = kRed;
                RightRotate(x->mParent);
                w = x->mParent->mLeftChild;
            }

            if (w->mRightChild->mColor == kBlack && w->mLeftChild->mColor == kBlack) {
                w->mColor == kRed;
                x = x->mParent;
            } else {
                if (w->mLeftChild->mColor == kBlack) {
                    w->mRightChild->mColor = kBlack;
                    w->mColor = kRed;
                    LeftRotate(w);
                    w = x->mParent->mLeftChild;
                }
                w->mColor = x->mParent->mColor;
                x->mParent->mColor = kBlack;
                w->mLeftChild->mColor = kBlack;
                RightRotate(x->mParent);
                x = mRoot;
            }
        }
    }
    x->mColor = kBlack;
}

//searching should before deleting
void RBTree::RBDelete(RBTreeNode *z) {
    if (z == mNilNode) {
        std::cout << " z is nil node, can't delete " << std::endl;
        return;
    }

    RBTreeNode *x;
    RBTreeNode *y = z;
    Color yOriginalColor = y->mColor;

    if (z->mLeftChild == mNilNode) {
        x = z->mRightChild;
        RBTransplant(z, z->mRightChild);
    } else if (z->mRightChild == mNilNode) {
        x = z->mLeftChild;
        RBTransplant(z, z->mLeftChild);
    } else {
        y = RBTreeMinimum(z->mRightChild);
        yOriginalColor = y->mColor;
        x = y->mRightChild;

        if (y->mParent == z) {
            x->mParent = y;
        } else {
            RBTransplant(y, y->mRightChild);
            y->mRightChild = z->mRightChild;
            y->mRightChild->mParent = y;
        }

        RBTransplant(z, y);
        y->mLeftChild = z->mLeftChild;
        y->mLeftChild->mParent = y;
        y->mColor = z->mColor;
    }

    if (yOriginalColor == kBlack) {
        RBDeleteFixUp(x);
    }
}


void RBTree::InOrderTreeWalk() const {
    InOrderTreeWalk(mRoot);
}

void RBTree::InOrderTreeWalk(RBTreeNode *node) const {
    if (node != mNilNode) {
        InOrderTreeWalk(node->mLeftChild);
        std::cout << " key: " << node->mKey
            << " color " << node->mColor;
        InOrderTreeWalk(node->mRightChild);
    }
    std::cout << std::endl;
}

void RBTree::PreOrderTreeWalk() const {
    PreOrderTreeWalk(mRoot);
}

void RBTree::PreOrderTreeWalk(RBTreeNode *node) const {
    if (node != mNilNode) {
        std::cout << " key: " << node->mKey
            << " color " << node->mColor;
        InOrderTreeWalk(node->mLeftChild);
        InOrderTreeWalk(node->mRightChild);
    }
    std::cout << std::endl;
}

void RBTree::PostOrderTreeWalk() const {
    PostOrderTreeWalk(mRoot);
}

void RBTree::PostOrderTreeWalk(RBTreeNode *node) const {
    if (node != mNilNode) {
        InOrderTreeWalk(node->mLeftChild);
        InOrderTreeWalk(node->mRightChild);
        std::cout << " key: " << node->mKey
            << " color " << node->mColor;
    }
    std::cout << std::endl;
}

void RBTree::ClearRBTree(RBTreeNode *node) {
    if (node != mNilNode) {
        ClearRBTree(node->mLeftChild);
        ClearRBTree(node->mRightChild);
        delete node;
    }
}

RBTreeNode *RBTree::IterativeRBTreeSearch(int key) const {
    RBTreeNode *p = IterativeRBTreeSearch(mRoot, key);

    if (p != mNilNode) {
        std::cout << " find key " << p->mKey << std::endl;
    } else {
        std::cout << " not find key " << p->mKey << std::endl;
    }

    return p;
}

RBTreeNode *RBTree::IterativeRBTreeSearch(RBTreeNode *node, int key) const {
    while (node != mNilNode && key != node->mKey) {
        if (key < node->mKey) {
            node = node->mLeftChild;
        } else {
            node = node->mRightChild;
        }
    }
    return node;
}

RBTreeNode *RBTree::RBTreeSearch(int key) const {
    RBTreeNode *p = RBTreeSearch(mRoot, key);

    if (p != mNilNode) {
        std::cout << " find key " << p->mKey << std::endl;
    } else {
        std::cout << " no find key " << key << std::endl;
    }

    return p;
}

RBTreeNode *RBTree::RBTreeSearch(RBTreeNode *node, int key) const {
    if (node == mNilNode || key == node->mKey) {
        return node;
    }

    if (key < node->mKey) {
        return RBTreeSearch(node->mLeftChild, key);
    } else {
        return RBTreeSearch(node->mRightChild, key);
    }
}

RBTreeNode *RBTree::RBTreeMaximum() const {
    RBTreeNode *p = RBTreeMaximum(mRoot);

    std::cout << " tree maximum: " << p->mKey << std::endl;
    return p;
}

RBTreeNode *RBTree::RBTreeMaximum(RBTreeNode *node) const {
    while (node != mNilNode && node->mRightChild != mNilNode) {
        node = node->mRightChild;
    }

    return node;
}

RBTreeNode *RBTree::RBTreeMinimum() const {
    RBTreeNode *p = RBTreeMinimum(mRoot);
    std::cout << " tree minimum: " << p->mKey << std::endl;
    return p;
}

RBTreeNode *RBTree::RBTreeMinimum(RBTreeNode *node) const {
    while (node != mNilNode && node->mLeftChild != mNilNode) {
        node = node->mLeftChild;
    }

    return node;
}

RBTreeNode *RBTree::RBTreeInOrderPredecessor(RBTreeNode *node) const {
    if (node->mLeftChild != mNilNode) {
        return RBTreeMaximum(node);
    }

    RBTreeNode *predecessorNode = node->mParent;

    while (predecessorNode != mNilNode && node == predecessorNode->mLeftChild) {
        node = predecessorNode;
        predecessorNode = predecessorNode->mParent;
    }

    return predecessorNode;
}

RBTreeNode *RBTree::RBTreeInOrderSuccessor(RBTreeNode *node) const {
    if (node->mRightChild != mNilNode) {
        return RBTreeMinimum(node);
    }

    RBTreeNode *successorNode = node->mParent;

    while (successorNode != mNilNode && node == successorNode->mRightChild) {
        node = successorNode;
        successorNode = successorNode->mParent;
    }

    return successorNode;
}

void RBTree::RBTreeBFSTraverse() {
    RBTreeBFSTraverse(mRoot);
}

void RBTree::RBTreeBFSTraverse(RBTreeNode *node) {
    std::vector<RBTreeNode *> vec;
    vec.push_back(node);
    int cur = 0;
    int last = 1;
    while (cur < vec.size()) {
        last = vec.size(); // 新的一行访问开始，重新定位last于当前行最后一个节点的下一个位置
        while (cur < last) {
            std::cout << " key " << vec[cur]->mKey << " "
                << " color " << vec[cur]->mColor; // 访问节点
            if (vec[cur]->mLeftChild != mNilNode) // 当前访问节点的左节点不为空则压入
                vec.push_back(vec[cur]->mLeftChild);
            if (vec[cur]->mRightChild != mNilNode) // 当前访问节点的右节点不为空则压入，注意左右节点的访问顺序不能颠倒
                vec.push_back(vec[cur]->mRightChild);
            cur++;
        }
        std::cout << std::endl; // 当cur == last时,说明该层访问结束，输出换行符
    }
}
