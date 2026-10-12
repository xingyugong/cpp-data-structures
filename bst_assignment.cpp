#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string name;
    double weight;
    Node* left;
    Node* right;

    Node(string n, double w) : name(n), weight(w), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertHelper(Node* node, string name, double weight) {
        if (node == nullptr) {
            return new Node(name, weight);
        }
        // Names are the key value for building the tree
        if (name < node->name) {
            node->left = insertHelper(node->left, name, weight);
        } else if (name > node->name) {
            node->right = insertHelper(node->right, name, weight);
        }
        return node;
    }

    void preorderHelper(Node* node) {
        if (node != nullptr) {
            cout << node->name << " (" << node->weight << ") ";
            preorderHelper(node->left);
            preorderHelper(node->right);
        }
    }

    void inorderHelper(Node* node) {
        if (node != nullptr) {
            inorderHelper(node->left);
            cout << node->name << " (" << node->weight << ") ";
            inorderHelper(node->right);
        }
    }

    void postorderHelper(Node* node) {
        if (node != nullptr) {
            postorderHelper(node->left);
            postorderHelper(node->right);
            cout << node->name << " (" << node->weight << ") ";
        }
    }

    int getHeightHelper(Node* node) {
        if (node == nullptr) {
            return -1; // Standard definition: empty tree height is -1, leaf node height is 0
        }
        // Recursively find the height. The algorithm stack holds the height state.
        int leftHeight = getHeightHelper(node->left);
        int rightHeight = getHeightHelper(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    int countLeavesHelper(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        // A leaf has no children
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return countLeavesHelper(node->left) + countLeavesHelper(node->right);
    }

    void searchHelper(Node* node, string searchName) {
        if (node == nullptr) {
            cout << "No match exists for " << searchName << "." << endl;
            return;
        }
        if (node->name == searchName) {
            cout << searchName << " found! Weight: " << node->weight << endl;
        } else if (searchName < node->name) {
            searchHelper(node->left, searchName);
        } else {
            searchHelper(node->right, searchName);
        }
    }

    double getLowestWeightHelper(Node* node) {
        if (node == nullptr) {
            // Return a very large number so it doesn't affect the minimum finding
            return numeric_limits<double>::max(); 
        }
        
        double currentWeight = node->weight;
        double leftMin = getLowestWeightHelper(node->left);
        double rightMin = getLowestWeightHelper(node->right);
        
        // Find the minimum among current, left subtree, and right subtree
        double minWeight = min(currentWeight, min(leftMin, rightMin));
        return minWeight;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Method 1: Build the tree
    void insert(string name, double weight) {
        root = insertHelper(root, name, weight);
    }

    // Method 2: Execute a preorder traversal
    void printPreorder() {
        cout << "Preorder Traversal: ";
        preorderHelper(root);
        cout << endl;
    }

    // Method 3: Execute an inorder traversal
    void printInorder() {
        cout << "Inorder Traversal:  ";
        inorderHelper(root);
        cout << endl;
    }

    // Method 4: Execute a postorder traversal
    void printPostorder() {
        cout << "Postorder Traversal:";
        postorderHelper(root);
        cout << endl;
    }

    // Method 5: Find and print the height of the tree using recursion
    void printHeight() {
        cout << "Tree Height: " << getHeightHelper(root) << endl;
    }

    // Method 6: Determine the number of leaves
    void printLeafCount() {
        cout << "Number of leaves: " << countLeavesHelper(root) << endl;
    }

    // Method 7: Implement search functionality
    void searchName(string name) {
        searchHelper(root, name);
    }

    // Method 8: Determine the lowest weight contained in the tree
    void printLowestWeight() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
        } else {
            cout << "Lowest weight in the tree: " << getLowestWeightHelper(root) << endl;
        }
    }

    // Method 9: Find the first name in alphabetical order
    void printFirstName() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        Node* current = root;
        // Keep traversing left to find the first alphabetical name 
        // (Does not go through every node)
        while (current->left != nullptr) {
            current = current->left;
        }
        cout << "First name in alphabetical order: " << current->name << endl;
    }
};

int main() {
    BinarySearchTree bst;
    string name;
    double weight;
    const int NUM_RECORDS = 15;

    cout << "Please enter " << NUM_RECORDS << " records (Name followed by Weight):" << endl;
    
    for (int i = 0; i < NUM_RECORDS; ++i) {
        cout << "Record " << i + 1 << ": ";
        cin >> name >> weight;
        bst.insert(name, weight);
    }

    cout << "\n--- Tree Analysis Results ---\n";
    
    bst.printPreorder();
    bst.printInorder();
    bst.printPostorder();
    bst.printHeight();
    bst.printLeafCount();
    
    bst.printLowestWeight();
    bst.printFirstName();

    cout << "\n--- Search Test ---\n";
    cout << "Enter a name to search: ";
    string searchTarget;
    cin >> searchTarget;
    bst.searchName(searchTarget);

    cout << "Enter another name to search (that doesn't exist): ";
    cin >> searchTarget;
    bst.searchName(searchTarget);

    return 0;
}

/*
--- Tree Analysis Results ---
Preorder Traversal: Mike (180.5) Alice (120) Bob (150.2) Charlie (145) Diana (115.5) Eve (105) Frank (190) Gina (125) Harry (160) Ivy (110) Jack (155) Kelly (140) Zack (210) Sara (130) Tom (175) 
Inorder Traversal:  Alice (120) Bob (150.2) Charlie (145) Diana (115.5) Eve (105) Frank (190) Gina (125) Harry (160) Ivy (110) Jack (155) Kelly (140) Mike (180.5) Sara (130) Tom (175) Zack (210) 
Postorder Traversal:Kelly (140) Jack (155) Ivy (110) Harry (160) Gina (125) Frank (190) Eve (105) Diana (115.5) Charlie (145) Bob (150.2) Alice (120) Tom (175) Sara (130) Zack (210) Mike (180.5) 
Tree Height: 11
Number of leaves: 2
Lowest weight in the tree: 105
First name in alphabetical order: Alice

--- Search Test ---
Enter a name to search: Frank
Frank found! Weight: 190
Enter another name to search (that doesn't exist): xin
No match exists for xin.
*/