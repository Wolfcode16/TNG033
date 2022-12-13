/*******************************
 * Lab 3: exercise 1            *
 * Frequency table of words     *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>   //std::pair
#include <fstream>
#include <cassert>
#include <algorithm> // std::transform

/*******************************
 * 1. Declarations              *
 ********************************/

// Using pair for each element, buildt in function in library
// https://en.cppreference.com/w/cpp/utility/pair
using pair = std::pair<std::string, int>;

// A function to test the tables created by the program
void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n);


// A function to make capital cases into lower cases
void lowerCase(std::string& word) {
    // From Lecture 13: transform(start1, end, start2, operation)
    // Transform: https://en.cppreference.com/w/cpp/algorithm/transform
    std::transform(word.begin(), word.end(), word.begin(), tolower);
}

// Checks if its one of the punctuations
bool isPunc(const char& c) {
    std::string chars = ".,!?:();\"";           // Punctuations checked
    return chars.find(c) != std::string::npos;  // std::string::npos = "until end of the string" usually used to indicate no matches
}

// A function to remove special cases
void removeChar(std::string& word) {
    word.erase(remove_if(word.begin(), word.end(), isPunc), word.end());    // If isPunc is true -> remove
}

// Sort by frequency
bool sortBy(const pair& t1, const pair& t2) {

    if (t1.second == t2.second)         // If same amount, alphabetical order 
    {
        return(t1.first < t2.first);    // sort alphabetically by word
    }
    return (t1.second > t2.second);     // else...?
}


/*******************************
 * 2. Main function             *
 *******************************/

int main() {
    
    std::cout << "Text file: ";
    std::string name;
    std::cin >> name;

    // Create a input stream for file at this location.
    std::ifstream in_File{"C:/Users/Jovan/Desktop/University/1.Programming/TNG033_(C++)/Labs/lab3/code/" + name};

    // If not possible to open the stream
    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    // Creates our map
    std::map<std::string, int> table;
    int counter{0};  // to count total number of words read from the input file

    std::string Word;           // Create a string variable (Why std tho?)

    while (in_File >> Word) {   // As long as the stream can take in words

        // Remove special characters
        removeChar(Word);

        // Change all to lowercase
        lowerCase(Word);

        // Increase int "counter" in map
        // If word already exist the word will not be added but will increase int "counter"
        table[Word]++;

        ++counter;
    }

    //ADD CODE to build vector freq

    // Create a vector of type pair to keep track of frequency
    std::vector<pair> freq;

    // copy table to freq, insert values from the back
    std::copy(table.begin(), table.end(), std::back_inserter(freq));

    // Sort freq by frequency
    std::sort(freq.begin(), freq.end(), sortBy);

    /* ************** Testing **************** */

    test(table, freq, name, counter);
}


/*******************************
 * 2. Test implementation      *
 * Do not modify               *
 *******************************/

void test(const std::map<std::string, int>& t, const std::vector<std::pair<std::string, int>>& v,
          const std::string& file_name, int n) {

    std::ifstream file{"../code/out_" + file_name};

    // Test if stream is in good state
    assert(bool(file) == true);

    std::map<std::string, int> result1;
    std::string word;
    int counter{0};
    int total{0};

    // load expected frequency table sorted alphabetically
    while (file >> word >> counter && counter > 0) {
        result1[word] = counter;
        total += counter;
    }
	
	/*
    * uppgift1_kort: 69 words
    * uppgift1.txt: 1063 words
    */

    assert(total == n);  // test if total number of words is correct
    assert(t == result1);

    std::vector<std::pair<std::string, int>> result2;

    // load expected frequency table sorted by frequence
    while (file >> word >> counter) {
        result2.push_back(std::pair{word, counter});
    }

    assert(v == result2);

    std::cout << "\nPassed all tests successfully!!\n";
}
