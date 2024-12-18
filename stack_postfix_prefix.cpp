/*
Implement stack as an abstract data type using singly
linked list and use this ADT for conversion of infix
expression to postfix and evaluation of postfix expression. 
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Stack ADT as singly linked list
class Stack {
    private:
        Node* top;
    public:
        Stack() : top(nullptr) {}
        ~Stack() {
            while (!isEmpty()) {
                pop();
            }
        }
    //push operation
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }
    //pop operation
    int pop() {
        if (isEmpty()) {
            throw runtime_error("Stack underflow");
        }
        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }
    //peek operation
    int peek() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return top -> data;
    }
    //check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }
};

//check operator precedence
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

//check if charactor is operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

//infix to postfix
string infixToPostfix(const string& infix) {
    Stack stack;
    string postfix = "";

    for (char ch : infix) {
        if (isdigit(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += (char)stack.pop();
            }
            stack.pop();
        } else if (isOperator(ch)) {
            while (!stack.isEmpty() && precedence(ch) <= precedence(stack.peek())) {
                postfix += (char)stack.pop();
            }
            stack.push(ch);
        }
    }
    //pop remaining operators
    while (!stack.isEmpty()) {
        postfix += (char)stack.pop();
    }

    return postfix;
}

//evaluate postfix
int evaluatePostfix(const string& postfix) {
    Stack stack;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            stack.push(ch - '0'); //convert character to integer
        } else if (isOperator(ch)) {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            switch(ch) {
                case '+': stack.push(operand1 + operand2); break;
                case '-': stack.push(operand1 - operand2); break;
                case '*': stack.push(operand1 * operand2); break;
                case '/': stack.push(operand1 / operand2); break;
                case '^': stack.push(pow(operand1, operand2)); break;
            }
        }
    }
    return stack.pop();
}

//main function
int main() {
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;

    try{
        string postfix = infixToPostfix(infix);
        cout << "Postfix expression: " << postfix << endl;
        
        string newinfix = infix;
        reverse(newinfix.begin(), newinfix.end());
        for (char& ch: newinfix) {
            if (ch == '(') ch = ')';
            else if (ch == ')') ch = '(';
        }

        string prefix = infixToPostfix(newinfix);
        reverse(prefix.begin(), prefix.end());
        cout << "Prefix expression: " << prefix << endl;

        int result = evaluatePostfix(postfix);
        cout << "Evaluation: " << result << endl;
        
    } catch(const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}