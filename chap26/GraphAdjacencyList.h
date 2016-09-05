//
// Created by yijun on 7/23/16.
//

#ifndef CHAP26_GRAPHADJACENCYLIST_H
#define CHAP26_GRAPHADJACENCYLIST_H

#include <vector>
#include <list>
#include <limits>
#include <list>
#include <queue>
#include <memory>
#include <iostream>
#include <algorithm>
#include <set>

//#define  DEBUG

enum class Color {
    kWhite = 0,
    kGray = 1,
    kBlack = 2,
};

struct Edge {
    Edge();
    Edge(const Edge &) = default;
    Edge &operator=(const Edge &);
    ~Edge() = default;

    int mWeight;
    int mFlow;
    int mCapacity;
    std::pair<int, int> mEdge;
    Edge(int u, int v, int weight = 0, int capacity = 0, int flow = 0);
};

Edge::Edge() : mFlow(0), mCapacity(0) {
    mEdge.first = std::numeric_limits<int>::max();
    mEdge.second = std::numeric_limits<int>::max();
    mWeight = std::numeric_limits<int>::max();
}

Edge::Edge(int u, int v, int weight, int capacity, int flow) {
    mEdge.first = u;
    mEdge.second = v;
    mWeight = weight;
    mCapacity = capacity;
    mFlow = flow;
}

Edge &Edge::operator=(const Edge &edge) {
    mEdge.first = edge.mEdge.first;
    mEdge.second = edge.mEdge.second;
    mWeight = edge.mWeight;
    mCapacity = edge.mCapacity;
    mFlow = edge.mFlow;
}

template<typename KeyType>
struct Vertex: public std::enable_shared_from_this<Vertex<KeyType>> {
    Vertex();
    Vertex(const Vertex<KeyType> &);
    Vertex<KeyType> &operator=(const Vertex<KeyType> &);
    ~Vertex();

    Vertex(int key, KeyType value = std::numeric_limits<KeyType>::min());

    Color mColor;
    int mDistance;
    int mKey;
    int mStartTime;
    int mFinishTime;
    KeyType mValue;

    std::shared_ptr<std::list<Edge>> mHead;
    std::shared_ptr<Vertex<KeyType>> mPi;
    std::list<int> mNeighbor;

    int mRank = 0;
    std::shared_ptr<Vertex<KeyType>> mParent = nullptr;
    int mLeastWeight = std::numeric_limits<int>::max();

    int mExcessFlow;
    int mHeight;
};

template<typename KeyType>
Vertex<KeyType>::Vertex(): mStartTime(0), mFinishTime(0), mExcessFlow(0), mHeight(0) {
    mColor = Color::kWhite;
    mDistance = std::numeric_limits<int>::max();
    mKey = std::numeric_limits<int>::min();
    mValue = std::numeric_limits<KeyType>::min();
    mPi = nullptr;
    mHead = nullptr;
}

template<typename KeyType>
Vertex<KeyType>::Vertex(int key, KeyType value)
    : mValue(value), mStartTime(0), mFinishTime(0), mExcessFlow(0), mHeight(0) {
    mColor = Color::kWhite;
    mDistance = std::numeric_limits<int>::max();
    mKey = key;

    mHead = std::make_shared<std::list<Edge>>(std::list<Edge>{});
//    mHead = std::make_shared<std::list<Edge>>();
    mPi = nullptr;
}

template<typename KeyType>
Vertex<KeyType>::Vertex(const Vertex<KeyType> &vertex) :
    mColor(vertex.mColor),
    mDistance(vertex.mDistance),
    mKey(vertex.mKey),
    mStartTime(vertex.mStartTime),
    mFinishTime(vertex.mFinishTime),
    mValue(vertex.mValue),
    mRank(vertex.mRank),
    mLeastWeight(vertex.mLeastWeight),
    mExcessFlow(vertex.mExcessFlow),
    mHeight(vertex.mHeight),
    mNeighbor(vertex.mNeighbor) {
    if (vertex.mHead != nullptr) {
//        mHead.reset(new std::list<Edge>{});
        mHead = std::make_shared<std::list<Edge>>(std::list<Edge>{});
        *mHead = *vertex.mHead;
    }

    if (vertex.mPi != nullptr) {
//        mPi.reset(new Vertex<KeyType>());
        mPi = std::make_shared<Vertex<KeyType>>();
        *mPi = *vertex.mPi;
    }

    if (vertex.mParent != nullptr) {
//        mPi.reset(new Vertex<KeyType>());
        mParent = std::make_shared<Vertex<KeyType>>();
        *mParent = *vertex.mParent;
    }
}

template<typename KeyType>
Vertex<KeyType> &Vertex<KeyType>::operator=(const Vertex<KeyType> &vertex) {
    if (this != &vertex) {
        mColor = vertex.mColor;
        mDistance = vertex.mDistance;
        mKey = vertex.mKey;
        mStartTime = vertex.mStartTime;
        mFinishTime = vertex.mFinishTime;
        mValue = vertex.mValue;
        mRank = vertex.mRank;
        mLeastWeight = vertex.mLeastWeight;
        mExcessFlow = vertex.mExcessFlow;
        mHeight = vertex.mHeight;
        mNeighbor = vertex.mNeighbor;

        if (vertex.mHead != nullptr) {
//            mHead.reset(new std::list<Edge>{});
            mHead = std::make_shared<std::list<Edge>>(std::list<Edge>{});
            *mHead = *vertex.mHead;
        }

        if (vertex.mPi != nullptr) {
//            mPi.reset(new Vertex<KeyType>());
            mPi = std::make_shared<Vertex<KeyType>>();
            *mPi = *vertex.mPi;
        }

        if (vertex.mParent != nullptr) {
//            mPi.reset(new Vertex<KeyType>());
            mParent = std::make_shared<Vertex<KeyType>>();
            *mParent = *vertex.mParent;
        }
    }

    return *this;
}

template<typename KeyType>
Vertex<KeyType>::~Vertex() {
    mHead.reset();
    mPi.reset();
    mParent.reset();
    mNeighbor.clear();
}

template<typename KeyType>
class Graph {
public:
    Graph();
    Graph(const Graph<KeyType> &);
    Graph<KeyType> &operator=(const Graph<KeyType> &);
    ~Graph();

    Graph(int number,
          bool isDirectedGraphs,
          std::list<Edge> &edgeVector,
          std::vector<Vertex<KeyType>> &nodeVector);

    void BFS(Graph<KeyType> &G, int s);
    void DFS(Graph<KeyType> &G);
    void DFSForSCC(Graph<KeyType> &G, int key);
    void DFSVisit(Graph<KeyType> &G, int u);
    void PrintPath(Graph<KeyType> &G, int s, int v);

    void PrintAdjacencyList(Graph<KeyType> &G);
    void PrintNodeList(Graph<KeyType> &G);

    std::vector<Vertex<KeyType>> TopologicalSort(Graph<KeyType> &G);
    void StronglyConnectedComponents(Graph<KeyType> &G);
    void Transpose(Graph<KeyType> &inGraph, Graph<KeyType> &outGraph);

