//
// Created by yijun on 7/7/16.
//

#ifndef CHAP19_FIBHEAP_H
#define CHAP19_FIBHEAP_H

#include <functional>
#include <cmath>
#include <vector>
#include <iostream>
#include <limits>

//template<typename KeyType = int>
template<typename KeyType>
struct FibHeapNode {
    KeyType mKey;

    int mDegree;
    bool mMark;

    FibHeapNode<KeyType> *mParent;
    FibHeapNode<KeyType> *mChild;
    FibHeapNode<KeyType> *mLeftSibling;
    FibHeapNode<KeyType> *mRightSibling;
    FibHeapNode(KeyType key);
    bool operator<(FibHeapNode<KeyType> &right);
    bool operator>(FibHeapNode<KeyType> &right);
    bool operator==(FibHeapNode<KeyType> &right);
};

template<typename KeyType>
FibHeapNode<KeyType>::FibHeapNode(KeyType key) {
    mKey = key;
    mParent = nullptr;
    mChild = nullptr;
    mLeftSibling = nullptr;
    mRightSibling = nullptr;
    mDegree = 0;
    mMark = false;
}

template<typename KeyType>
bool FibHeapNode<KeyType>::operator<(FibHeapNode<KeyType> &right) {
    return this->mKey < right.mKey;
}

template<typename KeyType>
bool FibHeapNode<KeyType>::operator>(FibHeapNode<KeyType> &right) {
    return this->mKey > right.mKey;
}

template<typename KeyType>
bool FibHeapNode<KeyType>::operator==(FibHeapNode<KeyType> &right) {
    return this->mKey == right.mKey;
}

//template<typename KeyType = int>
template<typename KeyType>
class FibHeap {
public:
    FibHeap();
    ~FibHeap();

    void FibHeapInsert(FibHeap<KeyType> *fibHeap, FibHeapNode<KeyType> *x);
    FibHeap<KeyType> *FibHeapUnion(FibHeap<KeyType> *H1, FibHeap<KeyType> *H2);
    FibHeapNode<KeyType> *FibHeapExtractMin(FibHeap<KeyType> *H);
    void FibHeapDecreaseKey(FibHeap<KeyType> *H, FibHeapNode<KeyType> *x, KeyType key);
    void FibHeapDelete(FibHeap<KeyType> *H, FibHeapNode<KeyType> *x);
    FibHeap<KeyType> *MakeFibHeap();
    FibHeapNode<KeyType> *FibNodeSearch(FibHeapNode<KeyType> *x, KeyType key);
    FibHeapNode<KeyType> *FibHeapSearch(FibHeap<KeyType> *fibheap, KeyType key);
    void FibheapPrint(FibHeap<KeyType> *fibheap);
    void FibNodePrint(FibHeapNode<KeyType> *x);


private:
    void DestroyFibHeap(FibHeapNode<KeyType> *node);
    void FibHeapLink(FibHeap<KeyType> *H, FibHeapNode<KeyType> *y, FibHeapNode<KeyType> *x);
    void Consolidate(FibHeap<KeyType> *fibheap);
    void Cut(FibHeap<KeyType> *H, FibHeapNode<KeyType> *x, FibHeapNode<KeyType> *y);
    void CascadingCut(FibHeap<KeyType> *H, FibHeapNode<KeyType> *y);
    void FibAddNode(FibHeapNode<KeyType> *node1, FibHeapNode<KeyType> *node2);
    FibHeapNode<KeyType> *FibRemoveHeadFromRootList(FibHeap<KeyType> *fibheap);
    FibHeapNode<KeyType> *FibRemoveNode(FibHeapNode<KeyType> *node);

    std::less<KeyType> Less;
    std::equal_to<KeyType> EqualTo;
    std::greater<KeyType> Greater;
    int mNumber;
    FibHeapNode<KeyType> *mMin;
};

template<typename KeyType>
FibHeap<KeyType>::FibHeap() : mMin(nullptr), mNumber(0) {
}

template<typename KeyType>
FibHeap<KeyType>::~FibHeap() {
    DestroyFibHeap(mMin);
}

template<typename KeyType>
void FibHeap<KeyType>::FibHeapInsert(FibHeap<KeyType> *fibHeap, FibHeapNode<KeyType> *x) {
    x->mDegree = 0;
    x->mParent = nullptr;
    x->mChild = nullptr;
    x->mMark = false;

    if (fibHeap->mMin == nullptr) {
        x->mLeftSibling = x;
        x->mRightSibling = x;
        fibHeap->mMin = x;
    } else {
        FibAddNode(fibHeap->mMin, x);
        if (x->mKey < fibHeap->mMin->mKey) {
            fibHeap->mMin = x;
        }
    }

    fibHeap->mNumber = fibHeap->mNumber + 1;
}

