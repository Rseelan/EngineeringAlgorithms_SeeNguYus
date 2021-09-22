#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class code
{
public:
    int length;
    int range;
    vector<int> v;
    code(int n, int m)
    {
        length = n;
        range = m;
        v.resize(length);
    }

    int checkCorrect(code guess);
    int checkIncorrect(code guess);
    int main();
};

void makeSecret(int n, int m)
{
    code secret(int n, int m);
    for (int i = 0; i < secret.length; i++)
    {
        secret.v[i] = rand() % (secret.range + 1);
    }
}

int code::checkCorrect(code guess)
{
    int count = 0;
    for (int i = 0; i < secret.length; i++)
    {
        if (secret.v[i] == guess.v[i])
        {
            count++;
        }
    }
    return count;
}
int code::checkIncorrect(code guess)
{
    int count = 0;
    for (int i = 0; i)
    {

    }
}


int code::main()
{
    makeSecret(5, 5);
    code guess;
    guess.v.
}