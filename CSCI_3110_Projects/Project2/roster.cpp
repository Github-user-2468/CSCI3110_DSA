#include <string>
#include "student.h"
#include "roster.h"
#include <iomanip>
#include <fstream>
using namespace std;

Roster::Roster(string courseName) : courseName(courseName), studentNum(0) {};

/*********************************************************************
This function reads the grades.dat file and stores the information
in the file and store in an array of Student class objects as 
defined in student.h and student.cpp
*********************************************************************/
void Roster::readStudentRecord(string filename) {
	ifstream file(filename);
	//checks to see if file opens correctly 
	if (!file) {			
		cerr << "Error opening file" << endl;
		return;
		}

	string headerLine;
	getline(file, headerLine);  // Skip the header line
	getline(file, headerLine);

//Reading from file
	while (file >> students[studentNum]) {
		students[studentNum].ComputeTotal();    //Computes the total for that student
		students[studentNum].ComputeGrade();    //Computes the letter grade for the computed total
		studentNum++;
	}
	file.close();
}

/*********************************************************************
Returns the number of students recorded
*********************************************************************/
int Roster::GetStudentCount() const {
	return studentNum;
}

/*********************************************************************
This function collects a string input from the user and checls
if the classId entered is a valid ID found in the file. The function
returns a bool value. True = found ; False = not found
*********************************************************************/
bool Roster::isValid(string id) const {
	for (int i = 0; i < studentNum; i++) {
		if (students[i].getID() == id) {
			return true;
		}
	}
	return false;    
}

/*********************************************************************
This funcition is to display the value of a single student
*********************************************************************/
void Roster::ShowOneStudent(string id) const {
	for (int i = 0; i < studentNum; i++){
		if (students[i].getID() == id) {
			students[i].DisplayInfo();
			return;
		}
	}
  //if the ID could not be found
	cout << "Error the student with id " << id << "could not be found" << endl;
}

/*********************************************************************
This function an overloaded << operator and is used to output the
information in the file of ALL the students data 
*********************************************************************/
ostream& operator << (ostream& os, const Roster& oneClass) {
	os << right << setw(10) << "ID" << setw(15) << "Name" << setw(8) << "CLA" << setw(8) << "OLA" << setw(8) << "Quiz" << setw(15) << "Homework"
		<< setw(8) << "Exam" << setw(8) << "Bonus" << endl;

	os  << endl;
	for (int i = 0; i < oneClass.studentNum; i++) {
		os << right << setw(10) << oneClass.students[i].getID() << setw(15) << oneClass.students[i].getName()
			<< setw(8) << oneClass.students[i].getScore(Student::CLA)
			<< setw(8) << oneClass.students[i].getScore(Student::OLA)
			<< setw(8) << oneClass.students[i].getScore(Student::QUIZ)
			<< setw(15) << oneClass.students[i].getScore(Student::HOMEWORK)
			<< setw(8) << oneClass.students[i].getScore(Student::EXAM)
			<< setw(8) << oneClass.students[i].getScore(Student::BONUS) << endl;
	}
	return os;
}
