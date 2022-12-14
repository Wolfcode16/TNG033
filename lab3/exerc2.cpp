/*****************************************
 * Lab 3: exercise 2                      *
 * Anagrams table                         *
 ******************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <set>
#include <iterator>
#include <iomanip>

 /*******************************
 * 0. Idea & Concept            *
 ********************************/
 // STEP 1: Create a table to hold all subjects and their anagrams
 // STEP 2: Create a vector<std::string>  and insert words from uppgift2.txt
 // STEP 3: Convert word to subject and insert both the word & subject into the table
 //         The table will make sure no duplicates happen, therefore if you send a word 
 //         with already existing subject they will add the anagram.

/*******************************
* 1. Declarations              *
********************************/

// std::pair < Type1, Type2 >
// Type1 = string           (Subject)
// Type2 = set<std::string> (Anagrams)
using Table = std::pair < std::string, std::set<std::string>>;


/*******************************
* 2. Main function             *
*******************************/
int main() {

    // Skriva in och läsa filen
    std::cout << "Text file: ";
    std::string fileName;
    std::cin >> fileName;

    // Open input file
    std::ifstream in_File{ "../code/" + fileName };

    // If failed to open
    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    // ============= STEP 1 ============= 
    // Create a map to hold all the subjects and their corresponding anagrams
    std::map<std::string, std::set<std::string>> subjects;

    // Creates a vector of type string to hold our words (from dictionary)
    std::vector<std::string> words; 

    // ============= STEP 2 ============= 
    // Std::copy( start range, end range, beginning of destination range)
    //[std::istream_iterator] = points to the container of istream
    std::copy(std::istream_iterator<std::string>(in_File), std::istream_iterator<std::string>(), std::back_inserter(words));

    // ============= STEP 3 =============
    // Add the each word from the vector "words" to the list of anagrams for its subject
    // for_each( start range, end range, function) 
    std::for_each(words.begin(), words.end(), [&subjects](std::string Word) {

        std::string temp = Word;                // Create temp string to store Word
 
        std::sort(Word.begin(), Word.end());    // Sort the alphabets in Word
        subjects[Word].insert(temp);            // Insert temp (Word) and subject into the table "subjects" 
        });

    // ============= Writing it out to an output =============
    // Create an output file stream
    std::ofstream output("../code/output.txt");

    // Write the number of words read from the input file
    output << "Total number of words: " << words.size() << std::endl;
    output << std::endl << "-- ANAGRAMS --" << std::endl;

    // Iterate over the map and write the anagrams for each subject
    // for_each(start range, end range, function)
    std::for_each(subjects.begin(), subjects.end(), [&output](Table table) {

    // Write the anagrams only if there are two or more
    if (table.second.size() >= 2) {

        //std::copy(start range, end range, output destination range)
        // copy anagrams
        // use ostream_iterator to write each word to ofstream "output" and add a " " between the words
        std::copy(table.second.begin(), table.second.end(), std::ostream_iterator<std::string>(output, " "));

        // Write following into output
        output << " --> " << table.second.size() << " words." << std::endl;
    }
    });

    return 0;
}
