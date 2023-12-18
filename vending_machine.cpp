#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>

using namespace std;

// Structure to represent a product
struct Product {
    string name;
    double price;
    int quantity;
};

// Binary tree node structure
struct Node {
    Product product;
    Node* left;
    Node* right;
};

// Function to create a new binary tree node
Node* createNode(Product product) {
    Node* newNode = new Node;
    newNode->product = product;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a node into the binary tree
void insertNode(Node* &root, Product product) {
    if (root == nullptr) {
        root = createNode(product);
        return;
    }
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        
        if (temp->left == nullptr) {
            temp->left = createNode(product);
            return;
        } else {
            q.push(temp->left);
        }
        
        if (temp->right == nullptr) {
            temp->right = createNode(product);
            return;
        } else {
            q.push(temp->right);
        }
    }
}

// Function to display the product menu using inorder traversal of the binary tree
void displayMenu(Node* root) {
    if (root == nullptr) {
        return;
    }
    
    displayMenu(root->left);
    
    cout << setw(15) << left << root->product.name << setw(10) << root->product.price << setw(10) << root->product.quantity << endl;
    
    displayMenu(root->right);
}

// Function to process the user's selection using stack
void processSelection(Node* root, int choice) {
    stack<Node*> s;
    s.push(root);
    
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        
        if (current->product.quantity == 0) {
            cout << "Sorry, the selected product is out of stock." << endl;
            return;
        }
        
        if (current->product.price > 0) {
            if (choice == 1) {
                cout << "Please insert $" << current->product.price << " to purchase " << current->product.name << "." << endl;
                
                double amount;
                cin >> amount;
                
                if (amount >= current->product.price) {
                    cout << "Thank you for your purchase! Here is your " << current->product.name << "." << endl;
                    current->product.quantity--;
                    cout << "Don't forget to take your change of $" << amount - current->product.price << "." << endl;
                } else {
                    cout << "Insufficient amount. Transaction canceled." << endl;
                }
                
                return;
            } else {
                choice--;
            }
        }
        
        if (current->right != nullptr) {
            s.push(current->right);
        }
        
        if (current->left != nullptr) {
            s.push(current->left);
        }
    }
    
    cout << "Invalid selection. Please try again." << endl;
}

int main() {
    // Create the binary tree with products
    Node* root = nullptr;
    
    insertNode(root, {"Coke", 1.5, 5});
    insertNode(root, {"Chips", 1.0, 7});
    insertNode(root, {"Candy", 0.75, 3});
    insertNode(root, {"Water", 1.0, 10});
    insertNode(root, {"Gum", 0.5, 2});
    
    // Display the product menu
    cout << "========================" << endl;
    cout << "       VENDING MACHINE" << endl;
    cout << "========================" << endl;
    cout << "     Available Products" << endl;
    cout << "========================" << endl;
    cout << setw(15) << left << "Product" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
    cout << "------------------------" << endl;
    
    displayMenu(root);
    
    cout << "========================" << endl;
    
    // Prompt for the user's selection
    int choice;
    cout << "Enter the number corresponding to the product you want to purchase (1-5): ";
    cin >> choice;
    
    // Process the user's selection
    processSelection(root, choice);
    
    return 0;
}
