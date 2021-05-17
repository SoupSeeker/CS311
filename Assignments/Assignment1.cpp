//Name: Jake Tremblay


#include <iostream>

using namespace std;


struct Node{
    int element;
    Node *next;
};

class linkedList{    
    public:
        Node *head;
        Node *rear;

    linkedList(){
        head = NULL;
        rear = NULL;
    }

    //if the list is not empty, rear->next points to null, rear pointer to temp
    void addNode(int data){
        Node * temp = new Node(); 
        temp->element = data;
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
        Node * temp;
        temp = head;
        
        while(temp != NULL){
            cout << temp->element << " ";
            temp = temp->next;
        }       
        cout << endl;
    }
};

Node * unionLL(Node *LA, Node *LB);
Node * mergeLL(Node *LA, Node *LB);


int main(){
    //LA will be = (3,5,8,11)
    linkedList * LA = new linkedList();
    LA->addNode(3), LA->addNode(5), LA->addNode(8), LA->addNode(11);
    cout << "List A: ";
    LA->printList();
    
    //LB will be =(2,6,8,9,22,24)
    linkedList * LB = new linkedList();
    LB->addNode(2), LB->addNode(6), LB->addNode(8), LB->addNode(9), LB->addNode(22), LB->addNode(24);
    cout << "List B: ";
    LB->printList();

    //both modified list will be printed from within each function
    unionLL(LA->head, LB->head);     
    cout << "List A: ";
    LA->printList();
    cout << "List B: ";
    LB->printList();

    mergeLL(LA->head, LB->head);
    cout << "List A: ";
    LA->printList();
    cout << "List B: ";
    LB->printList();
 

    delete LA, LB;
    return 0;
}

//Union the two lists such that set A will come before set B, delete any extra entires
Node * unionLL(Node *LA, Node *LB){
    linkedList *unionList = new linkedList();   
    Node *temp = new Node();   

    while(LA != NULL){
        unionList->addNode(LA->element);
        LA = LA->next;
    }

    //we have a list comprised of set A, now we need to add set B without duplicates
    while(LB != NULL){
        temp = unionList->head; //reset temp each iteration of inner while loop

        while(temp != NULL){
            //while going thru unionList, if our current LB element is in the list already,
            //we will break to allow LB pointer to move past the matching node
            if(LB->element == temp->element){               
                break;
            } else if(temp->next == NULL){
                //we have gotten to end of unionList and not found any equal elements, so add
                //the node to the unionList and break
                unionList->addNode(LB->element);
                break; 
            }
            temp = temp->next;
        }
        LB = LB->next;
    }
    cout << "Union List: ";
    unionList->printList();
    return unionList->head;
}

//Merge the two sets, add any duplicate entries, create a new list and return it
//in non-decending order
Node * mergeLL(Node *LA, Node *LB){

    linkedList * mergeList = new linkedList();

    while(true){
        //if LA is NULL, add the rest of LB to new list and vice versa
        if(LA == NULL){          
            mergeList->rear->next = LB;
            mergeList->rear = LB;
            break; 
        } else if (LB == NULL){
            mergeList->rear->next = LA;
            mergeList->rear = LA;
            break;
        }      

        //LA < LB, add(LA) and LA++ 
        if(LA->element < LB->element){
            mergeList->addNode(LA->element); 
            LA = LA->next;    
        } else if (LA->element > LB->element){
            //LA > LB, add(LB) and LB++ 
            mergeList->addNode(LB->element);    
            LB = LB->next;               
        } else {
            //LA = LB, add(LA) add(LB) and LA++ LB++
            mergeList->addNode(LA->element);
            mergeList->addNode(LB->element);
            LA = LA->next;   
            LB = LB->next;   
        }   
    }
    cout << "Merged List: ";
    mergeList->printList();
    return mergeList->head;
}
