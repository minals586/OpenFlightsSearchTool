#include "openflights.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "vector"


OpenFlights::OpenFlights(string& airports, string& routes) {
    routeFile = routes;
    insertAirports(airports);
}

void OpenFlights::insertAirports(string& airports) {
    ifstream airportsFile(airports);
    string line;

    if (airportsFile.is_open()) {
        
        //reading in each line of routes file
        while (getline(airportsFile, line)) {
            
            //calling split routes on line which returns vector of strings 
            vector<string> airport = split(line);
            if (!airport.empty()) {

                // ommiting lines with invalid or incomplete data
                if (airport[4] != "N" && airport[6] != "N" && airport[7] != "N" 
                    && airport[4] != "\\N" && airport[6] != "\\N" && airport[7] != "\\N") { 

                    // removing quotes from IATA code
                    airport[4] = airport[4].substr(1, airport[4].size() - 2); 
                    
                    //create a vector object using 4th, 6th, 7th indecies (iata code, lat, and lon)
                    Vertex vertex(airport[4], airport[6], airport[7]);
                    
                    //inserting vectors into graph
                    graph.insertVertex(vertex);

                    //fill map with vertex at value at the iata code key
                    IataToVertex[airport[4]] = vertex;
                }
            }    
        }
    }  
    insertRoutes(routeFile);
}

void OpenFlights::insertRoutes(string& routes) {
    ifstream routesFile(routes);
    string line;
    
    if (routesFile.is_open()) {
        //reading in each line of routes file
        while (getline(routesFile, line)) {

            //calling split routes on line which returns vector of strings 
            vector<string> route = split(line);
            if (!route.empty()) {

                // we will use indexs 2 and 4 to contruct the edges between two aiport nodes
                if (IataToVertex.find(route[2]) != IataToVertex.end() 
                && IataToVertex.find(route[4]) != IataToVertex.end()) {
                    Vertex vertex1 = IataToVertex[route[2]];
                    Vertex vertex2 = IataToVertex[route[4]];

                    // inserting edge into graph
                    graph.insertEdge(vertex1, vertex2);
                }
            }
        }
    }   
}

vector<string> OpenFlights::split(string& line) {
    vector<string> result;

    stringstream s_stream(line); //create string stream from the string
    while(s_stream.good()) {
      string substr;
      getline(s_stream, substr, ','); //get first string delimited by comma
      result.push_back(substr);
    }
    return result;  
}

vector<string> OpenFlights::BFS(string IATA) {
    vector<string> vec;
    map<string, bool> visited;
    queue<string> queue1; //initializing queue for BFS
    queue1.push(IATA); //enqueue first airport
  
    int count = 0;
    for (Vertex v : graph.getVertices()) {
        visited[v.getIATA()] = false; //initializing all booleans to false (not visited)
    }

    visited[IATA] = true; //marking first vertex as visited

    while(!queue1.empty()) {
        string s = queue1.front();
        vec.push_back(s);
        vector<Vertex> verts = graph.getAdjacentVerticies(IataToVertex[s]);
        for (Vertex vert : verts) {
            if ((!visited[vert.getIATA()])) {
                visited[vert.getIATA()] = true;
                queue1.push(vert.getIATA());
                count++;
            }
        }
        queue1.pop();
    }
    return vec;
}

vector<string> OpenFlights::Dijkstra(string start, string end) {
    map<string, string> map = Dijkstra(start);

    auto itr = map.find(end);
    vector<string> vec;
    vec.push_back(end);
    while(itr != map.end()) {
        string previous = itr->second;
        vec.push_back(previous);
        itr = map.find(previous);

        if (itr->second.compare("") == 0) {
            reverse(vec.begin(), vec.end());
            return vec;
        }
    }
    reverse(vec.begin(), vec.end());
    return vec;
}

map<string, string> OpenFlights::Dijkstra(string start) {
    map<string, double> distance; // IATA to double val of distance
    map<string, bool> visited; // IATA to bool visted/unvisted for each node
    map<string, string> previous;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> queue;

    queue.push(make_pair(0.0, start));

    for (Vertex v : graph.getVertices()) {
        distance[v.getIATA()] = INT_MAX;
        visited[v.getIATA()] = false;
        previous[start] = "";
    }
    distance[start] = 0;
    previous[start] = "";

    
    while (!queue.empty()) {
        pair<double, string> min = queue.top(); //Extract MIN from queue
 
        queue.pop();
        Vertex vert = IataToVertex[min.second];
        for (Vertex v : graph.getAdjacentOutgoingVertices(vert)) {      // for each unvisited neighbour V of min
            Edge edge(vert, v);
            double temp_dist = distance[vert.getIATA()] + edge.getWeight();
            if (temp_dist < distance[v.getIATA()] && visited[v.getIATA()] == false) { 
                distance[v.getIATA()] = temp_dist;
                visited[v.getIATA()] = true;
                previous[v.getIATA()] = vert.getIATA();
                queue.push(make_pair(temp_dist, v.getIATA()));
            }       
        }
    }
    return previous;
}

double OpenFlights::BetweennessCentrality(string IATA) {

    int num_shortest_paths = 0; //counter for the total number of shortest paths in the graph
    int num_paths_through_node = 0; //counter for the number of shortest paths that go through the specified node

    for (unsigned int i = 0; i < graph.getVertices().size() - 1; i++) {
        Vertex v1 = graph.getVertices().at(i);
        for (unsigned int j = i; j < graph.getVertices().size(); j++) {
            Vertex v2 = graph.getVertices().at(j);
            vector<string> path = Dijkstra(v1.getIATA(), v2.getIATA()); //find the shortest path between every single node
            num_shortest_paths++;
            for (string p : path) {
                if (p == IATA) { //check if path passes through the vertex
                num_paths_through_node++;
                }
            }
        }
    }
    return num_paths_through_node/num_shortest_paths; 
}

Graph OpenFlights::getGraph() {
    return graph;
}

map<string, Vertex> OpenFlights::GetIataToVertex() {
    return IataToVertex;
}