    void PrintSCC(Graph<KeyType> &G);

    std::list<Edge> MstKruskal(Graph<KeyType> &G);
    void MstPrim(Graph<KeyType> &G, int r);

    bool BellmanFord(Graph<KeyType> &G, int s);
    void DagShortestPath(Graph<KeyType> &G, int s);
    void Dijkstra(Graph<KeyType> &G, int s);
    std::vector<std::vector<int>> Johnson(Graph<KeyType> &G);

    int EdmondsKarp(Graph<KeyType> &G, int s, int t);
    int GenericPushRelabel(Graph<KeyType> &G, int s, int t);
    int RelabelTorFront(Graph<KeyType> &G, int s, int t);

private:
    bool HasExcessVertex(Graph<KeyType> &G, int s, int t);
    void CreateResidualGraph(Graph<KeyType> &G, Graph<KeyType> &Gf);
    bool CanBePushed(Graph<KeyType> &G, Graph<KeyType> &Gf, int s, int t, int &u, int &v);
    bool CanBeRelabelled(Graph<KeyType> &G, Graph<KeyType> &Gf, int s, int t, int &u);
    bool FindPathInResidualGraph(Graph<KeyType> &G, int s, int t);
    int FindMinimalResidualCapacity(Graph<KeyType> &G, int s, int t);

    int ResidualCapacity(Graph<KeyType> &G, int u, int v);
    void AddEdge(Graph<KeyType> &G, Edge edge);
    Edge *AddEdge(Graph<KeyType> &G, int u, int v);
    Edge *SearchEdge(Graph<KeyType> &G, int u, int v);

    void InitializeSingleSource(Graph<KeyType> &G, int s);
    void Relax(Graph<KeyType> &G, int u, int v);
    void MakeSet(Vertex<KeyType> &vertex);
    Vertex<KeyType> &FindSet(Graph<KeyType> &G, int key);
    void Link(Graph<KeyType> &G, int x, int y);
    void Union(Graph<KeyType> &G, int x, int y);

    void Push(Graph<KeyType> &G, Graph<KeyType> &Gf, int u, int v);
    void InitializePerflow(Graph<KeyType> &G, int s);
    void Relabel(Graph<KeyType> &G, Graph<KeyType> &Gf, int u);

    void Discharge(Graph<KeyType> &G, int u);

    int mNodeNumber;
    bool mDirectedGraphs;
    std::vector<Vertex<KeyType>> mAdjacencyList;
    int mTime;

    //for strongly connection component
    int mCount;
    int mSCCCount;

    std::vector<int> mPostI;
    std::vector<int> mPostR;
    std::vector<int> mId;
    std::list<Edge> mEdgeList;
};

template<typename KeyType>
Graph<KeyType>::Graph() {
    mNodeNumber = 0;
    mDirectedGraphs = false;
    mAdjacencyList.clear();
    mTime = 0;
    mCount = 0;
    mSCCCount = 0;

    mPostI.resize(mNodeNumber);
    mPostR.resize(mNodeNumber);
    mId.resize(mNodeNumber);

    mPostI.assign(mPostI.size(), 0);
    mPostR.assign(mPostR.size(), 0);
    mId.assign(mId.size(), std::numeric_limits<int>::min());
}

template<typename KeyType>
Graph<KeyType>::Graph(const Graph<KeyType> &G) {
    mNodeNumber = G.mNodeNumber;
    mDirectedGraphs = G.mDirectedGraphs;
    mAdjacencyList = G.mAdjacencyList;
    mTime = G.mTime;
    mPostI = G.mPostI;
    mPostR = G.mPostR;
    mId = G.mId;
    mCount = G.mCount;
    mSCCCount = G.mSCCCount;
    mEdgeList = G.mEdgeList;
}

template<typename KeyType>
Graph<KeyType> &Graph<KeyType>::operator=(const Graph<KeyType> &G) {
    if (this != &G) {
        mNodeNumber = G.mNodeNumber;
        mDirectedGraphs = G.mDirectedGraphs;
        mAdjacencyList = G.mAdjacencyList;
        mTime = G.mTime;
        mPostI = G.mPostI;
        mPostR = G.mPostR;
        mId = G.mId;
        mCount = G.mCount;
        mSCCCount = G.mSCCCount;
        mEdgeList = G.mEdgeList;
    }

    return *this;
}

template<typename KeyType>
Graph<KeyType>::Graph(int number,
                      bool isDirectedGraphs,
                      std::list<Edge> &edgeList,
                      std::vector<Vertex<KeyType>> &nodeVector) {
    mNodeNumber = number;
    mDirectedGraphs = isDirectedGraphs;
    mCount = 0;
    mSCCCount = 0;

    mPostI.resize(mNodeNumber);
    mPostR.resize(mNodeNumber);
    mId.resize(mNodeNumber);

    mPostI.assign(mPostI.size(), 0);
    mPostR.assign(mPostR.size(), 0);
    mId.assign(mId.size(), std::numeric_limits<int>::min());

    std::list<Edge>::iterator edgeIter;
    typename std::vector<Vertex<KeyType>>::iterator nodeIter;

    for (nodeIter = nodeVector.begin(); nodeIter != nodeVector.end(); nodeIter++) {
        mAdjacencyList.push_back(*nodeIter);
    }

    for (nodeIter = nodeVector.begin(); nodeIter != nodeVector.end(); nodeIter++) {
        if (nodeIter->mHead == nullptr) {
            std::cout << " vertex->mKey " << nodeIter->mKey << " mHead nullptr " << std::endl;
        }
    }

    mEdgeList = edgeList;

    if (mDirectedGraphs) {
        for (edgeIter = edgeList.begin(); edgeIter != edgeList.end(); edgeIter++) {
            mAdjacencyList.at(edgeIter->mEdge.first).mHead->push_back(*edgeIter);
        }
    } else {
        for (edgeIter = edgeList.begin(); edgeIter != edgeList.end(); edgeIter++) {
            mAdjacencyList.at(edgeIter->mEdge.first).mHead->push_back(*edgeIter);

            if (edgeIter->mEdge.first != edgeIter->mEdge.second) {
                std::swap(edgeIter->mEdge.first, edgeIter->mEdge.second);
                mAdjacencyList.at(edgeIter->mEdge.first).mHead->push_back(*edgeIter);
            }
        }
    }

    //initialize neighbor list
    for (std::list<Edge>::iterator edgeiter = edgeList.begin(); edgeiter != edgeList.end(); edgeiter++) {
        if (std::find(mAdjacencyList.at(edgeiter->mEdge.first).mNeighbor.begin(),
                      mAdjacencyList.at(edgeiter->mEdge.first).mNeighbor.end(),
                      edgeiter->mEdge.second) == mAdjacencyList.at(edgeiter->mEdge.first).mNeighbor.end()) {
            mAdjacencyList.at(edgeiter->mEdge.first).mNeighbor.push_back(edgeiter->mEdge.second);
        }

        if (std::find(mAdjacencyList.at(edgeiter->mEdge.second).mNeighbor.begin(),
                      mAdjacencyList.at(edgeiter->mEdge.second).mNeighbor.end(),
                      edgeiter->mEdge.first) == mAdjacencyList.at(edgeiter->mEdge.second).mNeighbor.end()) {
            mAdjacencyList.at(edgeiter->mEdge.second).mNeighbor.push_back(edgeiter->mEdge.first);
        }
    }

#if DEBUG
    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = mAdjacencyList.begin();
         nodeIter != mAdjacencyList.end(); nodeIter++) {
        std::cout << " node key " << nodeIter->mKey << std::endl;
        for (std::list<int>::iterator neighborIter = nodeIter->mNeighbor.begin();
             neighborIter != nodeIter->mNeighbor.end(); neighborIter++) {
            std::cout << " neighbor " << *neighborIter;
        }
        std::cout << std::endl;

        for (std::list<Edge>::iterator listIter = nodeIter->mHead->begin(); listIter != nodeIter->mHead->end();
             listIter++) {
            std::cout << " node " << nodeIter->mKey << " Edge " << listIter->mEdge.first << " "
                      << listIter->mEdge.second << " weight " << listIter->mWeight << std::endl;
        }
    }
