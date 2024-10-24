/*******************************************************************************
Program Name: Project 4
Programmer: Karigan Stewart
Date: 10/24/2024
Description: This program reads the city names, flight request, and flight
information for BlueSky airport. It is to prompt the user for a origin and
destination city. The program then builds a path itinirary to display
what flights need to be taken to reach destination along with the flight
information and the total cost of trip.
*******************************************************************************/

#include <iostream>
#include <fstream>
#include "FlightMapClass.h"

using namespace std;


int main() {
    FlightMapClass flightMap;
    ifstream cityFile("cities.dat");
    ifstream flightFile("flights.dat");

    //Checks if files open correctly 
    if (!cityFile || !flightFile) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    flightMap.ReadCities(cityFile);    // Reads and stores cities
    flightMap.BuildMap(flightFile);    // Reads and stores flight information


    string origin, destination;
    while (true) {
        cout << "Enter origin city (or 'exit' to quit): ";    // Asks for origin city
        cin >> origin;
        if (origin == "exit")                                 // If exit is entered it ends the program
            break;                           

        cout << "Enter destination city: ";                   // Asks for destination city
        cin >> destination;

        flightMap.FindPath(origin, destination);
    }

    return 0;
}
