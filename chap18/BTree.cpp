//
// Created by yijun on 7/5/16.
//


#include <iostream>
#include "BTree.h"

BTreeNode::BTreeNode(int degree) {
    mNumberOfKey = 2 * degree - 1;
    mKey.resize(mNumberOfKey);
    mChild.resize(mNumberOfKey + 1);
    mLeaf = true;
}

BTreeNode::~BTreeNode() {
    mNumberOfKey = 0;
}

BTree::BTree(int degree) : mMinimumDegree(degree), mRoot(nullptr) {
//    BTreeCreate();
}

BTree::~BTree() {
    BTreeDestroy(mRoot);
}
std::pair<BTreeNode *, int> *BTree::BTreeSearch(BTreeNode *x, int k) {
    int i = 0;
    std::pair<BTreeNode *, int> *pair;

    while (i < x->mNumberOfKey && k > x->mKey[i]) {
        i++;
    }

    if (i < x->mNumberOfKey && k == x->mKey[i]) {
        pair->first = x;
        pair->second = x->mKey[i];
        return pair;
    } else if (x->mLeaf) {
        return nullptr;
    } else {
        return BTreeSearch(x->mChild[i], k);
    }
}

void BTree::BTreeSplitChild(BTreeNode *x, int index) {
    BTreeNode *z = new BTreeNode(mMinimumDegree);
    if (z == nullptr) {
        std::cout << "file " << __FILE__ << " line " << __LINE__ << " allocate error " << std::endl;
        return;
    }
    BTreeNode *y = x->mChild[index];

    z->mLeaf = y->mLeaf;
    z->mNumberOfKey = mMinimumDegree - 1;

    for (int j = 0; j < z->mNumberOfKey; j++) {
        z->mKey[j] = y->mKey[j + mMinimumDegree];
        y->mKey[mMinimumDegree + j] = 0;
    }

    if (!y->mLeaf) {
        for (int j = 0; j < mMinimumDegree; j++) {
            z->mChild[j] = y->mChild[j + mMinimumDegree];
            y->mChild[mMinimumDegree + j] = nullptr;
        }
    }

    y->mNumberOfKey = mMinimumDegree - 1;
//    y->mKey.resize(y->mNumberOfKey);
//    y->mChild.resize(y->mNumberOfKey + 1);

    for (int j = x->mNumberOfKey; j > index; j--) {
        x->mChild[j + 1] = x->mChild[j];
    }

    x->mChild[index + 1] = z;

    for (int j = x->mNumberOfKey - 1; j >= index; j--) {
        x->mKey[j + 1] = x->mKey[j];
    }

    x->mKey[index] = y->mKey[mMinimumDegree - 1];
    x->mNumberOfKey = x->mNumberOfKey + 1;
//    x->mKey.resize(x->mNumberOfKey);
//    x->mChild.resize(x->mNumberOfKey + 1);

//    for (int i = mMinimumDegree - 1; i < mMinimumDegree * 2 - 1; i++) {
//        x->mKey[i]  = 0;
//        x->mChild[i + 1] = nullptr;
//    }
}

void BTree::BTreeInsert(int key) {
    BTreeNode *r = mRoot;

    if (mRoot == nullptr) {
        mRoot = new BTreeNode(mMinimumDegree);
        if (mRoot == nullptr) {
            std::cout << " allocate error " << std::endl;
            return;
        }
        mRoot->mLeaf = true;
        mRoot->mNumberOfKey = 0;
//        mRoot->mKey.resize(mRoot->mNumberOfKey);
        mRoot->mKey[0] = key;
        return;
    }

    if (r->mNumberOfKey == 2 * mMinimumDegree - 1) {
        BTreeNode *s = new BTreeNode(mMinimumDegree);
        mRoot = s;
        s->mLeaf = false;
        s->mNumberOfKey = 0;
//        s->mKey.resize(s->mNumberOfKey);
        s->mChild[0] = r;
        BTreeSplitChild(s, 0);
        BTreeInsertNonfull(s, key);
    } else {
        BTreeInsertNonfull(r, key);
    }
}

