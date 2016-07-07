//
// Created by yijun on 7/7/16.
//

#include <gtest/gtest.h>
#include "BTree.h"

TEST(BTreeTest, BTree) {
    const int degree = 3;
    int array[] = {'P', 'C', 'G', 'M', 'T', 'X', 'A', 'B', 'D', 'E', 'F', 'J', 'K', 'L', 'N', 'O', 'Q', 'R', 'S', 'U', 'V', 'Y', 'Z'};
    std::vector<int> vec(array, array + sizeof(array) / sizeof(int));
    std::vector<int>::iterator iter;

    BTree *bTree = new BTree(degree);
    ASSERT_TRUE(bTree != nullptr);

    int i = 0;
    for (iter = vec.begin(); iter != vec.end(); iter++, i++) {
        bTree->BTreeInsert(*iter);
//        std::cout << " the " << i << " time " << std::endl;
//        bTree->BTreeBFSTraverse();
    }

    bTree->BTreeBFSTraverse();

//    for (iter = vec.begin(); iter != vec.end(); iter++, i++) {
//        bTree->BTreeDelete(*iter);
//    }

    bTree->BTreeDelete('P');
    bTree->BTreeDelete('C');
    bTree->BTreeDelete('G');
    bTree->BTreeDelete('M');
    bTree->BTreeDelete('T');
    bTree->BTreeDelete('X');
    bTree->BTreeDelete('A');
    bTree->BTreeDelete('B');
    bTree->BTreeDelete('D');
    bTree->BTreeDelete('E');
    bTree->BTreeDelete('F');
    bTree->BTreeDelete('J');
    bTree->BTreeDelete('K');
    bTree->BTreeDelete('L');
    bTree->BTreeDelete('N');
    bTree->BTreeDelete('O');
    bTree->BTreeDelete('Q');
    bTree->BTreeDelete('R');
    bTree->BTreeDelete('S');
    bTree->BTreeDelete('U');
    bTree->BTreeDelete('V');
    bTree->BTreeDelete('Y');
    bTree->BTreeDelete('Z');

    bTree->BTreeBFSTraverse();
}
