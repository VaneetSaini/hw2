#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    //criteria: split at punctuation or space, need at least 2 chars 
    std::set<std::string> parsed; //thing to return 
    unsigned int start = 0;
    for (unsigned int i = 0; i < rawWords.length(); i++){
        if (ispunct(rawWords[i]) || rawWords[i] == ' '){ //if punctuation or space 
            if (i - start >= 2){  //make sure size is at least 2
                parsed.insert(convToLower(rawWords.substr(start, i-start)));
            }
            start = i+1; //start after the punctuation/space
        }
				else if (i == rawWords.length()-1){
					parsed.insert(convToLower(rawWords.substr(start, rawWords.length() - start)));
				}
    }
    return parsed;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
