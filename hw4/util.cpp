#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <string>

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWord) 
{
	string convrawWord = convToLower(rawWord);

	std::set<std::string> myset;

	int position = 0;
	//iterating through the string letter by letter
	for(unsigned int i=0; i<convrawWord.size(); i++)
	{
		if(convrawWord[i] == ' ' || ispunct(convrawWord[i]))
		{
			string fWord = convrawWord.substr(position,(i-position));
			position = i+1;

			if(fWord.size()>=2)
			{
				myset.insert(fWord);
			}
		}
	}
	return myset;
}
