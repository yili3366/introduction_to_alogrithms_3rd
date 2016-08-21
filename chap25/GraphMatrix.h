//
// Created by yijun on 8/16/16.
//

#ifndef CHAP25_GRAPH_H
#define CHAP25_GRAPH_H

#include <vector>

//#define DEBUG

class GraphMatrix {
public:

    GraphMatrix() = default;
    GraphMatrix(std::vector<std::vector<int>>);
    GraphMatrix(const GraphMatrix &);
    GraphMatrix &operator=(const GraphMatrix &);
    ~GraphMatrix() = default;

    GraphMatrix ExtendShortestPaths(GraphMatrix &L, GraphMatrix &W);
    GraphMatrix SquareMatrixMultiply(GraphMatrix &A, GraphMatrix &B);
    GraphMatrix SlowAllPairsShortestPaths(GraphMatrix &W);
    GraphMatrix FasterAllPairsShortestPaths(GraphMatrix &W);
    GraphMatrix FloydWarshall(GraphMatrix& W, GraphMatrix& Pi);
    GraphMatrix TrasitiveClosure(GraphMatrix& G);

    void PrintMatrix(GraphMatrix &G);

private:
    std::vector<std::vector<int>> mAdjacencyMatrix;

};

#endif //CHAP25_GRAPH_H
