/******************************************************************************
 * Project 1b		   Group members:				      *
 * 			   Rohan Seelan - seelan.r@northeastern.edu	      *
 * 			   Andrew Nguyen - nguyen.andrew@northeastern.edu     *
 * 			   Arbid Ysuuf - yusuf.ar@northeastern.edu            *
 * 								     	      *
 * This program contains the declaration of the code class, the code class's  *
 * member functions, as well as a main function that implements a rough	      *
 * version of the mastermind game.					      *
 ******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "mastermind.h"

using namespace std;

int main()
{
	int length;	//length of secret code
	int range;	//range of numbers inside secret code

	cout << "How many numbers would you like the secret code to be?  \n";
	cin >> length;
	cout << "What would you like the range of numbers to be?  \n";
	cin >> range;

	mastermind codemaker(length, range);

	codemaker.playGame();

	return 0;
}
