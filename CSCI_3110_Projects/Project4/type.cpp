#include "type.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Overloaded operator for comparing flightRec objects by flight number
bool flightRec::operator<(const flightRec& rhs) const {
    return flightNum < rhs.flightNum; // Compare flight numbers
}

// Overloaded operator for checking equality of flightRec objects
bool flightRec::operator==(const flightRec& rhs) const {
    return (origin == rhs.origin && destination == rhs.destination); // Compare origin and destination
}

// Overloaded output operator for displaying flightRec details
ostream& operator<<(ostream& os, const flightRec& f) {
    os << left << setw(10) << f.flightNum
        << setw(15) << f.origin
        << setw(15) << f.destination
        << "$" << f.price;
    return os; // Return the output stream
}
