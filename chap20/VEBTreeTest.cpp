//
// Created by yijun on 7/19/16.
//

#include <gtest/gtest.h>
#include "VEBTree.h"

TEST(VEBTreeTest, VEBTreeNode) {
    VEBTree<int> *vebTree = new VEBTree<int>(16);
    int arrary[] = {2, 3, 4, 5, 7, 14, 15};
    std::vector<int> vec(arrary, arrary + sizeof(arrary) / sizeof(int));
    std::vector<int>::iterator iter;
    ASSERT_TRUE(vebTree != nullptr);

    for (iter = vec.begin(); iter != vec.end(); iter++) {
        vebTree->VEBTreeInsert(vebTree->GetRoot(), *iter);
    }

//    vebTree->VEBEmptyTreeInsert();
    int min = vebTree->VEBTreeMinimum(vebTree->GetRoot());
    std::cout << "min is " << min << std::endl;

    int max = vebTree->VEBTreeMaximum(vebTree->GetRoot());
    std::cout << "max is " << max << std::endl;

    if (vebTree->VEBTreeMember(vebTree->GetRoot(), 6)) {
        std::cout << "6 is member" << std::endl;
    } else {
        std::cout << "6 is not member" << std::endl;
    }

    vebTree->VEBTreeDelete(vebTree->GetRoot(), 3);
    if (vebTree->VEBTreeMember(vebTree->GetRoot(), 3)) {
        std::cout << "3 is member" << std::endl;
    } else {
        std::cout << " 3 is not member " << std::endl;
    }


    if (vebTree->VEBTreeMember(vebTree->GetRoot(), 8)) {
        std::cout << "8 is member" << std::endl;
    } else {
        std::cout << "8 is not member" << std::endl;
    }

    vebTree->VEBTreeInsert(vebTree->GetRoot(), 8);

    if (vebTree->VEBTreeMember(vebTree->GetRoot(), 8)) {
        std::cout << "8 is member" << std::endl;
    } else {
        std::cout << "8 is not member" << std::endl;
    }
}