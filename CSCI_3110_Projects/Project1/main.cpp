/*********************************************************************************************************
Programmer: Karigan Stewart
Date: 09/08/2024
Description:This program reads from grades.dat and presents the data in a table format. The program
then takes input from the user, retrieving a single students classID and searches for that students data
If the information is found it then displays the students data. The program then sorts the information
of all students in alphabetical order and displays in a table format. 
*********************************************************************************************************/
#include <cassert>  // assert
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
#include "type.h"

// Function Prototypes
int CountStudents(ifstream& file);                                                    // Used to dynamically allocate space
void ReadStudentData(ifstream& file, StudentType* roster, int numStudents);           // Used to read all student data from file
void DisplayStudents(const StudentType roster[], int numStudents);                    // Used to Display ALL student data
int LinearSearch(const StudentType roster[], int numStudents, const string& itemToLookfor);  // Used to search for a certain student according to C number
void SortStudents(StudentType roster[], int numStudents);                             // Sorts students data into alphabetical order
void DisplayStudentData(const StudentType roster[], int studentIndex);                // Displays a certain student's data 
string GetValidStudentID(const StudentType roster[], int numStudents);                 // Checks if the input student ID is valid

int main() {

    string itemToLookfor;   // Holds classID given by the user to search for student
    int studentIndex = 0;   // Holds the index of the student to be found

    // Opens the file and ensures it opens correctly 
    ifstream file("grades.dat");
    assert(file);  

    // Count the number of students for memory allocation
    int numStudents = CountStudents(file);


    StudentType* roster = new StudentType[numStudents];  // Allocate memory dynamically

    // Reopen the file to read student data
    file.clear(); // Clear flags
    file.seekg(0); // Move to the beginning of the file

    // Reads Student Data
    ReadStudentData(file, roster, numStudents);
    // Displays ALL student data in table format
    DisplayStudents(roster, numStudents);

    // Get a valid student ID from the user
    itemToLookfor = GetValidStudentID(roster, numStudents);

    // Find the index of the valid student ID
    studentIndex = LinearSearch(roster, numStudents, itemToLookfor);

    // Displays the specific student's data according to the output for linear search
    DisplayStudentData(roster, studentIndex);


    // Sorts the students by alphabetical order
    cout << "Sorting student records by name ..... " << endl;
    SortStudents(roster, numStudents);
    DisplayStudents(roster, numStudents);   // Displays in alphabetical order

    // Free dynamically allocated memory
    delete[] roster;
    // Close the file 
    file.close();

    return 0;
}

/********************************************************* FUNCTION DEFINITIONS ********************************************************/


/**************************************************************************
DESCRIPTION: This function could the rows of student reconds to determine
how many students there are in record. The purpose of this is to
be able to dynammically allocate just enough memory for the structure
of student records
Pre: The file needs to be open and ready to read from
post: An count of students is returned to tell the main program how
many student records there are
************************************************************************/

int CountStudents(ifstream& file) {
    int count = 0;
    string temp;

    // Skip the header line
    getline(file, temp);

    // Count the lines as each line represents a student
    while (getline(file, temp)) {
        count++;
    }

    return count;
}


/**************************************************************************
DESCRIPTION: This is to read grades.dat and store the file data in the
array of objects.
Pre: The file needs to be open and ready to read from and an array of
objects needs to be defined to hold thed data
post: An array of objects is filled with the student data
************************************************************************/


void ReadStudentData(ifstream& file, StudentType* roster, int numStudents) {
    string headerLine;
    getline(file, headerLine);  // Skip the header line

    //Reads the student data and stores it in the array of objects
    for (int i = 0; i < numStudents; i++) {
        file >> roster[i].classID >> roster[i].studentName >> roster[i].claScore
            >> roster[i].olaScore >> roster[i].quizScore >> roster[i].homeworkScore
            >> roster[i].examScore >> roster[i].bonusPoints;
    }
}


/**************************************************************************
DESCRIPTION: This function is to display all of the students data in
a table format.
Pre: The array of objects need to be filled and ready for display
post: A table is displayed to the user filled with ALL the students data
************************************************************************/


