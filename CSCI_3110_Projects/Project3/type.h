#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include <string>
using namespace std;


struct FlightRecord {
    int flightNumber;       //Holds Flight Number
    string origin;          //Holds orgin name
    string destination;     //Holds detination name
    double price;           //Holds price of flight

    
    
    //Compares two flight records
    bool operator==(const FlightRecord& rhs) const;
    //Compares Flight Numbers
    bool operator<(const FlightRecord& rhs) const;
    //Assigns one FlightRecord object to another
    FlightRecord& operator=(const FlightRecord& rhs);
    //Prints flight Record details 
    friend ostream& operator<<(ostream& os, const FlightRecord& record);
};

#endif // TYPE_H
