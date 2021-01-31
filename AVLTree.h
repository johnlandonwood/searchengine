#ifndef SEARCH_ENGINE_HARRISON_WOOD_AVLTREE_H
#define SEARCH_ENGINE_HARRISON_WOOD_AVLTREE_H
#include "Node.h"
//written by Maria Harrison
//help from https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
/// Written by Maria Harrison.
/// Help taken from https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
template <class T, class L>
class AVLTree{
private:
    Node<T, L>* root;
    int treesize;
    vector<T> nodes;
public:
    //overloaded default constructor
    /// Default constructor
    AVLTree(){
        root = nullptr;
        treesize = 0;
    }
    //constructor with single argument
    /// Parameterized constructor
    AVLTree(T data, L value){
        root = new Node<T, L>(data, value);
        treesize++;
    }

    /// Finds the maximum between two integers.
    /// \param data An integer
    /// \param data2 An integer
    /// \return The maximum of the two parameters.
    int max(int data, int data2){
        if(data > data2){
            return data;
        }
        else{
            return data2;
        }
    }
    /// Gets the height of a node.
    /// \param n The node
    /// \return An integer for the node's height
    int height(Node<T, L>* n){
        if(n == nullptr){
            return 0;
        }
        else{
            return n->height;
        }
    }
    /// Gets the balance factor of a node
    /// \param n The node
    /// \return An integer for the node's balance
    int getBalance(Node<T, L> *n){
        if(n == nullptr){
            return 0;
        }
        else{
            return height(n->left) - height(n->right);
        }
    }

    //return rotate right
    /// Rotates a node in the tree to the right.
    /// \param alpha Node to be rotated
    /// \return The newly rotated node
    Node<T,L> *rotateRight(Node<T,L> *alpha)
    {
        Node<T,L> *x = alpha->left;
        Node<T,L> *T2 = x->right;

        x->right = alpha;
        alpha->left = T2;

        alpha->height = max(height(alpha->left),
                        height(alpha->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;

        return x;
    }

    //return rotate left
    /// Rotates a node in the tree to the left.
    /// \param alpha Node to be rotated
    /// \return The newly rotated node
    Node<T,L> *leftRotate(Node<T,L> *alpha)
    {
        Node<T,L> *y = alpha->right;
        Node<T,L> *T2 = y->left;

        y->left = alpha;
        alpha->right = T2;

        alpha->height = max(height(alpha->left),
                        height(alpha->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;

        return y;
    }

    //initialize new node
    /// Instantiates a new node.
    /// \param data Data to be passed into the node
    /// \param value Value to be passed into the node
    /// \return A pointer to the new node
    Node<T,L>* newNode(T data, L value)
    {
        Node<T,L>* node = new Node<T,L>();
        node->data = data;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;

        return(node);
    }
    /// Inserts a node into the AVL tree.
    /// \param node Node to be inserted
    /// \param data Data to be inserted
    /// \param value Value to be inserted
    /// \return The newly inserted node
    Node<T,L>* insert(Node<T,L>* node, T data, L value)
    {
        if (node == NULL) {
            treesize++;
            return (newNode(data, value));
        }

        if (value < node->value)
            node->left = insert(node->left, data, value);
        else if (value > node->value)
            node->right = insert(node->right, data, value);
        else
            return node;

        node->height = 1 + max(height(node->left),
                               height(node->right));

        int balance = getBalance(node);

        //left left case
        if (balance > 1 && value < node->left->value)
            return rotateRight(node);

        //right right case
        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        //left right case
        if (balance > 1 && value > node->left->value){
            node->left = leftRotate(node->left);
            return rotateRight(node);
        }

        //right left case
        if (balance < -1 && value < node->right->value){
            node->right = rotateRight(node->right);
            return leftRotate(node);
        }

        return node;
    }
    /// Inserts a node into the tree.
    /// \param data Data to be inserted
    /// \param value Node to be inserted
    void insert(T data, L value){
        this->root = insert(root, data, value);
    }
    /// Checks if a value is in the tree.
    /// \param value Value to be searched for in the tree
    /// \return True if value is in the tree, false if not
    bool dataInTree(L value){
        Node<T,L>* temp = root;
        while(temp != nullptr){
            if(value > temp->value){
                temp = temp->right;
            }
            else if(value < temp->value){
                temp = temp->left;
            }
            else{
                return true;
            }
        }
        return false;
    }
    /// Returns the data in a node
    /// \param value The value of the node
    /// \return The data of a node
    T& findNode(L value){
        Node<T, L>* temp = root;
        while(temp!= nullptr){
            if(value > temp->value){
                temp = temp->right;
            }
            else if(value < temp->value){
                temp = temp->left;
            }
            else{
                return temp->data;
            }
        }
    }
    /// Adds the data of all nodes to a private vector
    /// \param root Root of the tree
    void getNodes(Node<T,L>*& root) {
        Node<T, L>* temp = root;
        if(root != nullptr) {
            getNodes(root->left);
            temp = root;
            this->nodes.push_back(temp->data);
            getNodes(root->right);
        }
    }
    /// Returns the private vector
    /// \return Private nodes vector
    vector<T> returnNodes() {
        getNodes(root);
        return this->nodes;
    }
    /// Inorder traversal to print the values of all nodes in tree
    /// \param root Root of the tree
    void printTree(Node<T,L>*& root) {
        if (root != nullptr) {
            printTree(root->left);
            cout << root->value << endl;
            printTree(root->right);
        }
    }
    /// Calls printTree function
    void print() {
        printTree(root);
    }
    /// Postorder traversal to delete all nodes in tree
    /// \param root Root of the tree
    void clear(Node<T,L>*& root){
        if(root != nullptr){
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }

    /// Calls the clear function, resets root to nullptr and treesize to 0
    void deleteTree(){
        clear(root);
        root = nullptr;
        treesize = 0;
    }

};
#endif //SEARCH_ENGINE_HARRISON_WOOD_AVLTREE_H