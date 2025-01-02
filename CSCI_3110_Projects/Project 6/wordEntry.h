#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <list>      
#include <string>   

using namespace std; 

class wordEntry {
public:
    // Default constructor
    wordEntry();

    // Constructor
    wordEntry(const string& word, int lineNumber);

    // Accessor 
    string Key() const;  // Returns the word

    // Gets frequency and returns frequency
    int getFrequency() const;  // Returns frequency

    // Gets line numbers abd returns
    const list<int>& getLineNums() const;  // Returns the list of line numbers

    // Function to increase frequency and add line number
    void incrementFrequency(int lineNumber);

private:
    string word;              // The word itself
    int freq;                 // Frequency of the word
    int lastLine;             // Last line number where the word was found
    list<int> lineNums;       // Store line numbers as a list
};

#endif
