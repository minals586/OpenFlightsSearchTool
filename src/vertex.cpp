#include "vertex.h"
#include <string>


Vertex::Vertex(){}

Vertex::Vertex(string iata_, string lat_, string lon_) {
    IATA = iata_;
    lat = lat_;
    lon = lon_;
}

string Vertex::getIATA() {
    return IATA;
}

string Vertex::getLat() {
    return lat;
}

string Vertex::getLon(){
    return lon;
}