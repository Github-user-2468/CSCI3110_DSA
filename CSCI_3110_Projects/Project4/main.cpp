#include <iostream>
#include <fstream>
#include "flightMapClass.h"

using namespace std;

int main() {
    FlightMapClass flightMap;
    ifstream cityFile("cities.dat");
    ifstream flightFile("flights.dat");

    if (!cityFile || !flightFile) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    flightMap.ReadCities(cityFile);
    flightMap.BuildMap(flightFile);

    string origin, destination;
    while (true) {
        cout << "Enter origin city (or 'exit' to quit): ";
        cin >> origin;
        if (origin == "exit") break;

        cout << "Enter destination city: ";
        cin >> destination;

        flightMap.FindPath(origin, destination);
    }

    return 0;
}
