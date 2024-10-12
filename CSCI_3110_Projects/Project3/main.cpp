#include <iostream>
#include <fstream>
#include "FlightMap.h"
using namespace std;

int main() {
    FlightMap flightMap;

    //opens city names file
    ifstream citiesFile("cities.dat");
    if (!citiesFile) {
            cerr << "Error opening cities.dat\n";
        return 1;
    }
    //Reads the cities fromo the file
    flightMap.readCities(citiesFile);
    citiesFile.close();

    //Opens the file containing flight information 
    ifstream flightsFile("flights.dat");
    if (!flightsFile) {
        cerr << "Error opening flights.dat\n";
        return 1;
    }
    //Reads flight information and builds adjancy list
    flightMap.readFlights(flightsFile);
    flightsFile.close();

    //Uses overloaded << operator to display information in a table format 
    cout << flightMap;

    return 0;
}
