//
// Created by yijun on 8/22/16.
//

#include <gtest/gtest.h>
#include "GraphAdjacencyList.h"

TEST(GraphAdjacencyList, GraphAdjacencyListTest) {

    Vertex<int> node0{0};
    Vertex<int> node1{1};
    Vertex<int> node2{2};
    Vertex<int> node3{3};
    Vertex<int> node4{4};
    Vertex<int> node5{5};

    Edge edge1{node0.mKey, node1.mKey, 0, 16};
    Edge edge2{node0.mKey, node2.mKey, 0, 13};
    Edge edge3{node1.mKey, node3.mKey, 0, 12};
    Edge edge4{node2.mKey, node1.mKey, 0, 4};
    Edge edge5{node2.mKey, node4.mKey, 0, 14};
    Edge edge6{node3.mKey, node2.mKey, 0, 9};
    Edge edge7{node3.mKey, node5.mKey, 0, 20};
    Edge edge8{node4.mKey, node3.mKey, 0, 7};
    Edge edge9{node4.mKey, node5.mKey, 0, 4};

    std::vector<Vertex<int>> nodeVector{node0, node1, node2, node3, node4, node5};
    std::list<Edge> edgeList{edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9};

    Graph<int> EdmondsKarpGraph{nodeVector.size(), true, edgeList, nodeVector};
    Graph<int> GenericPushRelabelGraph{nodeVector.size(), true, edgeList, nodeVector};
    Graph<int> RelabelToFrontGraph{nodeVector.size(), true, edgeList, nodeVector};

    int edmonKarpMaxFlow;
    int genericPushRelabelMaxFlow;
    int relabelToFrontGraphMaxFlow;

//    graph.EdmondsKarp(graph, 0, 5);
    edmonKarpMaxFlow =  EdmondsKarpGraph.EdmondsKarp(EdmondsKarpGraph, 0, 5);
    std::cout << " edmonKarpMaxFlow " << edmonKarpMaxFlow << std::endl;

    genericPushRelabelMaxFlow =  GenericPushRelabelGraph.GenericPushRelabel(GenericPushRelabelGraph, 0, 5);
    std::cout << " genericPushRelabelMaxFlow " << genericPushRelabelMaxFlow << std::endl;

    relabelToFrontGraphMaxFlow = RelabelToFrontGraph.RelabelTorFront(RelabelToFrontGraph, 0, 5);
    std::cout << " relabelToFrontGraphMaxFlow " << relabelToFrontGraphMaxFlow << std::endl;

}

