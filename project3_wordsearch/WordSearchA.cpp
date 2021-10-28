#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

//#include "Matrix.h"

//dictionary class
//grid class
/*class grid{

    public:
        void loadGrid(string filename){

            ifstream fin (filename);

            fin>>numRows;
            fin >>numCols;
            string grid1[15][15];

            for (int i = 0; i<numRows; i++){

                for (int j = 0; j<numCols; j++){

                    fin>>grid[i][j];

                }

            }

        void PrintGrid(){
            for (int i = 0; i<numRows; i++){

                for (int j = 0; j<numCols; j++){

                    cout<<grid[i][j]<<" ";

                }
                cout<<endl;

            }
        }
    private:
        int numRows = 0;
        int numCols = 0;

};
*/

//search function

// string search(){

//     //create grid

//     vector<vector<string>> vect
//     {
//         {"n", "y", "d", "m"},
//         {"n", "y", "d", "m"},
//         {"n", "y", "d", "m"},
//         {"n", "y", "d", "m"}
//     };

//     vector<string> testvector;

//     //start at each character in the grid

//     for (int i=0; i<4; i++){

//         for (int j=0; j<4; j++){

//             testvector[j] = vect[i][j];
//             cout<<testvector[j];


//         }

//     }
//     //create a testString that loops around
//     //loop through teststring looking for that word

// }

int main(){


    string startChar;

    vector<vector<string>> vect
    {
        {"n", "a", "d", "e", "b", "h", "i", "o"},
        {"c", "a", "d", "m", "n", "a", "d", "e"},
        {"b", "y", "r", "m", "n", "a", "d", "e"},
        {"i", "y", "e", "c", "n", "a", "d", "e"},
        {"h", "a", "c", "e", "n", "a", "d", "e"},
        {"n", "a", "b", "m", "b", "a", "d", "e"},
        {"k", "y", "a", "m", "n", "i", "d", "e"},
        {"l", "y", "e", "c", "n", "a", "h", "e"},
    };


    vector<string> testvector;

    int numRows = 8;
    int numCols = 8;
    int temp;
    int counter;
    int temp2;
    int counterX;
    int counterY;

    for (int i = 0; i<numRows; i++){

        testvector.push_back("c");

    }



    //start at each character in the grid

    for (int row=3; row<4; row++){

        cout<<"seperate row"<<endl;

        for (int col=3; col<4; col++){

            /*
            //go right

            cout<<"Going right"<<endl;
            counter = col;
            temp = col;
            while(counter < numRows){

                testvector[counter-temp] = vect[row][counter];
                cout<<testvector[counter-temp];
                counter++;

            }

            cout<<"/";
      
            for(int a = 0; a < col; a++){

                testvector[counter-temp+a] = vect[row][a];
                cout<<testvector[counter-temp+a];

            } 

            if (counter > 4){
                for (int f = 0; f<counter; f++){
                    cout<<testvector[f]<<endl;
                }
                cout<<endl;
            }
            //done going right

            cout<<endl;

            //go down
            cout<<"Going down"<<endl;
            counter = row;
            temp = row;
            while(counter < numCols){

                testvector[counter-temp] = vect[counter][col];
                cout<<testvector[counter-temp];
                counter++;

            }

            cout<<"/";

      
            for(int a = 0; a < row; a++){

                testvector[counter-temp+a] = vect[a][col];
                cout<<testvector[counter-temp+a];

            } 
            
            //done going down
            

            //going diagonal down right
            cout<<"Going left"<<endl;
            counter = col;
            temp = col;
            while(counter > -1){

                testvector[temp-counter] = vect[row][counter];
                cout<<testvector[temp-counter];
                temp2 = temp - counter;
                counter--;

            }

            cout<<"/";

            for(int a = 0; a < numCols - temp2 - 1; a++){

                testvector[a + temp2 + 1] = vect[row][numCols-a-1];
                cout<<testvector[a + temp2 + 1];
            } 

            //done going left

            

           //going up
            cout<<"Going up"<<endl;
            counter = row;
            temp = row;
            while(counter > -1){

                testvector[temp-counter] = vect[counter][col];
                cout<<testvector[temp-counter];
                temp2 = temp - counter;
                counter--;

            }

            cout<<"/";

            for(int a = 0; a < numCols - temp2 - 1; a++){

                testvector[a + temp2 + 1] = vect[numCols-a-1][col];
                cout<<testvector[a + temp2 + 1];
            } 

            */

            //improved algo for going down right - diagonal
            

            cout<<"Going down right"<<endl;
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = vect[counterX][counterY];
                cout<<testvector[counter]<<endl;

                counter++;
                counterX++;
                counterY++;

                if (counterX == numRows){
                    counterX = 0;

                }

                if (counterY == numCols){
                    counterY = 0;

                }

                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }

            //going down left - diagonal
            cout<<"going down left"<<endl;
            counterX = row;
            counterY = col;
            counter = 0;

            while (counter < numRows){

                testvector[counter] = vect[counterX][counterY];
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

                testvector[counter] = vect[counterX][counterY];
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

                testvector[counter] = vect[counterX][counterY];
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

                testvector[counter] = vect[row][counterY];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterY++;

                if (counterY == numCols){
                    counterY = 0;

                }

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

                testvector[counter] = vect[row][counterY];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterY--;

                if (counterY == -1){
                    counterY = numCols - 1;

                }

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

                testvector[counter] = vect[counterX][col];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterX--;

                if (counterX == -1){
                    counterX = numRows - 1;

                }

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

                testvector[counter] = vect[counterX][col];
                cout<<testvector[counter]<<endl;;

                counter++;
                counterX++;

                if (counterX == numRows){
                    counterX = 0;

                }

                // if (counter > 4){
                //     for (int f = 0; f<counter; f++){
                //         cout<<testvector[f]<<endl;
                //     }
                //     cout<<endl;
                // }

            }




            cout<<endl;



        }

        cout<<endl;



    }

    return 0;

}