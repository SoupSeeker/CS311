//Name: Jake Tremblay
//Hash Tables Assignment 7

#include <iostream>
#include <string>

using namespace std;

class Student{
    private: 
        string studentName; //DJBx33A will use string from student name as key into hash into table
        int studentAge;
        string studentID; //id is a string, the id could hold alpha-numeric if we needed
        double studentGPA;
        Student * next; //incase we collide with another, we have pointer in the student class

    public:
        Student(string name, int age, string id, double gpa){
            studentName = name;
            studentAge = age;
            studentID = id;
            studentGPA = gpa;
            next = NULL;
        }

        string getID(){
            return this->studentID;
        }

        void setNext(Student *n){      
            this->next = n;
            n->next = NULL;
        }

        Student * getNext(){
            return this->next;
        }       

};

class HashTable{
    Student **studentTable;
    int size;

    public:
    HashTable(int size){
        this->size = size;
        studentTable = new Student*[size];
        for(int i=0; i<size; i++){
            studentTable[i] = NULL;
        }
    }

    //DJBx33A from course slides using c++ strings
    unsigned long DJBx33A(string str){
        const char* cstr = str.c_str();

        unsigned long hash = 5381;
        int c;
        for(auto x : str){
            c = x;
            hash = (hash * 33) + c;
        }
        return hash;
    }   

    //uses id to hash into table, check if size 10 first
    void insert(string name, int age, string id, double gpa){
        if(id.size() != 10){
            cout << "Could not insert, ID needs to be 10 digits." << endl;
            return;
        }

        Student * s = new Student(name, age, id, gpa);
        int index = DJBx33A(id) % size;      
        
        if(studentTable[index] == NULL){
            cout << "Inserting at: " << index << endl;
            studentTable[index] = s;
        } else {
            Student * temp = studentTable[index];

            while(temp->getNext() != NULL){ 
                temp = temp->getNext();
            }
            cout << "Inserting behind: " << index << endl;
            temp->setNext(s);
        }
    }

    Student * search(string key){
        int index = DJBx33A(key) % size;
        int startIndex = index;

        if(studentTable[index] == NULL){
            cout << "Search failed, no student found with id: " << key << endl;
            return NULL;

        } else {
            Student * temp = studentTable[index];

            while(temp != NULL){
                if(temp->getID() == key){
                    break; //looking for key in the nonempty set at studentTalbe[index]
                }
                temp = temp->getNext();
            }

            if(temp == NULL){ 
                cout << "Search failed, no student found with id: " << key << endl;
                return NULL;
            }

            cout << "Search successful: " <<  temp->getID() << " found at index " << startIndex << endl;
            return studentTable[index];
        }
    }
};

int main(){
    HashTable * studentDB = new HashTable(13);

    studentDB->insert("Jake Tremblay", 26, "2009004981", 3.2);
    studentDB->insert("John Vesnin", 19, "2009004751", 2.6);
    studentDB->insert("Jerry Tonelli", 22, "2009004777", 2.9);
    studentDB->insert("Jon Perry", 22, "2009005011", 3.4);
    studentDB->insert("Jeremy Swelson", 25, "2009005846", 3.8);
    studentDB->insert("Jimmy Neutro", 18, "2009001116", 4.0);
    studentDB->insert("Justin Timberlake", 20, "2009001046", 3.8);
    studentDB->insert("Bob Law", 45, "2009002112", 3.1);
    studentDB->insert("Bob Law", 44, "2009004449", 1.3);

    studentDB->search("2009002112");
    studentDB->search("21212");
    studentDB->search("2009004981");

     
    return 0;
}

