//
// Created by yijun on 7/25/16.
//

#include <gtest/gtest.h>
#include "Graph.h"

TEST(GraphTest, Graph) {

    Vertex<int> node0{0};
    Vertex<int> node1{1};
    Vertex<int> node2{2};
    Vertex<int> node3{3};
    Vertex<int> node4{4};
    Vertex<int> node5{5};
    Vertex<int> node6{6};
    Vertex<int> node7{7};
    Vertex<int> node8{8};

    Edge edge1{node0.mKey, node1.mKey, 4};
    Edge edge2{node0.mKey, node7.mKey, 8};
    Edge edge3{node1.mKey, node2.mKey, 8};
    Edge edge4{node1.mKey, node7.mKey, 11};
    Edge edge5{node2.mKey, node3.mKey, 7};
    Edge edge6{node3.mKey, node4.mKey, 9};
    Edge edge7{node3.mKey, node5.mKey, 14};
    Edge edge8{node4.mKey, node5.mKey, 10};
    Edge edge9{node5.mKey, node2.mKey, 4};
    Edge edge10{node5.mKey, node6.mKey, 2};
    Edge edge11{node6.mKey, node7.mKey, 1};
    Edge edge12{node6.mKey, node8.mKey, 6};
    Edge edge13{node7.mKey, node8.mKey, 7};
    Edge edge14{node8.mKey, node2.mKey, 2};

//    std::vector<std::pair<Vertex<int>, Vertex<int>>>
//        edge{pair1, pair2, pair3, pair4, pair5, pair6, pair7, pair8, pair9, pair10};

    std::list<Edge> edgeList1
        {edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11, edge12, edge13, edge14};
    std::vector<Vertex<int>> nodeList1{node0, node1, node2, node3, node4, node5, node6, node7, node8};

//    std::list<Edge>::iterator edgeIter;
//    std::vector<Vertex<int>>::iterator nodeIter;
//    std::list<Edge> A;

//    for (edgeIter = edgeList1.begin(); edgeIter != edgeList1.end(); edgeIter++) {
//        std::cout << " first " << edgeIter->mEdge.first
//                  << " second " << edgeIter->mEdge.second << std::endl;
//    }

//    for (nodeIter = nodeList1.begin(); nodeIter != nodeList1.end(); nodeIter++) {
//        if (nodeIter->mHead == nullptr) {
//            std::cout << " vertex->mKey " << nodeIter->mKey << " mHead nullptr " << std::endl;
//        }
//    }

    Graph<int> graph{nodeList1.size(), false, edgeList1, nodeList1};

//    A = graph.MstKruskal(graph);

//    for (edgeIter = A.begin(); edgeIter != A.end(); edgeIter++) {
//        std::cout << " first " << edgeIter->mEdge.first
//                  << " second " << edgeIter->mEdge.second << std::endl;
//    }

    graph.MstPrim(graph, 0);
}