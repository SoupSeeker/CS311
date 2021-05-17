//Name: Jake Tremblay
//Student ID: 200633568
//Email: tremb008@cougars.csusm.edu
//Binary Search Tree

#include <iostream>

using namespace std;

struct Node{
    int data;
    Node * LC;
    Node * RC;

    Node(int key){
        data = key;
        LC = NULL;
        RC = NULL;
    }
};

class BST{
    Node *root;

    public:
        BST(){
            root = NULL;
        }

        void insert(int key){
            root = insert(root, key);
        }
        
        //returns pointer to new root after insertion of node
        Node* insert(Node * node, int insertKey){
            if(node == NULL){
                node = new Node(insertKey);
            } else if(node->data > insertKey){
                node->LC = insert(node->LC, insertKey);
            } else if(insertKey > node->data){
                node->RC = insert(node->RC, insertKey);
            }

            return node;
        }

        void remove(int deleteKey){
            root = remove(root, deleteKey);
        }

        //return pointer to root of tree after deletion
        Node* remove(Node * node, int deleteKey){
            if(node == NULL){
                return node;
            }

            if(node->data > deleteKey){
                node->LC = remove(node->LC, deleteKey);
            } else if(deleteKey > node->data){
                node->RC = remove(node->RC, deleteKey);
            } else {
                //case 1/2 node w one child
                if(node->LC == NULL){
                    Node *temp = node->RC;
                    delete node;
                    return temp;
                } else if(node->RC == NULL){
                    Node *temp = node->LC;
                    delete node;
                    return temp;
                }
                //case 3
                Node* temp = rightMostNode(node->LC);
                node->data = temp->data;
                node->LC = remove(node->LC, temp->data);
            }
        }

        Node* rightMostNode(Node * node){
            Node* current = node;
            //loop down to find rightmost leaf
            while(current->RC != NULL){
                current = current->RC;
            }
            return current;
        }        

        //return value is pointer to node that has the key
        Node* search(int searchKey){
            return search(root, searchKey);
        }

        Node* search(Node * root, int searchKey){
            if(root == NULL || root->data == searchKey){
                return root;
            }
            if(root->data < searchKey){
                return search(root->RC, searchKey);
            }
            return search(root->LC, searchKey);
        }        
        
        /**
         * use helper methods for preorder, inorder, and postorder 
         * to ensure program maintains a private root node
         **/
        void preorder(){
            preorder(root);
        }

        void preorder(Node *root){
            if(root != NULL){
                cout << root->data << " ";
                preorder(root->LC);
                preorder(root->RC);
            }
        }

        void inorder(){
            inorder(root);
        }

        void inorder(Node *root){
            if(root != NULL){
                inorder(root->LC);
                cout << root->data << " ";
                inorder(root->RC);
            }
        }

        void postorder(){
            postorder(root);
        }

        void postorder(Node *root){
            if(root != NULL){
                postorder(root->LC);                
                postorder(root->RC);
                cout << root->data << " ";
            }
        }
};


int main(){ 
    BST * happyTree = new BST();
    int userInput = 0;
    
    //insertion of elements by user
    cout << "Enter integers or any negative integer to stop:" << endl;
    do{
        cin >> userInput;

        if(userInput >=0){ 
            happyTree->insert(userInput); 
        } else {
            break;
        }
    }while(true);

    //printing
    happyTree->preorder(); cout << endl;
    happyTree->inorder(); cout << endl;
    happyTree->postorder(); cout << endl;

    //searching (only 1 iteration of searching for convience)
    Node * searchNode; int searchKey;
    cout << "Enter a number to search for: " << endl;
    cin >> searchKey;
    searchNode = happyTree->search(searchKey);  
    if(searchNode != NULL){
        cout << "Search successful: " << searchNode->data << " found." << endl;
    } else {
        cout << "Search failed" << endl;
    }

    //removal
    happyTree->remove(2);
    happyTree->remove(8);
    happyTree->remove(4);

    //reprint after removal
    happyTree->preorder(); cout << endl;
    happyTree->inorder(); cout << endl;
    happyTree->postorder(); cout << endl;
  

    return 0;
}