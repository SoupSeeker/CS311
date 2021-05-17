//Name: Jake Tremblay
//Calculator program

#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string>
using namespace std;

struct Node
{
    double value;
    char element;
    Node *next;
};

class StackLinkedList
{
private:
    Node *top;
    int size;

public:
    StackLinkedList()
    {
        top = NULL;
        size = 0;
    }

    void push(char data)    //for pushing char operators to stack
    {
        Node *temp = new Node();
        temp->element = data;
        temp->next = top;
        top = temp;
        size++;
    }

    void push(double data)  //for pushing doubles to operand stack
    {
        Node *temp = new Node();
        temp->value = data;
        temp->next = top;
        top = temp;
        size++;
    }

    Node *pop()
    {
        if (top != NULL)
        {
            Node *temp = top;
            top = top->next;
            size--;
            return temp;
        }
        else
        {
            return NULL;
        }
    }

    Node *getTop()
    {
        return top;
    }

    int getStackSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0 ? 1 : 0;
    }
};

StackLinkedList *operands = new StackLinkedList();
StackLinkedList *operators = new StackLinkedList();

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
    {
        return true;
    }
    return false;
}

//isOperator returns true if + - * /
char evalOperatorScore(char currentOp, char top)
{
    if (isOperator(currentOp) && top == '(')
    {
        return '<';
    }
    else if (isOperator(currentOp) && top == ')')
    {
        return '>';
    }
    else if (isOperator(currentOp) && top == '#')
    {
        return '<';
    }
    else if (currentOp == '(' && isOperator(top))
    {
        return '<';
    }
    else if (currentOp == ')' && isOperator(top))
    {
        return '>';
    }
    else if (currentOp == top)
    {
        return '>';
    }
    else if (currentOp == '#' && (isOperator(top) || top == '('))
    {
        return '<';
    }
    else if ((currentOp == '*' || currentOp == '/') && isOperator(top))
    {
        return '>';
    }
}

void operate(char op, char b, char a)
{
    int A = a-48, B = b-48;
    int result; 
    char buffer[16];
    
    switch (op)
    {
    case '+':
        result = B + A;
        operands->push(*(itoa(result, buffer, 10)));
        break;
    case '-':
        result = B - A;
        operands->push(*(itoa(result, buffer, 10)));
        break;
    case '*':
        result = B * A;
        operands->push(*(itoa(result, buffer, 10)));
        break;
    case '/':
        if (A != 0)
        {
            result = B / A;
            
            operands->push(*(itoa(result, buffer, 10)));
        }
        else
        {
            throw "Something happened!";
        }
        break;
    }
    
}

double evalExpression(char *exp)
{
    char *i = exp;
    
    while (*i != '#' || operators->getTop()->element != '#')
    {

        if (*i == '#')
        {
            operate(operators->pop()->element, operands->pop()->element, operands->pop()->element);
            if(operators->getTop()->element == '#')
            {
                return atof(&(operands->pop()->element));
            }
        }

        if (isdigit(*i))
        {
            operands->push(*i);
        }
        else if (isOperator(*i))
        {
            switch (evalOperatorScore(*i, operators->getTop()->element))
            {
            case '<':
                operators->push(*i);
                break;
            case '>':
                operate(operators->pop()->element, int(operands->pop()->element), int(operands->pop()->element));
                break;
            case '=':
                operands->pop()->element;
                break; // when we have ( and ) we should hit this case
            }
        }
        else if (*i == '(')
        {
            operators->push(*i);
        }
        else if (*i == ')')
        {
            operate(operators->pop()->element, int(operands->pop()->element), int(operands->pop()->element));
            operators->pop();
        }

        i++;
    }

    return operands->pop()->element;
}

int main()
{
    operators->push('#');
    
    string expression = "3 * (2 + 1)#";
    const char *c = expression.c_str();
    string expression2 = "3.14 / (1 + 2.14)";

    try
    {
        // evalExpression(exp);
        cout << evalExpression("3 * (2 + 1)#") << endl;

        cout << evalExpression("(3 + 2) * 2#") << endl;
    }
    catch (exception e)
    {
        cout << "Something happened!" << endl;
        return -1;
    }
    return 0;
}
