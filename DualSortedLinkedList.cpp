#include <iostream>
#include <string>

using namespace std;

struct Node {
    string name;
    int weight;
    Node* nextName;  
    Node* nextWeight; 

    Node(string n, int w) {
        name = n;
        weight = w;
        nextName = nullptr;
        nextWeight = nullptr;
    }
};

class DualLinkedList {
private:
    Node* headName;  
    Node* headWeight; 

public:
    DualLinkedList() {
        headName = nullptr;
        headWeight = nullptr;
    }

    ~DualLinkedList() {
        Node* current = headName;
        while (current != nullptr) {
            Node* temp = current;
            current = current->nextName;
            delete temp;
        }
    }

    void insert(string n, int w) {
        Node* newNode = new Node(n, w);

        if (headName == nullptr || headName->name > n) {
            newNode->nextName = headName;
            headName = newNode;
        } else {
            Node* current = headName;
            while (current->nextName != nullptr && current->nextName->name <= n) {
                current = current->nextName;
            }
            newNode->nextName = current->nextName;
            current->nextName = newNode;
        }

        if (headWeight == nullptr || headWeight->weight > w) {
            newNode->nextWeight = headWeight;
            headWeight = newNode;
        } else {
            Node* current = headWeight;
            while (current->nextWeight != nullptr && current->nextWeight->weight <= w) {
                current = current->nextWeight;
            }
            newNode->nextWeight = current->nextWeight;
            current->nextWeight = newNode;
        }
    }

    void printByName() {
        cout << "Names & weights sorted(ascending) by name. : ";
        Node* current = headName;
        while (current != nullptr) {
            cout << current->name << " - " << current->weight;
            if (current->nextName != nullptr) {
                cout << ", "; 
            }
            current = current->nextName;
        }
        cout << endl;
    }

    void printByWeight() {
        cout << "Names & weights sorted(ascending) by weight. : ";
        Node* current = headWeight;
        while (current != nullptr) {
            cout << current->name << " - " << current->weight;
            if (current->nextWeight != nullptr) {
                cout << ", "; 
            }
            current = current->nextWeight;
        }
        cout << endl;
    }
};

int main() {
    DualLinkedList list;
    string name;
    int weight;
    
    cout << "Please enter 15 names and weights (name on one line, weight on the next):" << endl;
    
    for (int i = 0; i < 15; i++) {
        cin >> name;
        cin >> weight;
        list.insert(name, weight);
    }

    cout << "\n--- Output ---" << endl;
    
    list.printByName();
    list.printByWeight();

    return 0;
}