template<typename KeyType>
void FibHeap<KeyType>::FibAddNode(FibHeapNode<KeyType> *node1, FibHeapNode<KeyType> *node2) {

//    if (node1 == nullptr && node2 != nullptr) {
//        node2->mRightSibling = node2;
//        node2->mLeftSibling = node2;
//        node1 = node2;
//        return;
//    }

//    if (node1 != nullptr && node2 != nullptr) {
    node1->mRightSibling->mLeftSibling = node2;
    node2->mRightSibling = node1->mRightSibling;
    node1->mRightSibling = node2;
    node2->mLeftSibling = node1;
//        return;
//    }

//    if (node2 == nullptr) {
//        return;
//    }
}

template<typename KeyType>
FibHeapNode<KeyType> *FibHeap<KeyType>::FibRemoveNode(FibHeapNode<KeyType> *node) {
//    if (node->mRightSibling = node) {
//        node->mLeftSibling = nullptr;
//        node->mRightSibling = nullptr;
//    } else {
    node->mLeftSibling->mRightSibling = node->mRightSibling;
    node->mRightSibling->mLeftSibling = node->mLeftSibling;
//    }

    return node;
}

template<typename KeyType>
void FibHeap<KeyType>::FibHeapLink(FibHeap<KeyType> *H,
                                   FibHeapNode<KeyType> *y,
                                   FibHeapNode<KeyType> *x) {

    FibRemoveNode(y);

    if (x->mChild == nullptr) {
        y->mLeftSibling = y;
        y->mRightSibling = y;
        x->mChild = y;
    } else {
        FibAddNode(x->mChild, y);
    }

    y->mParent = x;
    x->mDegree = x->mDegree + 1;
    y->mMark = false;
}

template<typename KeyType>
FibHeap<KeyType> *FibHeap<KeyType>::FibHeapUnion(FibHeap<KeyType> *H1,
                                                 FibHeap<KeyType> *H2) {
    FibHeapNode<KeyType> *Node;
    FibHeap<KeyType> *H = MakeFibHeap();
    H->mMin = H1->mMin;

//    if (H1->mMin == nullptr || (H2->mMin != nullptr && H2->mMin->mKey < H1->mMin->mKey)) {
//        H->mMin = H2->mMin;
//    }
    if (H1->mMin->mKey > H2->mMin->mKey) {
        H->mMin = H2->mMin;
        while (H1->mMin != nullptr) {
            Node = H1->FibRemoveHeadFromRootList(H1);
            FibAddNode(H->mMin, Node);
        }
    } else {
        H->mMin = H1->mMin;
        while (H2->mMin != nullptr) {
            Node = H2->FibRemoveHeadFromRootList(H2);
            FibAddNode(H->mMin, Node);
        }
    }

    H->mNumber = H1->mNumber + H2->mNumber;

    return H;
}

template<typename KeyType>
FibHeap<KeyType> *FibHeap<KeyType>::MakeFibHeap() {
    FibHeap<KeyType> *fibHeap = new FibHeap();
    fibHeap->mNumber = 0;
    fibHeap->mMin = nullptr;
    return fibHeap;
}

template<typename KeyType>
FibHeapNode<KeyType> *FibHeap<KeyType>::FibHeapExtractMin(FibHeap<KeyType> *H) {
    FibHeapNode<KeyType> *z = H->mMin;
    FibHeapNode<KeyType> *x = nullptr;

    if (z != nullptr) {

#if 1
        while (z->mChild != nullptr) {
            x = z->mChild;
            FibRemoveNode(x);
            if (x->mRightSibling == x) {
                z->mChild = nullptr;
            } else {
                z->mChild = x->mRightSibling;
            }
            FibAddNode(H->mMin, x);
            x->mParent = nullptr;
        }
#endif

        FibRemoveNode(z);
        if (z == z->mRightSibling) {
            H->mMin = nullptr;
        } else {
            H->mMin = z->mRightSibling;
            Consolidate(H);
        }

        H->mNumber = H->mNumber - 1;
    }

    return z;
}

template<typename KeyType>
void FibHeap<KeyType>::Consolidate(FibHeap<KeyType> *H) {
    int maxDegree = static_cast<int> (log(H->mNumber * 1.0) / log(2)) + 1;
    std::vector<FibHeapNode<KeyType> *> A(maxDegree + 1);
    typename std::vector<FibHeapNode<KeyType> *>::iterator iter;

    FibHeapNode<KeyType> *x = H->mMin;
    FibHeapNode<KeyType> *y;

    for (iter = A.begin(); iter != A.end(); iter++) {
        *iter = nullptr;
    }

#if 0
    FibHeapNode<KeyType> *j = H->mMin;
    do {
        std::cout << " j is " << j->mKey << std::endl;
        j = j->mRightSibling;
    } while (j != H->mMin);
#endif

    while (H->mMin != nullptr) {
        x = FibRemoveHeadFromRootList(H);

        int d = x->mDegree;

        while (A[d] != nullptr) {
            y = A[d];
            if (x->mKey > y->mKey) {
                std::swap(x, y);
            }

            FibHeapLink(H, y, x);

            A[d] = nullptr;
            d = d + 1;
        }
        A[d] = x;
    }

    H->mMin = nullptr;

    for (int i = 0; i <= maxDegree; i++) {
        if (A[i] != nullptr) {

            if (H->mMin == nullptr) {
                H->mMin = A[i];
                H->mMin->mLeftSibling = H->mMin;
                H->mMin->mRightSibling = H->mMin;
            } else {
                FibAddNode(H->mMin, A[i]);
                if (A[i]->mKey < H->mMin->mKey) {
                    H->mMin = A[i];
                }
            }
        }
    }
}

