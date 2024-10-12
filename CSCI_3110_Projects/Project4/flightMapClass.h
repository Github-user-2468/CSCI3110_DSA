#ifndef FLIGHTMAPCLASS_H
#define FLIGHTMAPCLASS_H

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "type.h"

using namespace std;

class FlightMapClass {
public:
    FlightMapClass();
    FlightMapClass(const FlightMapClass& f);
    ~FlightMapClass();

    void ReadCities(ifstream& myCities);
    void BuildMap(ifstream& myFlights);
    void DisplayMap();
    bool CheckCity(string cityName) const;
    void DisplayAllCities() const;
    void MarkVisited(int city);
    void UnvisitAll();
    bool IsVisited(int city) const;
    bool GetNextCity(string fromCity, string& nextCity);
    int GetCityNumber(string cityName) const;
    string GetCityName(int cityNumber) const;
    void FindPath(string originCity, string destinationCity);

private:
    int size;
    vector<string> cities;
    list<flightRec>* map;
    vector<bool> visited;
};

#endif // FLIGHTMAPCLASS_H
