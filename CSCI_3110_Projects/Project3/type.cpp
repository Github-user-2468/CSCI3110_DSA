#include "type.h"
using namespace std;

// Define operator overloads for the FlightRecord struct

/**************************************************************************
This function takes two FlightRecords object and compares then to
see if they are equal. The function will return a true/false value 
whether they are equal or not
**************************************************************************/

bool FlightRecord::operator==(const FlightRecord& rhs) const {
    return flightNumber == rhs.flightNumber;                      // Compare flight numbers for equality
}

/**********************************************************************
The function overloads the < operator to determine the order
in which the FlightRecord's flightNumber objects order
**********************************************************************/
bool FlightRecord::operator<(const FlightRecord& rhs) const {
    return flightNumber < rhs.flightNumber;                       // Compare flight numbers to determine order
}


/**************************************************************************
This function overloads the = operator to copy objects from one 
FlightRecord object to another FlightRecord object
***************************************************************************/
FlightRecord& FlightRecord::operator=(const FlightRecord& rhs) {
     // Check for self-assignment
    if (this != &rhs) { 
       // Copy the member variables from the other FlightRecord
        flightNumber = rhs.flightNumber;
        origin = rhs.origin;
        destination = rhs.destination;
        price = rhs.price;
    }
    return *this; // Return the current object to allow for chained assignments
}

/***************************************************************************
This function overloads the << operator to display the Orgin and 
Destination flight information in a table format
***************************************************************************/
ostream& operator<<(ostream& os, const FlightRecord& record) {
  // Format the output to show flight number, origin, destination, and price
    os << record.flightNumber << " " 
       << record.origin << " " 
       << record.destination << " $" 
       << record.price;
    return os;       // Return the output stream
}
