#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dictionary.h"

using namespace std;
/*
vector<string> readDict(string filename)
{
    ifstream dict(filename);

    vector<string> words;   //vector of words stores the whole dictionary
    string tmp;             //create temporary sting to push into vector

    int wordNum = 0;

    if (dict.is_open())
    {
        while (!dict.eof())
        {
            dict >> tmp;    

            //append "end line" character to each string in vector so that when
            //we insert any given word in the vector into a file, it will input
            //a new line after that word:
            words.push_back(tmp);
            words[wordNum].append("\n");    

            wordNum++;
        }  
        
        dict.close();
    }
    else cout << "Unable to open file \n";

    return words;
}
*/
/*
void sortDict(vector<string> &dictionary)
{
    int minIndex = 0;

    string minVal;  //smallest 'value' in list
    string compVal; //'value' to be compared
    string swapVal; //'value' to be swapped

    //The algorithm:
    for (int i = 0; i < dictionary.size(); i++)
    {
        //Scan for smallest element 
        for (int j = i + 1; j < dictionary.size(); j++)
        {
            minVal = dictionary[minIndex];
            
            //only executes if the ASCII code of the string in compVal
            //is smaller than the respective ASCII code of minVal:
            if(minVal > dictionary[j])
            {
                minVal = dictionary[j];
                minIndex = j;
            }
        } //end j-loop
    
        // swapping!
        swapVal = dictionary[i];

        //If I don't include this statement, it gives you wrong answers ;-;
        //This statement makes sure you only swap if minVal is actually smaller
        //than swapVal, because sometimes this function decides to be wrong...
        if (swapVal > minVal)
        {
            dictionary[i] = minVal;
            dictionary[minIndex] = swapVal;
        }
    } //end for loop
}
*/

int main()
{
    dictionary myDict("test-dict.txt");
    myDict.sortDict();

    cout << myDict;

    cout << myDict.searchDict("banana") << endl;
    cout << myDict.searchDict("pogchampion") << endl;

    return 0;
}