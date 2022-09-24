#include "graph.h"

using namespace std;

void Graph::insertEdge(Vertex start, Vertex end){
    Edge edge(start, end);
    edges.push_back(edge);

}
void Graph::insertVertex(Vertex v){
    vertices.push_back(v);
}

vector<Vertex> Graph::getVertices() {
    return vertices;
}

vector<Edge> Graph::getEdges() {
    return edges;
}

vector<Vertex> Graph::getAdjacentVerticies(Vertex vert) {
    vector<Vertex> ret;
    for (Edge edge : edges) {
        if (edge.getStart().getIATA() == vert.getIATA()) {  
            ret.push_back(edge.getEnd()); //adding the destination vertex to the vector, outgoing flights
        }
        if (edge.getEnd().getIATA() == vert.getIATA()) {
            ret.push_back(edge.getStart()); //adding the source vertex to the vector, incoming flights
        }
    }
    return ret;
}

vector<Vertex> Graph::getAdjacentOutgoingVertices(Vertex vert) {
    vector<Vertex> ret;
    for (Edge edge : edges) {
        if (edge.getStart().getIATA() == vert.getIATA()) {
            ret.push_back(edge.getEnd()); //adding the destination vertex to the vector, outgoing flights
        }
    }
    return ret;
}
