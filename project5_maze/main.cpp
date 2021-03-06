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
        void DFS_stack_solve(graph &g);
      void markEdges(graph &g);
      void printSteps(graph &g);

   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;
      matrix<int> map;      // Mapping from maze (i,j) values to node index values
      stack<node> stack_v;
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
            setMap(i,j,n);	//set legal node to new id
            n++;
            value[i][j] = true;
         }
	      else
         {
            setMap(i,j,-1);	//set illegal node to id = -1
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
	//we know which direction we went based on that edge's wieght
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
      return "Invalid edge in maze::edgeDirection";
      break;
   }
}

void maze::mapMazeToGraph(maze &m, graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
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
            tmp = value[i-1][j];	//check node above 
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i-1,j), 4);
         }
         if(i < rows-1)
         {
            tmp = value[i+1][j];	//check node below
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i+1,j), 2);
         }
         if(j > 0)
         {
            tmp = value[i][j-1];	//check left node
            if(tmp) g.addEdge(m.getMap(i,j), m.getMap(i,j-1), 3);
         }
         if(j < cols-1)
         {
            tmp = value[i][j+1];	//check right node
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
   // if a path is found, print out how we got there
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
      if(currI > 0)	//check above current node
         if(isLegal(currI-1,currJ) && !g.isVisited(getMap(currI-1,currJ)))
         {
            nextI = currI - 1;
            nextJ = currJ;
            nextNode = getMap(nextI, nextJ);

            moves.push_back(edgeDirection(g, currentNode, nextNode));
            findPathRecursive(m, g, goalI, goalJ, nextI, nextJ, moves);
            moves.pop_back();      //backtrack
         }
      if(currI < rows-1)	//check below current node
         if(isLegal(currI+1,currJ) && !g.isVisited(getMap(currI+1,currJ)))
         {
            nextI = currI + 1;
            nextJ = currJ;
            nextNode = getMap(nextI, nextJ);

            moves.push_back(edgeDirection(g, currentNode, nextNode));
            findPathRecursive(m, g, goalI, goalJ, nextI, nextJ, moves);
            moves.pop_back();	//backtrack
         }
      if(currJ > 0)	//check to the left of current node
         if(isLegal(currI,currJ-1) && !g.isVisited(getMap(currI,currJ-1)))
         {
            nextI = currI;
            nextJ = currJ - 1;
            nextNode = getMap(nextI, nextJ);

            moves.push_back(edgeDirection(g, currentNode, nextNode));
            findPathRecursive(m, g, goalI, goalJ, nextI, nextJ, moves);
            moves.pop_back();	//backtrack
         } 
      if(currJ < cols-1)	//check to the right of current node
         if(isLegal(currI,currJ+1) && !g.isVisited(getMap(currI,currJ+1)))
         {
            nextI = currI;
            nextJ = currJ + 1;
            nextNode = getMap(nextI, nextJ);

            moves.push_back(edgeDirection(g, currentNode, nextNode));
            findPathRecursive(m, g, goalI, goalJ, nextI, nextJ, moves);
            moves.pop_back();	//backtrack
         }
   }
   //this ends up getting printed a lot of times, but it does the job
   if(g.allNodesVisited()) 
      cout << "No more possible paths \n";
}

