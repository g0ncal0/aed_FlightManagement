//
// Created by Filipe Correia on 30/11/2023.
//

#ifndef AVIOES_GRAPH_H
#define AVIOES_GRAPH_H


#include <cstddef>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <stack>
#include <unordered_set>

using namespace std;

class Edge;
class Graph;
class Vertex;


/****************** Provided structures  ********************/

class Vertex {
    std::string iata;                // contents
    vector<Edge> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int num;
    int low;

    void addEdge(Vertex *dest, double w);
    bool removeEdgeTo(Vertex *d);
public:
    Vertex(string in);
    string getIATA() const;
    void setIATA(const std::string& in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    int getNum() const;
    int setNum(int num);
    int getLow() const;
    int setLow(int low);
    const vector<Edge> &getAdj() const;
    vector<Edge> &getAdj();
    void setAdj(const vector<Edge> &adj);
    void addAdj(const Edge& edge);
    friend class Graph;
};


class Edge {
    Vertex * dest;  // destination vertex
    double weight;  // edge weight
    set<string> airlines; // airlines that operate certain trip (represented by edge)

public:
    Edge(Vertex *d, double w);
    Vertex *getDest() const;
    void setDest(Vertex *dest);
    double getWeight() const;
    void setWeight(double weight);
    set<string> getAirlines();
    void addAirline(std::string airline);
    friend class Graph;
    friend class Vertex;
};

class Graph {
    vector<Vertex *> vertexSet;    // vertex set
    void dfsVisit(Vertex *v,  vector<string> & res) const;
    bool dfsIsDAG(Vertex *v) const;
public:
    Vertex *findVertex(const string &in) const;
    int getNumVertex() const;
    bool addVertex(const string &in);
    bool removeVertex(const string &in);
    bool addEdge(const string &sourc, const string &dest, double w);
    bool removeEdge(const string &sourc, const string &dest);
    vector<Vertex * > getVertexSet() const;
    vector<string> dfs();
    vector<string> dfs(const string & source) const;
    vector<string> bfs(const string &source) const;
    int getDiameter(Vertex * vertex, vector<string>& lastLevelVertices);
    void dfs_articulationPoints(Vertex *v, stack<std::string> &s, unordered_set<std::string> &l, int &i);
    unordered_set<std::string> articulationPoints();
    int countEdges() const;
};



#endif //AVIOES_GRAPH_H
