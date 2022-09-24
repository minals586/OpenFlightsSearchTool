#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <map>
#include "../openflights.h"
#include "../graph.h"
#include "../edge.h"
#include <unordered_set>
#include <string>
using namespace std;

	std::string str = "data/airports.txt";
    std::string str1 = "data/routes.txt";
    OpenFlights openflights(str, str1);
    map<string, Vertex> map1 = openflights.GetIataToVertex();
    Graph g = openflights.getGraph();
    vector<string> vec = openflights.BFS("SFO");

TEST_CASE("Graph Creation - Edges", "[weight=10][part1]") {
    SECTION("Edges") {
	    REQUIRE(66607 == openflights.getGraph().getEdges().size());
    }
}

TEST_CASE("Graph Creation - Vertex", "[weight=10][part1]") {
    SECTION("Vertices") {
	    REQUIRE(6074 == openflights.getGraph().getVertices().size());
    }
}

TEST_CASE("BFS - SFO connections", "[weight=10][part1]") {
    SECTION("CLT is a node connected to SFO") { //line 5003 in routes.dat
    	REQUIRE("CLT" == vec[1]);
    }
    SECTION("MIA is a node connected to SFO") { //line 6103 in routes.dat
    	REQUIRE("MIA" == vec[8]);
    }
    SECTION("The first node is the starting node") {
    	REQUIRE("SFO" == vec[0]);
    }
}

TEST_CASE("Distance Tests", "[weight=10][part1]") {
    SECTION("Distance between CLT and SFO") {
        Vertex v1 = map1["CLT"];
        Vertex v2 = map1["SFO"];
        Edge edge(v1, v2);
        int distance = edge.getWeight();
        REQUIRE(3686 == distance);
    }
}

TEST_CASE("Ariports are visited once in BFS", "[weight=10][part1]") {
    SECTION("No repeating airports in BFS") {
        unordered_set<string> set;

        for (size_t i = 0; i < vec.size(); i++) {
            REQUIRE(set.find(vec[i]) == set.end());
            set.emplace(vec[i]);
        }
    }
}

vector<string> vecLax = openflights.BFS("LAX");
Vertex lax = map1["LAX"]; 
vector<Vertex> v = g.getAdjacentVerticies(lax); 

TEST_CASE("BFS - LAX", "[weight=10][part1]") {
    SECTION("The first node is the starting node") {
    	REQUIRE("LAX" == vecLax[0]);
    }
    SECTION("LAS is a node connected to LAX") {
    	REQUIRE("LAS" == vecLax[1]);
    }
    SECTION("Checking adjacent vertex order #1") { 
        REQUIRE(v[1].getIATA() == vecLax[1]);
    }

    SECTION("Checking adjacent vertex order #2") {
        REQUIRE(v[5].getIATA() == vecLax[5]);
    }
}

TEST_CASE("Check LAX is not connected to Iceland(HFN)", "[weight=10][part1]") {
    SECTION("No connection between LAX and HFN") {
        int counter = 0;
        for (size_t i = 0; i < vecLax.size(); i++) {
            if(vecLax[i].compare("HFN") == 0) {
                counter++;
            }
            //cout << vecLax[i] << endl;
        }
        REQUIRE(counter == 0);
    }
}

TEST_CASE("Distance in edge weight", "[weight=10][part1]") {
    
    SECTION("Distance between CLT and ORD") {
        Vertex v1 = map1["CLT"];
        Vertex v2 = map1["SFO"];
        Edge edge(v1, v2);
        int distance = edge.getWeight();
        REQUIRE(3686 == distance);
    }

}


TEST_CASE("Checks that BFS only visits nodes once", "[weight=10][part1]") {
    SECTION("No repeating airports in ORD") {
        unordered_set<string> set;

        for (size_t i = 0; i < vecLax.size(); i++) {
            REQUIRE(set.find(vecLax[i]) == set.end());
            set.emplace(vecLax[i]);
        }
    }
}



vector<string> vecJFK = openflights.BFS("JFK");
Vertex jfk = map1["JFK"]; 
vector<Vertex> vjfk = g.getAdjacentVerticies(jfk); 

TEST_CASE("BFS - JFK", "[weight=10][part1]") {
    SECTION("The first node is the starting node") {
    	REQUIRE("JFK" == vecJFK[0]);
    }
    SECTION("LAS is a node connected to JFK") {
    	REQUIRE("EZE" == vecJFK[1]);
    }
    SECTION("Checking adjacent vertex order #1") { 
        REQUIRE(vjfk[1].getIATA() == vecJFK[1]);
    }
}

TEST_CASE("Distance in edge weight JFK example", "[weight=10][part1]") {
    
    SECTION("Distance between JFK and ORD") {
        Vertex v1 = map1["JFK"];
        Vertex v2 = map1["ORD"];
        Edge edge(v1, v2);
        int distance = edge.getWeight();
        REQUIRE(1187 == distance);
    }

}

TEST_CASE("Dijstkra") {

    SECTION("Testing distance between CMI and GKA") {
        Vertex cmi = map1["CMI"];
        Vertex ord = map1["ORD"];
        Vertex nrt = map1["NRT"];
        Vertex pom = map1["POM"];
        Vertex gka = map1["GKA"];
        
        Edge edge(cmi, ord);
        Edge edge1(ord, nrt);
        Edge edge2(nrt, pom);
        Edge edge3(pom, gka);

        int sum = edge.getWeight() + edge1.getWeight() + edge2.getWeight() + edge3.getWeight();
        REQUIRE(sum == 15794);

    }
    
    SECTION("Checking path between CMI and GKA") {
        vector<string> ret = openflights.Dijkstra("CMI", "GKA");
        REQUIRE(ret[0] == "CMI");
        REQUIRE(ret[1] == "ORD");
        REQUIRE(ret[2] == "NRT");
        REQUIRE(ret[3] == "POM");
        REQUIRE(ret[4] == "GKA");
    }
}

TEST_CASE("Dijstkra path correct") {

    SECTION("Direct flight: MIA and JFK") {
        vector<string> ret = openflights.Dijkstra("MIA", "JFK");
        
        REQUIRE(ret[0] == "MIA");
        REQUIRE(ret[1] == "JFK");
    }

    SECTION("Non direct flight: ATL and DEL") {
        vector<string> ret = openflights.Dijkstra("ATL", "DEL");
        
        REQUIRE(ret[0] == "ATL");
        REQUIRE(ret[1] == "ORD");
        REQUIRE(ret[2] == "DEL");
    }

    SECTION("Long non direct flight: IXC and ITH") {
        vector<string> ret = openflights.Dijkstra("IXC", "ITH");

        
        REQUIRE(ret[0] == "IXC");
        REQUIRE(ret[1] == "DEL");
        REQUIRE(ret[2] == "EWR");
        REQUIRE(ret[3] == "ITH");

    }
}

TEST_CASE("Disconnected flight") {

    SECTION("Disconnected flight: ATL and YAV") {
        vector<string> ret = openflights.Dijkstra("ATL", "YAV");

        //only prints out destination when there are no connecting flights
        REQUIRE(ret[0] == "YAV");
    }
}




    

    
