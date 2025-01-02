/***************************************************************************************
Programmer: Karigan Stewart
Date" 11/12/24
Program Name: Project 5
Description: This program performs various jobs. It can find the fibanacci number
in nth sequence. It can find the summation of a given value. It can also find
the largest number in a given array. As well as examine a grid and determine the
number and size of the eagles represented in the grid pattern.
**************************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include "parameters.h"

using namespace std;

// Fibonacci function finds the nth fibanacci number 
int fibonacci(int n) {
    if (n == 0) 
        return 0;
    if (n == 1) 
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Sum Function to find the summation of a given number 
int sum(int n) {
    if (n == 0) 
        return 0;

    return n + sum(n - 1);
}

// Function to find the largest number in an array
int largest(const int arr[], int size) {
    // If there is only one element return that element
    if (size == 1) {
        return arr[0];
    }

    // Get the largest number from the rest of the array
    int subLargest = largest(arr, size - 1);

    // Compare the current element with the largest number
    if (arr[size - 1] > subLargest) {
        return arr[size - 1];        // If current element is larger return it
    } else {
        return subLargest;           // If not return the largest so far
    }
}


// FindEagles function finds the size of the eagles 
int findEagles(vector<vector<int>>& grid, int x, int y) {

    //Checks for out of bounds or 0 (empty space)
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 0) {
        return 0;
    }
    int count = 1;   // current cell
    grid[x][y] = 0;  // erase the eagle
    // Check all 8 directions
    count += findEagles(grid, x - 1, y);      // Up
    count += findEagles(grid, x + 1, y);      // Down
    count += findEagles(grid, x, y - 1);      // Left
    count += findEagles(grid, x, y + 1);      // Right
    count += findEagles(grid, x - 1, y - 1);  // Upper-left diagonal
    count += findEagles(grid, x - 1, y + 1);  // Upper-right diagonal
    count += findEagles(grid, x + 1, y - 1);  // Lower-left diagonal
    count += findEagles(grid, x + 1, y + 1);  // Lower-right diagonal
    return count;
}

// This function processes the grid and calls the findEagles function to determine the size and number of eagle
// It then displays the size and count of the eagles to the user
void FindEagle(vector<vector<int>>& grid) {
    int eagleCount = 0;   // Holds the number of eagles found 

  // Loops through each cell of the grid 
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) { 
          // If an eagle is detected call findEagles to determine size
            if (grid[i][j] != 0) {
                int size = findEagles(grid, i, j);
                cout << "An eagle size " << size << " is found."  << endl;
                ++eagleCount;
            }
        }
    }
    // Display the number of eagles found 
    cout << eagleCount << " eagle(s) found in the picture." << endl << endl;
}


int main() {
    // Calls the fibonacci function wirh the value in parameters.h
    cout << "Fibonacci of " << FibVal << " is " << fibonacci(FibVal) << endl ;

    // Calls the sum function wirh the value in parameters.h
    cout << "Sum of first " << SumVal << " integers is " << sum(SumVal) << endl;

    // Calls the largest function wirh the array in parameters.h
    cout << "Largest value in the array is " << largest(LargestVal, 13) << endl << endl;

    // Opens file for reading
    ifstream infile("eagle.dat");
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int rows, cols;  // holds data from rows and columns
   // Reads data file for eagle counting
    while (infile >> rows >> cols) {  

        vector<vector<int>> Eaglegrid(rows, vector<int>(cols));   // Creating a 2D vector told hold data
      // Reading Data into the grid
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                infile >> Eaglegrid[i][j];          // Reads into the grid vector 
            }
        }

    // Prints the grid
    for (int i = 0; i < rows; ++i) {       // Loop through each row
        for (int j = 0; j < cols; ++j) {   // Loop through each column in the current row
            cout << Eaglegrid[i][j] << " ";     // Print the value at grid[i][j]
            }
        cout << endl;  // Print a new line after each row
        }
    cout << endl;

    // Finds and displays the number and size of the eagles represented in eagles.dat 
    FindEagle(Eaglegrid);
    }

    return 0;
}