#endif
}

template<typename KeyType>
void Graph<KeyType>::BFS(Graph<KeyType> &G, int s) {
    std::queue<Vertex<KeyType>> Q;

    for (int i = 0; i < G.mNodeNumber; i++) {
        if (G.mAdjacencyList.at(i).mKey != s) {
            G.mAdjacencyList.at(i).mColor = Color::kWhite;
            G.mAdjacencyList.at(i).mDistance = std::numeric_limits<KeyType>::max();
            G.mAdjacencyList.at(i).mPi = nullptr;
        }
    }

    G.mAdjacencyList.at(s).mColor = Color::kGray;
    G.mAdjacencyList.at(s).mDistance = 0;
    G.mAdjacencyList.at(s).mPi = nullptr;

    Q.push(G.mAdjacencyList.at(s));

    while (!Q.empty()) {
        Vertex<KeyType> u = Q.front();
        Q.pop();

        typename std::list<Edge>::iterator iter = G.mAdjacencyList.at(u.mKey).mHead->begin();

        for (; iter != G.mAdjacencyList.at(u.mKey).mHead->end(); iter++) {
            if (G.mAdjacencyList.at(iter->mEdge.second).mColor == Color::kWhite) {
                G.mAdjacencyList.at(iter->mEdge.second).mColor = Color::kGray;
                G.mAdjacencyList.at(iter->mEdge.second).mDistance = u.mDistance + 1;
                G.mAdjacencyList.at(iter->mEdge.second).mPi =
                    std::shared_ptr<Vertex<KeyType>>(&G.mAdjacencyList.at(u.mKey), [](Vertex<KeyType> *) {});
//                mAdjacencyList.at(iter->mEdge.second).mPi =
//                    std::make_shared<Vertex<KeyType>>(mAdjacencyList.at(u.mKey));
                Q.push(G.mAdjacencyList.at(iter->mEdge.second));
            }
        }
        u.mColor = Color::kBlack;
    }
}

template<typename KeyType>
void Graph<KeyType>::PrintPath(Graph<KeyType> &G, int s, int v) {
    if (v == s) {
        std::cout << " " << s << " ";
    } else if (G.mAdjacencyList.at(v).mPi == nullptr) {
        std::cout << "no path from " << s
                  << " to " << v << " exists " << std::endl;
    } else {
        PrintPath(G, s, G.mAdjacencyList.at(v).mPi->mKey);
        std::cout << " " << v << " ";
    }
    std::cout << std::endl;
}

template<typename KeyType>
void Graph<KeyType>::PrintAdjacencyList(Graph<KeyType> &G) {
    typename std::vector<Vertex<KeyType>>::iterator nodeIter;
    std::list<Edge>::iterator listIter;

    for (nodeIter = G.mAdjacencyList.begin(); nodeIter != G.mAdjacencyList.end(); nodeIter++) {
        std::cout << " node " << nodeIter->mKey << " height " << nodeIter->mHeight
                  << " excess " << nodeIter->mExcessFlow;
        if (nodeIter->mPi != nullptr) {
            std::cout << " mPi->mKey " << nodeIter->mPi->mKey;
        }
        for (listIter = nodeIter->mHead->begin(); listIter != nodeIter->mHead->end(); listIter++) {
            std::cout << " edge " << listIter->mEdge.first << "  " << listIter->mEdge.second
                      << " capacity " << listIter->mCapacity << " flow " << listIter->mFlow;
        }
        std::cout << std::endl;
    }
}

template<typename KeyType>
void Graph<KeyType>::PrintNodeList(Graph<KeyType> &G) {
    typename std::vector<Vertex<KeyType>>::iterator iter;

    for (iter = G.mAdjacencyList.begin(); iter != G.mAdjacencyList.end(); iter++) {
        std::cout << " iter->mKey " << iter->mKey << " iter->mDistance " << iter->mDistance;
        if (iter->mPi) {
            std::cout << " iter->mPi->mKey " << iter->mPi->mKey;
        }
//        std::cout << std::endl;
    }
}

template<typename KeyType>
void Graph<KeyType>::DFS(Graph &G) {
    typename std::vector<Vertex<KeyType>>::iterator iter;
    for (iter = G.mAdjacencyList.begin(); iter != G.mAdjacencyList.end(); iter++) {
        iter->mColor = Color::kWhite;
        iter->mPi = nullptr;
    }
    G.mTime = 0;
    for (iter = G.mAdjacencyList.begin(); iter != G.mAdjacencyList.end(); iter++) {
        if (iter->mColor == Color::kWhite) {
            DFSVisit(G, iter->mKey);
        }
    }
}

template<typename KeyType>
void Graph<KeyType>::DFSVisit(Graph &G, int u) {
    std::list<Edge>::iterator edgeIter;

    G.mTime = G.mTime + 1;
    G.mAdjacencyList.at(u).mStartTime = G.mTime;
    G.mAdjacencyList.at(u).mColor = Color::kGray;

    for (edgeIter = G.mAdjacencyList.at(u).mHead->begin(); edgeIter != G.mAdjacencyList.at(u).mHead->end();
         edgeIter++) {
        if (G.mAdjacencyList.at(edgeIter->mEdge.second).mColor == Color::kWhite) {
            G.mAdjacencyList.at(edgeIter->mEdge.second).mPi = std::make_shared<Vertex<KeyType>>(G.mAdjacencyList.at(u));
            DFSVisit(G, edgeIter->mEdge.second);
        }
    }

    G.mAdjacencyList.at(u).mColor = Color::kBlack;
    G.mTime = G.mTime + 1;
    G.mAdjacencyList.at(u).mFinishTime = G.mTime;
}

