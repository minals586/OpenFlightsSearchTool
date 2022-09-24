#pragma once

#include <string>
using namespace std;

class Vertex {
    public:
        /**
        * Vertex Class Constructor
        */
        Vertex();

        /**
        * Vertex Custom Constructor
        * @param iata the IATA code of the airport
        * @param lat the latitude of this airport
        * @param lon the longitude of this airport
        */
        Vertex(string iata_, string lat_, string lon_);

        /**
        * Returns the latitude of a vertex
        * @return string of the airport's latitude
        */
        string getLat();

        /**
        * Returns the longitude of a vertex
        * @return string of the airport's longitude
        */
        string getLon();

        /**
        * Returns the IATA code of the airport in the vertex
        * @return string of the airport's IATA code
        */
        string getIATA();
    private:
        string IATA;
        string lat;
        string lon;    
};