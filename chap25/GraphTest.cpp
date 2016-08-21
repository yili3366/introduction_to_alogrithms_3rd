//
// Created by yijun on 8/17/16.
//

#include <gtest/gtest.h>
#include "GraphMatrix.h"

TEST(GraphMatrixTest, GraphMatrix) {

    std::vector<std::vector<int>> Matrix{
        {0, 3, 8, std::numeric_limits<int>::max(), -4},
        {std::numeric_limits<int>::max(), 0, std::numeric_limits<int>::max(), 1, 7},
        {std::numeric_limits<int>::max(), 4, 0, std::numeric_limits<int>::max(), std::numeric_limits<int>::max()},
        {2, std::numeric_limits<int>::max(), -5, 0, std::numeric_limits<int>::max()},
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), 6, 0}};

    GraphMatrix graph{Matrix};
    GraphMatrix graph2;
    GraphMatrix graph3;
    GraphMatrix floydWarshallGraphMatrix;
    GraphMatrix Pi;

    graph2 = graph.SlowAllPairsShortestPaths(graph);
    graph3 = graph.FasterAllPairsShortestPaths(graph);
    floydWarshallGraphMatrix = graph.FloydWarshall(graph, Pi);

    std::cout << " graph2" << std::endl;
    graph2.PrintMatrix(graph2);

    std::cout << " graph3" << std::endl;
    graph3.PrintMatrix(graph3);

    std::cout << " floydWarshallGraphMatrix " << std::endl;
    floydWarshallGraphMatrix.PrintMatrix(floydWarshallGraphMatrix);

    std::cout << " Pi " << std::endl;
    Pi.PrintMatrix(Pi);


    std::vector<std::vector<int>> transitiveMatrix{
        {0, std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max()},
        {std::numeric_limits<int>::max(), 0, 1, 1},
        {std::numeric_limits<int>::max(), 1, 0, std::numeric_limits<int>::max()},
        {1, std::numeric_limits<int>::max(), 1, 0}
    };

    GraphMatrix transitiveGraphMatrix{transitiveMatrix};
    GraphMatrix transitive;

    transitive = transitiveGraphMatrix.TrasitiveClosure(transitiveGraphMatrix);

    std::cout << " transitive graph " << std::endl;
    transitive.PrintMatrix(transitive);
}