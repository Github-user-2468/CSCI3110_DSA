#include "FlightMap.h"
#include <iostream>
#include <algorithm>
#include <iomanip> 

using namespace std;

// Default constructor
FlightMap::FlightMap() : numCities(0), flightMap(nullptr) {}

// Copy constructor
FlightMap::FlightMap(const FlightMap& rhs)
    : numCities(rhs.numCities), cities(rhs.cities) {
    // Allocate new array of lists for flight records
        flightMap = new list<FlightRecord>[numCities];
    // Copy each flight list from the other FlightMap
        for (int i = 0; i < numCities; ++i) {
            flightMap[i] = rhs.flightMap[i];
         }
}

// Destructor
FlightMap::~FlightMap() {
    // Free the dynamically allocated memory for flightMap
        delete[] flightMap;
}

/*******************************************************************
This function reads data from the files and stores it in the 
appropriate vector. It also holds a count of the number of cities
read from file. The function then sorts the vector holding the
cities names in alphabetical order
*******************************************************************/
void FlightMap::readCities(ifstream& file) {
    string city;
    string header;
    getline(file, city);

  // Reads each line from the file and add it to the cities vector
    while (getline(file, city)) {
        cities.push_back(city);
    }
  // Set the number of cities based on the number of entries read
    numCities = cities.size();

  // Dynamically allocates array of lists for flight records
    flightMap = new list<FlightRecord>[numCities];

  // Sort the cities alphabetically for display
    sort(cities.begin(), cities.end());
}

/********************************************************************
This function reads flights from a file and builds the adjancy list
using type.h structure 
*********************************************************************/
void FlightMap::readFlights(ifstream& file) {
    int flightNumber;
    string origin, destination;
    double price;

   // Read flight records from the file
    while (file >> flightNumber >> origin >> destination >> price) {
      
      // Creats FlightRecord object
        FlightRecord record = { flightNumber, origin, destination, price };
      
        // Finds index of the origin city in the cities vector
        int originIndex = distance(cities.begin(), find(cities.begin(), cities.end(), origin));
      
        // Add the flight record to the list in the flightMap
        flightMap[originIndex].push_back(record);
    }

    // Sort destinations for each origin city
    for (int i = 0; i < numCities; ++i) {
        flightMap[i].sort([](const FlightRecord& a, const FlightRecord& b) {
            return a.destination < b.destination; // Sort by destination name
            });
    }
}

/*********************************************************************************
This function display the origin and destinition flight information in a table 
format using overloaded << operators 
**********************************************************************************/
ostream& operator<<(ostream& os, const FlightMap& map) {
    // Set up HEADER for the flight information
    os << left << setw(35) << "\nOrigin"
        << setw(30) << "Destination"
        << setw(15) << "Flight"
        << "Price\n";
    os << "==================================================================================================\n\n";

    // Iterate through each city to display its flights
    for (int i = 0; i < map.numCities; ++i) {
        // Create the origin string for the city
        string originString = "From " + map.cities[i] + " to:";

        // Check if there are flights for this city
        if (!map.flightMap[i].empty()) {
            // If there are flights, print each one
            bool printedOrigin = false;

            for (const auto& flight : map.flightMap[i]) {
                if (!printedOrigin) {
                    os << left << setw(35) << originString; // Print the origin
                    printedOrigin = true;
                }
                else {
                    os << setw(35) << ""; // Leave space for the destination line
                }

                // Print the destination details
                os << left << setw(30) << flight.destination     // Print destination
                    << setw(15) << flight.flightNumber           // Print flight number
                    << "$" << flight.price << "\n";              // Print price
            }
        }
        else {
            // If there are no flights, print the origin and leave other fields blank
            os << left << setw(35) << originString
                << setw(50) << "This city has no flights" << endl;         // Indicate no flight availble
        }
    }
    return os; // Return the output stream for chaining
}