template<typename KeyType>
std::vector<Vertex<KeyType>> Graph<KeyType>::TopologicalSort(Graph &G) {

    std::vector<Vertex<KeyType>> nodeList;
    typename std::vector<Vertex<KeyType>>::iterator nodeListIter;
    nodeList = G.mAdjacencyList;

    struct compare {
        bool operator()(const Vertex<KeyType> &lhs, const Vertex<KeyType> &rhs) const {
            return lhs.mFinishTime > rhs.mFinishTime;
        }
    };

    DFS(G);
    std::sort(nodeList.begin(), nodeList.end(), compare());
    G.mAdjacencyList = nodeList;

    for (nodeListIter = nodeList.begin(); nodeListIter != nodeList.end(); nodeListIter++) {
        std::cout << " Key " << nodeListIter->mKey << " finished time " << nodeListIter->mFinishTime << std::endl;
    }
    std::cout << std::endl;
    return nodeList;
}

template<typename KeyType>
void Graph<KeyType>::Transpose(Graph<KeyType> &inGraph, Graph<KeyType> &outGraph) {
    std::vector<Vertex<KeyType>> adjacencyList = inGraph.mAdjacencyList;

//    outGraph.mAdjacencyList = inGraph.mAdjacencyList;
    typename std::vector<Vertex<KeyType>>::iterator nodeIter;
    std::list<Edge>::iterator oldEdgeIter;

    for (nodeIter = outGraph.mAdjacencyList.begin(); nodeIter != outGraph.mAdjacencyList.end(); nodeIter++) {
        nodeIter->mHead->clear();
    }

    for (nodeIter = adjacencyList.begin(); nodeIter != adjacencyList.end(); nodeIter++) {
        for (oldEdgeIter = nodeIter->mHead->begin(); oldEdgeIter != nodeIter->mHead->end(); oldEdgeIter++) {
            Edge newEdge = *oldEdgeIter;
            std::swap(newEdge.mEdge.first, newEdge.mEdge.second);
            outGraph.mAdjacencyList.at(newEdge.mEdge.first).mHead->push_back(newEdge);
        }
    }
}

template<typename KeyType>
void Graph<KeyType>::StronglyConnectedComponents(Graph<KeyType> &G) {
    Graph<KeyType> R = G;
    Transpose(G, R);

    typename std::vector<Vertex<KeyType>>::iterator Riter;
    typename std::vector<Vertex<KeyType>>::iterator Giter;

    for (Riter = R.mAdjacencyList.begin(); Riter != R.mAdjacencyList.end(); Riter++) {
        if (R.mId.at(Riter->mKey) == std::numeric_limits<int>::min()) {
            DFSForSCC(R, Riter->mKey);
        }
    }

    G.mPostI = R.mPostI;
    G.mPostR = R.mPostI;
//    G.mCount = G.mSCCCount = 0;

    for (Giter = G.mAdjacencyList.end() - 1; Giter >= G.mAdjacencyList.begin(); Giter--) {
        if (G.mId.at(G.mPostR.at(Giter->mKey)) == std::numeric_limits<int>::min()) {
            DFSForSCC(G, G.mPostR.at(Giter->mKey));
            G.mSCCCount++;
        }
    }
}

template<typename KeyType>
void Graph<KeyType>::DFSForSCC(Graph &G, int key) {
    G.mId.at(key) = G.mSCCCount;
    typename std::list<Edge>::iterator iter;

    for (iter = G.mAdjacencyList.at(key).mHead->begin(); iter != G.mAdjacencyList.at(key).mHead->end(); iter++) {
        if (G.mId.at(iter->mEdge.second) == std::numeric_limits<int>::min()) {
            DFSForSCC(G, iter->mEdge.second);
        }
    }
    G.mPostI.at(G.mCount++) = key;

}

template<typename KeyType>
void Graph<KeyType>::PrintSCC(Graph<KeyType> &G) {
//    std::vector<Vertex<KeyType>>::const_iterator iter;
    std::vector<int>::const_iterator iter;

    for (iter = G.mId.begin(); iter != G.mId.end(); iter++) {
        std::cout << " " << *iter << " " << std::endl;
    }
}

template<typename KeyType>
Graph<KeyType>::~Graph() {
    typename std::vector<Vertex<KeyType>>::iterator edgeIter;
    for (edgeIter = mAdjacencyList.begin(); edgeIter != mAdjacencyList.end(); edgeIter++) {
        edgeIter->mHead->clear();
    }
    mAdjacencyList.clear();
}

template<typename KeyType>
std::list<Edge> Graph<KeyType>::MstKruskal(Graph<KeyType> &G) {
    typename std::list<Edge> A;

    for (typename std::vector<Vertex<KeyType>>::iterator iter = G.mAdjacencyList.begin();
         iter != G.mAdjacencyList.end(); iter++) {
        MakeSet(*iter);
    }

    struct compare {
        bool operator()(const Edge &lhs, const Edge &rhs) const {
            return lhs.mWeight < rhs.mWeight;
        }
    };

//    std::sort(G.mEdgeList.begin(), G.mEdgeList.end(), compare());
    G.mEdgeList.sort(compare());

    for (std::list<Edge>::iterator iter = G.mEdgeList.begin(); iter != G.mEdgeList.end(); iter++) {
        if (FindSet(G, iter->mEdge.first).mKey
            != FindSet(G, iter->mEdge.second).mKey) {
//            std::cout << " u " << iter->mEdge.first << " v " << iter->mEdge.second
//                      << " weight " << iter->mWeight << std::endl;
            A.push_back(*iter);
            Union(G, iter->mEdge.first, iter->mEdge.second);
        }
    }

    return A;
}

template<typename KeyType>
void Graph<KeyType>::MakeSet(Vertex<KeyType> &vertex) {
    vertex.mParent = std::make_shared<Vertex<KeyType>>(vertex);
    vertex.mRank = 0;
}

template<typename KeyType>
Vertex<KeyType> &Graph<KeyType>::FindSet(Graph<KeyType> &G, int key) {
    if (G.mAdjacencyList.at(key).mKey != G.mAdjacencyList.at(key).mParent->mKey) {
        *G.mAdjacencyList.at(key).mParent = FindSet(G, G.mAdjacencyList.at(key).mParent->mKey);
    }

    return *G.mAdjacencyList.at(key).mParent;
}

template<typename KeyType>
void Graph<KeyType>::Link(Graph<KeyType> &G, int x, int y) {
    if (G.mAdjacencyList.at(x).mRank > G.mAdjacencyList.at(y).mRank) {
        G.mAdjacencyList.at(y).mParent = std::make_shared<Vertex<KeyType>>(G.mAdjacencyList.at(x));
    } else {
        G.mAdjacencyList.at(x).mParent = std::make_shared<Vertex<KeyType>>(G.mAdjacencyList.at(y));
//        std::cout << " x->mKey " << x.mKey << " x.Parent->mKey " << x.mParent->mKey << std::endl;
        if (G.mAdjacencyList.at(x).mRank == G.mAdjacencyList.at(y).mRank) {
            G.mAdjacencyList.at(x).mRank = G.mAdjacencyList.at(y).mRank + 1;
        }
    }
}

template<typename KeyType>
void Graph<KeyType>::Union(Graph<KeyType> &G, int x, int y) {
    Link(G, FindSet(G, x).mKey, FindSet(G, y).mKey);
}

