//
// Created by yijun on 7/23/16.
//

#ifndef CHAP22_GRAPHNODE_H
#define CHAP22_GRAPHNODE_H

#include <vector>
#include <list>
#include <limits>
#include <list>
#include <queue>

enum class Color {
    kWhite = 0,
    kGray = 1,
    kBlack = 2,
};

enum class EdgeType {
};

template<typename KeyType>
struct Vertex {
    Vertex(int key, KeyType value = 0);

    Color mColor;
    int mDistance;
    Vertex<KeyType> *mPi;
    int mKey;
    int mStartTime;
    int mFinishTime;
    KeyType mValue;
};

struct Edge {
    int mWeight;
    std::pair<int, int> mEdge;
    Edge(int u, int v, int weight = 0);
};

Edge::Edge(int u, int v, int weight) {
    mEdge.first = u;
    mEdge.second = v;
    mWeight = weight;
}

template<typename KeyType>
Vertex<KeyType>::Vertex(int key, KeyType value) : mValue(value) {
    mColor = Color::kWhite;
    mPi = nullptr;
    mDistance = std::numeric_limits<int>::max();
    mKey = key;
    mStartTime = 0;
    mFinishTime = 0;
}

template<typename KeyType>
class Graph {
public:
    Graph(int number,
          bool isDirectedGraphs,
          std::vector<Edge> &edgeVector,
          std::vector<Vertex<KeyType>> &nodeVector);

    void BFS(Graph<KeyType> G, int s);
    void DFS(Graph<KeyType> G);
    void DFSVisit(Graph<KeyType> G, int u);

    void PrintPath(Graph<KeyType> G, int s, int v);
    void PrintAdjacencyList(Graph<KeyType> G);
    void PrintNodeList(Graph<KeyType> G);

    std::vector<Vertex<KeyType>> TopologicalSort(Graph<KeyType> G);

private:
    int mNodeNumber;
    bool mDirectedGraphs;
    std::vector<Vertex<KeyType>> mNodeList;
    std::vector<std::list<Edge>> mAdjacencyList;
    int mTime;
};

template<typename KeyType>
Graph<KeyType>::Graph(int number,
                      bool isDirectedGraphs,
                      std::vector<Edge> &edgeVector,
                      std::vector<Vertex<KeyType>> &nodeVector) {
    mNodeNumber = number;
    mDirectedGraphs = isDirectedGraphs;

    mAdjacencyList.resize(number);

    std::vector<Edge>::iterator edgeIter;
    typename std::vector<Vertex<KeyType>>::iterator nodeIter;

    for (nodeIter = nodeVector.begin(); nodeIter != nodeVector.end(); nodeIter++) {
        mNodeList.push_back(*nodeIter);
    }

    if (mDirectedGraphs) {
        for (edgeIter = edgeVector.begin(); edgeIter != edgeVector.end(); edgeIter++) {
            mAdjacencyList.at(edgeIter->mEdge.first).push_back(*edgeIter);
        }
    } else {
        for (edgeIter = edgeVector.begin(); edgeIter != edgeVector.end(); edgeIter++) {
            mAdjacencyList.at(edgeIter->mEdge.first).push_back(*edgeIter);

            std::swap(edgeIter->mEdge.first, edgeIter->mEdge.second);
            mAdjacencyList.at(edgeIter->mEdge.first).push_back(*edgeIter);
        }
    }
}

template<typename KeyType>
void Graph<KeyType>::BFS(Graph<KeyType> G, int s) {
    std::queue<Vertex<KeyType>> Q;

    for (int i = 0; i < mNodeNumber; i++) {
        if (G.mNodeList.at(i).mKey != s) {
            G.mNodeList.at(i).mColor = Color::kWhite;
            G.mNodeList.at(i).mDistance = std::numeric_limits<KeyType>::max();
            G.mNodeList.at(i).mPi = nullptr;
        }
    }

    G.mNodeList.at(s).mColor = Color::kGray;
    G.mNodeList.at(s).mDistance = 0;
    G.mNodeList.at(s).mPi = nullptr;

    Q.push(G.mNodeList.at(s));

    while (!Q.empty()) {
        Vertex<KeyType> u = Q.front();
        Q.pop();

        typename std::list<Edge>::iterator iter = G.mAdjacencyList.at(u.mKey).begin();

        for (; iter != G.mAdjacencyList.at(u.mKey).end(); iter++) {
//            std::cout << "u->mKey " << u.mKey << std::endl;
//            std::cout << " iter->mEdge.second " << iter->mEdge.second << std::endl;
            if (mNodeList.at(iter->mEdge.second).mColor == Color::kWhite) {
                mNodeList.at(iter->mEdge.second).mColor = Color::kGray;
                mNodeList.at(iter->mEdge.second).mDistance = u.mDistance + 1;
                mNodeList.at(iter->mEdge.second).mPi = &mNodeList.at(u.mKey);
                Q.push(mNodeList.at(iter->mEdge.second));
            }
        }
        u.mColor = Color::kBlack;
    }
}

