//Name: Jake Tremblay
//Student ID: 200633568
//Email: tremb008@cougars.csusm.edu
//Calculator program

#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string>
using namespace std;

struct Node{
    double value;
    char element;
    Node *next;
};

class StackLinkedList{
private:
    Node *top;
    int size;

public:
    StackLinkedList(){
        top = NULL;
        size = 0;
    }

    void push(char data){
        Node *temp = new Node();
        temp->element = data;
        temp->next = top;
        top = temp;
        size++;
    }

    void push(double data){
        Node *temp = new Node();
        temp->value = data;
        temp->next = top;
        top = temp;
        size++;
    }

    Node *pop(){
        if (top != NULL){
            Node *temp = top;
            top = top->next;
            size--;
            return temp;
        }
        else{
            return NULL;
        }
    }

    Node *getTop(){
        return top;
    }

    int getStackSize(){
        return size;
    }

    bool isEmpty(){
        return size == 0 ? 1 : 0;
    }
};

StackLinkedList * operands = new StackLinkedList();
StackLinkedList * operators = new StackLinkedList();

void operate(char op, double a, double b){
    double result;
    
    switch (op)
    {
    case '+':
        result = a + b;
        operands->push(result);
        break;
    case '-':
        result = a - b;
        operands->push(result);
        break;
    case '*':
        result = a * b;
        operands->push(result);
        break;
    case '/':
        if (b != 0){
            result = a / b;
            operands->push(result);
        }
        else{
            throw "Division by 0";
        }
        break;
    }
    
}

//1 is greater than, -1 is less than, 0 is equal to
int evalOperatorPriority(char currentOperation){
    bool isOperator = false;
    char topOfStack = operators->getTop()->element;
    int operatorGroup;
    
    if (currentOperation == '+' || currentOperation == '-' || currentOperation == '*' || currentOperation == '/' || currentOperation == '(' || currentOperation == ')'){
        isOperator = true;
        if(currentOperation == '-' || currentOperation == '+'){
            operatorGroup = 1;
        } else if(currentOperation == '*' || currentOperation == '/'){
            operatorGroup = 2;
        } 
    }   

    //pretty clunky, but it works <(^o^)>
    if(isOperator && topOfStack == '#'){
        if(currentOperation == ')'){
            throw "Missing (";
        }
        return -1;
    } else if(currentOperation == '#' && topOfStack =='#'){ 
        return 0;
    } else if(currentOperation == '#'){ 
        if(topOfStack == '('){
            throw "Extra (";
        }
        return 1;
    } else if(operatorGroup == 1 && (topOfStack == '/' || topOfStack == '*') ){
        return 1;
    } else if(operatorGroup == 1 && (topOfStack == '+' || topOfStack == '-') ){
        return 1;
    } else if(operatorGroup == 2 && (topOfStack == '+' || topOfStack == '-') ){
        return 1;
    } else if(operatorGroup == 2 && (topOfStack == '/' || topOfStack == '*') ){
        return 1;
    }else if(isOperator && topOfStack == '(') {
        return -1;
    } else if(isOperator && topOfStack == ')'){
        return 1;
    } 
    else if(currentOperation == ')' && topOfStack == '('){
        return 0;
    } else if(currentOperation == '('){
        if(topOfStack == ')'){
            throw "Mismatch ()";
        }
        return -1;
    } else if(currentOperation == ')'){
        return 0;
    } else if(currentOperation == topOfStack){
        return 1;
    } 
    throw "Something happened!";
}

double evalExpression(const char *exp)
{
    string floatingPointHelper;
    while(*exp != '\0'){

        if(isdigit(*exp)){
            if(*(exp+1) == '.'){
                floatingPointHelper += *exp;
                floatingPointHelper += '.';
                floatingPointHelper += *(exp+2);
                exp = exp+2;

                operands->push(stod(floatingPointHelper));
            } else {
                operands->push(atof(exp));
            }
            
        } else if(*exp != ' ') {
            switch(evalOperatorPriority(*exp)){
                //case 1: current operator has greater priority than top of stack
                case 1:  
                    operate(operators->pop()->element, operands->pop()->value, operands->pop()->value);
                    
                    operators->push(*exp);
                    break;
                //case -1: current operator has less priority than top of stack
                case -1: 
                    operators->push(*exp); 
                    break;
                //case 0: current op and top are equal
                case 0: 
                    while(operators->getTop()->element != '('){
                        operate(operators->pop()->element, operands->pop()->value, operands->pop()->value);
                    } 
                    //operate(operators->pop()->element, operands->pop()->value, operands->pop()->value);
                    operators->pop();
                    break;
            }
        }

        exp++;
    }  
    return operands->pop()->value;
}

int main(){

    operators->push('#');
    
    string expression = "3 + 2 * (4 - 2 / 3)#";
    string expression2 = "3 - 2 / 2#";
    string expression3 = "1.8 + 1#";
    string expression4 = "2 * 2 - 2 + 2#";
    string expression5 = "8 - 5 + 3 * (3 - 1 / 4)#";

    const char *c = expression.c_str();
    const char *c2 = expression2.c_str();
    const char *c3 = expression3.c_str();
    const char *c4 = expression4.c_str();
    const char *c5 = expression5.c_str();
    
    try{
        cout << evalExpression(c) << endl;
        cout << evalExpression(c2) << endl;
        cout << evalExpression(c3) << endl;
        cout << evalExpression(c4) << endl;
        cout << evalExpression(c5) << endl;
    } catch (...){
        cout << "Something happened!" << endl;
        return -1;
    }
    
    delete operands;
    delete operators;
    return 0;
}
