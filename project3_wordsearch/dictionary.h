#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class dictionary
{
    public:
        dictionary(/* args */);
        //~dictionary();

        void readDict(string filename);    //reads dictionary file

        void sortDict();    //sorts the dictionary
        void searchDict();  //looks up words from the dictionary

    private:
        vector<string> words;
};

/****************************Function Implementation***************************/

//constructor
dictionary::dictionary(/* args */)
{
    readDict("Dictionary");

    //definitely won't do this in the final product:
    cout << words[0] << endl;
}

//destructor?
//dictionary::~dictionary()
//{
    //stuff...
//}

//reads data from the dictionary file to store each word into a string vector
//**used this site for referance: https://www.cplusplus.com/doc/tutorial/files/
//Right now, I think this doesn't work!
void dictionary::readDict(string filename)
{
    ifstream dict(filename);
    int wordNum = 0;

    if (dict.is_open())
    {
        while ( getline (dict, words[wordNum]) )
        {
            cout << words[wordNum] << '\n';
        }  

        dict.close();
    }
    else cout << "Unable to open file \n";
}

//sorts the dictionary:
void dictionary::sortDict(){cout << "Work in Progress \n";}    

//looks up words from the dictionary:
void dictionary::searchDict(){cout << "Work in Progress \n";}  
/******************************************************************************/

#endif