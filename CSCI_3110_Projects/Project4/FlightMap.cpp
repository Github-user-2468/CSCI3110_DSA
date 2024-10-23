#include "flightMapClass.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <iomanip>


using namespace std;

//Default Constructor
FlightMapClass::FlightMapClass() : size(0), map(nullptr) {}

//Copy Constructor
FlightMapClass::FlightMapClass(const FlightMapClass& f)
    : size(f.size), cities(f.cities), visited(f.visited) {
    map = new list<flightRec>[size];
    for (int i = 0; i < size; ++i) {
        map[i] = f.map[i];
    }
}

//Destructor 
FlightMapClass::~FlightMapClass() {
    delete[] map;
}

/********************************************************************
This function reads cities.dat and fills the cities vector with
the infomation in the file. It also finds the size of the cities
vector and updates the visited vector to fit the size of the cities
vector. The function then sorts the cities vector alphabetically.
The map vector is then dynamically allocated enough memory space
to hold the flight records for each city
*******************************************************************/
void FlightMapClass::ReadCities(ifstream& myCities) {
    string city;
    string headerLine;
    getline(myCities, headerLine);         // Ignores the first line
    
    while (getline(myCities, city)) {     // Reads the cities from cities.dat
        cities.push_back(city);
    }
    size = cities.size();                  // Holds the size ofo the cities vector (Number of cities)
    visited.resize(size, false);           // Resize visited vector
    sort(cities.begin(), cities.end());    // Sorts the cities vector alphabetically 
    map = new list<flightRec>[size];
}

 
/*******************************************************************
This function reads the flight details from flights.dat. This 
function a flightRec structure to hold the information read from 
the file. GetCityNumber is used to get the index of the origin city
The function then adds the flight record to the list map
*******************************************************************/
void FlightMapClass::BuildMap(ifstream& myFlights) {
    int flightNumber;                   // Holds the flight Number
    string origin, destination;         // Holds origin and destination flight names
    int price;                          // Holds price
    while (myFlights >> flightNumber >> origin >> destination >> price) {     // Reads the flight destination
        flightRec record = { origin, flightNumber, destination, price };      // Builds structure to hold flight information
        int originIndex = GetCityNumber(origin);                              // Gets index of origin city 
        map[originIndex].push_back(record);                                   // Builds map list from the flightRec struncture
    }
}


/**************************************************************************
This funciton iterates through map and prints out each cities list.This 
function uses the << overloaded operator.
*************************************************************************/
void FlightMapClass::DisplayMap() {
    cout << "Flight Map:\n";                    
    for (int i = 0; i < size; ++i) {            
        for (const auto& flight : map[i]) {
            cout << flight << endl;
        }
    }
}

/**************************************************************************
This city finds the city and determinesif the cityName exists in the 
cities vector and returns true/false
**************************************************************************/
bool FlightMapClass::CheckCity(string cityName) const {
    return find(cities.begin(), cities.end(), cityName) != cities.end();  // Searches vector from beginning to end
}

/**************************************************************************
This function iteratates over the cities vector and prints each city name
**************************************************************************/
void FlightMapClass::DisplayAllCities() const {
    cout << "Cities served:\n";
    for (const auto& city : cities) {        // Iterates through vector
        cout << city << endl;                // Print cities
    }
}

/**************************************************************************
This function checks if the city is valid before marking it as true.
As true meaning visited
*************************************************************************/
void FlightMapClass::MarkVisited(int city) {
    if (city >= 0 && city < visited.size()) {   
        visited[city] = true;
    }
}

/**************************************************************************
Sets all the cities in the vector as false, meaning unvisited 
*************************************************************************/
void FlightMapClass::UnvisitAll() {
    fill(visited.begin(), visited.end(), false);
}

/**************************************************************************
This function checks to see if the city has been visited and returns 
the entry
*************************************************************************/
bool FlightMapClass::IsVisited(int city) const {
    return visited[city];
}

/**************************************************************************
This function finds the index of the given city name in the cities vector
*************************************************************************/
int FlightMapClass::GetCityNumber(string cityName) const {
    auto it = find(cities.begin(), cities.end(), cityName);               // Finds the city name
    return (it != cities.end()) ? distance(cities.begin(), it) : -1;      // If found return location, if not return -1
}

/**************************************************************************
This funciton returns the city name that cooresponds to the city index
*************************************************************************/
string FlightMapClass::GetCityName(int cityNumber) const {
    return cities[cityNumber];
}

