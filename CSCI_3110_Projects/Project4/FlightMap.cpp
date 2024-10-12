#include "flightMapClass.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <iomanip>


using namespace std;

FlightMapClass::FlightMapClass() : size(0), map(nullptr) {}

FlightMapClass::FlightMapClass(const FlightMapClass& f)
    : size(f.size), cities(f.cities), visited(f.visited) {
    map = new list<flightRec>[size];
    for (int i = 0; i < size; ++i) {
        map[i] = f.map[i];
    }
}

FlightMapClass::~FlightMapClass() {
    delete[] map;
}

void FlightMapClass::ReadCities(ifstream& myCities) {
    string city;
    string headerLine;
    getline(myCities, headerLine);
    while (getline(myCities, city)) {
        cities.push_back(city);
    }
    size = cities.size();
    visited.resize(size, false); // Resize visited vector
    sort(cities.begin(), cities.end());
    map = new list<flightRec>[size];
}

void FlightMapClass::BuildMap(ifstream& myFlights) {
    int flightNumber;
    string origin, destination;
    int price;
    while (myFlights >> flightNumber >> origin >> destination >> price) {
        flightRec record = { origin, flightNumber, destination, price };
        int originIndex = GetCityNumber(origin);
        map[originIndex].push_back(record);
    }
}

void FlightMapClass::DisplayMap() {
    cout << "Flight Map:\n";
    for (int i = 0; i < size; ++i) {
        for (const auto& flight : map[i]) {
            cout << flight << endl;
        }
    }
}

bool FlightMapClass::CheckCity(string cityName) const {
    return find(cities.begin(), cities.end(), cityName) != cities.end();
}

void FlightMapClass::DisplayAllCities() const {
    cout << "Cities served:\n";
    for (const auto& city : cities) {
        cout << city << endl;
    }
}

void FlightMapClass::MarkVisited(int city) {
    if (city >= 0 && city < visited.size()) {
        visited[city] = true;
    }
}


void FlightMapClass::UnvisitAll() {
    fill(visited.begin(), visited.end(), false);
}

bool FlightMapClass::IsVisited(int city) const {
    return visited[city];
}

int FlightMapClass::GetCityNumber(string cityName) const {
    auto it = find(cities.begin(), cities.end(), cityName);
    return (it != cities.end()) ? distance(cities.begin(), it) : -1;
}

string FlightMapClass::GetCityName(int cityNumber) const {
    return cities[cityNumber];
}

void FlightMapClass::FindPath(string originCity, string destinationCity) {
    if (!CheckCity(originCity)) {
        cout << "Sorry, BlueSky airline does not serve " << originCity << ".\n";
        return;
    }
    if (!CheckCity(destinationCity)) {
        cout << "Sorry, BlueSky airline does not serve " << destinationCity << ".\n";
        return;
    }

    UnvisitAll(); // Clear visited cities

    int originIndex = GetCityNumber(originCity);
    int destinationIndex = GetCityNumber(destinationCity);

    // Check if indices are valid
    if (originIndex == -1 || destinationIndex == -1) {
        cout << "Invalid city index.\n";
        return;
    }

    queue<int> cityQueue;
    vector<int> parent(size, -1); // To reconstruct the path
    cityQueue.push(originIndex);
    visited[originIndex] = true;

    // BFS to find the path
    bool pathFound = false;

    while (!cityQueue.empty()) {
        int currentCity = cityQueue.front();
        cityQueue.pop();

        // Check if we have reached the destination
        if (currentCity == destinationIndex) {
            pathFound = true;
            break;
        }

        // Iterate through adjacent flights
        for (const auto& flight : map[currentCity]) {
            int nextCity = GetCityNumber(flight.destination);
            if (nextCity != -1 && !IsVisited(nextCity)) {
                visited[nextCity] = true;
                cityQueue.push(nextCity);
                parent[nextCity] = currentCity; // Track the parent for path reconstruction
            }
        }
    }

    // Display the results
    if (pathFound) {
        vector<flightRec> flightPath;
        int currentCity = destinationIndex;

        // Reconstruct the flight path
        while (currentCity != originIndex) {
            int parentCity = parent[currentCity];
            for (const auto& flight : map[parentCity]) {
                if (GetCityNumber(flight.destination) == currentCity) {
                    flightPath.push_back(flight);
                    break;
                }
            }
            currentCity = parentCity;
        }

        // Output the itinerary
        cout << "Request is to fly from " << originCity << " to " << destinationCity << ".\n";
        cout << "BlueSky airline serves between these two cities.\n";
        cout << "The flight itinerary is:\n";
        cout << left << setw(10) <<"Flight #" << setw(20) <<"From" << setw(20) << "To" <<"Cost\n";

        double totalCost = 0.0;
        // Reverse the path to display from origin to destination
        for (auto it = flightPath.rbegin(); it != flightPath.rend(); ++it) {
            cout << left <<  setw(10) <<  it->flightNum 
                << setw(20) << it->origin 
                << setw(20) << it->destination << "$"
                << setw(20) << it->price << "\n";
            totalCost += it->price;
        }
        cout << right << setw(51) << "Total:  $" << totalCost << "\n\n";
    }
    else {
        cout << "Sorry, BlueSky airline does not fly from " << originCity << " to " << destinationCity << ".\n";
    }
}