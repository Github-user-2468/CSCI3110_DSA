#include "student.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


//default constructor
Student::Student() : id(""), name(""), total(0),letterGrade('F') {
	for (int i = 0; i < CATEGORY_NUM; i++) {
		score[i] = 0;
	}
}

//copy constructor
Student::Student(const Student& s) {
	id = s.id;
	name = s.name; 
	total = s.total;
	letterGrade = s.letterGrade;
	for (int i = 0; i < CATEGORY_NUM; i++){
			score[i] = s.score[i];
	}
}

/*********************************************************************
This function overloads the = operator. The overloaded = operator 
is to take a student class as an parameter. This function acts
to set one class object equal to another
*********************************************************************/
Student& Student::operator = (const Student& s) {
	id = s.id;
	name = s.name;
	total = s.total;
	letterGrade = s.letterGrade;
	for (int i = 0; i < CATEGORY_NUM; i++) {
		score[i] = s.score[i];
	}
	return *this;
}

/*********************************************************************
This function returns the string value stored in the private 
variable id
*********************************************************************/
string Student::getID() const {
	return id;
}


/*********************************************************************
This function accepts a string from the user and sets the string
given as the parameter into the private variable id
*********************************************************************/
void Student::setID(string newID) {
	id = newID;
}

/*********************************************************************
This function is to compute the total number of scores by accessing
the array of scores of one student and adding them all together
and storing them in the private variable total
*********************************************************************/
void  Student::ComputeTotal() {
	total = 0;
	for (int i = 0; i < CATEGORY_NUM; i++) {
		total += score[i];
	}
}

/*********************************************************************
This function return the integer value stored in the variable total
*********************************************************************/
int Student::GetTotal() const {
	return total;
}
/*********************************************************************
This function is to use the integer value stored in total variable
and calculate the cooresponding letter grade according to the value 
in total. 100-90 = a; 89-89 = B; 79-70 = C; 69-60 = D; else F
*********************************************************************/
void Student::ComputeGrade() {
	if (total >= 90) {
		letterGrade = 'A';
	}
	else if (total >= 80) {
		letterGrade = 'B';
	}
	else if (total >= 70) {
		letterGrade = 'C';
	}
	else if (total >= 60) {
		letterGrade = 'D';
	}
	else {
		letterGrade = 'F';
	}
}

/*********************************************************************
This function is to return the char variable letterGrade that holds 
the computed letterGrade fromo the ComputeGrade function
*********************************************************************/
char Student::GetGrade() const {
	return letterGrade;
}

/*********************************************************************
This function is to change the score of an inputted type with the 
integer value inputted in the parameter scoreValue 
**********************************************************************/
void Student::changeScore(ScoreType scoreName, int scoreValue) {
	if (scoreName >= CLA && scoreName <= BONUS) {    //checks to see if score name is valid 
		score[scoreName] = scoreValue; 
	}
}

/*********************************************************************
This function is to return the score stored in the score array 
cooresponding scoreName given by the user
*********************************************************************/
int Student::getScore(ScoreType scoreName) const {
	if (scoreName >= CLA && scoreName <= BONUS) {    //checks to see if score name is valid 
		return score[scoreName];
	}
	return 0;
}

/*********************************************************************
This function is to display the information of a single student
*********************************************************************/
void Student::DisplayInfo() const {
	cout << "Information for the student with ID " << id << endl;
	cout << "Here is information for student with ID:  " << id << endl;
	cout << "------------------------------" << endl;
	cout << "Name : " << name << endl;
	cout << "ClA : " << score[CLA] << endl;
	cout << "OLA : " << score[OLA] << endl;
	cout << "Quiz : " << score[QUIZ] << endl;
	cout << "Homework : " << score[HOMEWORK] << endl;
	cout << "Exam : " << score[EXAM] << endl;
	cout << "Bonus : " << score[BONUS] << endl;
	cout << "______________________________" << endl;
	cout << "Total Score : " << total << endl;
	cout << "Final Grade : " << letterGrade << endl;

}

/*********************************************************************
This program overloads the >> operator to read input from the file
and store it into the class array
*********************************************************************/
istream& operator >> (istream& myin, Student& s) {
	myin >> s.id >> s.name;
	for (int i = 0; i < Student::CATEGORY_NUM; i++) {
		myin >> s.score[i];
	  }
	return myin;
}

/*********************************************************************
This function overloads the << operator to display the information 
of the single students data
*********************************************************************/
ostream& operator << (ostream& myout, const Student& s) {
	myout << s.id << "\t" << s.name << "\t";
	for (int i = 0; i < Student::CATEGORY_NUM; i++) {
		myout << s.score[i] << "\t";
	}
	return myout; 
}

/*********************************************************************
This function is to return the string value stored in the variable
name
*********************************************************************/
string Student::getName() const {
	return name;
}