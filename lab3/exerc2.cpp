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
  * 1. Declarations              *
  ********************************/

// Type1 = string           (Subject)
// Type2 = set<std::string> (Anagrams)
using Table = std::map<std::string, std::set<std::string>>;

  /*******************************
   * 2. Main function             *
   *******************************/
int main() {

    // Skriva in och läsa filen
    std::cout << "Text file: ";
    std::string fileName;
    std::cin >> fileName;

    std::ifstream in_File{ "C:/Users/Jovan/Desktop/University/1.Programming/TNG033_(C++)/Labs/lab3/code/" + fileName };

    if (!in_File) {
        std::cout << "Could not open input file!!\n";
        return 0;
    }

    /* ========== Insert & Sort ========== */
    // ---------- CONCEPT ---------- 
    // STEP 1: Create vector & get words from file
    // STEP 2: Created new vector & sort words to get word_key
    // STEP 3: Insert into table, table will handle uniqueness of keys
    //         will also insert word into slot with same key

    // Creates a vector of type string to hold our words (from dictionary)
    std::vector<std::string> words; 

    /* - 1st input: (start range) 
    *  - 2nd input: (end range)
    *  - 3rd input: (beginning of destinatin range)
    *   [std::istream_iterator] = points to the container of istream
    */
    std::copy(std::istream_iterator<std::string>{in_File}, std::istream_iterator<std::string>{}, std::back_inserter(words));

    // Create a table
    Table anagram;

    std::for_each(words.begin(), words.end(), anagram);

}