/**************************************************************************
This function first checks for input Validation to ensure that both
cities exist on record. This function locates a route between the 
origin city and the destination city. If a path is found the function
constructs a flight itinerary which includes the flight information and
the costs, as well as the total cost. If no path is found then the 
funxtion returns a message indicating so. 
*************************************************************************/
void FlightMapClass::FindPath(string originCity, string destinationCity) {
   //Input Validation 
    if (!CheckCity(originCity) && !CheckCity(destinationCity)) {      // If destination and origin city dont exist
        cout << "Sorry, BlueSky does not serve " << originCity << " and " << destinationCity << ".\n";
        return;
    }
    else if (!CheckCity(originCity)) {     // If origin city doesnt exist
        cout << "Sorry, BlueSky airline does not serve " << originCity << ".\n";
        return;
    }
    else if (!CheckCity(destinationCity)) { // If the destination city doesnt exist
        cout << "Sorry, BlueSky airline does not serve " << destinationCity << ".\n";
        return;
    }

    UnvisitAll();   // Clear visited cities

    int originIndex = GetCityNumber(originCity);              // Gets index of origin city 
    int destinationIndex = GetCityNumber(destinationCity);    // Gets index of destinatino city 

    // Check if indexes are valid
    if (originIndex == -1 || destinationIndex == -1) {      
        cout << "Invalid city index.\n";
        return;
    }

    queue<int> cityQueue;         // Represent city indexes
    vector<int> parent(size, -1); // To reconstruct the path
    cityQueue.push(originIndex);  // Pushes index of origin city
    visited[originIndex] = true;  // Marks origin city as visited

    
    bool pathFound = false;


    while (!cityQueue.empty()) {
        int currentCity = cityQueue.front();  // Gets city at front of queue to be processed
        cityQueue.pop();                      // Pops so the next city can be processed 

        // Check if the destination has been reached
        if (currentCity == destinationIndex) {
            pathFound = true;
            break;
        }

        // Iterate through adjacent flights
        for (const auto& flight : map[currentCity]) {          
            int nextCity = GetCityNumber(flight.destination);      // Gets index of the destination city   
            if (nextCity != -1 && !IsVisited(nextCity)) {          // If the city has not yet been visited
                visited[nextCity] = true;                          // Marks it as visited
                cityQueue.push(nextCity);                          // Pushes next city to queue                     
                parent[nextCity] = currentCity;                    
            }
        }
    }

    // Display the results
    if (pathFound) {                               // Checks if valid path is found 
        vector<flightRec> flightPath;              // Initializes a vecor to hold the reconstructed flight path
        int currentCity = destinationIndex;        // Start at destination city

        // Reconstruct the flight path
        while (currentCity != originIndex) {          // Continues until orgin city is reached
            int parentCity = parent[currentCity];  
            //Iterates through all the flights in the parent city 
            for (const auto& flight : map[parentCity]) {
                if (GetCityNumber(flight.destination) == currentCity) {
                    flightPath.push_back(flight);   // Adds flight to the flight path. 
                    break;
                }
            }
            currentCity = parentCity;               // Move to parent city for next iteration
        }

      // Output the itinerary
        //Headers
        cout << "Request is to fly from " << originCity << " to " << destinationCity << ".\n";
        cout << "BlueSky airline serves between these two cities.\n";
        cout << "The flight itinerary is:\n";
        cout << left << setw(10) <<"Flight #" << setw(20) <<"From" << setw(20) << "To" <<"Cost\n";

        double totalCost = 0.0;         // Holds the total cost of the flights
       
        // Reverse the path to display from origin to destination
        for (auto it = flightPath.rbegin(); it != flightPath.rend(); ++it) {    
            cout << left <<  setw(10) <<  it->flightNum         // Outputs flight number
                << setw(20) << it->origin                       // Outputs origin flight
                << setw(20) << it->destination << "$"           // Outputs destination flight
                << setw(20) << it->price << "\n";               // Outputs price
            totalCost += it->price;                             // Cacluates total cost 
        }
        cout << right << setw(51) << "Total:  $" << totalCost << "\n\n";  // Outputs total cost for trips
    }
    else {
       // If their is no flight path itinerary
        cout << "Sorry, BlueSky airline does not fly from " << originCity << " to " << destinationCity << ".\n";
    }
}
