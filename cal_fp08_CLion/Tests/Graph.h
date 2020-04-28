/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
	T info;
	vector<Edge<T> *> outgoing;  // adj
	vector<Edge<T> *> incoming;
	Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
	Vertex(T in);

	bool visited;  // for path finding
	Edge<T> *path; // for path finding

public:
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
	Edge<T> * e = new Edge<T>(this, dest, c, f);
	this->outgoing.push_back(e);
	dest->incoming.push_back(e);
	return e;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
	return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	Vertex<T> * orig;
	Vertex<T> * dest;
	double capacity;
	double flow;
	Edge(Vertex<T> *o, Vertex<T> *d, double c, double f=0);

public:
	double getFlow() const;
	Vertex<T> *getDest() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f): orig(o), dest(d), capacity(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
	return flow;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
	return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	Vertex<T>* findVertex(const T &inf) const;
    bool FindAugmentationPath(T source, T target);
    double FindMinResidualAlongPath(T source, T target);
    void AugmentFlowAlongPath(T source, T target, float f);
public:
	vector<Vertex<T> *> getVertexSet() const;
	Vertex<T> *addVertex(const T &in);
	Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f=0);
	void fordFulkerson(T source, T target);

};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
	auto s = findVertex(sourc);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	else
		return s->addEdge(d, c, f);
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
	for (auto v : vertexSet)
		if (v->info == inf)
			return v;
	return nullptr;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}


/**
 * Finds the maximum flow in a graph using the Ford Fulkerson algorithm
 * (with the improvement of Edmonds-Karp).
 * Assumes that the graph forms a flow network from source vertex 's'
 * to sink vertex 't' (distinct vertices).
 * Receives as arguments the source and target vertices (identified by their contents).
 * The result is defined by the "flow" field of each edge.
 */
template <class T>
void Graph<T>::fordFulkerson(T source, T target) {
    for (Vertex<T>* vertex : vertexSet) {
        for (Edge<T>* edge: vertex->getAdj())
            edge->flow = 0;
    }

    double tot = 0, f;
    while(FindAugmentationPath(source, target)) {
        f = FindMinResidualAlongPath(source, target);
        AugmentFlowAlongPath(source, target, f);
        tot += f;
    }
}

template <class T>
bool Graph<T>::FindAugmentationPath(T source, T target) {
    for(Vertex<T>* vertex: vertexSet)
        vertex->visited = false;
    Vertex<T> * s = findVertex(source);
    Vertex<T> * t = findVertex(target);
    s->visited = true;
    queue<Vertex<T>*> q;
    q.push(s);
    while(!q.empty() && !(t->visited)) {
        Vertex<T>* v = q.front();
        q.pop();
        for (Edge<T> * edge: v->outgoing) {
            if(!(edge->getDest())->visited && (edge->capacity - edge->getFlow()) > 0) {
                (edge->getDest())->visited = true;
                (edge->getDest())->path = edge;
                q.push(edge->getDest());
            }
        }
        for (Edge<T>* edge: v->incoming) {
            if(!(edge->orig)->visited && edge->getFlow() > 0) {
                (edge->orig)->visited = true;
                (edge->orig)->path = edge;
                q.push(edge->orig);
            }
        }

    }
    return t->visited;
}

template <class T>
double Graph<T>::FindMinResidualAlongPath(T source, T target) {
    double f = INT_MAX;
    Vertex<T>* v = findVertex(target);
    Vertex<T>* s = findVertex(source);
    while(v != s) {
        Edge<T>* edge = v->path;
        if(edge->getDest() == v) {
            f = min(f, edge->capacity - edge->flow);
            v = edge->orig;
        }
        else {
            f = min(f, edge->flow);
            v = edge->dest;
        }
    }
    return f;
}

template <class T>
void Graph<T>::AugmentFlowAlongPath(T source, T target, float f) {
    Vertex<T>* v = findVertex(target);
    Vertex<T>* s = findVertex(source);
    while(v != s) {
        Edge<T> * edge = v->path;
        if(edge->dest == v) {
            edge->flow += f;
            v = edge->orig;
        }
        else {
            edge->flow -= f;
            v = edge->dest;
        }
    }
}

#endif /* GRAPH_H_ */