template<typename KeyType>
void Graph<KeyType>::PrintPath(Graph<KeyType> G, int s, int v) {
    if (v == s) {
        std::cout << " " << s << " ";
    } else if (mNodeList.at(v).mPi == nullptr) {
        std::cout << "no path from " << s
                  << " to " << v << " exists " << std::endl;
    } else {
        PrintPath(G, s, mNodeList.at(v).mPi->mKey);
        std::cout << " " << v << " ";
    }
//    std::cout << std::endl;
}

template<typename KeyType>
void Graph<KeyType>::PrintAdjacencyList(Graph<KeyType> G) {
    std::vector<std::list<Edge>>::iterator nodeIter;
    std::list<Edge>::iterator listIter;

    for (nodeIter = mAdjacencyList.begin(); nodeIter != mAdjacencyList.end(); nodeIter++) {
        for (listIter = nodeIter->begin(); listIter != nodeIter->end(); listIter++) {
            std::cout << "  " << listIter->mEdge.second;
        }
        std::cout << std::endl;
    }
}

template<typename KeyType>
void Graph<KeyType>::PrintNodeList(Graph<KeyType> G) {
    typename std::vector<Vertex<KeyType>>::iterator iter;

    for (iter = G.mNodeList.begin(); iter != G.mNodeList.end(); iter++) {
        std::cout << " iter->mKey " << iter->mKey << " iter->mDistance " << iter->mDistance;
        if (iter->mPi) {
            std::cout << " iter->mPi->mKey " << iter->mPi->mKey;
        }
//        std::cout << std::endl;
    }
}

template<typename KeyType>
void Graph<KeyType>::DFS(Graph G) {
    typename std::vector<Vertex<KeyType>>::iterator iter;
    for (iter = mNodeList.begin(); iter != mNodeList.end(); iter++) {
        iter->mColor = Color::kWhite;
        iter->mPi = nullptr;
    }
    mTime = 0;
    for (iter = mNodeList.begin(); iter != mNodeList.end(); iter++) {
        if (iter->mColor == Color::kWhite) {
            DFSVisit(G, iter->mKey);
        }
    }
}

template<typename KeyType>
void Graph<KeyType>::DFSVisit(Graph G, int u) {
    std::list<Edge>::iterator edgeIter;

    mTime = mTime + 1;
    mNodeList.at(u).mStartTime = mTime;
    mNodeList.at(u).mColor = Color::kGray;

    for (edgeIter = mAdjacencyList.at(u).begin(); edgeIter != mAdjacencyList.at(u).end(); edgeIter++) {
        if (mNodeList.at(edgeIter->mEdge.second).mColor == Color::kWhite) {
            mNodeList.at(edgeIter->mEdge.second).mPi = &mNodeList.at(u);
            DFSVisit(G, edgeIter->mEdge.second);
        }
    }

    mNodeList.at(u).mColor = Color::kBlack;
    mTime = mTime + 1;
    mNodeList.at(u).mFinishTime = mTime;
}

template<typename KeyType>
std::vector<Vertex<KeyType>> Graph<KeyType>::TopologicalSort(Graph G) {

    std::vector<Vertex<KeyType>> nodeList;
    typename std::vector<Vertex<KeyType>>::iterator nodeListIter;
    nodeList = mNodeList;

    struct compare {
        bool operator()(const Vertex<KeyType> &lhs, const Vertex<KeyType> &rhs) const {
            return lhs.mFinishTime > rhs.mFinishTime;
        }
    };

    DFS(G);
    std::sort(nodeList.begin(), nodeList.end(), compare());

    for (nodeListIter = nodeList.begin(); nodeListIter != nodeList.end(); nodeListIter++) {
        std::cout << " Key " << nodeListIter->mKey << " finished time " << nodeListIter->mFinishTime << std::endl;
    }
//    std::cout << std::endl;
    return nodeList;
}

#endif //CHAP22_GRAPHNODE_H
