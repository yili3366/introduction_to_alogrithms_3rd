//
// Created by yijun on 8/19/16.
//

#include "GraphAdjacencyList.h"
#include <gtest/gtest.h>

TEST(GraphAdjacencyList, GraphAdjacencyListTest) {

    std::vector<std::vector<int>> johnMatrix;

    Vertex<int> node0{0};
    Vertex<int> node1{1};
    Vertex<int> node2{2};
    Vertex<int> node3{3};
    Vertex<int> node4{4};

    Edge edge1{node0.mKey, node1.mKey, 3};
    Edge edge2{node0.mKey, node2.mKey, 8};
    Edge edge3{node0.mKey, node4.mKey, -4};
    Edge edge4{node1.mKey, node3.mKey, 1};
    Edge edge5{node1.mKey, node4.mKey, 7};
    Edge edge6{node2.mKey, node1.mKey, 4};
    Edge edge7{node3.mKey, node0.mKey, 2};
    Edge edge8{node3.mKey, node2.mKey, -5};
    Edge edge9{node4.mKey, node3.mKey, 6};

    std::vector<Vertex<int>> nodeVector{node0, node1, node2, node3, node4};
    std::list<Edge> edgeList{edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9};

    Graph<int> graph{nodeVector.size(), true, edgeList, nodeVector};

    johnMatrix = graph.Johnson(graph);

    for (std::vector<std::vector<int>>::iterator iterI = johnMatrix.begin(); iterI != johnMatrix.end(); iterI++) {
        for (std::vector<int>::iterator iterJ = iterI->begin(); iterJ != iterI->end(); iterJ++) {
            std::cout << *iterJ << "    ";
        }
        std::cout << std::endl;
    }
}
