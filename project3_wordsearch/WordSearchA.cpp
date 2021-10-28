#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "grid.h"

using namespace std;


int main(){


    grid gridIn("input15.txt"); //create a new grid object
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
    return 0;
}