void maze::DFS_stack_solve(graph &g){

   //mark all nodes as unvisited
   for (int i = 0; i <  g.numNodes(); i++){
      g.unVisit(i);
   }


   //push first node to stack
   node currentNode = g.getNode(0);
   stack_v.push(currentNode);

   //mark first node as visited
   g.visit(0);

   //variables used for traversal
   int x = 0;
   int y = 0;

   //mark first node
   g.getNode(0).mark();

   //traverse graph until stack is empty
    while(!stack_v.empty()){

       //check if traversal variables are the destination location parameters
        if((x == rows - 1) && (y == cols - 1)){
           cout<<"Destination reached at "<<x<<", "<<y<<endl;
            break;
        }
      
      //current node equal to top of the stack
      currentNode = stack_v.top();

      //check if it's possible to traverse right
      if((map[x][y+1] !=-1)&& (y < cols - 1)&&g.getNode(getMap(x, y+1)).isVisited() == false){\


         cout<<"traverse right"<<endl;

         //This node is visited
         g.visit(getMap(x, y+1));

         //push this node to the top of the stack
         currentNode = g.getNode(getMap(x, y+1));
         stack_v.push(currentNode);
         y++;
      
      }

      //traverse down
      else if((map[x+1][y] != -1)&&(x < rows - 1)&&g.getNode(getMap(x+1, y)).isVisited() == false){
   
         cout<<"traverse down"<<endl;

         //This node is visited
         g.visit(getMap(x+1, y));

         //push this node to the top of the stack
         currentNode = g.getNode(getMap(x+1, y));
         stack_v.push(currentNode);
         x++;
         
      }

      //traverse left
      else if((y>0)&&(map[x][y-1] !=-1)&&g.getNode(getMap(x, y-1)).isVisited() == false){

         cout<<"traverse left"<<endl;

         //this node is visited
         g.visit(getMap(x, y-1));

         //push this node to the top of the stack
         currentNode = g.getNode(getMap(x, y-1));
         stack_v.push(currentNode);
         y--;
      
      }

      //traverse up
      else if((x>0)&&(map[x-1][y] !=-1)&&g.getNode(getMap(x-1, y)).isVisited() == false){
         
         cout<<"traverse up"<<endl;

         //this node is visited
         g.visit(getMap(x-1, y));

         //push this node to the top of the stack
         currentNode = g.getNode(getMap(x-1, y));
         stack_v.push(currentNode);
         x--;
         
         
      }
      else{

        //back track
        //mark current and label it as visited 
        g.getNode(getMap(x,y)).mark();
        g.visit(currentNode.getId());

        //pop the top node
        stack_v.pop();
        currentNode = stack_v.top();

        //unMark the current node
        g.getNode(getMap(x,y)).unMark();

        //find indices of node based on id
        for (int a = 0; a < rows; a++){

            for(int b = 0; b < cols; b++){

                if(map[a][b] == currentNode.getId()){
                    x = a;
                    y = b;
  
                }

            }
        }

      }

      //mark node based on location parameters
      g.getNode(getMap(x,y)).mark();

      cout<<"row, col :"<<x<<", "<<y<<endl;

   }

   
   
   cout<<"No more paths exist"<<endl;
   markEdges(g);

}

//mark the required edges used for node traversal
void maze::markEdges(graph &g){

   //examine every edge to see if it touches a marked node
    for(int i = 0; i<g.numNodes(); i++){
      
      for(int j = 0; j < g.numNodes(); j++){

          if((i<j)&&(g.getNode(i).isMarked() == true)&&(g.getNode(j).isMarked() == true)&&(g.isEdge(i, j))){

            g.mark(i, j);

          }
      }
    }
}

void maze::printSteps(graph &g){

   cout<<"The following steps are taken to reach the destination."<<endl;
   //print the state of all nodes and edges
   //g.printNodes();
   //g.printEdges();

   int edge = 0;

   for(int i = 0; i<g.numNodes(); i++){
      
      for(int j = 0; j < g.numNodes(); j++){

         //examine every adjacent node for traversal
         if((g.getNode(i).isMarked() == true)&&(g.getNode(j).isMarked() == true)&& (g.isEdge(i, j))&&(g.isMarked(i,j))){
            
               
               edge = g.getEdgeWeight(i, j);
               
               if(edge == 1){
                  cout<<"Go right"<<endl;
               }
               if(edge == 2){
                  cout<<"Go down"<<endl;
               }
               if(edge == 3){
                  cout<<"Go left"<<endl;
               }
               if(edge == 4){
                  cout<<"Go up"<<endl;
               }

               cout<<"Currently at node "<<g.getNode(j).getId()<<endl;
         }
      }
   }
}

int main()
{
   char x;
   ifstream fin;
   
   // Read the maze from the file.
   //remember to change the name of the text file
   string fileName = "Maze 1.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      graph g;
      vector<string> moves;	//stores the steps taken to the destination

      while (fin && fin.peek() != 'Z')
      {
         maze m(fin);

         //remember to change the destination coordinates
         m.print(6,9,0,0);
         m.mapMazeToGraph(m, g);

         //remember to change the destination coordinates
         m.findPathRecursive(m, g, 6, 9, 0, 0, moves);

         cout<<"The non recursive method is used below"<<endl;
         cout<<endl;

	 //solve the maze without recursion
         m.DFS_stack_solve(g);
         cout<<endl;
	 
         m.markEdges(g);
         cout<<endl;

         m.printSteps(g);
      }
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
