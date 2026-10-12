#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> 

using namespace std;

// Part 1: Linked List Stack Implementation

// Node structure for the Linked List
struct Node {
    double data;
    Node* next;
};

// Stack class using Linked List
class Stack {
private:
    Node* top;
    int count;

public:
    Stack() {
        top = nullptr;
        count = 0;
    }

    // Destructor to clean up memory
    ~Stack() {
        makeEmpty();
    }

    // Adds value to the top
    void push(double val) {
        Node* newNode = new Node;
        newNode->data = val;
        newNode->next = top;
        top = newNode;
        count++;
    }

    // Returns true if successful, false if stack is empty
    bool pop(double& val) {
        if (isEmpty()) {
            return false;
        }
        Node* temp = top;
        val = temp->data;
        top = top->next;
        delete temp;
        count--;
        return true;
    }

    // Check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Get current size of stack
    int size() {
        return count;
    }

    // Helper to clear the stack 
    void makeEmpty() {
        double temp;
        while (!isEmpty()) {
            pop(temp);
        }
    }
};

// Part 2: Calculator Logic

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

double applyOp(string op, double b, double a) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    return 0;
}

int main() {
    Stack stack;
    string line;

    cout << "RPN Calculator Started. Enter expression (e.g., 10 15 + =)." << endl;
    cout << "Enter '0' on a new line to quit." << endl;

    while (true) {
        // Read the entire line of input
        getline(cin, line);

        // Exit condition: User enters "0"
        if (line == "0") {
            break;
        }

        // Use stringstream to parse the line word by word
        stringstream ss(line);
        string token;
        bool errorFound = false; 
        
        // Clear stack for the new calculation
        stack.makeEmpty();

        while (ss >> token) {
            
            if (token == "=") {
                if (stack.size() == 1) {
                    double result;
                    stack.pop(result);
                    cout << line << " " << result << endl;
                } else {
                    cout << line << " Error: Too many operands" << endl;
                }
                errorFound = true;
                break;
            }

            else if (isOperator(token)) {
                
                if (stack.size() < 2) {
                    cout << line << " Error: Too many operators" << endl;
                    errorFound = true;
                    break;
                }

                double val2, val1;
                stack.pop(val2); 
                stack.pop(val1); 

                // Check for Division by Zero
                if (token == "/" && val2 == 0) {
                    cout << line << " Error: Division by zero" << endl;
                    errorFound = true;
                    break;
                }

                double result = applyOp(token, val2, val1);
                stack.push(result);
            }

            else {
                try {
                    double val = stod(token);
                    stack.push(val);
                } catch (...) {
                    cout << line << " Error: Invalid number format" << endl;
                    errorFound = true;
                    break;
                }
            }
        }
    }

    return 0;
}

//RPN Calculator Started. Enter expression (e.g., 10 15 + =).
//Enter '0' on a new line to quit.
//10 15 + = 25
//10 15 - = -5
//2.5 3.5 + = 6
//10 0 / = Error: Division by zero
//10 20 * / = Error: Too many operators
//12 20 30 / = Error: Too many operands
//-10 -30 - =  20
//100 10 50 25 / * - -2 / = -40
