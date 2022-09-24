#include <iostream>
#include <cctype>
#include "openflights.h"
#include "graph.h"
#include "edge.h"
#include <string>
#include <vector>
using namespace std;

int main()
{
    std::string str = "data/airports.txt"; //dataset that can be changed
    std::string str1 = "data/routes.txt";  //dataset that can be changed
    OpenFlights openflights(str, str1);

    string bfsSource;
    string userInput;
    string indicator;

    bool properCode = false;
    bool properCode2 = false;


    string sourceCode;
    string destinationCode;
    string algIndicator;
    bool validInput = false;
    int counter = 0;

    while (validInput == false) {
        
        //if they want bfs (connected airports), then have a check that null is typed for destination airport --> otherwise false
        std::cout << "Welcome to our Flight Planner! Please enter your source airport IATA code!" << endl;
        cin >> sourceCode;
        std::transform(sourceCode.begin(), sourceCode.end(),sourceCode.begin(), ::toupper);

        std::cout << "If you would like to see if two airports are connected using BFS, enter 1. If you would like to find the shortest path to a destination, enter 2. If you want to quit press 0." << endl;
        cin >> algIndicator;

        if (algIndicator.compare("0") == 0) {
            exit(1);
        }
        if (algIndicator.compare("2") == 0) {
            std::cout << "Please enter your destination airport IATA code!" << endl;
            cin >> destinationCode;
            std::transform(destinationCode.begin(), destinationCode.end(),destinationCode.begin(), ::toupper);
        }

        //Check if user input source code, destination code, and algorithm indicator is valid.
        bool validSourceCode = false;
        bool validDestCode = false;
        validInput = true;

        map<string, Vertex> map = openflights.GetIataToVertex();
        for (const auto &myPair : map) {
            string str = myPair.first;

            if (sourceCode.compare(str) == 0) {
                validSourceCode = true;
            }

            if (destinationCode.compare(str) == 0) {
                validDestCode = true;
            }
        }

        if ((algIndicator.compare("1") != 0) && (algIndicator.compare("2") != 0)) {
            validInput = false;
        }

        if (algIndicator.compare("1") == 0) {
            if (!validSourceCode) {
                validInput = false;
            }
        } else if (algIndicator.compare("2") == 0) {
            if (!validSourceCode || !validDestCode) {
                validInput = false;
            }
        }


        //done with input checks
        if (validInput == true) {
            if (algIndicator.compare("1") == 0) {
                std::cout << "Please enter your destination airport IATA code!" << endl;
                string stop_point;
                cin >> stop_point;
                std::transform(stop_point.begin(), stop_point.end(),stop_point.begin(), ::toupper);
                vector<string> ret = openflights.BFS(sourceCode);
                bool yes = false;
                for (size_t i = 0; i < ret.size(); i++) {
                    if (ret[i].compare(stop_point) == 0) {
                        yes = true;
                        i = ret.size();
                    }
                }
                if (yes == true) {
                    std::cout << sourceCode << " and " << stop_point << " are connected and there are flights between them!" << endl;
                } else {
                    std::cout << sourceCode << " and " << stop_point << " are not connected!" << endl;

                }
                
            } else {
                vector<string> ret = openflights.Dijkstra(sourceCode, destinationCode);
                    string str;
                    int counter = 0;
                    double distance_traveled = 0;
                    for (size_t i = 0; i < ret.size(); i++) {
                        if (i + 1 < ret.size()) {
                            Vertex vert1 = map[ret[i]];
                            Vertex vert2 = map[ret[i + 1]];
                            Edge edge(vert1, vert2);
                            distance_traveled += edge.getWeight();
                        }
                        
                        if (counter == (int)(ret.size() - 1)) {
                            str += ret[i];
                        } else {
                            str += ret[i] + ", ";
                            counter++;
                        }  
                    }
                    std::cout << "Here is your shortest flight path: " << str << endl;
                    std::cout << "Distance traveled: " << distance_traveled << " km. " << endl;
            }
            
        } else if (validInput == false) {
            counter++;
            std::cout << "Invalid response. Please make sure you are entering a valid input." << endl;
            
            if (counter > 2) {
                std::cout << "Please rerun the program. Too many invalid inputs have been inputted." << endl;
                exit(1);
            }
        }
        
    }
    return 0;
}

    