void DisplayStudents(const StudentType roster[], int numStudents) {
    
    //Displays header for table
    cout << "\n\nHere is the information of the " << numStudents << " students:" << endl << endl;

    cout << left << setw(15) << "Class ID" << setw(15) << "Name"
        << setw(10) << "CLA" << setw(10) << "OLA" << setw(10)
        << "Quiz" << setw(15) << "Homework" << setw(10) << "Exam"
        << setw(10) << "Bonus" << endl << endl;
   

    //Steps through array to display ALL the students data
    for (int i = 0; i < numStudents; i++) {
        cout << left << setw(15) << roster[i].classID << setw(15) << roster[i].studentName
            << setw(10) << roster[i].claScore << setw(10) << roster[i].olaScore
            << setw(10) << roster[i].quizScore << setw(15)
            << roster[i].homeworkScore << setw(10) << roster[i].examScore
            << setw(10) << roster[i].bonusPoints << endl;
    }
}



/**************************************************************************
DESCRIPTION: This function is to take the class ID taken from the user
and search the .classID of all the students to return the location of
the specfic students records
Pre: The array of objects roster[].classID needs to be filled and
ready to read from
post: The function returns the index(location) of the students records
************************************************************************/


int LinearSearch(const StudentType roster[], int numStudents, const string& itemToLookfor) {
    for (int index = 0; index < numStudents; index++) {
        if (itemToLookfor == roster[index].classID) {   //Compares the item to look for with each index in the classID array
            return index;
        }
    }
    return -1;
}


/**************************************************************************
DESCRIPTION: This function uses bubble sort to step through the array
and compare the ASCII values of the student names to sort them in
alphabetical order.
Pre: The array of objects needs to be filled and read to read from
post:The array of objects is returned sorted by alphabetical order
************************************************************************/

void SortStudents(StudentType roster[], int numStudents) {
    bool sorted = false;
    int last = numStudents - 1;
    StudentType tmp;

    while (!sorted) {
        sorted = true;
        for (int i = 0; i < last; i++) {
            if (roster[i].studentName > roster[i + 1].studentName) {   //If the value of the index next to the current index is greater; then swap the values
                // Swap the two students
                tmp = roster[i];
                roster[i] = roster[i + 1];
                roster[i + 1] = tmp;
                sorted = false;
            }
        }
        last--;
    }
}


/**************************************************************************
DESCRIPTION: This function is to display the information of the
student found in the linear Search function by their found array index
Pre: The linear Search funtion must have already been called and the
index of that specific students information must have been returned and
a main() variable must be holding that index to input as parameter
post: That specific students data is read and displayed
************************************************************************/


void DisplayStudentData(const StudentType roster[], int studentIndex) {
                 

    cout << "\nInformation for student with ID: " << roster[studentIndex].classID << endl;
    cout << "Student Name: " << roster[studentIndex].studentName << endl;
    cout << "CLA: " << roster[studentIndex].claScore << endl;
    cout << "OLA: " << roster[studentIndex].olaScore << endl;
    cout << "Quiz: " << roster[studentIndex].quizScore << endl;
    cout << "Homework: " << roster[studentIndex].homeworkScore << endl;
    cout << "Exam: " << roster[studentIndex].examScore << endl;
    cout << "Bonus: " << roster[studentIndex].bonusPoints << endl << endl;
}


/**************************************************************************
DESCRIPTION: This function is to get a ClassID number and is to use
the linear search function to ensures that the ClassID is valid. If the
ID is valid it will return the user input for ClassID to be searched and 
returned in main(). If it is not valid it will ask the user to try again 
entering a valid ID number
Pre: The linear Search funtion must be defined and ready to call and a 
variable in main must be defined to accept the return statement of this
function.
post: This function will return the valid class ID to be called later in
main
************************************************************************/

string GetValidStudentID(const StudentType roster[], int numStudents) {
    string itemToLookfor;
    int studentIndex;

    do {
        cout << "\nPlease enter a valid student ID: ";
        getline(cin, itemToLookfor);

        studentIndex = LinearSearch(roster, numStudents, itemToLookfor);

    } while (studentIndex < 0);    //If a -1 (false) is returned try again

    return itemToLookfor;
}