template<typename KeyType>
void Graph<KeyType>::MstPrim(Graph<KeyType> &G, int key) {

    struct compare {
        bool operator()(const Vertex<KeyType> &lhs, const Vertex<KeyType> &rhs) const {
            return lhs.mLeastWeight < rhs.mLeastWeight;
        }
    };

    struct FindByKey {
        FindByKey(const int &key) : mKey(key) {
        }
        bool operator()(const Vertex<KeyType> &vertex) {
            return vertex.mKey == mKey;
        }
    private:
        int mKey;
    };

    for (typename std::vector<Vertex<KeyType>>::iterator iter = G.mAdjacencyList.begin();
         iter != G.mAdjacencyList.end();
         iter++) {
        iter->mLeastWeight = std::numeric_limits<int>::max();
        iter->mPi = nullptr;
    }

    G.mAdjacencyList.at(key).mLeastWeight = 0;

    std::multiset<Vertex<KeyType>, compare> Q;

    for (typename std::vector<Vertex<KeyType>>::iterator iter = G.mAdjacencyList.begin();
         iter != G.mAdjacencyList.end();
         iter++) {
        std::cout << " insert " << iter->mKey << std::endl;
        Q.emplace(*iter);
    }

    for (typename std::set<Vertex<KeyType>, compare>::iterator iter = Q.begin(); iter != Q.end(); iter++) {
        std::cout << " iter key " << iter->mKey << " mLeastWeight " << iter->mLeastWeight << std::endl;
    }

    while (Q.size() != 0) {
        Vertex<KeyType> u = G.mAdjacencyList.at(Q.begin()->mKey);
        Q.erase(Q.begin());

        std::cout << " size " << Q.size() << " u->mKey " << u.mKey << std::endl;
        for (typename std::set<Vertex<KeyType>, compare>::iterator iter = Q.begin(); iter != Q.end(); iter++) {
            std::cout << " iter key " << iter->mKey << " mLeastWeight " << iter->mLeastWeight << std::endl;
        }

        for (std::list<Edge>::iterator iter = G.mAdjacencyList.at(u.mKey).mHead->begin();
             iter != G.mAdjacencyList.at(u.mKey).mHead->end(); iter++) {
            if (std::find_if(Q.begin(), Q.end(), FindByKey(iter->mEdge.second)) != Q.end()
                && iter->mWeight < G.mAdjacencyList.at(iter->mEdge.second).mLeastWeight) {
                std::cout << " first " << iter->mEdge.first << " second " << iter->mEdge.second << std::endl;
                G.mAdjacencyList.at(iter->mEdge.second).mPi =
                    std::make_shared<Vertex<KeyType>>(G.mAdjacencyList.at(u.mKey));
                G.mAdjacencyList.at(iter->mEdge.second).mLeastWeight = iter->mWeight;
            }
        }
    }

    for (typename std::vector<Vertex<KeyType>>::iterator edgeIter = G.mAdjacencyList.begin();
         edgeIter != G.mAdjacencyList.end();
         edgeIter++) {
        std::cout << " key " << edgeIter->mKey
                  << " leastWeight " << edgeIter->mLeastWeight;
        if (edgeIter->mPi != nullptr) {
            std::cout << " mPi->mKey " << edgeIter->mPi->mKey;
        }
        std::cout << std::endl;
    }
}

template<typename KeyType>
void Graph<KeyType>::InitializeSingleSource(Graph<KeyType> &G, int s) {
    for (typename std::vector<Vertex<KeyType>>::iterator iter = G.mAdjacencyList.begin();
         iter != G.mAdjacencyList.end();
         iter++) {
        iter->mDistance = std::numeric_limits<int>::max();
        iter->mPi = nullptr;
    }
    G.mAdjacencyList.at(s).mDistance = 0;
}

