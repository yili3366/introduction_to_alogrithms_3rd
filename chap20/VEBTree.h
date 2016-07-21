//
// Created by yijun on 7/16/16.
//

#ifndef CHAP20_VEBTREE_H
#define CHAP20_VEBTREE_H

#include <vector>
#include <cmath>
#include <limits>

template<typename KeyType>
struct VEBTreeNode {
    VEBTreeNode(int u);
    KeyType mMin;
    KeyType mMax;
    int mU;
    std::vector<VEBTreeNode<KeyType> *> mCluster;
    VEBTreeNode<KeyType> *mSummary;

//    VEBTreeNode<KeyType> *operator new(size_t size, size_t numPointers);
//    void operator delete(void *memory, size_t numBits);
};

template<typename KeyType>
class VEBTree {
public:
    VEBTree(int u);
    ~VEBTree();

    bool VEBTreeMember(VEBTreeNode<KeyType> *V, KeyType x);
    KeyType VEBTreeMinimum(VEBTreeNode<KeyType> *V);
    KeyType VEBTreeMaximum(VEBTreeNode<KeyType> *V);
    KeyType VEBTreeSuccessor(VEBTreeNode<KeyType> *V, KeyType x);
    KeyType VEBTreePredecessor(VEBTreeNode<KeyType> *V, KeyType x);
    void VEBEmptyTreeInsert(VEBTreeNode<KeyType> *V, KeyType x);
    void VEBTreeInsert(VEBTreeNode<KeyType> *V, KeyType x);
    void VEBTreeDelete(VEBTreeNode<KeyType> *V, KeyType x);
    VEBTreeNode<KeyType> *VEBCreateTree(int mU);
    VEBTreeNode<KeyType> *GetRoot();

private:
    VEBTreeNode<KeyType> *mRoot;
    KeyType High(VEBTreeNode<KeyType> *node, KeyType x);
    KeyType Low(VEBTreeNode<KeyType> *node, KeyType x);
    KeyType Index(VEBTreeNode<KeyType> *node, KeyType x, KeyType y);
    int mU;
};

template<typename KeyType>
VEBTreeNode<KeyType>::VEBTreeNode(int u) : mU(u) {
    mMin = std::numeric_limits<KeyType>::min();
    mMax = std::numeric_limits<KeyType>::min();
    mCluster.resize(std::floor(std::sqrt(mU)));
    mSummary = nullptr;
}

#if 0
template<typename KeyType>
void *VEBTreeNode<KeyType>::operator new(size_t size, size_t numPointers) {
    return ::operator new(size + sizeof(VEBTreeNode<KeyType> *) * (numPointers - 1));
}

template<typename KeyType>
void VEBTreeNode<KeyType>::operator delete(void *memory, size_t numPointers) {
    ::operator delete(memory);
}
#endif

template<typename KeyType>
KeyType VEBTree<KeyType>::VEBTreeMaximum(VEBTreeNode<KeyType> *V) {
    return V->mMax;
}

template<typename KeyType>
KeyType VEBTree<KeyType>::VEBTreeMinimum(VEBTreeNode<KeyType> *V) {
    return V->mMin;
}

template<typename KeyType>
bool VEBTree<KeyType>::VEBTreeMember(VEBTreeNode<KeyType> *V, KeyType x) {
    if (x == V->mMin || x == V->mMax) {
        return true;
    } else if (V->mU == 2) {
        return false;
    } else {
        return VEBTreeMember(V->mCluster[High(V, x)], Low(V, x));
    }
}

template<typename KeyType>
KeyType VEBTree<KeyType>::High(VEBTreeNode<KeyType> *node, KeyType x) {
    return std::floor(x / static_cast<KeyType>(std::floor(std::sqrt(node->mU))));
}

template<typename KeyType>
KeyType VEBTree<KeyType>::Low(VEBTreeNode<KeyType> *node, KeyType x) {
    return x % static_cast<KeyType>(std::floor(std::sqrt(node->mU)));
}

template<typename KeyType>
KeyType VEBTree<KeyType>::Index(VEBTreeNode<KeyType> *node, KeyType x, KeyType y) {
    return x * static_cast<KeyType>(std::floor(std::sqrt(node->mU))) + y;
}

template<typename KeyType>
KeyType VEBTree<KeyType>::VEBTreeSuccessor(VEBTreeNode<KeyType> *V, KeyType x) {
    if (V->mU == 2) {
        if (x == 0 && V->mMax == 1) {
            return 1;
        } else {
            return std::numeric_limits<KeyType>::min();
        }
    } else if (V->mMin != std::numeric_limits<KeyType>::min() && x < V->mMin) {
        return V->mMin;
    } else {
        KeyType maxLow = VEBTreeMaximum(V->mCluster[High(V, x)]);
        if (maxLow != std::numeric_limits<KeyType>::min() && Low(V, x) < maxLow) {
            KeyType offset = VEBTreeSuccessor(V->mCluster[High(V, x)], Low(V, x));
            return Index(V, High(V, x), offset);
        } else {
            KeyType succCluster = VEBTreeSuccessor(V->mSummary, High(V, x));
            if (succCluster == std::numeric_limits<KeyType>::min()) {
                return std::numeric_limits<KeyType>::min();
            } else {
                KeyType offset = VEBTreeMinimum(V->mCluster[succCluster]);
                return Index(V, succCluster, offset);
            }
        }
    }
}

