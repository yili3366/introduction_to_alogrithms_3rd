//
// Created by yijun on 7/25/16.
//

#include <gtest/gtest.h>
#include "Graph.h"

TEST(GraphTest, Graph) {

    Vertex<int> node0 = Vertex<int>(0);
    Vertex<int> node1 = Vertex<int>(1);
    Vertex<int> node2 = Vertex<int>(2);
    Vertex<int> node3 = Vertex<int>(3);
    Vertex<int> node4 = Vertex<int>(4);
    Vertex<int> node5 = Vertex<int>(5);
    Vertex<int> node6 = Vertex<int>(6);
    Vertex<int> node7 = Vertex<int>(7);

    Edge edge1(node1.mKey, node2.mKey);
    Edge edge2(node1.mKey, node0.mKey);
    Edge edge3(node0.mKey, node3.mKey);
    Edge edge4(node3.mKey, node4.mKey);
    Edge edge5(node3.mKey, node5.mKey);
    Edge edge6(node4.mKey, node5.mKey);
    Edge edge7(node4.mKey, node6.mKey);
    Edge edge8(node5.mKey, node6.mKey);
    Edge edge9(node5.mKey, node7.mKey);
    Edge edge10(node6.mKey, node7.mKey);


//    std::vector<std::pair<Vertex<int>, Vertex<int>>>
//        edge{pair1, pair2, pair3, pair4, pair5, pair6, pair7, pair8, pair9, pair10};

    std::vector<Edge> edge{edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10};
    std::vector<Edge>::iterator edgeIter;

    std::vector<Vertex<int>> node{node0, node1, node2, node3, node4, node5, node6, node7};
    std::vector<Vertex<int>>::iterator nodeIter;

//    for (edgeIter = edge.begin(); edgeIter < edge.end(); edgeIter++) {
//        std::cout << " first " << edgeIter->mEdge.first
//                  << " second " << edgeIter->mEdge.second << std::endl;
//    }

    Graph<int> graph(8, false, edge, node);

//    graph.PrintAdjacencyList(graph);

    graph.BFS(graph, 0);
    graph.PrintPath(graph, 3, 7);
    std::cout << std::endl;

    graph.DFS(graph);
    graph.PrintPath(graph, 3, 7);
    std::cout << std::endl;
    graph.TopologicalSort(graph);
//    graph.PrintNodeList(graph);
}