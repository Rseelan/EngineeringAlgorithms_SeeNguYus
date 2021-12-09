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
      string edgeDirection(const graph &g, int i, int j);

      void mapMazeToGraph(maze &m, graph &g);
      void findPathRecursive(maze &m, graph &g, int goalI, int goalJ, int currI, int currJ, vector<string> moves);

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
   int n = 0; //node id

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

string maze::edgeDirection(const graph &g, int i, int j)
// returns what direction you must travel to get from node i to node j
{
   switch (g.getEdgeWeight(i, j))
   {
   case 1:
      return "Move right. \n";
      break;

   case 2:
      return "Move down. \n";
      break;
   
   case 3:
      return "Move left. \n";
      break;
   
   case 4:
      return "Move up. \n";
      break;
   
   default:
      return "invalid edge. \n";
      break;
   }
}

void maze::mapMazeToGraph(maze &m, graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
   int n = 1;
   bool tmp;

   //create list of nodes from maze map
   for(int i = 0; i < rows; i++)
   for(int j = 0; j < cols; j++)
   {  
      tmp = value[i][j]; 
      if(tmp) g.addNode(m.getMap(i,j));
   }

   //Creating edges. If two nodes are adjacent create an edge bw them.
   //Edge weight corresponds to direction 1 = right, 2 = down, 3 = left, 4 = up
   for(int i = 0; i < rows; i++)
   for(int j = 0; j < cols; j++)
   {
      tmp = value[i][j]; 
      if(tmp)
      {
         if(i > 0)
         {
            tmp = value[i-1][j];
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i-1,j), 4);
         }
         if(i < rows-1)
         {
            tmp = value[i+1][j];
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i+1,j), 2);
         }
         if(j > 0)
         {
            tmp = value[i][j-1];
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i,j-1), 3);
         }
         if(j < cols-1)
         {
            tmp = value[i][j+1];
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i,j+1), 1);
         }
      }
   }
}

void maze::findPathRecursive(maze &m, graph &g, int goalI, int goalJ, int currI, int currJ, vector<string> moves)
{
   int nextI, nextJ, nextNode;
   int currentNode = getMap(currI,currJ);

   g.visit(currentNode);

   if(currentNode == getMap(goalI,goalJ))
   // if a path is found, print out how to get there
   {  
      cout << "------------Path found: ------------\n";
      for(int i = 0; i < moves.size(); i++)
         cout << "Step " << i+1 << ": " << moves[i];
      cout << "------------------------------------\n";
      cout << endl;
   }
   else if(!g.allNodesVisited())
   // if there are unvisisted nodes, continue to search for a path by calling
   // function on adjacent nodes:
   {   
      if(currI > 0) 
         if(isLegal(currI-1,currJ) && !g.isVisited(getMap(currI-1,currJ)))
         {
            nextI = currI - 1;
            nextJ = currJ;
            nextNode = getMap(nextI, nextJ);

            moves.push_back(edgeDirection(g, currentNode, nextNode));
            findPathRecursive(m, g, goalI, goalJ, nextI, nextJ, moves);
            moves.pop_back();      
         }
      if(currI < rows-1)
         if(isLegal(currI+1,currJ) && !g.isVisited(getMap(currI+1,currJ)))
         {
            nextI = currI + 1;
            nextJ = currJ;
            nextNode = getMap(nextI, nextJ);

            moves.push_back(edgeDirection(g, currentNode, nextNode));
            findPathRecursive(m, g, goalI, goalJ, nextI, nextJ, moves);
            moves.pop_back();
         }
      if(currJ > 0)
         if(isLegal(currI,currJ-1) && !g.isVisited(getMap(currI,currJ-1)))
         {
            nextI = currI;
            nextJ = currJ - 1;
            nextNode = getMap(nextI, nextJ);

            moves.push_back(edgeDirection(g, currentNode, nextNode));
            findPathRecursive(m, g, goalI, goalJ, nextI, nextJ, moves);
            moves.pop_back();
         } 
      if(currJ < cols-1) 
         if(isLegal(currI,currJ+1) && !g.isVisited(getMap(currI,currJ+1)))
         {
            nextI = currI;
            nextJ = currJ + 1;
            nextNode = getMap(nextI, nextJ);

            moves.push_back(edgeDirection(g, currentNode, nextNode));
            findPathRecursive(m, g, goalI, goalJ, nextI, nextJ, moves);
            moves.pop_back();
         }
   }
   if(g.allNodesVisited()) 
      cout << "No more possible paths \n";
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
      vector<string> moves;

      while (fin && fin.peek() != 'Z')
      {
         maze m(fin);
         m.print(6,9,0,0);
         m.mapMazeToGraph(m, g);
         m.findPathRecursive(m, g, 6, 9, 0, 0, moves);
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
