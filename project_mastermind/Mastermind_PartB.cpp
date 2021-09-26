#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Response {

    public:

        Response(){
            
            numCorrect = 0;
            numIncorrect = 0;

        }

        void set(int &x, int &y);

        int get() const;

        int get_numCorrect() const;

        int get_numIncorrect() const;


        //friend Response operator<<(Response const &);
        friend ostream& operator<< (ostream& ostr, const Response& r);
        friend bool operator == (const Response &lhs, const Response &rhs);

    

    private:

        int numCorrect;

        int numIncorrect;

};

void Response::set(int &x, int &y){

    numCorrect = x;
    numIncorrect = y;

}

int Response::get() const{

    return (numCorrect, numIncorrect);

}

int Response::get_numCorrect() const{

    return (numCorrect);
}

int Response::get_numIncorrect() const{

    return (numIncorrect);

}

//Response operator<<(Response const &obj){

    //cout<<obj.get()<<endl;

//}

ostream& operator<< (ostream& ostr, const Response& r){
    ostr << r.numCorrect << ',' << r.numIncorrect;
    return ostr;
}

bool operator == (const Response &lhs, const Response &rhs){

    return ((lhs.get_numCorrect() == rhs.get_numCorrect()) && (lhs.get_numIncorrect() == rhs.get_numIncorrect()));

}