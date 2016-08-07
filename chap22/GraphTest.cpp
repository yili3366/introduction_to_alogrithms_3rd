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
    Vertex<int> node9{9};
    Vertex<int> node10{10};
    Vertex<int> node11{11};
    Vertex<int> node12{12};

    Edge edge1{node1.mKey, node2.mKey};
    Edge edge2{node1.mKey, node0.mKey};
    Edge edge3{node0.mKey, node3.mKey};
    Edge edge4{node3.mKey, node4.mKey};
    Edge edge5{node3.mKey, node5.mKey};
    Edge edge6{node4.mKey, node5.mKey};
    Edge edge7{node4.mKey, node6.mKey};
    Edge edge8{node5.mKey, node6.mKey};
    Edge edge9{node5.mKey, node7.mKey};
    Edge edge10{node6.mKey, node7.mKey};

//    std::vector<std::pair<Vertex<int>, Vertex<int>>>
//        edge{pair1, pair2, pair3, pair4, pair5, pair6, pair7, pair8, pair9, pair10};

    std::list<Edge> edgeList1{edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10};
//    auto edge{edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10};
    std::vector<Vertex<int>> nodeVector1{node0, node1, node2, node3, node4, node5, node6, node7};
//    auto node{node0, node1, node2, node3, node4, node5, node6, node7};

    std::list<Edge>::iterator edgeIter;
    std::vector<Vertex<int>>::iterator nodeIter;

    for (edgeIter = edgeList1.begin(); edgeIter != edgeList1.end(); edgeIter++) {
        std::cout << " first " << edgeIter->mEdge.first
                  << " second " << edgeIter->mEdge.second << std::endl;
    }

    for (nodeIter = nodeVector1.begin(); nodeIter != nodeVector1.end(); nodeIter++) {
        if (nodeIter->mHead == nullptr) {
            std::cout << " vertex->mKey " << nodeIter->mKey << " mHead nullptr " << std::endl;
        }
    }

    Graph<int> graph(8, false, edgeList1, nodeVector1);

    graph.PrintAdjacencyList(graph);

    graph.BFS(graph, 0);
    graph.PrintPath(graph, 3, 7);
    std::cout << std::endl;

    graph.DFS(graph);
    graph.PrintPath(graph, 3, 7);
    std::cout << std::endl;
    graph.TopologicalSort(graph);
//    graph.PrintNodeList(graph);


    //graph1 strongly connected components
    Edge directedEdge1{node0.mKey, node1.mKey};
    Edge directedEdge2{node0.mKey, node5.mKey};
    Edge directedEdge3{node0.mKey, node6.mKey};
    Edge directedEdge4{node2.mKey, node0.mKey};
    Edge directedEdge5{node2.mKey, node3.mKey};
    Edge directedEdge6{node3.mKey, node2.mKey};
    Edge directedEdge7{node3.mKey, node5.mKey};
    Edge directedEdge8{node4.mKey, node2.mKey};
    Edge directedEdge9{node4.mKey, node3.mKey};
    Edge directedEdge10{node4.mKey, node11.mKey};
    Edge directedEdge11{node5.mKey, node4.mKey};
    Edge directedEdge12{node6.mKey, node4.mKey};
    Edge directedEdge13{node6.mKey, node9.mKey};
    Edge directedEdge14{node7.mKey, node6.mKey};
    Edge directedEdge15{node7.mKey, node8.mKey};
    Edge directedEdge16{node8.mKey, node7.mKey};
    Edge directedEdge17{node8.mKey, node9.mKey};
    Edge directedEdge18{node9.mKey, node10.mKey};
    Edge directedEdge19{node9.mKey, node11.mKey};
    Edge directedEdge20{node10.mKey, node12.mKey};
    Edge directedEdge21{node11.mKey, node12.mKey};
    Edge directedEdge22{node12.mKey, node9.mKey};

    std::list<Edge>
        directedEdge
        {directedEdge1, directedEdge2, directedEdge3, directedEdge4, directedEdge5, directedEdge6,
         directedEdge7, directedEdge8, directedEdge9, directedEdge10, directedEdge11, directedEdge12,
         directedEdge13, directedEdge14, directedEdge15, directedEdge16, directedEdge17,
         directedEdge18, directedEdge19, directedEdge20, directedEdge21, directedEdge22};

    std::vector<Vertex<int>>
        nodeVector2{node0, node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11, node12};

    Graph<int> graph1(13, true, directedEdge, nodeVector2);

//    std::cout << " before transpose " << std::endl;
//    graph1.PrintAdjacencyList(graph1);
//    graph1.Transpose(graph1, graph1);
//    std::cout << " after transpose " << std::endl;
//    graph1.PrintAdjacencyList(graph1);



    graph1.StronglyConnectedComponents(graph1);
    graph1.PrintSCC(graph1);
}