template<typename KeyType>
void FibHeap<KeyType>::FibHeapDecreaseKey(FibHeap<KeyType> *H,
                                          FibHeapNode<KeyType> *x,
                                          KeyType key) {
    FibHeapNode<KeyType> *y;
    if (key > x->mKey) {
        std::cerr << "new key is greater than current key" << std::endl;
        return;
    }

    x->mKey = key;
    y = x->mParent;

    if (y != nullptr && x->mKey < y->mKey) {
        Cut(H, x, y);
        CascadingCut(H, y);
    }

    if (x->mKey < H->mMin->mKey) {
        H->mMin = x;
    }
}

template<typename KeyType>
void FibHeap<KeyType>::Cut(FibHeap<KeyType> *H, FibHeapNode<KeyType> *x, FibHeapNode<KeyType> *y) {

    FibRemoveNode(x);
    if (x == x->mRightSibling) {
        y->mChild = nullptr;
    } else {
        y->mChild = x->mRightSibling;
    }

    y->mDegree = y->mDegree - 1;

    FibAddNode(H->mMin, x);
    x->mParent = nullptr;
    x->mMark = false;
}

template<typename KeyType>
void FibHeap<KeyType>::CascadingCut(FibHeap<KeyType> *H, FibHeapNode<KeyType> *y) {
    FibHeapNode<KeyType> *z = y->mParent;

    if (z != nullptr) {
        if (y->mMark == false) {
            y->mMark = true;
        } else {
            Cut(H, y, z);
            CascadingCut(H, z);
        }
    }
}

template<typename KeyType>
void FibHeap<KeyType>::FibHeapDelete(FibHeap<KeyType> *H, FibHeapNode<KeyType> *x) {
    FibHeapDecreaseKey(H, x, std::numeric_limits<KeyType>::min());
    FibHeapExtractMin(H);
}

template<typename KeyType>
void FibHeap<KeyType>::DestroyFibHeap(FibHeapNode<KeyType> *node) {
    if (node == nullptr) {
        return;
    }

    FibHeapNode<KeyType> *first = node->mRightSibling;
    FibHeapNode<KeyType> *current;
    do {
        current = first;
        first = first->mRightSibling;
        DestroyFibHeap(current->mChild);
        mNumber--;
        delete (current);
    } while (current != node);
}

template<typename KeyType>
FibHeapNode<KeyType> *FibHeap<KeyType>::FibNodeSearch(FibHeapNode<KeyType> *x, KeyType key) {
    FibHeapNode<KeyType> *w;
    FibHeapNode<KeyType> *y;

    w = x;
    y = nullptr;

    if (x != nullptr) {
        do {
            if (EqualTo(w->mKey, key)) {
                y = w;
                break;
            } else if ((y = FibNodeSearch(w->mChild, key)) != nullptr) {
                break;
            }
            w = w->mRightSibling;
        } while (w != x);
    }
    return y;
}

template<typename KeyType>
FibHeapNode<KeyType> *FibHeap<KeyType>::FibHeapSearch(FibHeap<KeyType> *fibheap, KeyType key) {
    return FibNodeSearch(fibheap->mMin, key);
}

template<typename KeyType>
void FibHeap<KeyType>::FibNodePrint(FibHeapNode<KeyType> *x) {
    FibHeapNode<KeyType> *p = nullptr;
    if (x == nullptr) {
        return;
    }

    p = x;
    do {
        printf("(");
        printf("key %d degree %d", p->mKey, p->mDegree);
        if (p->mChild != nullptr) {
            FibNodePrint(p->mChild);
        }
        printf(")");
        p = p->mLeftSibling;
    } while (x != p);
}

template<typename KeyType>
void FibHeap<KeyType>::FibheapPrint(FibHeap<KeyType> *fibheap) {
    printf("The KeyNum = %d\n", fibheap->mNumber);
    FibNodePrint(fibheap->mMin);
    printf("\n");
}

template<typename KeyType>
FibHeapNode<KeyType> *FibHeap<KeyType>::FibRemoveHeadFromRootList(FibHeap<KeyType> *fibheap) {
    FibHeapNode<KeyType> *min = fibheap->mMin;
    if (fibheap->mMin == min->mRightSibling) {
        fibheap->mMin = nullptr;
    } else {
        FibRemoveNode(min);
        fibheap->mMin = min->mRightSibling;
    }
    min->mLeftSibling = min;
    min->mRightSibling = min;

    return min;
}

#endif //CHAP19_FIBHEAP_H
