#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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

template<typename T>
void selectionsort(vector<T> &list)
{
    int minIndex = 0;           //index of smallest value in list

    T minVal;  //smallest value in list
    T swapVal;  //value to be swapped

    //The algorithm:
    for (int i = 0; i < list.size(); i++)
    {
        /*** Scan for smallest element ***/
        for (int j = i + 1; j < list.size(); j++)
        {
            minVal = list[minIndex];

            //only executes if there is a number smaller than min:
            if(minVal > list[j])
            {
                minVal = list[j];
                minIndex = j;       //update min value and index
            }
        }
    
        /*** swapping! ***/
        swapVal = list[i];

        //If I don't include this statement, it gives you wrong answers ;-;
        if (swapVal > minVal)
        {
            list[i] = minVal;
            list[minIndex] = swapVal;
        }
    }
}

int main()
{
    vector<int> list;
    
    //vector<string> myDict = readDict("Dictionary");
    return 0;
}