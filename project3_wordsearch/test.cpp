#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dictionary.h"

using namespace std;

//this function currently takes in a dictionary object and a filename string.
//Hopefully the filename corresponds to an input file that's in the same format
//as the dictionary and if it is, then we can output a file of candidate words:
void findMatches(dictionary dict, string filename)
{
    cout << "Work in Progress \n";
    cout << dict;

    ifstream candidates(filename);      //load file containing candidate words
    ofstream fout("found-words.txt");   //load file to contain found words

    string tmp; //temporary value for comparison

    if(candidates.is_open() && fout.is_open())
    {
        while (!candidates.eof())
        {
            candidates >> tmp;  //load candidate word into temp variable 
            tmp.append("\n");   //I keep forgetting to append this...

            //if the word in 'tmp' is in the dictionary, output it to the file:
            if(dict.searchDict(tmp) != "Not present")
                fout << "found: " << dict.searchDict(tmp);
                //*note:* if 'candidates' file is not in alphabetical order, 
                //"found-words.txt" won't be either (not a big deal tho, imo)
        }
    }
    else
    {
        cout << "Unable to open file(s) \n";
    }

    fout.close();
    candidates.close();
}

int main()
{
    dictionary myDict("test-dict.txt");
    myDict.sortDict();

    cout << myDict;

    cout << myDict.searchDict("banana") << endl;
    cout << myDict.searchDict("pogchampion") << endl;

    return 0;
}
