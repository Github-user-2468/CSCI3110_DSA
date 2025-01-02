/***************************************************************************************************
HOPE YOU HAVE A GOOD CHRISTMAS DR.LI :)--Karigan-- 
Program Name: Program 6
Programmer: Karigan Stewart
Date: 12/1/24
Program Description: This program is to read from a text file and build and traverse a 
binary search tree. It is then to traverse and output the frequency and the lines that
each number appears in the text file 
************************************************************************************************/

#include "wordEntry.h"
#include "BST.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// Function prototypes--------------------------
void printWords(wordEntry& word);
void insertWords(BinarySearchTree& bst, const map<string, wordEntry>& words);
string removePunc(const string& word);
bool readFile(const string& filename, map<string, wordEntry>& words);
void printHeader(); 

int main() {
    string filename;                    // Holds the filename 
    map<string, wordEntry> words;       // Word map to tracks words and where they occur

    cout << "Enter the name of the file: ";          // Ask the user for a file name 
          cin >> filename;                         // Stores file name 


  // Call the functions to read and process the file
    if (!readFile(filename, words)) {
        cerr << "Error processing file!" << endl;
        return 1;     // Exit if program cannot process file 
    }

    // Creating the tree
    BinarySearchTree bst;

    // Insert words from the map into the Binary Search Tree
    insertWords(bst, words);

    // Prints the header for Display 
    printHeader();

    // Perform in-order traversal and print each extry  
    bst.InorderTraverse(printWords);

    return 0;
}


//------------------------------------------- FUNCTION DEFINITIONS ----------------------------------------------------


/**********************************************************************************
This function is too print the word entry details like the word, frequency and
the lines in which they occur
**********************************************************************************/
void printWords(wordEntry& word) {
    // Prints the word and frequency
    cout << left << setw(20) << word.Key();      // Prints word
    cout << setw(15) << word.getFrequency();     // Prints frequency 

    
    const auto& lineNumbers = word.getLineNums();  // Gets the line number 
    
    if (!lineNumbers.empty()) {
        // Create a stringstream to accumulate line numbers
        stringstream linesStream;

        // Iterates through each element in lineNumbers with iterator it
        for (auto it = lineNumbers.begin(); it != lineNumbers.end(); ++it) {
            linesStream << *it;                              // Add line number to stream
            if (next(it) != lineNumbers.end()) {        // Checks if iterator is not the last element   
                linesStream << ", ";                         // Add a comma if its not the last element
            }
        }

        // Output the line numbers collected in the stringstream
        cout << setw(30) << linesStream.str(); 
    }

    cout << endl;
}



/***********************************************************************************************
This function is to insert words into the Binary Search tree from the map of words. It 
iterates through the build map of words and adds into the binary search tree. If the
insertion was unsucessful then an error message will be returned 
************************************************************************************************/
void insertWords(BinarySearchTree& bst, const map<string, wordEntry>& words) {

    // Iterate over the map of words
    for (auto it = words.begin(); it != words.end(); ++it) {
        bool success = false;

        // Attempt to insert the current wordEntry into the BST
        bst.SearchTreeInsert(it->second, success);

        // Provide feedback for failed insertions
        if (!success) {
            cout << "Error: Could not insert word '" << it->first << "' into the Binary Search tree" << endl;
        }
    }
}


/***********************************************************************************************
This function accepts a file name and reads data from the file. It is to then process
the data in file line by line into a stringstream to process each line word by work and 
increment the number of lines. As it processes the words it is to check for punctutation 
and remove if needed by calling removePunc function. It is to then convert each word to 
lowercase to create uniformity  when comparing. If the word already exists in map then update'
frequency and line number. If it does not already exist then create a new wordEntry object 
to hold the word data 
************************************************************************************************/

bool readFile(const string& filename, map<string, wordEntry>& words) {
   
    ifstream inputFile(filename);  // Declare and open the file stream
    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return false;  // Return false if the file cannot be opened
    }

    string line;           // To store each line from the file
    int lineNumber = 0;    // Variable to track the current line number

    // Read the file line by line
    while (getline(inputFile, line)) {
        ++lineNumber;     // Increment line number for each new line

      // Split the line into words using a stringstream
        istringstream wordStream(line);      // Stream to process each word
        string currentWord;                  // Temporary var to hold each word 

        // Process each word in the current line
        while (wordStream >> currentWord) {
            currentWord = removePunc(currentWord);  // Function call to remove punctuation from the word
            
          // Transform word to lowercase
            transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower); 

            // If the word is not already in the map add it with the current line number
            auto it = words.find(currentWord);
              if (it == words.end()) {
                   words[currentWord] = wordEntry(currentWord, lineNumber);  // Create a new word entry
              }
              else { 
                // If the word is already in the map increment the frequency and add line number 
                  it->second.incrementFrequency(lineNumber);  // Increment frequency and add a new line number
              }
        }
    }
    // Closes file with text 
    inputFile.close();

    // Returns true if the file has been sucessfully read 
    return true;  
}



/***********************************************************************************************
This function is to print the header of the output display for ease and modularity  
************************************************************************************************/
void printHeader() {
    
    cout << endl;
    // Print header ( Title for the word, Frequency of word appears, and what lines it occurs on)
    cout << left << setw(15) << "Word"
        << setw(16) << "Frequency" << setw(10)
        << "Occurs on lines:" << endl;

    // Print a separator
    cout << setfill('-') << setw(10) << ""
        << setw(15) << ""
        << "---------------------------------" << endl;
    cout << setfill(' ');
}



/******************************************************************************************
This function is called to ensure that a word entered in the map does not have a 
punctutation attached to it. In the function it iterates through each character and 
checks if that character is punctutation. If it is not it will add the
character to the resulting string. If it is punctuation it is not added to the resulting 
string 
*******************************************************************************************/
string removePunc(const string& word) {
    string result;

    // Loop through each character of the word
    for (unsigned int i = 0; i < word.length(); ++i) {
        
        // If the character is not punctuation, add it to the result string
        if (!ispunct(static_cast<unsigned char>(word[i]))) {
            result += word[i];
        }
    }
    return result; // Return the word with punctuation removed
}