template<typename KeyType>
void Graph<KeyType>::Relax(Graph<KeyType> &G, int u, int v) {
    int w;

    for (std::list<Edge>::iterator iter = G.mAdjacencyList.at(u).mHead->begin();
         iter != G.mAdjacencyList.at(u).mHead->end(); iter++) {
        if (iter->mEdge.second == v) {
            w = iter->mWeight;
            break;
        }
    }

    if (G.mAdjacencyList.at(u).mDistance != std::numeric_limits<int>::max()
        && G.mAdjacencyList.at(v).mDistance > G.mAdjacencyList.at(u).mDistance + w) {
        G.mAdjacencyList.at(v).mDistance = G.mAdjacencyList.at(u).mDistance + w;
        G.mAdjacencyList.at(v).mPi = std::make_shared<Vertex<KeyType>>(G.mAdjacencyList.at(u));
    }

#if DEBUG
    for (typename std::vector<Vertex<KeyType>>::iterator vertexIter = G.mAdjacencyList.begin();
         vertexIter != G.mAdjacencyList.end(); vertexIter++) {
        std::cout << " vertex->mKey " << vertexIter->mKey << " vertex->mDistance " << vertexIter->mDistance;
        if (vertexIter->mPi) {
            std::cout << " vertex->mPi->mKey " << vertexIter->mPi->mKey;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
#endif
}

template<typename KeyType>
bool Graph<KeyType>::BellmanFord(Graph<KeyType> &G, int s) {
    InitializeSingleSource(G, s);

    for (int i = 0; i < mNodeNumber; i++) {
        for (typename std::vector<Vertex<KeyType>>::iterator vertexIter = G.mAdjacencyList.begin();
             vertexIter != G.mAdjacencyList.end(); vertexIter++) {
            for (std::list<Edge>::iterator listIter = vertexIter->mHead->begin(); listIter != vertexIter->mHead->end();
                 listIter++) {
                Relax(G, listIter->mEdge.first, listIter->mEdge.second);
            }
        }
    }

    for (typename std::vector<Vertex<KeyType>>::iterator vertexIter = G.mAdjacencyList.begin();
         vertexIter != G.mAdjacencyList.end(); vertexIter++) {
        for (std::list<Edge>::iterator listIter = vertexIter->mHead->begin();
             listIter != vertexIter->mHead->end(); listIter++) {
            if (G.mAdjacencyList.at(listIter->mEdge.second).mDistance > vertexIter->mDistance + listIter->mWeight) {
                return false;
            }
        }
    }

    return true;
}

template<typename KeyType>
void Graph<KeyType>::DagShortestPath(Graph &G, int s) {
    TopologicalSort(G);
    InitializeSingleSource(G, s);

    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G.mAdjacencyList.begin();
         nodeIter != G.mAdjacencyList.end();
         nodeIter++) {
        for (std::list<Edge>::iterator listIter = nodeIter->mHead->begin(); listIter = nodeIter->mHead->end();
             listIter++) {
            Relax(G, listIter->mEdge.first, listIter->mEdge.second);
        }
    }
}

template<typename KeyType>
void Graph<KeyType>::Dijkstra(Graph<KeyType> &G, int s) {
    InitializeSingleSource(G, s);
    std::vector<Vertex<KeyType>> Set;

    std::vector<Vertex<KeyType> *> minHeap;

    struct compare {
        bool
        operator()(Vertex<KeyType> *const &lhs, Vertex<KeyType> *const &rhs) const {
            return lhs->mDistance > rhs->mDistance;
        }
    };

    std::make_heap(minHeap.begin(), minHeap.end(), compare());

    for (typename std::vector<Vertex<KeyType>>::iterator iter = G.mAdjacencyList.begin();
         iter != G.mAdjacencyList.end();
         iter++) {
        minHeap.push_back(&(*iter));
        std::push_heap(minHeap.begin(), minHeap.end(), compare());
    }

//    for (typename std::vector<std::shared_ptr<Vertex<KeyType>>>::iterator iter = minHeap.begin(); iter != minHeap.end();
//         iter++) {
//        std::cout << " key " << (*iter)->mKey << " distance " << (*iter)->mDistance << std::endl;
//    }

    while (!minHeap.empty()) {
        if (!std::is_heap(minHeap.begin(), minHeap.end(), compare())) {
            std::make_heap(minHeap.begin(), minHeap.end(), compare());
        }

        std::pop_heap(minHeap.begin(), minHeap.end(), compare());
        Vertex<KeyType> u = G.mAdjacencyList.at((*minHeap.rbegin())->mKey);
        minHeap.pop_back();

//        std::cout << " key " << u.mKey << " distance " << u.mDistance << std::endl;

//        for (typename std::vector<Vertex<KeyType> *>::iterator iter = minHeap.begin(); iter != minHeap.end();
//             iter++) {
//            std::cout << " key " << (*iter)->mKey << " distance " << (*iter)->mDistance << std::endl;
//        }

        Set.push_back(u);

        for (std::list<Edge>::iterator iter = G.mAdjacencyList.at(u.mKey).mHead->begin();
             iter != G.mAdjacencyList.at(u.mKey).mHead->end(); iter++) {
            Relax(G, iter->mEdge.first, iter->mEdge.second);
        }
    }
}

template<typename KeyType>
std::vector<std::vector<int>> Graph<KeyType>::Johnson(Graph<KeyType> &G) {

    std::list<Edge> G1EdgeList = G.mEdgeList;
    std::vector<Vertex<KeyType>> G1VertexVector = G.mAdjacencyList;
    Vertex<KeyType> G1NewNode{G.mAdjacencyList.size()};

    std::vector<std::vector<int>> D;
    D.resize(G.mNodeNumber);

    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G1VertexVector.begin();
         nodeIter != G1VertexVector.end(); nodeIter++) {
        nodeIter->mHead->clear();
    }

    G1VertexVector.push_back(G1NewNode);

    for (int i = 0; i < G.mAdjacencyList.size(); i++) {
        Edge edge{G.mAdjacencyList.size(), G.mAdjacencyList.at(i).mKey, 0};
        G1EdgeList.push_back(edge);
    }

//    std::cout << " G1edgelist " << std::endl;
//    for (std::list<Edge>::iterator iter = G1EdgeList.begin(); iter != G1EdgeList.end(); iter++) {
//        std::cout << " edge " << iter->mEdge.first << "    " << iter->mEdge.second << std::endl;
//    }

    Graph<KeyType> G1{G1VertexVector.size(), true, G1EdgeList, G1VertexVector};

    if (BellmanFord(G1, G1.mAdjacencyList.size() - 1) == false) {
        std::cout << " " << std::endl;
        return D;
    } else {
        int w;

        std::vector<int> h;

        for (typename std::vector<Vertex<KeyType>>::iterator iter = G1.mAdjacencyList.begin();
             iter != G1.mAdjacencyList.end() - 1; iter++) {
//            std::cout << " iter distance " << iter->mDistance << std::endl;
            h.push_back(iter->mDistance);
        }

        for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G1.mAdjacencyList.begin();
             nodeIter != G1.mAdjacencyList.end(); nodeIter++) {
            for (std::list<Edge>::iterator edgeIter = nodeIter->mHead->begin();
                 edgeIter != nodeIter->mHead->end(); edgeIter++) {
                edgeIter->mWeight = edgeIter->mWeight
                    + G1.mAdjacencyList.at(edgeIter->mEdge.first).mDistance
                    - G1.mAdjacencyList.at(edgeIter->mEdge.second).mDistance;
            }
        }

        G.mAdjacencyList = G1.mAdjacencyList;
        G.mAdjacencyList.erase(G.mAdjacencyList.end() - 1);

#if DEBUG
        for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G.mAdjacencyList.begin();
             nodeIter != G.mAdjacencyList.end();
             nodeIter++) {

            std::cout << " key " << nodeIter->mKey << " mDistance " << nodeIter->mDistance << std::endl;

            for (std::list<Edge>::iterator edgeIter = nodeIter->mHead->begin(); edgeIter != nodeIter->mHead->end();
                 edgeIter++) {
                std::cout << " edge " << edgeIter->mEdge.first << "  " << edgeIter->mEdge.second << " weight "
                          << edgeIter->mWeight << std::endl;
            }
            std::cout << std::endl;
        }
#endif

        for (std::vector<std::vector<int>>::iterator iter = D.begin(); iter != D.end(); iter++) {
            iter->resize(G.mNodeNumber);
        }

        for (typename std::vector<Vertex<KeyType>>::iterator outerNodeIter = G.mAdjacencyList.begin();
             outerNodeIter != G.mAdjacencyList.end(); outerNodeIter++) {
            Dijkstra(G, outerNodeIter->mKey);

#if DEBUG
            for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G.mAdjacencyList.begin();
                 nodeIter != G.mAdjacencyList.end(); nodeIter++) {

                std::cout << " key " << nodeIter->mKey << " distance " << nodeIter->mDistance;
                if (nodeIter->mPi != nullptr) {
                    std::cout << " nodeIter->mPi->mKey " << nodeIter->mPi->mKey;
                }
                std::cout << std::endl;
            }
#endif

            for (typename std::vector<Vertex<KeyType>>::iterator innerNodeIter = G.mAdjacencyList.begin();
                 innerNodeIter != G.mAdjacencyList.end(); innerNodeIter++) {

                D.at(outerNodeIter->mKey).at(innerNodeIter->mKey) =
                    innerNodeIter->mDistance + h.at(innerNodeIter->mKey) - h.at(outerNodeIter->mKey);
            }
        }
    }

#if DEBUG
    std::cout << std::endl;
    std::cout << " after BellmanFord " << std::endl;
    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G1.mAdjacencyList.begin();
         nodeIter != G1.mAdjacencyList.end();
         nodeIter++) {

        std::cout << " key " << nodeIter->mKey << " mDistance " << nodeIter->mDistance << std::endl;

        for (std::list<Edge>::iterator edgeIter = nodeIter->mHead->begin(); edgeIter != nodeIter->mHead->end();
             edgeIter++) {
            std::cout << " edge " << edgeIter->mEdge.first << "  " << edgeIter->mEdge.second << " weight "
                      << edgeIter->mWeight << std::endl;
        }
        std::cout << std::endl;
    }
