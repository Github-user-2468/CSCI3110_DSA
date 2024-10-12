#ifndef FLIGHTMAP_H
#define FLIGHTMAP_H

#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "type.h"
using namespace std;


class FlightMap {
public:
    // Default constructor 
    FlightMap();

    // Copy constructor 
    FlightMap(const FlightMap& rhs);

    // Destructor 
    ~FlightMap();

    // Function reads from file and fills cities vector
    void readCities(ifstream& file);

    //Reads fligh information from file and builds adjancy list 
    void readFlights(ifstream& file);

    // Outputs orgin and distination flight infomration 
    friend ostream& operator<<(ostream& os, const FlightMap& map);

private:
    int numCities;                         // Number of cities read from file
    vector<string> cities;                 // Vector to store names of cities
    list<FlightRecord>* flightMap;         // Pointer to an array of lists for flight records
};

#endif // FLIGHTMAP_H
