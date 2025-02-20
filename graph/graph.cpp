//
// Created by Filipe Correia on 30/11/2023.
//

#include "graph.h"
#include <string>
#include <iostream>

Vertex::Vertex(std::string in): iata(in) {}

Edge::Edge(Vertex *d, double w): dest(d), weight(w) {}


int Graph::getNumVertex() const {
    return vertexSet.size();
}

vector<Vertex * > Graph::getVertexSet() const {
    return vertexSet;
}

string Vertex::getIATA() const {
    return iata;
}

void Vertex::setIATA(const std::string& in) {
    Vertex::iata = in;
}

bool Vertex::isProcessing() const {
    return processing;
}

void Vertex::setProcessing(bool p) {
    Vertex::processing = p;
}

int Vertex::getNum() const{
    return num;
}

void Vertex::setNum(int num) {
    this->num = num;
}

int Vertex::getLow() const {
    return low;
}

void Vertex::setLow(int low) {
    this->low = low;
}

Vertex *Edge::getDest() const {
    return dest;
}

void Edge::setDest(Vertex *d) {
    Edge::dest = d;
}

double Edge::getWeight() const {
    return weight;
}

void Edge::setWeight(double weight) {
    Edge::weight = weight;
}

set<string> Edge::getAirlines() const {
    return airlines;
}

void Edge::addAirline(std::string airline) {
    airlines.insert(airline);
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const string &in) const {
    for (auto v : vertexSet)
        if (v->iata == in)
            return v;
    return NULL;
}

bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setVisited(bool v) {
    Vertex::visited = v;
}

const vector<Edge> &Vertex::getAdj() const {
    return adj;
}

vector<Edge> &Vertex::getAdj() {
    return adj;
}

void Vertex::setAdj(const vector<Edge> &adj) {
    Vertex::adj = adj;
}

void Vertex::addAdj(const Edge& edge) {
    adj.push_back(edge);
}

/**
 * Adds a vertex with a given content or info (in) to a graph (this).
 * @param in the content of the vertex
 * @return true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const string &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex(in));
    return true;
}

/**
 * Adds an edge to a graph (this), given the contents of the source and destination vertices and the edge weight (w).
 * @param sourc the code of the source
 * @param dest the code of the destination
 * @param w the weight of the edge
 * @return true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const string &sourc, const string &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}

/**
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * @param d destination of the edge
 * @param w weight of the edge
 */
void Vertex::addEdge(Vertex *d, double w) {
    adj.push_back(Edge(d, w));
}

/**
 * Removes an edge from a graph (this).
 * @param sourc source of the edge
 * @param dest destination of the edge
 * @return true if successful, and false if such edge does not exist.
 */
bool Graph::removeEdge(const string &sourc, const string &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/**
 * Auxiliary function to remove an outgoing edge (with a given destination (d)) from a vertex (this).
 * @param d
 * @return true if successful, and false if such edge does not exist.
 */
bool Vertex::removeEdgeTo(Vertex *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

/**
 * Removes a vertex with a given content (in) from a graph (this), and all outgoing and incoming edges.
 * @param in
 * @return true if successful, and false if such vertex does not exist.
 */
bool Graph::removeVertex(const string &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->iata  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

int Graph::getDiameter(Vertex* vertex, vector<string>& lastLevelVertices) {
    int diameter = -1;

    queue<Vertex*> q;
    for (Vertex* v : vertexSet) v->setVisited(false);

    vertex->setVisited(true);
    q.push(vertex);

    while (!q.empty()) {
        diameter++;
        int levelSize = q.size();
        lastLevelVertices.clear();

        for (int i = 0; i < levelSize; i++) {
            Vertex* v = q.front();
            q.pop();
            lastLevelVertices.push_back(v->getIATA());
            for (Edge edge : v->adj) {
                if (!edge.dest->isVisited()) {
                    edge.dest->setVisited(true);
                    q.push(edge.dest);
                }
            }
        }

    }

    return diameter;
}


void Graph::dfs_articulationPoints(Vertex *v, stack<Vertex*> &s, unordered_set<std::string> &l, int &i) {
    v->setNum(i);
    v->setLow(i);
    v->setProcessing(true);
    i++;

    int child = 0;
    for (const Edge& edge : v->getAdj()) {
        if (edge.getDest()->getNum() == -1) {
            child++;
            dfs_articulationPoints(edge.getDest(), s, l, i);
            v->setLow(min(v->getLow(), edge.getDest()->getLow()));
            if (edge.getDest()->getLow() >= v->getNum() && (v->getNum() != 1 || child > 1)) l.insert(v->getIATA());
        }
        else if (v->isProcessing()) v->setLow(min(v->getLow(), edge.getDest()->getNum()));
    }

    if (v->getNum() == 1 && child == 0) i = 1;

    v->setProcessing(false);
}

unordered_set<std::string> Graph::articulationPoints() {
    unordered_set<std::string> res;

    stack<Vertex *> s;
    int index = 1;

    for (Vertex * vertex : vertexSet) {
        vertex->setNum(-1);
        vertex->setLow(-1);
        for (const Edge& edge : vertex->getAdj()) edge.getDest()->addEdge(vertex, edge.weight);
    }

    for (Vertex * vertex : vertexSet) {
        if (vertex->getNum() == -1) dfs_articulationPoints(vertex, s, res, index);
    }

    return res;
}

int Graph::countEdges() const {
    int res = 0;
    for(Vertex* v: vertexSet){
        res += v->getAdj().size();
    }
    return res;
}

vector<string> Graph::dfs() {
    vector<string> res;
    int count = 0;
    for (auto v : vertexSet) {
        v->visited = false;
        for (const Edge& edge : v->adj) addEdge(edge.getDest()->getIATA(), v->getIATA(), edge.weight);
    }
    for (auto v : vertexSet)
        if (! v->visited) {
            count++;
            dfsVisit(v, res);
        }
    cout << "Numero de cc: " << count << endl;

    return res;
}

void Graph::dfsVisit(Vertex *v,  vector<string> & res) const {
    v->visited = true;
    res.push_back(v->getIATA());
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}

void Graph::setDefaults(){
    for(Vertex* v : vertexSet){
        v->setLow(-1);
        v->setNum(-1);
        v->setVisited(false);
        v->setProcessing(false);
    }
}

/**
 * Function to find all the possible destinations from one airport with max n stops. O(V + E)
 * @param airport the code of the source airport
 * @param n max stops
 * @return the codes of all possible destinations
 */
unordered_set<string> Graph::bfsmaxXstops(std::string airport, int n){
    setDefaults();
    unordered_set<std::string> res;
    auto a = findVertex(airport);
    queue<Vertex*> qv;
    qv.push(a);
    a->setNum(0);
    a->setVisited(true);
    while(!qv.empty()){
        auto u = qv.front();
        qv.pop();
        for(auto edge : u->getAdj()){
            if(!edge.getDest()->isVisited() && u->getNum() < n){
                qv.push(edge.getDest());
                edge.getDest()->setNum(u->getNum()+1);
                edge.getDest()->setVisited(true);
                res.insert(edge.getDest()->getIATA());
            }
        }
    }
    return res;
}

Graph Graph::clone(){
    Graph r;

    for(auto v : vertexSet){
        r.addVertex(v->getIATA());
    }
    for(auto v : vertexSet){
        for(auto e : v->getAdj()){
            r.addEdge(v->getIATA(), e.getDest()->getIATA(),0);
        }
    }
    return r;
}