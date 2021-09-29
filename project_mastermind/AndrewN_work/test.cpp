#include <iostream>
#include <stdlib.h>
#include <vector>
#include "mastermind.h"

using namespace std;

int main()
{
	//Initializing the game:
	mastermind codemaker;

	cout<<"Secret code: ";
	codemaker.printSecretCode();

	cout<<"Number correct, number incorrect: \n";
	cout<<codemaker.getResponse(codemaker.humanGuess())<<"\n";

	return 0;
}
