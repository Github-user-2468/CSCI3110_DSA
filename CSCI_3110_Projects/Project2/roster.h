/*
 * File:	Roster.h
 *
 * Purpose: This file gives the full definition of the class Roster.
 */

#ifndef __CSCI3110_ROSTER__
#define __CSCI3110_ROSTER__

#include <string>
#include "student.h"
using namespace std;

class Roster
{
	public:

    // a value constructor, the parameter is the course name
	// Create an empty roster, i.e. studentNum = 0 for
	// a specific course
	Roster(string courseName);

	// This function reads student information from a file
	// The parameter is a file name
	// post-condition: 
	//		students contains student information read from the file
	//		studentNum is the number of students read from the file	
	void readStudentRecord(string filename);

	// This function returns the number of students in the class roster  
    // post-condition: the studentNum value is returned
    int GetStudentCount() const;

    // This function determines whether there is a student with "id" in the class roster
    // post-condition: if there is a student in class with this "id", true is returned
    //                 Otherwise, false is returned
    bool isValid(string id) const;

    // This function displays all the information of one student, one value per line
    // This function also displays the total score and letter grade of the student with the id given
    // pre-condition: a valid user id is provided
    // post-condition: All information of the student with the given id is displayed, 
	//                 one value per line with label
    void ShowOneStudent(string id) const;

    // This function prints out all the information (exclude total score and letter grade) for
    // all the students in the class
    // The information is display in a table format, one student per row
    friend ostream & operator<< (ostream& os, const Roster& oneClass);

    //*****************************************
	//Add your functions here if necessary
	//*****************************************

	private:
		static const int	MAX_NUM = 90;	// The maximum # of students of a class
										// Class constant. All objects share the same copy
		string			  	courseName;	// THe name of the course
		int				  	studentNum;	// Actual Student #
		Student	  			students[MAX_NUM]; // The array of student objects
};
#endif
