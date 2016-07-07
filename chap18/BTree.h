//
// Created by yijun on 7/5/16.
//

#ifndef CHAP16_BTREE_H
#define CHAP16_BTREE_H

#include <vector>

struct BTreeNode {
    BTreeNode(int degree = 2);
    ~BTreeNode();
    int mNumberOfKey;
    std::vector<int> mKey;
    bool mLeaf;
    std::vector<BTreeNode *> mChild;
};

class BTree {
public:
    std::pair<BTreeNode *, int>* BTreeSearch(BTreeNode *x, int k);
    BTree(int degree = 2);
    ~BTree();
    void BTreeInsert(int k);
    void BTreeDelete(BTreeNode *x, int k);
    void BTreeDelete(int k);
    void BTreeBFSTraverse(BTreeNode* x, int level = 1);
    void BTreeBFSTraverse();

private:
    void BTreeCreate();
    void BTreeDestroy(BTreeNode* node);
    void BTreeSplitChild(BTreeNode *x, int i);
    void BTreeMergeChild(BTreeNode *x, int i);
    void BTreeInsertNonfull(BTreeNode *x, int k);
//    int FindKey(int k); // find the first key that is greater than or equal to k

    BTreeNode *mRoot;
    int mMinimumDegree;
};

#endif //CHAP16_BTREE_H
