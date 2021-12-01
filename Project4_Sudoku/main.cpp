// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <vector>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank
 
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
   public:
      board(int sqSize);
      void clear();
      void initialize(ifstream &fin);

      void print();

      bool isBlank(int i, int j);
      int getCell(int i, int j);

      int ColCheck(int ColIndex, int Num);
      int RowCheck(int RowIndex, int Num);
      int BoxCheck(int RowStartIndex, int ColStartIndex, int Num);

      void initializeConflicts();
      void copyConflicts();
      void updateConflicts();
      void PrintConflicts();

      void setCell(int i, int j, ValueType input);
      void clearCell(int i, int j);

      void resetFromConflicts();
      void backtrack();

      bool IsSolved();
      void solve();
      
      
      void findCell();
      
      
      
      
   private:

      // The following matrices go from 1 to BoardSize in each
      // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

      int numCalls = 0;

      matrix<int> value;
      int Conflicts[BoardSize+1][BoardSize+1][BoardSize+1];
      int ConflictsCopy[BoardSize+1][BoardSize+1][BoardSize+1];
      
      int currentRow, currentCol;
};

board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1)
// Board constructor
{
   clear();
}




void board::findCell()
{
    int max = 0;
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (isBlank(i, j))
            {
                int sum = 0;
                for (int k = 1; k <= BoardSize; k++)
                {
                    sum += Conflicts[i][j][k];
                }
                if (sum > max)
                {
                    max = sum;
                    currentRow = i;
                    currentCol = j;
                }
            }
        }
    }
}




void board::initializeConflicts()
{
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         for (int k = 1; k <= BoardSize; k++)
         {
            Conflicts[i][j][k] = 0;
         }
      }
   }
}

void board::clear()
// Mark all possible values as legal for each board entry
{
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         value[i][j] = 0;
      }
   }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
	   {
	      fin >> ch;

         // If the read char is not Blank
	      if (ch != '.')
         {
            value[i][j] = ch-'0';
         }
         //setCell(i,j,ch-'0');   // Convert char to int
         //set conflict vector to 0
      }
   }
}

void board::setCell(int i, int j, ValueType input)
// Set the value of cell (i,j) to 'input' 
{
   value[i][j] = input;
   updateConflicts();
   // we'll need to update conflicts manually because doing it here will mess
   // with my sinister plans elsewhere
}

void board::clearCell(int i, int j)
// Set value of cell (i,j) to 'Blank'
{
   value[i][j] = 0;
   updateConflicts(); //for consistancy
}


int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (int i = 0; i < v.size(); i++){
      ostr << v[i] << " ";

   }
      
   cout << endl;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
   {
      return value[i][j];
   }
   else
   {
      throw rangeError("bad value in getCell");
   }  
}

//check a specific column for conflicts
int board::ColCheck(int ColIndex, int Num)
{ 
   for (int RowIndex = 1; RowIndex <= BoardSize; RowIndex++)
   {
      if (value[RowIndex][ColIndex] == Num)
      {
         return 1;
      }     
   }
   return 0;
}

//check a specific row for conflicts
int board::RowCheck(int RowIndex, int Num)
{
   for (int ColIndex = 1; ColIndex <= BoardSize; ColIndex++)
   {
      if (value[RowIndex][ColIndex] == Num)
      {
         return 1;
      }   
   }
   return 0;
}

//check a specific box for conflicts
int board::BoxCheck(int RowStartIndex, int ColStartIndex, int Num)
{
   for (int RowIndex = 0; RowIndex < 3; RowIndex++)
   {
         for (int ColIndex = 0; ColIndex < 3; ColIndex++)
         {
            if (value[RowIndex+RowStartIndex][ColIndex+ColStartIndex] == Num)
            {
               return 1;
            }
         }
      }      
   return 0;
}

//copy the conflicts matrix
void board::copyConflicts()
{
      for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         for (int k = 1; k <= BoardSize; k++)
         {
            ConflictsCopy[i][j][k] = Conflicts[i][j][k];
         }
      }
   }
}

//update the conflict matrix
void board::updateConflicts()
{
   int x = 0;
   int y = 0;
   int startRow = 0;
   int startCol = 0;

   copyConflicts();
   initializeConflicts();

   for (int i = 1; i<= BoardSize; i++)
   {
      for (int j = 1; j<=BoardSize; j++)
      {
         if (getCell(i, j) == 0)
         {
            for (int k = 1; k<= BoardSize; k++)
            //conflicts iterator
            {
               //check row
               Conflicts[i][j][k] += RowCheck(i, k);

               //check column
               Conflicts[i][j][k] += ColCheck(j, k);

               //check box
               if (1<=i && i <=3)
               {
                  y = 1;
               }
               else if(4<=i && i <=6)
               {
                  y = 4;
               }
               else if(7<=i && i <=9)
               {
                  y = 7;
               }
               if (1<=j && j <=3)
               {
                  x = 1;
               }
               else if(4<=j && j<=6)
               {
                  x = 4;
               }
               else if(7<=j && j<=9)
               {
                  x = 7;
               }
               Conflicts[i][j][k] += BoxCheck(x,y,k);
            }
         }
         else
         {
            for (int k = 1; k<= BoardSize; k++)
            {
               if (k != getCell(i, j))
               {
                  Conflicts[i][j][k] = 1;
               }
            }
         }  
      }
   }
}



bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
   {
      throw rangeError("bad value in setCell");
   }
   return (getCell(i,j) == 0);
}

void board::print()
// Prints the current board.
{
   for (int i = 1; i <= BoardSize; i++)
   {
      if ((i-1) % SquareSize == 0)
      {
         cout << " -";
	      for (int j = 1; j <= BoardSize; j++)
	      cout << "---";
         cout << "-";
	      cout << endl;
      }
      for (int j = 1; j <= BoardSize; j++)
      {
	      if ((j-1) % SquareSize == 0)
	         cout << "|";
	      if (!isBlank(i,j))
	         cout << " " << getCell(i,j) << " ";
	      else
	         cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 1; j <= BoardSize; j++)
      cout << "---";
   cout << "-";
   cout << endl;
}

void board::PrintConflicts()
{
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         for (int k = 1; k <= BoardSize; k++)
         {
            // format of this function's messages:
            // # conflicts, i, j, k
            // ie: 3 i, j ,k: 1, 5, 2 means 3 conflicts for digit 2 in cell 1,5

            cout<<Conflicts[i][j][k]<<" ";
            cout<<"i, j, k: "<<i<<", "<<j<<", "<<k<<endl;

            // if any set of i, j, k has 0 conflicts, then that k can be placed 
         }
      }
   }
}


void board::resetFromConflicts()
// clears the board and sets cells based on previous conflicts. Will only set a 
// cell that has a 0 for 1 digit of k, and none else, because those are the
// cells that were already filled in.
{
   int numLegal = 0;
   int cellVal;

   //clear();

   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         for (int k = 1; k <= BoardSize; k++)
         {
            if (ConflictsCopy[i][j][k] == 0)
            {
               numLegal++; // if numLegal > 1, more than 1 legal digits in i, j
               cellVal = k;
            }
         }
         if (numLegal == 1)
         {
            setCell(i, j, cellVal);
         }
         else
         {
            clearCell(i, j);
         }
         numLegal = 0; // reset counter
      }
   }
}

void board::backtrack()
// implementing backtracking: when this function is called, the board is
// updated to how it was before the last setCell call
{
   cout << "End me" << endl;
}

bool board::IsSolved()
// Returns true if the entire board has been solved
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (isBlank(i, j) == true)    // Checks if each cell is filled
            {
                cout << numCalls << endl;
                return false;
            }
        }
    }
    cout << "The board has been solved!" << endl;
    return true;
}

void board::solve(){
   numCalls++;

   if(IsSolved())
   {
      print();
   }
   else //go to first blank cell
   {   
   print();
      for (int i = 1; i <= BoardSize; i++)
         {
            for (int j = 1; j <= BoardSize; j++){
               
               // num = 0;
               if(getCell(i,j) == 0)
               {
                     for (int k = 1; k <= BoardSize; k++)
                     {
                        if (Conflicts[i][j][k] == 0)
                        { 
                           setCell(i, j, k);
                           //updateConflicts();

                           solve();

                           clearCell(i, j);
                           //updateConflicts();
                        }
                        // else
                        // {
                        //    num++;
                        // }

                     }
                     // if(num == BoardSize)
                     // {
                     //    cout<<"fuck"<<endl;
                     //    resetFromConflicts();
                     // }
               }
            }
         }
   } 
}


int main()
{
   ifstream fin;
   
   // Read the sample grid from the file.
   string fileName = "sudoku1.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   else
   {
      board b1(SquareSize);

      while (fin && fin.peek() != 'Z')
      {
         b1.initialize(fin);
      }

      b1.initializeConflicts();
      b1.updateConflicts();
      //b1.PrintConflicts();
  


      cout << "   -------------------------    " << endl;
      cout << "-----------Original------------" << endl;
      cout << "   -------------------------    " << endl;
	   b1.print();

      b1.solve();

      cout << "   -------------------------    " << endl;
      cout << "-------------Changed-------------" << endl;
      cout << "   -------------------------    " << endl;
      //b1.setCell(1,2,9);
	   b1.print();

      /****************************************************************************************************
       * Right now. backtracking relies on the Conflicts being correct when you call resetFromConflicts()
       * So, next we have to implement checking for dead ends!
       * 
       * Here's how it ought to work: whenever we call setCell(), we check if it's a dead end.
       * If (and only if!) we have not hit a dead end after calling setCell(), we will update the Conflicts.
       * HOWEVER! If it is indeed a dead end, we then have to backtrack with resetFromConflicts()!!!!!
       ****************************************************************************************************/
      // cout << "   -------------------------    " << endl;
      // cout << "-------------Backtrack--------- " << endl;
      // cout << "   -------------------------    " << endl;
      // b1.resetFromConflicts();
	   // b1.print();

      // b1.backtrack();

      // b1.PrintConflicts();
      
      // b1.IsSolved();
   }
}
