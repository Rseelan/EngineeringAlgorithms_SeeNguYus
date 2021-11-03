#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "grid.h"
#include "dictionary.h"
#include "grid.h"

using namespace std;

//this function currently takes in a dictionary object and a filename string.
//Hopefully the filename corresponds to an input file that's in the same format
//as the dictionary and if it is, then we can output a file of candidate words:
void findMatches(dictionary dict, grid gridIn)
{
    ofstream MyFile("CandidateWords.txt");

    string outputWord;  //words to be outputted

    int numRows = gridIn.letters.rows();
    int numCols = gridIn.letters.cols();
    int temp;
    int counter;
    int temp2;
    int counterX;
    int counterY;
    
    //start at each character in the grid
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            /*******improved algo for going down right - diagonal*******/
            outputWord = "";

            counterX = row;
            counterY = col;
            counter = 0;
            
            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX++;
                counterY++;

                if (counterX == numRows){

                    counterX = 0;

                }
                    

                if (counterY == numCols){

                    counterY = 0;

                }
                    

                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
                    
            }
            /***********************************************************/

            /*******improved algo for going down left - diagonal********/
            outputWord = "";
            
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX++;
                counterY--;

                if (counterX == numRows)
                    counterX = 0;

                if (counterY == -1)
                    counterY = numCols - 1;

                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/        

            /********improved algo for going up left - diagonal*********/
            outputWord = "";
            
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX--;
                counterY--;

                if (counterX == -1)
                    counterX = numRows - 1;

                if (counterY == -1)
                    counterY = numCols - 1;
                
                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/            
          
            /********improved algo for going up right -ndiagonal********/
            outputWord = "";
            
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX--;
                counterY++;

                if (counterX == -1)
                    counterX = numRows - 1;

                if (counterY == numCols)
                    counterY = 0;
                
                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/
            
            /***************improved algo for going right***************/
            outputWord = "";
            
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterY++;

                if (counterY == numCols)
                    counterY = 0;

                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/

            /***************improved algo for going left****************/
            outputWord = "";
            
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterY--;

                if (counterY == -1)
                    counterY = numCols - 1;

                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/

            /****************improved algo for going up*****************/
            outputWord = "";
            
            counterX = row;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX--;

                if (counterX == -1){
                    counterX = numRows - 1;
                    
                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/

            /***************improved algo for going down****************/
            outputWord = "";
                
            counterX = row;
            counter = 0;

            while (counter < numRows)
            {

                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX++;

                if (counterX == numRows)
                    counterX = 0;
                
                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            cout<<endl;
            /***********************************************************/
        }
        cout << endl;
    }

    }

    MyFile.close();

    ifstream matching("CandidateWords.txt");
    ofstream fout("found-words.txt");           //load file to contain found words
    
    string tmp; //temporary value for comparison

    if(matching.is_open() && fout.is_open())
    {
        while (!matching.eof())
        {
            matching >> tmp;  //load candidate word into temp variable 
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
    matching.close();
}

void search(){

    string filename;
    cout<<"Please enter a filename for a grid you'd like to parse for words: "<<endl;
    cin>>filename;

    grid gridIn(filename); //create a new grid object
    ofstream MyFile("CandidateWords.txt");

    string outputWord;  //words to be outputted

    int numRows = gridIn.letters.rows();
    int numCols = gridIn.letters.cols();
    int temp;
    int counter;
    int temp2;
    int counterX;
    int counterY;
    
    //start at each character in the grid
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            /*******improved algo for going down right - diagonal*******/
            outputWord = "";

            counterX = row;
            counterY = col;
            counter = 0;
            
            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX++;
                counterY++;

                if (counterX == numRows){

                    counterX = 0;

                }
                    

                if (counterY == numCols){

                    counterY = 0;

                }
                    

                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
                    
            }
            /***********************************************************/

            /*******improved algo for going down left - diagonal********/
            outputWord = "";
            
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX++;
                counterY--;

                if (counterX == numRows)
                    counterX = 0;

                if (counterY == -1)
                    counterY = numCols - 1;

                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/        

            /********improved algo for going up left - diagonal*********/
            outputWord = "";
            
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX--;
                counterY--;

                if (counterX == -1)
                    counterX = numRows - 1;

                if (counterY == -1)
                    counterY = numCols - 1;
                
                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/            
          
            /********improved algo for going up right -ndiagonal********/
            outputWord = "";
            
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX--;
                counterY++;

                if (counterX == -1)
                    counterX = numRows - 1;

                if (counterY == numCols)
                    counterY = 0;
                
                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/
            
            /***************improved algo for going right***************/
            outputWord = "";
            
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterY++;

                if (counterY == numCols)
                    counterY = 0;

                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/

            /***************improved algo for going left****************/
            outputWord = "";
            
            counterY = col;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterY--;

                if (counterY == -1)
                    counterY = numCols - 1;

                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/

            /****************improved algo for going up*****************/
            outputWord = "";
            
            counterX = row;
            counter = 0;

            while (counter < numRows)
            {
                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX--;

                if (counterX == -1){
                    counterX = numRows - 1;
                    
                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            /***********************************************************/

            /***************improved algo for going down****************/
            outputWord = "";
                
            counterX = row;
            counter = 0;

            while (counter < numRows)
            {

                outputWord += gridIn.letters[counterX][counterY];

                counter++;
                counterX++;

                if (counterX == numRows)
                    counterX = 0;
                
                if (outputWord.size() > 4){

                    cout << outputWord << endl;
                    MyFile << outputWord<<"\n";


                }
            }
            cout<<endl;
            /***********************************************************/
        }
        cout << endl;
    }

    }

    MyFile.close();

}

int main()
{
    //grid testGrid1("input15.txt");
    //grid testGrid2("input30.txt");
    //grid testGrid3("input50.txt");

    dictionary myDict("Dictionary");
    int dictlength = myDict.getLength();
    //myDict.selectSort();
    myDict.quickSort(0, dictlength - 1);

    cout << myDict << endl;

    //findMatches(myDict, testGrid1);
    //findMatches(myDict, testGrid2);
    //findMatches(myDict, testGrid3);

    //search();
    
    return 0;
}
