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
      void updateConflicts();
      void PrintConflicts();

      void setCell(int i, int j, ValueType input);
      void clearCell(int i, int j);
      void findCell();

      bool IsSolved();
      void solve();
      
   private:

      // The following matrices go from 1 to BoardSize in each
      // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

      int numCalls = 0;
      int currentRow, currentCol;

      matrix<int> value;
      int Conflicts[BoardSize+1][BoardSize+1][BoardSize+1];
};

board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1)
// Board constructor
{
   clear();
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
            setCell(i,j,ch-'0');
         }
      }
   }
}

void board::setCell(int i, int j, ValueType input)
// Set the value of cell (i,j) to 'input' 
{
   value[i][j] = input;
   updateConflicts();
}

void board::clearCell(int i, int j)
// Set value of cell (i,j) to 'Blank'
{
   value[i][j] = 0;
   updateConflicts();
}

void board::findCell()
{
   /*
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
   */
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         if (isBlank(i, j))
         {
               currentRow = i;
               currentCol = j;
               return;
         }
      }
   }
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
      if (getCell(RowIndex, ColIndex) == Num)
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
      if(getCell(RowIndex, ColIndex) == Num)
      {
         return 1;
      }   
   }
   return 0;
}

//check a specific box for conflicts
int board::BoxCheck(int RowStartIndex, int ColStartIndex, int Num)
{
   for (int RowIndex = RowStartIndex; RowIndex < RowStartIndex + 3; RowIndex++)
   {
      for (int ColIndex = ColStartIndex; ColIndex < ColStartIndex + 3; ColIndex++)
      {
         if(getCell(RowIndex, ColIndex) == Num)
         {
               return 1;
         }
      }
   }      
   return 0;
}

//update the conflict matrix
void board::updateConflicts()
{
   int x = 0;
   int y = 0;
   initializeConflicts();

   for (int i = 1; i<= BoardSize; i++)
   {
      for (int j = 1; j<=BoardSize; j++)
      {
         //if (isBlank(i, j))
         //{
            for (int k = 1; k<= BoardSize; k++)
            //conflicts iterator
            {
               //check row
               Conflicts[i][j][k] += RowCheck(i, k);

               //check column
               Conflicts[i][j][k] += ColCheck(j, k);

               //check box
               switch (squareNumber(i, j))
               {
                  case 1:
                     x = y = 1;
                     break;
                  case 2:
                     x = 1;
                     y = 4;
                     break;
                  case 3:
                     x = 1;
                     y = 7;
                     break;
                  case 4:
                     x = 4;
                     y = 1;
                     break;
                  case 5:
                     x = y = 4;
                     break;
                  case 6:
                     x = 4;
                     y = 7;
                     break;
                  case 7:
                     x = 7;
                     y = 1;
                     break;
                  case 8:
                     x = 7;
                     y = 4;
                     break;
                  case 9:
                     x = y = 7;
                     break;
                  default:
                     throw range_error("Invalid Square");
                     break;
               }
               Conflicts[i][j][k] += BoxCheck(x,y,k);
               // if(x == 1 && y == 4 && k == 1) 
               //    cout << "(" << i << ", " << j << ") = box #" << squareNumber(i, j) << " | Conflicts: " << Conflicts[i][j][k] << endl;
            }
         //}
         /*else
         {
            for (int k = 1; k<= BoardSize; k++)
            {
               if (k != getCell(i, j))
               {
                  Conflicts[i][j][k] = 1;
               }
            }
         }*/  
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

bool board::IsSolved()
// Returns true if the entire board has been solved
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (isBlank(i, j) == true)    // Checks if each cell is filled
            {
                cout << "Number of recursive calls: " << numCalls << endl;
                return false;
            }
        }
    }
    cout << "The board has been solved after " << numCalls << "recursive calls!" << endl;
    return true;
}

void board::solve()
{
   numCalls++;
   int i, j;

   if(IsSolved())
   {
      print();
      cout << "hey \n";
   }
   else //go to first blank cell
   {
      //print();
      findCell();
      i = currentRow;
      j = currentCol;

      for (int k = 1; k <= BoardSize; k++)
      {
         if (Conflicts[i][j][k] == 0)
         {
            setCell(i, j, k);
            //print();
            solve();
            clearCell(i, j);
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

      //cout << squareNumber(2, 5) << endl;

      //b1.PrintConflicts();

      // cout << "   -------------------------    " << endl;
      // cout << "-----------Original------------" << endl;
      // cout << "   -------------------------    " << endl;
      // b1.setCell(1,4,1);
	   // b1.print();
      // cout << b1.BoxCheck(1, 4, 1) << endl;

      //b1.PrintConflicts();

      // cout << "   -------------------------    " << endl;
      // cout << "-------------Changed-------------" << endl;
      // cout << "   -------------------------    " << endl;
      b1.solve();
	   // b1.print();

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
