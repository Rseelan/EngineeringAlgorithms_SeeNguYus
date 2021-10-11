#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "d_node.h"

using namespace std;

class Card {

    public:
    
        Card();
        Card(int x, string y);


        void setvalue(int x);
        int getvalue();

        void setSuit(string s);
        string getSuit();


        friend ostream& operator<<(ostream& os, const Card& CD){
            os << CD.value << ' ' << CD.suit;
            return os; 
        }

    private:
        int value;
        string suit;

};

Card::Card(){

    value = 0;
    suit = "NA";
}

Card::Card(int x, string y){
    value = x;
    suit = y;
}

void Card::setvalue(int x){
    value = x;
}

int Card::getvalue(){
    return value;
}

void Card::setSuit(string s){
    suit = s;
}
string Card::getSuit(){
    return suit;
}


class Deck{
    public:
        Deck(){

            frontcard = new node<Card>();
            // Card cardtemp(1, "Clubs");
            // frontcard->nodeValue = cardtemp;

            head2 = frontcard;

            for (int j = 0; j<4; j++){

                if (j == 0){
                    suitVar = "Clubs";  
                }
                else if(j == 1){
                    suitVar = "Diamonds";
                }

                else if(j == 2){
                    suitVar = "Hearts";

                }
                else {
                    suitVar = "Spades";
                }

                //head2 = new node<Card>();
                Card cardtemp(1, suitVar);
                head2->nodeValue = cardtemp;
                //n->next = head2;
                t = head2;

                for (int i = 2; i<14; i++){
                    n = new node<Card>();
                    Card cardtemp(i, suitVar);
                    n-> nodeValue = cardtemp;
                    t->next = n;
                    t = n;

                }


                head2 = new node<Card>();
                t->next = head2;

                }

            n->next = NULL;

            printList(frontcard);
            
        }

        
        void shuffle();

        void printList(node<Card>* temp){

            while (temp != NULL) {
                cout << temp->nodeValue <<endl;
                temp = temp->next;
            }

        }
    private:

        node<Card> *frontcard;
        node<Card> *head2;
        node<Card> *n;
        node<Card> *t;
        node<Card> * last;
        string suitVar;

};

void Deck::shuffle(){

    node<Card>* temp;
    node<Card>* curr;
    node<Card>* prev;

    int max = 50;
    int min = 2;
    int range = max - min + 1;
    int num;


    for (int j = 0; j<100; j++){

        num = rand() % range + min;
        cout<<num<<endl;
        temp = frontcard;

        for (int i = 0; i<num;i++){

            prev = temp;
            temp = temp->next;

        }

        curr = temp->next;
        temp->next = curr->next;
        curr->next = temp;
        prev->next = curr;

    }

    printList(frontcard);

}

int main(){
    Deck Deck1;
    cout<<"seperate"<<endl;
    cout<<endl;
    Deck1.shuffle();
    return 0;
}