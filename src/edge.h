#include "vertex.h"
#pragma once

class Edge {
    public:

        /**
        * Edge custom constructor
        * @param start_ start vertex of an edge
        * @param end_ end vertex of an edge
        */
        Edge(Vertex start_, Vertex end_);

        /**
        * Get the starting vertex of an edge
        * @return Vertex object of the starting vertex of an edge
        */
        Vertex getStart();

        /**
        * Get the ending vertex of an edge
        * @return Vertex object of the ending vertex of an edge
        */
        Vertex getEnd();

        /**
        * Returns the weight of an edge(distance between two airports in the vertices)
        * @return weight of an edge
        */
        double getWeight();

    private:
        void calculateWeight();
        Vertex start;
        Vertex end;
        double weight;
};