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
 // STEP 1: Create vector & get words from file
 // STEP 2: Created new vector & sort words to get word_key
 // STEP 3: Insert into table, table will handle uniqueness of keys
 //         will also insert word into slot with same key

/*******************************
* 1. Declarations              *
********************************/

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

    // Create a map to hold all the subjects and their corresponding anagrams
    std::map<std::string, std::set<std::string>> subjects;

    // Creates a vector of type string to hold our words (from dictionary)
    std::vector<std::string> words; 

    /* - 1st input: (start range) 
    *  - 2nd input: (end range)
    *  - 3rd input: (beginning of destinatin range)
    *   [std::istream_iterator] = points to the container of istream */
    std::copy(std::istream_iterator<std::string>(in_File), std::istream_iterator<std::string>(), std::back_inserter(words));


    // Add the each word from the vector "words" to the list of anagrams for its subject
    // 
    std::for_each(words.begin(), words.end(), [&subjects](std::string Word) {

        std::string temp = Word;

        std::sort(Word.begin(), Word.end());
        subjects[Word].insert(temp);
        });

    // Create an output file stream
    std::ofstream output("../code/output.txt");

    // Write the number of words read from the input file
    output << "Total number of words: " << words.size() << std::endl;

    // Iterate over the map and write the anagrams for each subject
    //for (const auto& [subject, anagrams] : subjects) {}
    output << std::endl << "-- ANAGRAMS --" << std::endl;

    std::for_each(subjects.begin(), subjects.end(), [&output](Table p) {
    // Write the anagrams only if there are two or more
    if (p.second.size() >= 2) {

        // Use the std::for_each algorithm to write the anagrams to the output stream
        std::copy(p.second.begin(), p.second.end(), std::ostream_iterator<std::string>(output, " "));

        output << " --> " << p.second.size() << " words." << std::endl;
    }
    });

    std::cout << "Mhm borde funka...?";

    return 0;
}