void BTree::BTreeInsertNonfull(BTreeNode *x, int key) {
    int i = x->mNumberOfKey - 1;
    if (x->mLeaf) {
        while (i >= 0 && key < x->mKey[i]) {
            x->mKey[i + 1] = x->mKey[i];
            i--;
        }
        x->mNumberOfKey = x->mNumberOfKey + 1;
//        x->mKey.resize(x->mNumberOfKey);
        x->mKey[i + 1] = key;
    } else {
        while (i >= 0 && key < x->mKey[i]) {
            i--;
        }

        i++;
        if (x->mChild[i]->mNumberOfKey == 2 * mMinimumDegree - 1) {
            BTreeSplitChild(x, i);
            if (key > x->mKey[i]) {
                i++;
            }
        }
        BTreeInsertNonfull(x->mChild[i], key);
    }
}

void BTree::BTreeDelete(BTreeNode *x, int key) {
    int i;
    int j;
    int index;
    BTreeNode *root = x;
    BTreeNode *prevChild;
    BTreeNode *nextChild;
    BTreeNode *child;
    int prevChildKey;
    int nextChildKey;

    if (!root) {
        std::cout << " key " << key << " not in this tree " << std::endl;
        return;
    }

    index = 0;

    while (index < x->mNumberOfKey && key > x->mKey[index]) {
        index++;
    }

    if (index < x->mNumberOfKey && x->mKey[index] == key) { //key in x
        if (x->mLeaf) { // case 1
            for (i = index; i < x->mNumberOfKey; i++) {
                x->mKey[i] = x->mKey[i + 1];
                x->mChild[i + 1] = x->mChild[i + 2];
            }
            --x->mNumberOfKey;
//            x->mKey.resize(x->mNumberOfKey);
            if (x->mNumberOfKey == 0) {
//                mRoot = x;
//                delete x;
//                x = nullptr;
            }

            return;
        } else if (x->mChild[index]->mNumberOfKey >= mMinimumDegree) { // case 2a
            prevChild = x->mChild[index];
            prevChildKey = prevChild->mKey[prevChild->mNumberOfKey - 1];
            x->mKey[index] = prevChildKey;
            BTreeDelete(prevChild, prevChildKey);
        } else if (x->mChild[index + 1]->mNumberOfKey >= mMinimumDegree) { // case 2b
            nextChild = x->mChild[index + 1];
            nextChildKey = nextChild->mKey[0];
            x->mKey[index] = nextChildKey;
            BTreeDelete(nextChild, nextChildKey);
        } else if (x->mChild[index]->mNumberOfKey == mMinimumDegree - 1
            && x->mChild[index + 1]->mNumberOfKey == mMinimumDegree - 1) { //case 2c
            prevChild = x->mChild[index];
            BTreeMergeChild(x, index);
            BTreeDelete(prevChild, key);
        }
    } else { // key not in x
        child = x->mChild[index];
        if (child == nullptr) {
            std::cout << " key" << key << "is not in this tree " << std::endl;
            return;
        }

        if (child->mNumberOfKey == mMinimumDegree - 1) {
            prevChild = nullptr;
            nextChild = nullptr;

            if (index - 1 >= 0) { //not the leftmost
                prevChild = x->mChild[index - 1];
            }

            if (index + 1 <= x->mNumberOfKey) {
                nextChild = x->mChild[index + 1];
            }

            if ((prevChild && prevChild->mNumberOfKey >= mMinimumDegree)
                || (nextChild && nextChild->mNumberOfKey >= mMinimumDegree)) { // case 3a

                if (nextChild && nextChild->mNumberOfKey >= mMinimumDegree) { //right child
                    child->mKey[child->mNumberOfKey] = x->mKey[index];
                    child->mChild[child->mNumberOfKey + 1] = nextChild->mChild[0];
                    ++child->mNumberOfKey;
//                    child->mKey.resize(child->mNumberOfKey);
                    x->mKey[index] = nextChild->mKey[0];

                    for (j = 0; j < nextChild->mNumberOfKey - 1; j++) {
                        nextChild->mKey[j] = nextChild->mKey[j + 1];
                        nextChild->mChild[j] = nextChild->mChild[j + 1];
                    }
                    --nextChild->mNumberOfKey;
//                    child->mKey.resize(child->mNumberOfKey);
                } else { //left child
                    for (j = child->mNumberOfKey; j > 0; j--) {
                        child->mKey[j] = child->mKey[j - 1];
                        child->mChild[j + 1] = child->mChild[j];
                    }
                    child->mChild[1] = child->mChild[0];
                    child->mChild[0] = prevChild->mChild[prevChild->mNumberOfKey];
                    child->mKey[0] = x->mKey[index - 1];
                    ++child->mNumberOfKey;
//                    child->mKey.resize(child->mNumberOfKey);

                    x->mKey[index - 1] = prevChild->mKey[prevChild->mNumberOfKey - 1];
                    --prevChild->mNumberOfKey;
//                    prevChild->mKey.resize(prevChild->mNumberOfKey);
                }
            } else if ((!prevChild || (prevChild && prevChild->mNumberOfKey == mMinimumDegree - 1))
                && ((!nextChild || (nextChild && nextChild->mNumberOfKey == mMinimumDegree - 1)))) { // case 3b

                if (prevChild && prevChild->mNumberOfKey == mMinimumDegree - 1) {
                    BTreeMergeChild(x, index - 1);
                    child = prevChild;
                } else if (nextChild && nextChild->mNumberOfKey == mMinimumDegree - 1) {
                    BTreeMergeChild(x, index);
                }
            }
        }
        BTreeDelete(child, key);
    }
}

