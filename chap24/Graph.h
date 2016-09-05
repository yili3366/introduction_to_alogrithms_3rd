//
// Created by yijun on 7/23/16.
//

#ifndef CHAP24_GRAPHNODE_H
#define CHAP24_GRAPHNODE_H

#include <vector>
#include <list>
#include <limits>
#include <list>
#include <queue>
#include <memory>
#include <iostream>
#include <algorithm>

enum class Color {
    kWhite = 0,
    kGray = 1,
    kBlack = 2,
};

struct Edge {
    Edge();
    Edge(const Edge &) = default;
    Edge &operator=(const Edge &) = default;
    ~Edge() = default;

    int mWeight;
    std::pair<int, int> mEdge;
    Edge(int u, int v, int weight = 0);
};

Edge::Edge() {
    mEdge.first = std::numeric_limits<int>::max();
    mEdge.second = std::numeric_limits<int>::max();
    mWeight = std::numeric_limits<int>::max();
}

Edge::Edge(int u, int v, int weight) {
    mEdge.first = u;
    mEdge.second = v;
    mWeight = weight;
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

    int mRank = 0;
    std::shared_ptr<Vertex<KeyType>> mParent = nullptr;
    int mLeastWeight = std::numeric_limits<int>::max();
};

template<typename KeyType>
Vertex<KeyType>::Vertex() {
    mColor = Color::kWhite;
    mDistance = std::numeric_limits<int>::max();
    mKey = std::numeric_limits<int>::min();
    mValue = std::numeric_limits<KeyType>::min();
    mStartTime = 0;
    mFinishTime = 0;
    mPi = nullptr;
    mHead = nullptr;
}

template<typename KeyType>
Vertex<KeyType>::Vertex(int key, KeyType value) : mValue(value) {
    mColor = Color::kWhite;
    mDistance = std::numeric_limits<int>::max();
    mKey = key;
    mStartTime = 0;
    mFinishTime = 0;

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
    mLeastWeight(vertex.mLeastWeight) {
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

private:
    void InitializeSingleSource(Graph<KeyType> &G, int s);
    void Relax(Graph<KeyType> &G, int u, int v);
    void MakeSet(Vertex<KeyType> &vertex);
    Vertex<KeyType> &FindSet(Graph<KeyType> &G, int key);
    void Link(Graph<KeyType> &G, int x, int y);
    void Union(Graph<KeyType> &G, int x, int y);

    int mNodeNumber;
    bool mDirectedGraphs;
    std::vector<Vertex<KeyType>> mAdjacencyList;
//    std::vector<Vertex<KeyType>> mSCCAdjacencyList;
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

    for (std::vector<int>::iterator iter = mPostI.begin(); iter != mPostI.end(); iter++) {
        *iter = 0;
    }

    for (std::vector<int>::iterator iter = mPostR.begin(); iter != mPostR.end(); iter++) {
        *iter = 0;
    }

    for (std::vector<int>::iterator iter = mId.begin(); iter != mId.end(); iter++) {
        *iter = std::numeric_limits<int>::min();
    }
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

    for (std::vector<int>::iterator iter = mPostI.begin(); iter != mPostI.end(); iter++) {
        *iter = 0;
    }

    for (std::vector<int>::iterator iter = mPostR.begin(); iter != mPostR.end(); iter++) {
        *iter = 0;
    }

    for (std::vector<int>::iterator iter = mId.begin(); iter != mId.end(); iter++) {
        *iter = std::numeric_limits<int>::min();
    }

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

#if 0
    for (typename std::vector<Vertex<KeyType>>::iterator nodeIter = mAdjacencyList.begin();
         nodeIter != mAdjacencyList.end();
         nodeIter++) {
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

    for (int i = 0; i < mNodeNumber; i++) {
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
//                G.mAdjacencyList.at(iter->mEdge.second).mPi =
//                    std::shared_ptr<Vertex<KeyType>>(&G.mAdjacencyList.at(u.mKey), [](Vertex<KeyType>*){});
                G.mAdjacencyList.at(iter->mEdge.second).mPi =
                    std::make_shared<Vertex<KeyType>>(G.mAdjacencyList.at(u.mKey));
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
//    std::cout << std::endl;
}

template<typename KeyType>
void Graph<KeyType>::PrintAdjacencyList(Graph<KeyType> &G) {
//    std::vector<std::list<Edge>>::iterator nodeIter;
    typename std::vector<Vertex<KeyType>>::iterator nodeIter;
    std::list<Edge>::iterator listIter;

    for (nodeIter = G.mAdjacencyList.begin(); nodeIter != G.mAdjacencyList.end(); nodeIter++) {
        for (listIter = nodeIter->mHead->begin(); listIter != nodeIter->mHead->end(); listIter++) {
            std::cout << "  " << listIter->mEdge.second;
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
    mTime = 0;
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
        edgeIter->mHead.reset();
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

//    std::cout << " Q.size " << Q.size() << std::endl;

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

    if (G.mAdjacencyList.at(v).mDistance > G.mAdjacencyList.at(u).mDistance + w) {
        G.mAdjacencyList.at(v).mDistance = G.mAdjacencyList.at(u).mDistance + w;
        G.mAdjacencyList.at(v).mPi = std::make_shared<Vertex<KeyType>>(G.mAdjacencyList.at(u));
    }

#if 1
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

        for (typename std::vector<Vertex<KeyType> *>::iterator iter = minHeap.begin(); iter != minHeap.end();
             iter++) {
            std::cout << " key " << (*iter)->mKey << " distance " << (*iter)->mDistance << std::endl;
        }


        Set.push_back(u);

        for (std::list<Edge>::iterator iter = G.mAdjacencyList.at(u.mKey).mHead->begin();
             iter != G.mAdjacencyList.at(u.mKey).mHead->end(); iter++) {
            Relax(G, iter->mEdge.first, iter->mEdge.second);
        }
    }
}

#endif //CHAP24_GRAPHNODE_H
