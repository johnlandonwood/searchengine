#ifndef SEARCH_ENGINE_HARRISON_WOOD_NODE_H
#define SEARCH_ENGINE_HARRISON_WOOD_NODE_H
#include <iostream>
//written by Maria Harrison
//AVL Node class

/// Written by Maria Harrison.
/// Node class for AVL Tree
template <class T, class L>
class Node{
    template <class U, class X> friend class AVLTree;
private:
    T data;
    int height;
    L value;
public:
    /// Left child of the node
    Node<T, L>* left;
    /// Right child of the node
    Node<T, L>* right;

    /// Default constructor
    Node(){
        //set next and prev to null
        left = nullptr;
        right = nullptr;
    };

    //constructor with one argument
    /// Parameterized constructor
    Node(T data, L key){
        this->data = data;
        this->value = key;
        left = nullptr;
        right = nullptr;
        this->height = 1;
    };

    //copy constructor
    /// Copy constructor
    /// \param source Node to be copied
    Node(Node<T, L>& source){
        data = source.data;
        value = source.value;
        left = source.left;
        right = source.right;
    };

    //overload assignment operator
    /// Overloaded copy assignment operator
    /// \param source Right hand side node to be copied
    /// \return Copied node
    Node& operator=(const Node<T, L>& source){
        data = source.data;
        value = source.value;
        left = source.left;
        right = source.right;
    };


};
#endif //SEARCH_ENGINE_HARRISON_WOOD_NODE_H
