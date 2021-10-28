#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <fstream>
#include "d_matrix.h"


class grid
{
    public:
        grid(string filename);  //default constructor
        matrix<string> letters; //letters of the grid   
};

grid::grid(string filename)
{
    ifstream fileIn(filename);
    string bound1, bound2;

    if(fileIn.is_open())
    {
        fileIn >> bound1;
        fileIn >> bound2;
        letters.resize(stoi(bound1), stoi(bound2));

        for(int i = 0; i < stoi(bound1); i++)
        {
            for(int j = 0; j < stoi(bound2); j++)
            {
                fileIn >> letters[i][j];
            }
        }
    } //end if
    else
    {
        cout << "Unable to open file \n";
    }
    fileIn.close();
}

#endif