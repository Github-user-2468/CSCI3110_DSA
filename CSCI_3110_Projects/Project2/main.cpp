// 3110Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*****************************************************************************************************************
Program Name: Project2
Programmer: Karigan Stewart
Date: 9-20-24
Description: This program is to read student data from a file and display the data in a table format to the user
The program then asks the user for a valid class ID. Input validation is used to ensure that the input is an
actual class ID  listed in the file. If a valid Id is enter, the data for that student will be outputted. 
***************************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "student.h"
#include "roster.h"
using namespace std; 

int main()
{
    Roster myRoster("CSCI 3110"); 

    //Read student data
    myRoster.readStudentRecord("grades.dat");

    //Gets the total number of students 
    int studentCount;
    studentCount = myRoster.GetStudentCount();

    //Display all students in table format
    cout << "Here is the information for the " << studentCount << " students in class CSCI3110 "<< endl;
    cout << myRoster;   //uses overloaded << to display all student

    //Asks user for class ID
    string id;      //hold user input
    cout << "\nEnter a valid class ID:    ";
    cin >> id;

    //Checks to see if the ID inputted is a valid ID found in the file
    if (myRoster.isValid(id)) {
        myRoster.ShowOneStudent(id);            //If found; shows the data of that student
    }
    else {
        cout << "Student with the class ID " << id << " not found";         //if not found display error message
    }

    return 0;
}