void BTree::BTreeMergeChild(BTreeNode *x, int index) {
    int key = x->mKey[index];

    BTreeNode *prevChild = x->mChild[index];
    BTreeNode *nextChild = x->mChild[index + 1];

    prevChild->mKey[prevChild->mNumberOfKey] = key;
    prevChild->mChild[prevChild->mNumberOfKey + 1] = nextChild->mChild[0];
    ++prevChild->mNumberOfKey;

    //merge
    for (int i = 0; i < nextChild->mNumberOfKey; i++) {
        prevChild->mKey[prevChild->mNumberOfKey] = nextChild->mKey[i];
        prevChild->mChild[prevChild->mNumberOfKey + 1] = nextChild->mChild[i + 1];
        ++prevChild->mNumberOfKey;
    }

    for (int i = index; i < x->mNumberOfKey - 1; i++) {
        x->mKey[i] = x->mKey[i + 1];
        x->mChild[i + 1] = x->mChild[i + 2];
    }

    x->mKey[x->mNumberOfKey - 1] = 0;
    x->mChild[x->mNumberOfKey] = nullptr;
    --x->mNumberOfKey;

    if (x->mNumberOfKey == 0) {
        if (mRoot == x) {
            std::cout << " x is empty " << std::endl;
            mRoot = prevChild;
        }
        delete x;
        x = nullptr;
    }
    delete nextChild;
}

void BTree::BTreeCreate() {
    BTreeNode *x = new BTreeNode(mMinimumDegree);
    if (x == nullptr) {
        std::cout << " Allocate error " << std::endl;
        return;
    }

    x->mLeaf = true;
    x->mNumberOfKey = 1;
    mRoot = x;
}

void BTree::BTreeDestroy(BTreeNode *node) {
    BTreeNode *x = node;

    if (mRoot) {
        for (int i = 0; i <= mRoot->mNumberOfKey; i++) {
            BTreeDestroy(x->mChild[i]);
        }
    }
}

void BTree::BTreeDelete(int k) {
    BTreeDelete(mRoot, k);
}

void BTree::BTreeBFSTraverse(BTreeNode *x, int level) {
    BTreeNode *node = x;

    if (node) {
//        printf("第 %d 层， %d node : ", level, node->mNumberOfKey);
        std::cout << "level " << level << " " << node->mNumberOfKey << " nodes ";

        for (int i = 0; i < node->mNumberOfKey; ++i) {
//            std::cout << " " << node->mKey[i];
            printf("%c ", node->mKey[i]);
        }

//        printf("\n");
        std::cout << std::endl;

        ++level;
        for (int i = 0; i <= node->mNumberOfKey; i++) {
            if (node->mChild[i]) {
                BTreeBFSTraverse(node->mChild[i], level);
            }
        }
    } else {
//        printf("树为空。\n");
        std::cout << "tree is empty" << std::endl;
    }
}

void BTree::BTreeBFSTraverse() {
    BTreeBFSTraverse(mRoot);
}
