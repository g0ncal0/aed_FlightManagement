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

    void addEdge(Vertex *dest, double w);
    bool removeEdgeTo(Vertex *d);
public:
    Vertex(string in);
    string getIATA() const;
    void setIATA(string in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge> &getAdj() const;
    void setAdj(const vector<Edge> &adj);
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
    vector<string> dfs() const;
    vector<string> dfs(const string & source) const;
    vector<string> bfs(const string &source) const;
};



#endif //AVIOES_GRAPH_H
