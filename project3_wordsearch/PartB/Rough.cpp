#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Heap{

    public:

        int parent(int n){

            return n/2;

        }

        int left(int n){

            return n*2;

        }

        int right(int n){

            return (n*2)+1;

        }

        int getItem(int n){

            return heapArray[n];

        }

        void Max_Heapify(vector<int> &A, int i){

            int largest;
            int temp;

            l = left(i);
            r = right(i);

            if ((l <= A.size()) && (A[l] > A[i])){

                largest = l;

            }

            else{

                largest = r;

            }

            if ((r <= A.size()) && (A[r] > A[largest])){

                largest = r;

            }

            if (largest != i){

                //swap A[i] with A[largest]
                temp = A[i];
                A[i] = A[largest];
                A[largest] = temp;
                Max_Heapify(A, largest);

            }

        }

        void buildMaxHeap(vector<int> &A){

            for (int i = A.size(); i < 1; i--){

                Max_Heapify(A, i);

            }

        }
    
        void heapsort(vector <int> arr, int n)
        {
            for (int i = n / 2 - 1; i >= 0; i--)
            {
                maxHeapify(arr, n, i);
            }
            for (int i=n-1; i>=0; i--)
            {
                swap(arr[0], arr[i]);
                maxHeapify(arr, i, 0);
            }
        }

    private:

        vector<int> heapArray;

        int heapsize = 0;

        int l,r;


};


int main(){

    cout<<"bruh";

    for(int i = 5; i > 0; i--){

        cout<<i<<endl;
    }

    return 0;

}
