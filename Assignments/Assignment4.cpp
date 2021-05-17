//Name: Jake Tremblay
//HeapSort

#include <iostream>

using namespace std;

class maxHeap {
    int *heapArr;
    int heapCap;
    int currentSize;

    public:
        maxHeap(int cap){
            currentSize = 0; 
            heapCap = cap; 
            heapArr = new int[heapCap];
        }

        int getParent(int i){ return (i-1)/2; }

        int getLeft(int i){ return (2*i)+1; }

        int getRight(int i){ return (2*i)+2; }

        int getSize(){ return currentSize; }

        bool isLeaf(int i){ return (i < currentSize/2) ? false : true; }

        void swap(int &a, int &b){
            int temp = b;
            b = a;
            a = temp;
        }

        void siftUp(int i){
            while(i > 0 && getParent(i) > heapArr[i]){
                swap(heapArr[i], heapArr[getParent(i)]);
                i = getParent(i);
            }
        }

        void siftDown(int i){
            while(!isLeaf(i)){
                int left = getLeft(i);
                int right = getRight(i);
                int larger = left;

                if(right < currentSize){
                    larger = (heapArr[left] < heapArr[right]) ? right : left;
                }
                if(heapArr[i] >= heapArr[larger]){
                    break;
                }
                swap(heapArr[i], heapArr[larger]);
                i = larger;

            }
        }

        void insert(int k){
            if(currentSize >= heapCap){
                throw "Overflow";
            }

            int i = currentSize;
            heapArr[i] = k;
            siftUp(i);
            currentSize++;  
        }

        void removeAt(int i){
            if(i < 0 || currentSize <= i){
                throw "Underflow";
            } else if(currentSize == 1){
                 cout << "Removing: " << heapArr[--currentSize];
            }
            
            int target = heapArr[i];
            heapArr[i] = heapArr[--currentSize];
            if(heapArr[i] > target){
                siftDown(i);
            } else {
                siftUp(i);
            }
        }

        void extractMax(){
            if(currentSize <= 0){
                throw "Underflow";
            }
            if(currentSize == 1){
                cout << heapArr[--currentSize] << " ";
                return;
            }
            int target = heapArr[0];
            heapArr[0] = heapArr[--currentSize];
            siftDown(0);
            cout << target << " ";
        }

        /* Create a Max Heap from Array A, whose size is len. */
        void heapify(int A[], int len){
            heapArr = A;
            currentSize = len;
            int lastInternalNodeIndex = (len/2) - 1;
            for(int i = lastInternalNodeIndex; i >= 0; i--){
                siftDown(i);
            }
        }
};

    /* Sort array into a max heap*/ 
    void heapSort(int A[], int len){
        maxHeap currentHeap(len);
        currentHeap.heapify(A, len);
        int i = len;
        while(currentHeap.getSize() > 0){
            currentHeap.extractMax();
        }
    }


int main(){
    int input, inputSize = 0;
    const int heapCapacity = 50;
    int inputArr[heapCapacity] = {0};

    cout << "ENTER NUMERICAL VALUES, or enter any negative number to execute heapSort:" << endl;
    for(int i = 0; i < heapCapacity; i++){
        cin >> input;
        
        if(cin.fail()){ //checks to see if cin failed to assign input (user entered something that cant be assigned as int)
            cout << "No funny buisness, please try again." << endl;
            return -1;  
        } else if(input < 0){ //escape with any negative number
            break;
        } else if(input >= 0){ 
            inputArr[i] = input;
            inputSize++;
        }
    }

    try{
        heapSort(inputArr, inputSize);
    } catch (const exception &exc){
        cerr << exc.what(); 
    }

    return 0;
}
