#pragma once
#include <vector>
#include <string>
#include "graph.h"
#include "vertex.h"
#include <queue>
#include <map>

using namespace std;

class OpenFlights {
    public:
        /**
        * OpenFlights Constructor
        * @param airports the file name that contains all airport names
        * @param routes the file name that contains all routes
        */
        OpenFlights(string& airports, string& routes);

        /**
        * Performs BFS (Breadth-First-Search) on the given IATA code
        * @param IATA string that represents IATA code
        * @return vector<string> of all airports that are connected to given airport one way or another.
        * doesn't have to be direct connection
        */ 
        vector<string> BFS(string IATA);

        /**
        * Performs Dijkstra's algorithm on the given IATA code
        * @param start string that represents IATA code
        * @return map<string, string> the IATA code of airport and the one it's connected to
        * doesn't have to be direct connection
        */
        map<string, string> Dijkstra(string start);

        /**
        * Performs Dijkstra's algorithm on the source IATA code and dest IATA code
        * @param start string that represents IATA code of source
        * @param end string that represents IATA code of destination
        * @return vector<string> of the strings of the IATA code of the path
        */        
        vector<string> Dijkstra(string start, string end);

        /**
        * Gets the map that maps the iata (key) to the vertex (value)
        * @return map<string, vertex> of IATA code to the vertex
        */ 
        map<string, Vertex> GetIataToVertex();

        /**
        * Gets the Graph that contains edges and verticies
        * @return Graph
        */         
        Graph getGraph();

        /**
        * Finds Betweenness Centrality measure on a given IATA code.
        * @param IATA string that represents airport IATA code
        * @return double of centrality measure
        */
        double BetweennessCentrality(string IATA);


    private:
        /**
        * Inserting the verticies into the graph
        * @param airports the file name that contains all airport names
        */
        void insertAirports(string& airports);

        /**
        * Inserts edges in graphs
        * @param routes the file name that contains all routes names
        */
        void insertRoutes(string& routes);

        /**
        * Splits each line in routes file by removing commas
        * @param line each line of the routes file
        * @return vector<string> of all items in each line of routes
        */        
        vector<string> split(string& line);

        Graph graph;
        string routeFile;
        map<string, Vertex> IataToVertex;
};