#pragma once

#include "vertex.h"
#include "edge.h"

#include <vector>
class Graph {
    
    public:

        /**
        * Returns vector of the graph's vertices
        * @return vector of graph's vertices(Vertex objects)
        */
        vector<Vertex> getVertices();

        /**
        * Returns vector of the graph's edges
        * @return vector of graph's edges(Edge objects)
        */
        vector<Edge> getEdges();
        
        /**
        * Returns the adjjacent vertices, including incomeing and outgoing adjacent vertices, of an inputed vertex
        * @param vertex to find adjacent vertices of
        * @return vector of adjacent vertices
        */
        vector<Vertex> getAdjacentVerticies(Vertex vert);

        /**
        * Returns the adjjacent vertices, only outgoing vertices, of an inputed vertex
        * @param vertex to find adjacent vertices of
        * @return vector of adjacent vertices
        */
        vector<Vertex> getAdjacentOutgoingVertices(Vertex vert);

        /**
        * Inserts an edge between two vertices
        * @param start vertex of the wanted edge
        * @param end vertex of the wanted edge
        * @return void 
        */
        void insertEdge(Vertex start, Vertex end);

        /**
        * Inserts a vertex
        * @param v vertex wanted to be inserted
        * @return void 
        */
        void insertVertex(Vertex v);

    private:
        vector<Edge> edges;
        vector<Vertex> vertices;
};