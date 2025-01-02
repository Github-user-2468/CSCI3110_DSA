#include "wordEntry.h"
#include <algorithm> 

using namespace std;

// Default constructor
wordEntry::wordEntry() : word(""), freq(0), lastLine(0) {}

// Constructor with word and line number
wordEntry::wordEntry(const string& word, int lineNumber)
    : word(word), freq(1), lastLine(lineNumber) {
    lineNums.push_back(lineNumber);
}

// Accessor function for the word
string wordEntry::Key() const {
    return word;
}

// Gets and returns frequency
int wordEntry::getFrequency() const {
    return freq;
}

// Gets line numbers and returns
const list<int>& wordEntry::getLineNums() const {
    return lineNums;
}

// Function to increment frequency and add line number
void wordEntry::incrementFrequency(int lineNumber) {
    freq++;
    // If the line number is not already in the list, add it
    if (find(lineNums.begin(), lineNums.end(), lineNumber) == lineNums.end()) {
        lineNums.push_back(lineNumber);
    }
    // Update the last line number
    lastLine = lineNumber;
}
