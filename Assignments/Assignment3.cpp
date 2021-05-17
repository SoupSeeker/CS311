//Name: Jake Tremblay
//Student ID: 200633568
//Email: tremb008@cougars.csusm.edu
//Selection, Bubble, Insertion, Quick, and Merge Sort

#include <iostream>
#include <array>

using namespace std;


//some utility functions to help us print, swap
void printArray(int input[], int size){
    for(int i = 0; i < size; i++){
        cout << input[i] << " ";
    }
    cout << endl;
}

void swap(int * a, int * b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

//instead of finding max number in array and putting it in back
//put lowest in front for ascending order
void selectSort(int input[], int size){
    int lowestIndex;

    for(int i = 0; i < size-1; ++i){
        lowestIndex = i;
        //loop in front of the sorted elements
        for(int k = i+1; k < size; k++){
            if(input[k] < input[lowestIndex]){
                lowestIndex = k;
            }         
        }
        swap(&input[lowestIndex], &input[i]);  
    }
}

//do size-i-1 for inner loop, anything before i is sorted
void bubbleSort(int input[], int size){
    for(int i = 0; i < size-1; i++){

        for(int k = 0; k < size-i-1; k++){
            if(input[k] > input[k+1]){
                swap(&input[k], &input[k+1]);
            }
        }
    }
}

//pivot is first element after each step, lagIndex will lag behind i by 1 position
void insertionSort(int input[], int size){
    int pivot=0, lagIndex=0;

    for(int i = 1; i < size; i++){
        lagIndex = i-1;
        pivot = input[i];

        while(lagIndex >=0 && input[lagIndex] > pivot){
            input[lagIndex + 1] = input[lagIndex];
            lagIndex -= 1;
        }

        input[lagIndex + 1] = pivot;
    }
}


//Following sudo-code instructions from slide, set pivot to the 
//first element we see
int partition(int input[], int start, int end){
    int pivot = input[start];
    int partitionIndex = start;

    for(int k = start+1; k <= end; k++){
        if(input[k] <= pivot){
            swap(&input[k], &input[++partitionIndex]);           
        }
    }
    swap(&input[partitionIndex], &input[start]);
    return (partitionIndex);
}

//Recrusively calls quicksort using the partition() method
//to split up array into subarray, then sorting that
void quickSort(int input[], int start, int end){
    if(start >= end){
        return;
    } else {
        int partitionIndex = partition(input, start, end);
        quickSort(input, start, partitionIndex-1);
        quickSort(input, partitionIndex+1, end);
    }
}

//uses the sudo code we went over in class
void merge(int input[], int start, int pivot, int end){
    int inputB[50];

    int i = start, k = start;
    int j = pivot+1;
    
    while(i <= pivot && j <= end){
        if(input[i] <= input[j]){
            inputB[k++] = input[i++];
        } else {
            inputB[k++] = input[j++];
        }
    }

    while(i <= pivot){
        inputB[k++] = input[i++];
    }
    while(j <= end){
        inputB[k++] = input[j++];
    }

    for(int n = start; n <= end; n++){
        input[n] = inputB[n];
    } 
    
}

//recursively chops up the input, sends it to the merge() function
void mergeSort(int input[], int start, int end){
    if(start == end){
        return;
    } else {
        int middlePivot = (start+end)/2;
        mergeSort(input, start, middlePivot);
        mergeSort(input, middlePivot+1, end);
        merge(input, start, middlePivot, end);
    }
}

//for testing purposes, were just going to use 5 identical
//arrays for sorting
int main(){ 
    int inputArray[] = {98,76,3,5,51,35,74,981,654,8,165,438,54},
    inputArray1[] = {98,76,3,5,51,35,74,981,654,8,165,438,54},
    inputArray2[] = {98,76,3,5,51,35,74,981,654,8,165,438,54},
    inputArray3[] = {98,76,3,5,51,35,74,981,654,8,165,438,54},
    inputArray4[] = {98,76,3,5,51,35,74,981,654,8,165,438,54};
 
    //number of total bits / size of element in array = array size
    int inputSize = sizeof(inputArray)/sizeof(*inputArray);

    try{
        cout<<"Unsorted array"<<endl;
        printArray(inputArray, inputSize);

        selectSort(inputArray, inputSize);
        cout<<"Sorted by selection sort:"<<endl;
        printArray(inputArray, inputSize);

        bubbleSort(inputArray1, inputSize);
        cout<<"Sorted by bubble sort:"<<endl;
        printArray(inputArray1, inputSize);
        
        insertionSort(inputArray2, inputSize);
        cout<<"Sorted by insertion sort:"<<endl;
        printArray(inputArray2, inputSize);

        quickSort(inputArray3, 0, inputSize-1);
        cout<<"Sorted by quick sort:"<<endl;
        printArray(inputArray3, inputSize);

        mergeSort(inputArray4, 0, inputSize-1);
        cout<<"Sorted by merge sort:"<<endl;
        printArray(inputArray4, inputSize);
    } catch (...){
        cout << "Something happened" << endl;
    }
    
    return 0;
}