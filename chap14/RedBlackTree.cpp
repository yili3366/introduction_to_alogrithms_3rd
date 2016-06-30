//
// Created by yijun on 6/22/16.
//

#include "RedBlackTree.h"

Interval::Interval(int low, int high) : mLow(low), mHigh(high) {
}

RBTreeNode::RBTreeNode() :
    mInterval(-1, -1), mColor(kBlack), mLeftChild(nullptr), mRightChild(nullptr), mParent(nullptr), mKey(-1) {
}

RBTreeNode::RBTreeNode(Interval interval, Color color,
                       RBTreeNode *parent, RBTreeNode *leftChild, RBTreeNode *rightChild) :
    mInterval(interval), mColor(color), mLeftChild(leftChild),
    mRightChild(rightChild), mParent(parent), mMax(interval.mHigh), mKey(interval.mLow) {
}

RBTree::RBTree(const std::vector<Interval> &A) : mNilNode(new RBTreeNode()) {
    mNilNode->mColor = kBlack;
    mNilNode->mLeftChild = nullptr;
    mNilNode->mRightChild = nullptr;
    mNilNode->mParent = nullptr;
    mNilNode->mMax = -1;
    mNilNode->mInterval.mLow = -1;
    mNilNode->mInterval.mHigh = -1;
    mNilNode->mKey = -1;
    mRoot = mNilNode;

    for (int i = 0; i < A.size(); i++) {
        RBTreeNode *rbTreeNode = new RBTreeNode(A[i]);
        if (rbTreeNode == nullptr) {
            std::runtime_error("allcate error!");
            exit(kAllocateError);
        }
        IntervalInsert(rbTreeNode);
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

//    y->mSize = x->mSize;
//    x->mSize = x->mLeftChild->mSize + x->mRightChild->mSize + 1;

    y->mMax = x->mMax;
    x->mMax = GetMax(x->mLeftChild->mMax, x->mRightChild->mMax, x->mInterval.mHigh);
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

    x->mRightChild = y;
    y->mParent = x;

//    x->mSize = y->mSize;
//    y->mSize = y->mLeftChild->mSize + y->mRightChild->mSize + 1;

    x->mMax = y->mMax;
    y->mMax = GetMax(y->mLeftChild->mMax, y->mRightChild->mMax, y->mInterval.mHigh);
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
                w->mColor = kRed;
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
        } else if (x == x->mParent->mRightChild) {
            w = x->mParent->mLeftChild;
            if (w->mColor == kRed) {
                w->mColor = kBlack;
                x->mParent->mColor = kRed;
                RightRotate(x->mParent);
                w = x->mParent->mLeftChild;
            }

            if (w->mRightChild->mColor == kBlack && w->mLeftChild->mColor == kBlack) {
                w->mColor = kRed;
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

void RBTree::InOrderTreeWalk() const {
    InOrderTreeWalk(mRoot);
}

void RBTree::InOrderTreeWalk(RBTreeNode *node) const {
    if (node != mNilNode) {
        InOrderTreeWalk(node->mLeftChild);
        std::cout << " Low: " << node->mInterval.mLow
            << " Hight: " << node->mInterval.mHigh
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
        std::cout << " low: " << node->mInterval.mLow
            << " high: " << node->mInterval.mHigh
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
        std::cout << " Low: " << node->mInterval.mLow
            << "High :" << node->mInterval.mHigh
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

RBTreeNode *RBTree::RBTreeMaximum() const {
    RBTreeNode *p = RBTreeMaximum(mRoot);

    return p;
}

RBTreeNode *RBTree::RBTreeMaximum(RBTreeNode *node) const {
    while (node->mRightChild != mNilNode) {
        node = node->mRightChild;
    }

    return node;
}

RBTreeNode *RBTree::RBTreeMinimum() const {
    RBTreeNode *p = RBTreeMinimum(mRoot);
    return p;
}

RBTreeNode *RBTree::RBTreeMinimum(RBTreeNode *x) const {
    while (x->mLeftChild != mNilNode) {
        x = x->mLeftChild;
    }

    return x;
}

RBTreeNode *RBTree::RBTreeInOrderPredecessor(RBTreeNode *x) const {
    if (x->mLeftChild != mNilNode) {
        return RBTreeMaximum(x->mLeftChild);
    }

    RBTreeNode *y = x->mParent;

    while (y != mNilNode && x == y->mLeftChild) {
        x = y;
        y = y->mParent;
    }

    return y;
}

RBTreeNode *RBTree::RBTreeInOrderSuccessor(RBTreeNode *x) const {
    if (x->mRightChild != mNilNode) {
        return RBTreeMinimum(x->mRightChild);
    }

    RBTreeNode *y = x->mParent;
    while (y != mNilNode && x == y->mRightChild) {
        x = y;
        y = y->mParent;
    }

    return y;
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
        last = vec.size();
        while (cur < last) {
            std::cout << " (low " << vec[cur]->mInterval.mLow
                << " high " << vec[cur]->mInterval.mHigh
                << " color " << vec[cur]->mColor
                << " max " << vec[cur]->mMax << ") ";

            if (vec[cur]->mLeftChild != mNilNode)
                vec.push_back(vec[cur]->mLeftChild);
            if (vec[cur]->mRightChild != mNilNode)
                vec.push_back(vec[cur]->mRightChild);
            cur++;
        }
        std::cout << std::endl; // 当cur == last时,说明该层访问结束，输出换行符
    }
}

#if 0
RBTreeNode *RBTree::OSSelect(RBTreeNode *x, int i) {
    int r;
    r = x->mLeftChild->mSize + 1;

    if (i == r) {
        return x;
    } else if (i < r) {
        return OSSelect(x->mLeftChild, i);
    } else {
        return OSSelect(x->mRightChild, i - r);
    }
}

int RBTree::OSRank(RBTreeNode *x) {
    int r;
    RBTreeNode *y;

    r = x->mLeftChild->mSize + 1;
    y = x;

    while (y != mRoot) {
        if (y == y->mParent->mRightChild) {
            r = r + y->mParent->mLeftChild->mSize + 1;
        }
        y = y->mParent;
    }

    return r;
}
#endif

RBTreeNode *RBTree::IntervalSearch(Interval *i) {
    RBTreeNode *x;
    x = mRoot;

    while (x != mNilNode && !RBTreeOverlap(i, &(x->mInterval))) {
        if (x->mLeftChild != mNilNode && x->mLeftChild->mMax >= i->mLow) {
            x = x->mLeftChild;
        } else {
            x = x->mRightChild;
        }
    }

    return x;
}

bool RBTree::RBTreeOverlap(Interval *i, Interval *j) {
    return (i->mLow <= j->mHigh && j->mLow <= i->mHigh);
}

bool RBTree::RBTreeLeft(Interval *i, Interval *j) {
    return i->mHigh < j->mLow;
}

bool RBTree::RBTreeRight(Interval *i, Interval *j) {
    return j->mHigh < i->mLow;
}

int RBTree::GetMax(int a, int b, int c) {
    if (a > b) {
        return a > c ? a : c;
    } else {
        return b > c ? b : c;
    }
}

RBTreeNode *RBTree::IntervalInsert(RBTreeNode *z) {
    RBTreeNode *y = mNilNode;
    RBTreeNode *x = mRoot;

    while (x != mNilNode) {
        x->mMax = GetMax(x->mMax, x->mInterval.mHigh, z->mMax);
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

#if 0
void RBTree::IntervalDelete(RBTreeNode *z) {

    RBTreeNode *x;
    RBTreeNode *y;
    RBTreeNode *p;
    if (z->mLeftChild == mNilNode || z->mRightChild == mNilNode) {
        y = z;
        p = y->mParent;
        p->mMax = p->mInterval.mHigh;
        p = p->mParent;
        while (p->mMax == y->mMax) {
            p->mMax = GetMax(p->mMax, p->mLeftChild->mMax, p->mRightChild->mMax);
            p = p->mParent;
        }
    } else {
        y = RBTreeInOrderSuccessor(z);
    }

    p = y->mParent;
    p->mMax = p->mInterval.mHigh;
    p = p->mParent;
    while (p->mMax == y->mMax) {
        p->mMax = GetMax(p->mMax, p->mLeftChild->mMax, p->mRightChild->mMax);
        p = p->mParent;
    }

    if (y->mLeftChild != mNilNode) {
        x = y->mLeftChild;
    } else {
        x = y->mRightChild;
    }

    x->mParent = y->mParent;

    if (y->mParent == mNilNode) {
        mRoot = x;
    } else if (y == y->mParent->mLeftChild) {
        y->mParent->mLeftChild = x;
    } else {
        y->mParent->mRightChild = x;
    }

    if (y != z) {
        z->mInterval = y->mInterval;
        z->mKey = y->mKey;
        z->mMax = y->mMax;
        p = z->mParent;
        while (p->mMax < z->mMax) {
            p->mMax = z->mMax;
            p = p->mParent;
        }
    }

    if (y->mColor == kBlack) {
        RBDeleteFixUp(x);
    }
}
#endif

#if 1
void RBTree::IntervalDelete(RBTreeNode *z) {
    if (z == mNilNode) {
        std::cout << " z is nil node, can't delete " << std::endl;
        return;
    }

    RBTreeNode *x;
    RBTreeNode *y = z;
//    RBTreeNode *fixNode;

//    fixNode = y->mParent;
    Color yOriginalColor = y->mColor;

    if (z->mLeftChild == mNilNode) {
        x = z->mRightChild;
        RBTransplant(z, z->mRightChild);
    } else if (z->mRightChild == mNilNode) {
        x = z->mLeftChild;
        RBTransplant(z, z->mLeftChild);
    } else {
        y = RBTreeMinimum(z->mRightChild);
//        fixNode = y->mParent;
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

//    while (fixNode != mNilNode) {
//        fixNode->mMax = GetMax(fixNode->mLeftChild->mMax, fixNode->mRightChild->mMax, fixNode->mInterval.mHigh);
//        fixNode = fixNode->mParent;
//    }

    while (y != mNilNode) {
        y->mMax = GetMax(y->mLeftChild->mMax, y->mRightChild->mMax, y->mInterval.mHigh);
        y = y->mParent;
    }

    if (yOriginalColor == kBlack) {
        RBDeleteFixUp(x);
    }
}
#endif

RBTreeNode *RBTree::GetNilNode() const {
    return mNilNode;
}