#endif

    return D;
}

template<typename KeyType>
int Graph<KeyType>::EdmondsKarp(Graph<KeyType> &G, int s, int t) {

    int maxFlow = 0;

    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G.mAdjacencyList.begin();
         nodeIter != G.mAdjacencyList.end(); nodeIter++) {
        for (std::list<Edge>::iterator edgeIter = nodeIter->mHead->begin();
             edgeIter != nodeIter->mHead->end(); edgeIter++) {
            edgeIter->mFlow = 0;
        }
    }

    Graph Gf(G);

    CreateResidualGraph(G, Gf);
    BFS(Gf, s);

    while (FindPathInResidualGraph(Gf, s, t) == true) {
        int minimalCapacity = FindMinimalResidualCapacity(Gf, s, t);
        int v = t;
        int u;

        while (v != s) {
            u = Gf.mAdjacencyList.at(v).mPi->mKey;

            if (SearchEdge(G, u, v) != nullptr) {
                SearchEdge(G, u, v)->mFlow = SearchEdge(G, u, v)->mFlow + minimalCapacity;
            } else {
                SearchEdge(G, v, u)->mFlow = SearchEdge(G, v, u)->mFlow - minimalCapacity;
            }

            v = Gf.mAdjacencyList.at(v).mPi->mKey;
        }

        CreateResidualGraph(G, Gf);
        BFS(Gf, s);
    }

    for (std::list<Edge>::iterator edgeIter = G.mAdjacencyList.at(s).mHead->begin();
         edgeIter != G.mAdjacencyList.at(s).mHead->end(); edgeIter++) {
        maxFlow = maxFlow + edgeIter->mFlow;
    }

    std::cout << " Print G " << std::endl;
    PrintAdjacencyList(G);

    return maxFlow;
}

template<typename KeyType>
Edge *Graph<KeyType>::SearchEdge(Graph<KeyType> &G, int u, int v) {
    Edge *edge = nullptr;

    for (std::list<Edge>::iterator edgeIter = G.mAdjacencyList.at(u).mHead->begin();
         edgeIter != G.mAdjacencyList.at(u).mHead->end(); edgeIter++) {
        if (edgeIter->mEdge.second == v) {
            edge = &(*edgeIter);
        }
    }

    return edge;
}

template<typename KeyType>
Edge *Graph<KeyType>::AddEdge(Graph<KeyType> &G, int u, int v) {
    Edge *addEdge;

    addEdge = SearchEdge(G, u, v);

    if (addEdge == nullptr) {
        Edge *newEdge = new Edge{u, v, 0, 0, 0};
        G.mAdjacencyList.at(u).mHead->push_back(*newEdge);

        return newEdge;
    }

    return addEdge;
}

template<typename KeyType>
void Graph<KeyType>::AddEdge(Graph<KeyType> &G, Edge edge) {
    if (SearchEdge(G, edge.mEdge.first, edge.mEdge.second) == nullptr) {
//        std::cout << " Add edge " << edge.mEdge.first << "    " << edge.mEdge.second << std::endl;
        G.mAdjacencyList.at(edge.mEdge.first).mHead->push_back(edge);

        if (std::find(G.mAdjacencyList.at(edge.mEdge.first).mNeighbor.begin(),
                      G.mAdjacencyList.at(edge.mEdge.first).mNeighbor.end(), edge.mEdge.second)
            == G.mAdjacencyList.at(edge.mEdge.first).mNeighbor.end()) {
            G.mAdjacencyList.at(edge.mEdge.first).mNeighbor.push_back(edge.mEdge.second);
        }

        if (std::find(G.mAdjacencyList.at(edge.mEdge.second).mNeighbor.begin(),
                      G.mAdjacencyList.at(edge.mEdge.second).mNeighbor.end(), edge.mEdge.first)
            == G.mAdjacencyList.at(edge.mEdge.first).mNeighbor.end()) {
            G.mAdjacencyList.at(edge.mEdge.second).mNeighbor.push_back(edge.mEdge.first);
        }
    }
}

template<typename KeyType>
void Graph<KeyType>::Push(Graph<KeyType> &G, Graph<KeyType> &Gf, int u, int v) {

    int deltaF = std::min(G.mAdjacencyList.at(u).mExcessFlow, SearchEdge(Gf, u, v)->mCapacity);

    if (SearchEdge(G, u, v) != nullptr) {
        SearchEdge(G, u, v)->mFlow = SearchEdge(G, u, v)->mFlow + deltaF;
    } else {
        SearchEdge(G, v, u)->mFlow = SearchEdge(G, v, u)->mFlow - deltaF;
    }

    G.mAdjacencyList.at(u).mExcessFlow = G.mAdjacencyList.at(u).mExcessFlow - deltaF;
    G.mAdjacencyList.at(v).mExcessFlow = G.mAdjacencyList.at(v).mExcessFlow + deltaF;
}

template<typename KeyType>
void Graph<KeyType>::InitializePerflow(Graph<KeyType> &G, int s) {
    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G.mAdjacencyList.begin();
         nodeIter != G.mAdjacencyList.end(); nodeIter++) {
        nodeIter->mHeight = 0;
        nodeIter->mExcessFlow = 0;
    }

    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G.mAdjacencyList.begin();
         nodeIter != G.mAdjacencyList.end(); nodeIter++) {
        for (std::list<Edge>::iterator listIter = nodeIter->mHead->begin();
             listIter != nodeIter->mHead->end(); listIter++) {
            listIter->mFlow = 0;
        }
    }

    G.mAdjacencyList.at(s).mHeight = G.mNodeNumber;

    for (std::list<Edge>::iterator listIter = G.mAdjacencyList.at(s).mHead->begin();
         listIter != G.mAdjacencyList.at(s).mHead->end(); listIter++) {
        listIter->mFlow = listIter->mCapacity;
        G.mAdjacencyList.at(listIter->mEdge.second).mExcessFlow = listIter->mCapacity;
        G.mAdjacencyList.at(listIter->mEdge.first).mExcessFlow =
            G.mAdjacencyList.at(listIter->mEdge.first).mExcessFlow - listIter->mCapacity;
    }
}

template<typename KeyType>
void Graph<KeyType>::Relabel(Graph<KeyType> &G, Graph<KeyType> &Gf, int u) {
    int minHeight = std::numeric_limits<int>::max();

    for (std::list<Edge>::iterator edgeIter = Gf.mAdjacencyList.at(u).mHead->begin();
         edgeIter != Gf.mAdjacencyList.at(u).mHead->end(); edgeIter++) {
        minHeight = std::min(G.mAdjacencyList.at(edgeIter->mEdge.second).mHeight, minHeight);
    }

    G.mAdjacencyList.at(u).mHeight = minHeight + 1;
}

