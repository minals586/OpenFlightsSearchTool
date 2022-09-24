#include <cmath>
#include <iostream>
#include <math.h>
#include "edge.h"

using namespace std;

Edge::Edge(Vertex start_, Vertex end_) {
    start = start_;
    end = end_;
    calculateWeight();
}

void Edge::calculateWeight() {
    //use Haversine formula to calculate the distance between two points given latitude and longitude
    //convert string latitudes and longitudes to doubles
    // https://www.movable-type.co.uk/scripts/latlong.html
    double rad_conversion = M_PI/180;

    double lat1 =  rad_conversion * stod(start.getLat());
    double lon1 = rad_conversion * stod(start.getLon());
    double lat2 = rad_conversion * stod(end.getLat());
    double lon2 = rad_conversion * stod(end.getLon());
    
    double delta_lat = (lat2 - lat1);
    double delta_lon = (lon2-lon1);

    double R = 6371; 

    double a = pow(sin(delta_lat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(delta_lon/2), 2);
    double c = 2 * atan2(sqrt(a), sqrt((1-a)));
    double d = R * c;

    weight = d;
}

Vertex Edge::getStart() {
    return start;
}

Vertex Edge::getEnd() {
    return end;
}

double Edge::getWeight() {
    return weight;
}
