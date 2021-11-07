#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Heap{

    public:


        int parent(int n){

            return (n)/2;

        }

        int left(int n){

            return n*2 + 1;

        }

        int right(int n){

            return (n*2)+2;

        }

        int getItem(int n){

            return heapArray[n];

        }

        void Max_Heapify(vector<string> &A, int heapsize, int i){

            int largest = i;
            string temp;
    
            l = left(i);
            //cout<<"Left is "<<l<<endl;
            r = right(i);
            //cout<<"Right is "<<r<<endl;

            if ((l < heapsize) && (A[l] > A[largest])){

                largest = l;
                

            }


            if ((r < heapsize) && (A[r] > A[largest])){

                largest = r;

            }

            if (largest != i){

                //swap A[i] with A[largest]
                temp = A[i];
                A[i] = A[largest];
                A[largest] = temp;
                Max_Heapify(A, heapsize, largest);

            }

        }

        void buildMaxHeap(vector<string> &A, int heapsize){


            //cout<<"size is : "<<A.size()<<endl;
            int a = A.size();
            //cout<<"gu";

            for (int i = (heapsize/2)-1; i >= 0; i--){

                //cout<<"c2";
                Max_Heapify(A, heapsize, i);
                cout<<"Iterate: "<<i<<endl;

            }

        }

        void heapsort(vector <string> &A, int heapsize){

            buildMaxHeap(A, heapsize);

            /*for (int i = heapsize/2 - 1; i>= 0; i--){

                Max_Heapify(A, heapsize, i);

            }*/

            //int a = A.size();
            string temp;

            for (int i = heapsize-1; i > 0; i--){
                cout<<"Iterate is b"<<i<<endl;
                //swap A[0] with A[i]
                temp = A[0];
                A[0] = A[i];
                A[i] = temp;

                Max_Heapify(A, i, 0);


            }

            cout<<"Check1"<<endl;

        }

        void InitializeMaxHeap(){

            //create shitty array - pre heap

            //vector <int> sample = {12, 11, 13, 5, 6, 7};
            vector <string> sample = {"j", "a", "u", "o", "b", "x", "v"};

            int heapSize = sample.size();

            //buildMaxHeap(sample);
            heapsort(sample, heapSize);
            cout<<"Check2"<<endl;
            printarray(sample, heapSize);

            //build max heap

        }

        void printarray(vector <string> A, int heapsize){
            
            for (int i = 0; i< heapsize; i++){
                cout<<"New Array is "<<A[i]<<endl;
            }

        }


    private:

        vector<int> heapArray;

        int heapsize = 0;

        int l,r;


};


int main(){

    //cout<<"bruh";

    Heap heap1;
    heap1.InitializeMaxHeap();


    return 0;

}