template<typename KeyType>
int Graph<KeyType>::GenericPushRelabel(Graph<KeyType> &G, int s, int t) {
    InitializePerflow(G, s);
    int u, v;

    Graph Gf(G);
    CreateResidualGraph(G, Gf);

    while (HasExcessVertex(G, s, t)) {
        if (CanBePushed(G, Gf, s, t, u, v)) {
            Push(G, Gf, u, v);
        } else if (CanBeRelabelled(G, Gf, s, t, u)) {
            Relabel(G, Gf, u);
        }

        CreateResidualGraph(G, Gf);
    }

    PrintAdjacencyList(G);

    return G.mAdjacencyList.at(t).mExcessFlow;
}

template<typename KeyType>
void Graph<KeyType>::Discharge(Graph<KeyType> &G, int u) {
    std::list<int>::iterator neighborIter = G.mAdjacencyList.at(u).mNeighbor.begin();
    Graph Gf(G);
    CreateResidualGraph(G, Gf);

    while (G.mAdjacencyList.at(u).mExcessFlow > 0) {
        if (neighborIter == G.mAdjacencyList.at(u).mNeighbor.end()) {
            Relabel(G, Gf, u);
            neighborIter = G.mAdjacencyList.at(u).mNeighbor.begin();
        } else if (SearchEdge(Gf, u, *neighborIter) != nullptr
            && (SearchEdge(Gf, u, *neighborIter)->mCapacity > 0)
            && G.mAdjacencyList.at(u).mHeight == G.mAdjacencyList.at(*neighborIter).mHeight + 1) {
            Push(G, Gf, u, *neighborIter);
        } else {
            neighborIter++;
        }

        CreateResidualGraph(G, Gf);
    }
}

template<typename KeyType>
int Graph<KeyType>::RelabelTorFront(Graph<KeyType> &G, int s, int t) {
    InitializePerflow(G, s);
    std::list<int> nodeList;
    std::list<int>::iterator ListIter;

    for (typename std::vector<Vertex<KeyType>>::iterator nodeVectorIter = G.mAdjacencyList.begin();
         nodeVectorIter != G.mAdjacencyList.end(); nodeVectorIter++) {
        if (nodeVectorIter->mKey == s || nodeVectorIter->mKey == t) {
            continue;
        } else {
            nodeList.push_back(nodeVectorIter->mKey);
        }
    }

    ListIter = nodeList.begin();

    while (ListIter != nodeList.end()) {
        int oldHeight = G.mAdjacencyList.at(*ListIter).mHeight;

        Discharge(G, *ListIter);

        if (G.mAdjacencyList.at(*ListIter).mHeight > oldHeight) {
            nodeList.splice(nodeList.begin(), nodeList, ListIter);
        }

        ListIter++;
    }

    PrintAdjacencyList(G);

    return G.mAdjacencyList.at(t).mExcessFlow;
}

template<typename KeyType>
int Graph<KeyType>::ResidualCapacity(Graph &G, int u, int v) {
    int Cf;
    Edge *edge;

    if ((edge = SearchEdge(G, u, v)) != nullptr) {
        Cf = edge->mCapacity - edge->mFlow;
    } else if ((edge = SearchEdge(G, v, u)) != nullptr) {
        Cf = edge->mFlow;
    } else {
        Cf = 0;
    }

    return Cf;
}

template<typename KeyType>
bool Graph<KeyType>::FindPathInResidualGraph(Graph<KeyType> &G, int s, int t) {
    while (G.mAdjacencyList.at(t).mPi != nullptr) {
        t = G.mAdjacencyList.at(t).mPi->mKey;
    }

    if (t == s) {
        return true;
    } else {
        return false;
    }
}

template<typename KeyType>
int Graph<KeyType>::FindMinimalResidualCapacity(Graph<KeyType> &G, int s, int t) {
    int u;
    int v;
    int minimalResidualCapacity = std::numeric_limits<int>::max();

    v = t;

    while (v != s) {
        u = G.mAdjacencyList.at(v).mPi->mKey;
        minimalResidualCapacity = std::min(minimalResidualCapacity, SearchEdge(G, u, v)->mCapacity);
        v = G.mAdjacencyList.at(v).mPi->mKey;
    }

    return minimalResidualCapacity;
}

template<typename KeyType>
bool Graph<KeyType>::CanBePushed(Graph<KeyType> &G, Graph<KeyType> &Gf, int s, int t, int &u, int &v) {
    for (int i = 0; i < G.mNodeNumber; i++) {
        if (i == s || i == t) {
            continue;
        }

        if (G.mAdjacencyList.at(i).mExcessFlow > 0) {
            for (int j = 0; j < G.mNodeNumber; j++) {
                if ((SearchEdge(Gf, i, j) != nullptr)
                    && (SearchEdge(Gf, i, j)->mCapacity > 0)
                    && (G.mAdjacencyList.at(i).mHeight == G.mAdjacencyList.at(j).mHeight + 1)) {
                    u = i;
                    v = j;
                    return true;
                }
            }
        }
    }

    return false;
}

template<typename KeyType>
bool Graph<KeyType>::CanBeRelabelled(Graph<KeyType> &G, Graph<KeyType> &Gf, int s, int t, int &u) {
    for (int i = 0; i < G.mNodeNumber; i++) {
        if (i == s || i == t) {
            continue;
        }

        if (G.mAdjacencyList.at(i).mExcessFlow > 0) {
            bool ret = true;
            for (int j = 0; j < G.mNodeNumber; j++) {
                if (SearchEdge(Gf, i, j) != nullptr) {
                    ret = ret & (G.mAdjacencyList.at(i).mHeight <= G.mAdjacencyList.at(j).mHeight);
                }
            }

            if (ret == true) {
                u = i;
                return ret;
            }
        }
    }

    return false;
}

template<typename KeyType>
void Graph<KeyType>::CreateResidualGraph(Graph<KeyType> &G, Graph<KeyType> &Gf) {
    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = Gf.mAdjacencyList.begin();
         nodeIter != Gf.mAdjacencyList.end(); nodeIter++) {
        nodeIter->mHead->clear();
    }

    for (int i = 0; i < Gf.mNodeNumber; i++) {
        for (int j = 0; j < Gf.mNodeNumber; j++) {
            if (SearchEdge(G, i, j) != nullptr
                && (SearchEdge(G, i, j)->mCapacity - SearchEdge(G, i, j)->mFlow) > 0) {

                Edge edge{i, j, 0, SearchEdge(G, i, j)->mCapacity - SearchEdge(G, i, j)->mFlow, 0};
                AddEdge(Gf, edge);
            } else if (SearchEdge(G, j, i) != nullptr
                && SearchEdge(G, j, i)->mFlow > 0) {

                Edge edge{i, j, 0, SearchEdge(G, j, i)->mFlow, 0};
                AddEdge(Gf, edge);
            }
        }
    }
}

template<typename KeyType>
bool Graph<KeyType>::HasExcessVertex(Graph<KeyType> &G, int s, int t) {
    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = G.mAdjacencyList.begin();
         nodeIter != G.mAdjacencyList.end(); nodeIter++) {
        if (nodeIter->mKey == s || nodeIter->mKey == t) {
            continue;
        }

        if (nodeIter->mExcessFlow > 0) {
            return true;
        }
    }

    return false;
}

#endif //CHAP26_GRAPHNODE_H
