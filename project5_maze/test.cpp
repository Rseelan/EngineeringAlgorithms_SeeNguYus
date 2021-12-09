// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

class maze
{
   public:
      maze(ifstream &fin);
      void print(int,int,int,int);
      bool isLegal(int i, int j);

      void setMap(int i, int j, int n);
      int getMap(int i, int j) const;
	
      void mapMazeToGraph(maze &m, graph &g);

   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;
      matrix<int> map;      // Mapping from maze (i,j) values to node index values
};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n. 
{
   map[i][j] = n;
}

int maze ::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
   return map[i][j];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;

   char x;
   int n = 0;

   value.resize(rows,cols);
   map.resize(rows,cols);

   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
	      fin >> x;
	      if (x == 'O')
         {   
            setMap(i,j,n);
            n++;
            value[i][j] = true;
         }
	      else
         {
            setMap(i,j,-1);
	         value[i][j] = false;
         }
      }

   map.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows-1 || goalJ < 0 || goalJ > cols-1)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows-1 || currJ < 0 || currJ > cols-1)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	      if (i == goalI && j == goalJ)
	         cout << "*";
	      else
	         if (i == currI && j == currJ)
	            cout << "+";
	      else
	         if (value[i][j])
		         cout << "0";
	      else
		      cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
   if (i < 0 || i > rows-1 || j < 0 || j > cols-1)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(maze &m, graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
   int n = 1;
   bool tmp;
   for(int i = 0; i < rows; i++)
   for(int j = 0; j < cols; j++)
   {  
      tmp = value[i][j]; 
      if(tmp) g.addNode(m.getMap(i,j));
   }

   for(int i = 0; i < rows; i++)
   for(int j = 0; j < cols; j++)
   {
      tmp = value[i][j]; 
      if(tmp)
      {
         if(i > 0)
         {
            tmp = value[i-1][j];
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i-1,j), 0);
         }
         if(i < rows-1)
         {
            tmp = value[i+1][j];
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i+1,j), 0);
         }
         if(j > 0)
         {
            tmp = value[i][j-1];
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i,j-1), 0);
         }
         if(j < cols-1)
         {
            tmp = value[i][j+1];
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i,j+1), 0);
         }
      }
   }
}



int main()
{
   char x;
   ifstream fin;
   
   // Read the maze from the file.
   string fileName = "maze.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      graph g;

      while (fin && fin.peek() != 'Z')
      {
         maze m(fin);
         m.print(6,9,0,0);
         m.mapMazeToGraph(m, g);
      }

      // g.printNodes();
      // g.printEdges();
   } 
   catch (indexRangeError &ex) 
   { 
      cout << ex.what() << endl; exit(1);
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }

   
}
