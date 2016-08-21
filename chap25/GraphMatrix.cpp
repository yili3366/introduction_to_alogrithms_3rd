//
// Created by yijun on 8/17/16.
//
#include <gmpxx.h>
#include <iostream>
#include "GraphMatrix.h"

GraphMatrix GraphMatrix::ExtendShortestPaths(GraphMatrix &L, GraphMatrix &W) {
    int n = L.mAdjacencyMatrix.begin()->size();
    GraphMatrix Matrix;
    Matrix.mAdjacencyMatrix.resize(n);

    for (std::vector<std::vector<int>>::iterator iter = Matrix.mAdjacencyMatrix.begin();
         iter != Matrix.mAdjacencyMatrix.end(); iter++) {
        iter->resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Matrix.mAdjacencyMatrix.at(i).at(j) = std::numeric_limits<int>::max();
            for (int k = 0; k < n; k++) {
                if (L.mAdjacencyMatrix.at(i).at(k) != std::numeric_limits<int>::max()
                    && W.mAdjacencyMatrix.at(k).at(j) != std::numeric_limits<int>::max()) {
                    Matrix.mAdjacencyMatrix.at(i).at(j) =
                        std::min(Matrix.mAdjacencyMatrix.at(i).at(j),
                                 L.mAdjacencyMatrix.at(i).at(k) + W.mAdjacencyMatrix.at(k).at(j));
                }
            }
        }
    }

    return Matrix;
}

GraphMatrix GraphMatrix::SquareMatrixMultiply(GraphMatrix &A, GraphMatrix &B) {
    int n = A.mAdjacencyMatrix.begin()->size();
    GraphMatrix C;
    C.mAdjacencyMatrix.resize(n);

    for (std::vector<std::vector<int>>::iterator iter = C.mAdjacencyMatrix.begin(); iter != C.mAdjacencyMatrix.end();
         iter++) {
        iter->resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C.mAdjacencyMatrix.at(i).at(j) = 0;
            for (int k = 0; k < n; k++) {
                C.mAdjacencyMatrix.at(i).at(j) =
                    C.mAdjacencyMatrix.at(i).at(j) + A.mAdjacencyMatrix.at(i).at(k) * B.mAdjacencyMatrix.at(k).at(j);
            }
        }
    }

    return C;
}

GraphMatrix GraphMatrix::SlowAllPairsShortestPaths(GraphMatrix &W) {
    int n = W.mAdjacencyMatrix.begin()->size();
    GraphMatrix L(W);

    for (int m = 2; m < n; m++) {
        std::vector<std::vector<int>> Lm;
        L = ExtendShortestPaths(L, W);
        std::cout << std::endl;
        PrintMatrix(L);
        std::cout << std::endl;
    }

    return L;
}

GraphMatrix GraphMatrix::FasterAllPairsShortestPaths(GraphMatrix &W) {
    int n = W.mAdjacencyMatrix.begin()->size();
    GraphMatrix L(W);
    int m = 1;

    while (m < n) {
        L = ExtendShortestPaths(L, L);
        m = m * 2;
    }

    return L;
}

GraphMatrix::GraphMatrix(std::vector<std::vector<int>> Matrix) {
    mAdjacencyMatrix = Matrix;
}

GraphMatrix::GraphMatrix(const GraphMatrix &Matrix) {
    mAdjacencyMatrix = Matrix.mAdjacencyMatrix;
}

GraphMatrix &GraphMatrix::operator=(const GraphMatrix &Matrix) {
    if (&Matrix != this) {
        this->mAdjacencyMatrix.clear();
        this->mAdjacencyMatrix = Matrix.mAdjacencyMatrix;
    }
}

void GraphMatrix::PrintMatrix(GraphMatrix &G) {
    for (std::vector<std::vector<int>>::iterator iterI = G.mAdjacencyMatrix.begin(); iterI != G.mAdjacencyMatrix.end();
         iterI++) {
        for (std::vector<int>::iterator iterJ = iterI->begin(); iterJ != iterI->end(); iterJ++) {
            std::cout << *iterJ << "        ";
        }
        std::cout << std::endl;
    }
}

GraphMatrix GraphMatrix::FloydWarshall(GraphMatrix &W, GraphMatrix &Pi) {
    int n = W.mAdjacencyMatrix.begin()->size();

    GraphMatrix D(W);
//    GraphMatrix Pi(D);
    Pi = D;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || D.mAdjacencyMatrix.at(i).at(j) == std::numeric_limits<int>::max()) {
                Pi.mAdjacencyMatrix.at(i).at(j) = std::numeric_limits<int>::max();
            } else {
                Pi.mAdjacencyMatrix.at(i).at(j) = i;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (D.mAdjacencyMatrix.at(i).at(k) != std::numeric_limits<int>::max()
                    && D.mAdjacencyMatrix.at(k).at(j) != std::numeric_limits<int>::max()) {

                    if (D.mAdjacencyMatrix.at(i).at(j)
                        <= D.mAdjacencyMatrix.at(i).at(k) + D.mAdjacencyMatrix.at(k).at(j)) {
                        Pi.mAdjacencyMatrix.at(i).at(j) = Pi.mAdjacencyMatrix.at(i).at(j);
                    }

                    if (D.mAdjacencyMatrix.at(i).at(j)
                        > D.mAdjacencyMatrix.at(i).at(k) + D.mAdjacencyMatrix.at(k).at(j)) {
                        Pi.mAdjacencyMatrix.at(i).at(j) = Pi.mAdjacencyMatrix.at(k).at(j);
                    }


                    D.mAdjacencyMatrix.at(i).at(j) =
                        std::min(D.mAdjacencyMatrix.at(i).at(j),
                                 D.mAdjacencyMatrix.at(i).at(k) + D.mAdjacencyMatrix.at(k).at(j));
                }
            }
        }
#ifdef DEBUG
        std::cout << " Pi " << std::endl;
        for (std::vector<std::vector<int>>::iterator iterI = Pi.mAdjacencyMatrix.begin();
             iterI != Pi.mAdjacencyMatrix.end(); iterI++) {
            for (std::vector<int>::iterator iterJ = iterI->begin(); iterJ != iterI->end(); iterJ++) {
                std::cout << *iterJ << "        ";
            }
            std::cout << std::endl;
        }
#endif
    }

    return D;
}

GraphMatrix GraphMatrix::TrasitiveClosure(GraphMatrix &G) {
    int n = G.mAdjacencyMatrix.size();
    GraphMatrix T(G);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || G.mAdjacencyMatrix.at(i).at(j) != std::numeric_limits<int>::max()) {
                T.mAdjacencyMatrix.at(i).at(j) = 1;
            } else {
                T.mAdjacencyMatrix.at(i).at(j) = 0;
            }
        }
    }

#ifdef DEBUG
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << T.mAdjacencyMatrix.at(i).at(j) << "        ";
        }
        std::cout << std::endl;
    }
#endif

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                T.mAdjacencyMatrix.at(i).at(j) = T.mAdjacencyMatrix.at(i).at(j)
                    | (T.mAdjacencyMatrix.at(i).at(k) & T.mAdjacencyMatrix.at(k).at(j));
            }
        }

#ifdef DEBUG
        std::cout << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << T.mAdjacencyMatrix.at(i).at(j) << "        ";
            }
            std::cout << std::endl;
        }
#endif
    }

    return T;
}
