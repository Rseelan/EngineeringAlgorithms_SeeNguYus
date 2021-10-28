//#include <stdlib.h>
#include <iostream>
#include <vector>
//#include <cstdlib>
#include <fstream>
#include <string>
#include "grid.h"

using namespace std;


int main(){
    grid gridIn("input15.txt");

    //string startChar;
    string outputWord;

    //vector<string> testvector;

    int numRows = gridIn.letters.rows();
    int numCols = gridIn.letters.cols();
    int temp;
    int counter;
    int temp2;
    int counterX;
    int counterY;

    // for (int i = 0; i<numRows; i++){

    //     testvector.push_back("c");

    // }
    
    //start at each character in the grid
    for (int row = 0; row < numRows; row++){
        for (int col = 0; col < numCols; col++){

            //improved algo for going down right - diagonal
            //cout<<"Going down right"<<endl;

            outputWord = "";

            counterX = row;
            counterY = col;
            counter = 0;
            
            while (counter < numRows){

                //testvector[counter] = gridIn.letters[counterX][counterY];
                //cout<<testvector[counter]<<endl;
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

                if (outputWord.size() > 4)
                    cout << outputWord << endl;
            }

            /*
            //going down left - diagonal
            cout<<"going down left"<<endl;
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = gridIn.letters[counterX][counterY];
                cout<<testvector[counter]<<endl;

                counter++;
                counterX++;
                counterY--;

                if (counterX == numRows){
                    counterX = 0;

                }

                if (counterY == -1){
                    counterY = numCols - 1;

                }

                //arbid  -edit this
                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }
            

           //going up left
            cout<<"Going up left"<<endl;
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = gridIn.letters[counterX][counterY];
                cout<<testvector[counter]<<endl;

                counter++;
                counterX--;
                counterY--;

                if (counterX == -1){
                    counterX = numRows - 1;

                }

                if (counterY == -1){
                    counterY = numCols - 1;

                }

                //arbid  -edit this
                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }
            
           //going up right
            cout<<"Going up right"<<endl;
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = gridIn.letters[counterX][counterY];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterX--;
                counterY++;

                if (counterX == -1){
                    counterX = numRows - 1;

                }

                if (counterY == numCols){
                    counterY = 0;

                }

                //arbid  -edit this
                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }

            //going right - improved
            cout<<"Going right"<<endl;
            counterY = col;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = gridIn.letters[row][counterY];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterY++;

                if (counterY == numCols){
                    counterY = 0;

                }

                //arbid  -edit this
                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }

            //going left - improved
            cout<<"Going left"<<endl;
            counterY = col;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = gridIn.letters[row][counterY];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterY--;

                if (counterY == -1){
                    counterY = numCols - 1;

                }

                //arbid  -edit this
                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }

            //going up
            cout<<"Going up"<<endl;
            counterX = row;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = gridIn.letters[counterX][col];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterX--;

                if (counterX == -1){
                    counterX = numRows - 1;

                }

                //arbid edit this
                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }

            //going down
            cout<<"Going down"<<endl;
            counterX = row;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = gridIn.letters[counterX][col];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterX++;

                if (counterX == numRows){
                    counterX = 0;

                }

                //arbid edit this
                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }
            cout<<endl;
            */
        }
        cout << endl;
    }
    return 0;
}