template<typename KeyType>
KeyType VEBTree<KeyType>::VEBTreePredecessor(VEBTreeNode<KeyType> *V, KeyType x) {
    if (V->mU == 2) {
        if (x == 1 && V->mMax == 0) {
            return 0;
        } else {
            return std::numeric_limits<KeyType>::min();
        }
    } else if (V->mMax != std::numeric_limits<KeyType>::min() && x > V->mMax) {
        return V->mMax;
    } else {
        KeyType minLow = VEBTreeMinimum(V->mCluster[High(V, x)]);
        if (minLow != std::numeric_limits<KeyType>::min() && Low(V, x) > minLow) {
            KeyType offset = VEBTreePredecessor(V->mCluster[High(V, x)], Low(V, x));
            return Index(V, High(V, x), offset);
        } else {
            KeyType predCluster = VEBTreePredecessor(V->mSummary, High(V, x));
            if (predCluster == std::numeric_limits<KeyType>::min()) {
                if (V->mMin != std::numeric_limits<KeyType>::min() && x > V->mMin) {
                    return V->mMin;
                } else {
                    return V->mMin;
                }
            } else {
                KeyType offset = VEBTreeMaximum(V->mCluster[predCluster]);
                return Index(V, predCluster, offset);
            }
        }
    }
}

template<typename KeyType>
void VEBTree<KeyType>::VEBEmptyTreeInsert(VEBTreeNode<KeyType> *V, KeyType x) {
    V->mMin = x;
    V->mMax = x;
}

template<typename KeyType>
void VEBTree<KeyType>::VEBTreeInsert(VEBTreeNode<KeyType> *V, KeyType x) {
    if (V->mMin == std::numeric_limits<KeyType>::min()) {
        VEBEmptyTreeInsert(V, x);
    } else {
        if (x < V->mMin) {
            std::swap(x, V->mMin);
        }
        if (V->mU > 2) {
            if (VEBTreeMinimum(V->mCluster[High(V, x)]) == std::numeric_limits<KeyType>::min()) {
                VEBTreeInsert(V->mSummary, High(V, x));
                VEBEmptyTreeInsert(V->mCluster[High(V, x)], Low(V, x));
            } else {
                VEBTreeInsert(V->mCluster[High(V, x)], Low(V, x));
            }
        }

        if (x > V->mMax) {
            V->mMax = x;
        }
    }
}

template<typename KeyType>
void VEBTree<KeyType>::VEBTreeDelete(VEBTreeNode<KeyType> *V, KeyType x) {
    if (V->mMin == V->mMax) {
        V->mMax = std::numeric_limits<KeyType>::min();
        V->mMin = std::numeric_limits<KeyType>::min();
    } else if (V->mU == 2) {
        if (x == 0) {
            V->mMin = 1;
        } else {
            V->mMin = 0;
            V->mMax = V->mMin;
        }
    } else {
        if (x == V->mMin) {
            KeyType firstCluster = VEBTreeMinimum(V->mSummary);
            x = Index(V, firstCluster, VEBTreeMinimum(V->mCluster[firstCluster]));
            V->mMin = x;
        }

        VEBTreeDelete(V->mCluster[High(V, x)], Low(V, x));

        if (VEBTreeMinimum(V->mCluster[High(V, x)]) == std::numeric_limits<KeyType>::min()) {
            VEBTreeDelete(V->mSummary, High(V, x));
            if (x == V->mMax) {
                KeyType summaryMax = VEBTreeMaximum(V->mSummary);
                if (summaryMax == std::numeric_limits<KeyType>::min()) {
                    V->mMax = V->mMin;
                } else {
                    V->mMax = Index(V, summaryMax, VEBTreeMaximum(V->mCluster[summaryMax]));
                }
            }
        } else if (x == V->mMax) {
            V->mMax = Index(V, High(V, x), VEBTreeMaximum(V->mCluster[High(V, x)]));
        }
    }
}

template<typename KeyType>
VEBTree<KeyType>::VEBTree(int u) : mU(u) {
    mRoot = VEBCreateTree(mU);
}

template<typename KeyType>
VEBTreeNode<KeyType> *VEBTree<KeyType>::VEBCreateTree(int mU) {
//    if (numBits <= 2) {
//        return new long(0);
//    }

//    const size_t numPointers = 1 << (numBits / 2);
//    VEBTreeNode<KeyType> *result = new(numPointers) VEBTreeNode;

    if (mU <= 2) {
        return new VEBTreeNode<int>(mU);
    }

    VEBTreeNode<KeyType> *result = new VEBTreeNode<int>(mU);

//    result->mMin = std::numeric_limits<KeyType>::max();
//    result->mMax = std::numeric_limits<KeyType>::max();
//    result->mCluster.resize(std::ceil(std::sqrt(mU)));
    result->mSummary = VEBCreateTree(std::ceil(std::sqrt(mU)));

    for (size_t i = 0; i < std::ceil(std::sqrt(mU)); i++) {
        result->mCluster[i] = VEBCreateTree(std::floor(std::sqrt(mU)));
    }

    return result;
}

template<typename KeyType>
VEBTreeNode<KeyType> *VEBTree<KeyType>::GetRoot() {
    return mRoot;
}


#endif //CHAP20_VEBTREE_H
