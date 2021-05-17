//Name: Jake Tremblay
//Student ID: 200633568
//Email: tremb008@cougars.csusm.edu
//Reusing code from Assignment1.cpp

#include <iostream>
#include <iterator>

using namespace std;

struct Edge{
    int adj_vtx;    //index of adjacent vertex
    Edge * next;    //linked list of next edges
};

class linkedList{  
    
    public:
        Edge *head;
        Edge *rear;

    linkedList(){
        head = NULL;
        rear = NULL;
    }

    //if the list is not empty, rear->next points to null, rear pointer to temp
    void pushBack(int data){
        Edge * temp = new Edge(); 
        temp->adj_vtx = data;
        temp->next = NULL;

        if(head == NULL){       
            head = temp;
            rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
    }

    //simply iterate thru the list printing element field
    void printList(){
        Edge * temp;
        temp = head;
        
        while(temp != NULL){
            cout << temp->adj_vtx << " ";
            temp = temp->next;
        }       
        cout << endl;
    }

};