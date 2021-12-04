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
      vector<ValueType> findValue();

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

vector<ValueType> board::findValue()
{
   vector<ValueType> numDigits(BoardSize + 1, 0); //# occurances of each digit
   vector<bool> isChecked(BoardSize + 1, 0); //have we looked at each digit
   vector<ValueType> rankDigits; //list digits based on how often they appear

   //how many of each digit is there?
   for (int i = 1; i <= BoardSize; i++) 
      for (int j = 1; j <= BoardSize; j++) 
         numDigits[getCell(i, j)]++;
         //numDigits[0] = number of blank cells, 
         //numDigits[1] = number of cells with 1, etc.

   while (rankDigits.size() < 9)
   {
      int max = 0;

      for(int n = 1; n < numDigits.size(); n++)
         if (numDigits[n] > max) 
            max = numDigits[n];

      for(int m = 1; m < numDigits.size(); m++)
         if(numDigits[m] == max && !isChecked[m])
         {
            rankDigits.push_back(m);
            numDigits[m] = 0;
            isChecked[m] = 1;
         }      
      //the digit that occurs the most in the board will be the first item in
      //rankDigits, and then the second most is the second, and so on
   }
   return rankDigits;
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

bool board::IsSolved()
// Returns true if the entire board has been solved
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (isBlank(i, j) == true)    // Checks if each cell is filled
            {
               //cout << "Number of recursive calls: " << numCalls << endl;
               return false;
            }
        }
    }
    cout << "The board has been solved after " << numCalls << " recursive calls!" << endl;
    return true;
}



void board::solve()
{
   numCalls++;
   int i, j;
   vector<ValueType> digits = findValue();

   // for(int i = 0; i < 9; i++)
   //    cout << digits[i] << " ";
   // cout << endl;

   if(IsSolved())
   {
      print();
   }
   else //go to first blank cell
   {
      findCell();
      i = currentRow;
      j = currentCol;

      for (int k = 0; k < digits.size(); k++)
      {
         if (Conflicts[i][j][digits.at(k)] == 0)
         {
            setCell(i, j, digits.at(k));
            solve();
            clearCell(i, j);
         }   
      }
   }
}         
      
   



int main()
{
	ifstream fin1;
   ifstream fin2;
   ifstream fin3;
   
   // Read the sample grid from the file.
   string fileName = "sudoku1.txt";
   string fileName = "sudoku2.txt";
   string fileName = "sudoku3.txt";

   fin1.open(fileName.c_str());
   if (!fin1 || !fin2 || !fin3)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   else
   {
      board b1(SquareSize);
      board b2(SquareSize);
      board b3(SquareSize);

      while (fin1 && fin1.peek() != 'Z')
      {
         b1.initialize(fin1);
      }

      b1.print();

      b1.solve();
   }
}
