#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Define struct flightRec
struct flightRec {
    string origin;
    int flightNum;
    string destination;
    double price;

    bool operator<(const flightRec& rhs) const; // Overloaded < operator
    bool operator==(const flightRec& rhs) const; // Overloaded == operator
    friend ostream& operator<<(ostream& os, const flightRec& f); // Overloaded output operator
};

#endif // TYPE_H
