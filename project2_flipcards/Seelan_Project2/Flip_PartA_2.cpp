#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "d_node.h"

using namespace std;

//complete deck linked list implementation and shuffle function

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

        //constructor of Deck class
        Deck(){

            //allocate a new node for frontcard to contain
            frontcard = new node<Card>();

            //head2 serves as a temporary "head" for each suit
            head2 = frontcard;

            //logic for changing the suit 
                switch(j){
                    
                    case 0:
                    suitVar = "Clubs";
                    break;
                    case 1:
                    suitVar = "Diamonds";
                    case 2:
                    suitVar = "Hearts";
                    break;
                    case 3:
                    suitVar = "Spades";
                    break;

                }

                //logic for implementing the "head" of each suit is a bit different to what's in the for loop
                Card cardtemp(1, suitVar);
                head2->nodeValue = cardtemp;

                t = head2;

                //n represents the node we are on. t is a temporary node variable used.
                for (int i = 2; i<14; i++){
                    
                    //allocate a new node
                    n = new node<Card>();
                    Card cardtemp(i, suitVar);

                    //populate value of node
                    n-> nodeValue = cardtemp;

                    //update the "next" parameter of a t node
                    t->next = n;

                    //move t to our next node, n
                    t = n;

                }
                
                //allocate a new node to represent head 2
                head2 = new node<Card>();

                //have t point to the new "head" in our next suit
                t->next = head2;

                }

            //end our linked list
            n->next = NULL;
            
        }

        //shuffle function declarations
        void shuffle();
        void shuffle3Times();

        //print out our entire linked list
        friend ostream& operator<<(ostream &ostr, const Deck DeckObj);

        //print contents of linked list
        void printList(node<Card>* temp){

            while (temp != NULL) {
                cout << temp->nodeValue <<endl;
                temp = temp->next;
            }

        }


    private:

        //absolute head of our linked list
        node<Card> *frontcard;

        //nodes used to create linked list
        node<Card> *head2;
        node<Card> *n;
        node<Card> *t;

        string suitVar;

};

//the logic of our shuffle algorithm is to randomly choose pair in the linked list and then swap them
void Deck::shuffle(){

    //three node pointers will be used to shuffle our linked list
    node<Card>* temp;
    node<Card>* curr;
    node<Card>* prev;

    //specify parameters for choosing a node in our linked list
    int max = 50;
    int min = 0;
    int range = max - min + 1;
    int num;

    //our index is set to an extremely high value as we want to shuffle as many times possible
    for (int j = 0; j<1000; j++){

        //choose a random pair to shuffle
        num = rand() % range + min;

        //if we are dealing with the head node
        if (num == 0){

            //set our placeholder nodes
            prev = frontcard;
            temp = prev->next;
            curr = temp->next;

            //perform the swap but set our temp to be the absolute front of our linked list after
            prev->next = curr;
            temp->next = prev;
            frontcard = temp;

        }

        //if we are dealing with any node that isn't a header node
        //The logic for this is as follows:
        // prev node -> temp node -> curr node
        else {

            temp = frontcard;

            //traverse to the pair we want to swap
            for (int i = 0; i<num;i++){

                prev = temp;
                temp = temp->next;

            }

            //set curr to the next node present after "temp"
            curr = temp->next;

            //perform the swap
            temp->next = curr->next;
            curr->next = temp;
            prev->next = curr;
            //prev node ->  curr node -> temp node

        }


    }

}

//prototype algo - should be more efficient
// void Deck::shuffle2(){

//     node<Card>* tempx;
//     node<Card>* tempy;
//     node<Card>* prevx;
//     node<Card>* prevy;

//     tempx = frontcard;
//     tempy = frontcard;

//     for (int i = 0; i<8;i++){
//         prevx = tempx;
//         tempx = tempx->next;

//     }

//     for (int i = 0; i<10;i++){
//         prevy = tempy;
//         tempy = tempy->next;

//     }

//     // tempy->next = tempx->next;
//     // prevy->next = tempx;
//     // tempx->next = prevx;
//     // prevx -> next= tempy;
 
// }

void Deck::shuffle3Times(){

    //call on our shuffle function 3 times
    for (int i = 0; i<4; i++){
        shuffle();

    }

}

//main thing about this overloaded operator is that it checks the Card's value within nodeValue and prints if its a normal number
//Ace, Joker, Queen, and King
ostream& operator<<(ostream &ostr, const Deck DeckObj)
{

    //our "pointer" which is used to traverse the linked list
    node<Card>* temp;

    //set temp equal to the front card of the linked list
    temp = DeckObj.frontcard;

    //travese linked list until we reach the end 
    while (temp != NULL) {

        //check what the card value is at each traversal
        switch(temp->nodeValue.getvalue()){
            case 1:
            cout<<"Ace"<<" ";
            cout<<temp->nodeValue.getSuit()<<endl;
            break;
            case 11:
            cout<<"Joker"<<" ";
            cout<<temp->nodeValue.getSuit()<<endl;
            break;
            case 12:
            cout<<"Queen"<<" ";
            cout<<temp->nodeValue.getSuit()<<endl;
            break;
            case 13:
            cout<<"King"<<" ";
            cout<<temp->nodeValue.getSuit()<<endl;
            break;
            default :
            cout<< temp->nodeValue <<endl;

        }

        //traverse linked list
        temp = temp->next;
        }

	return ostr;
}


int main(){

    //our constructor will print out the linked list as well
    Deck Deck1;

    //test output stream operator
    cout<<Deck1;

    cout<<"seperate"<<endl;
    cout<<endl;

    //after being shuffled three times, the shuffled linked list will be printed
    Deck1.shuffle3Times();
    
    //test output stream operator
    cout<<Deck1;

    return 0;

}
