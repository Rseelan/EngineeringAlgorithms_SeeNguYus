#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dictionary.h"

using namespace std;

int main()
{
    dictionary myDict("test-dict.txt");
    myDict.sortDict();

    cout << myDict;

    cout << myDict.searchDict("banana") << endl;
    cout << myDict.searchDict("pogchampion") << endl;

    return 0;
}
