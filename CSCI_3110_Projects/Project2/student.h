/*
 * File:	Student.h
 * 
 * Purpose: This file is a part of the 1st open lab assignment, which 
 * includes Student.h, Student.cpp, Roster.h, Roster.cpp, 
 * and main.cpp. This file gives the full definition 
 * of the class Student.
 */

#ifndef __CSCI3110_STUDENT__
#define __CSCI3110_STUDENT__

#include <string>
#include <iostream>
using namespace std;

class Student
{
	public:
		// The types of score. You can access the type or enumerators outside
		// of the Student class scope by the following expressions:
		//	Student::ScoreType              Student::CLA    
		enum ScoreType {CLA, OLA, QUIZ, HOMEWORK, EXAM, BONUS};

		// To access the class constant outside of the Student class scope:
		//	Student::CATEGORY_NUM
		static const int CATEGORY_NUM = BONUS - CLA + 1;

		// default constructor. This is necessary since we define an array 
		// of students in the class Roster
		Student( );

 	   	// copy constructor
   	 	Student(const Student & s);

    	// overloaded assignment operator
    	Student& operator = (const Student & s);


		//Accessor & mutator of id 
		string getID( ) const;
		void setID( string ) ;

    	// Accessor & mutator of total (score)
    	void  ComputeTotal();
    	int   GetTotal() const;

    	// Accessor & mutator of letter grade
    	void  ComputeGrade();
    	char  GetGrade() const;

		//Accessor and mutator of m_score
		//ScoreType indicates which score you want to access
		void changeScore( ScoreType scoreName, int scoreValue);
		int  getScore( ScoreType scoreName) const;

    	// This function displays information of one student, one value per row 
    	// label for each value is included
    	// total score and letter grade are also included
    	void DisplayInfo() const;

	


    	// friend function to output information (exclude total score and letter grade) of one student 
    	// All information of one student is displayed on one row
    	friend ostream & operator << (ostream & myout, const Student & s);

    	// friend function to data of one student from the data file
    	friend istream & operator >> (istream & myin, Student & s);

		//********************************************************************
		//Add your functions here if necessary
    	//like getters and setters for m_total and m_letterGrade
		
		string getName() const;

		//********************************************************************
    


	private:
		string		id;		// Student ID
    	string    	name; // Student name
		int			score[CATEGORY_NUM];
						// score[CLA] is CLA score		
						// score[OLA] is OLA score		
						// score[QUIZ] is QUIZ score		
						// score[HOMEWORK] is HOMEWORK score		
						// score[EXAM] is EXAM score		
            			// score[BONUS] is Bonus score
    	int     total;  //total score, which is the sum of all scores
    	char    letterGrade;
};
#endif
