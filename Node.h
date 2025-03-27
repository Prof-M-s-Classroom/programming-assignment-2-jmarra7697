#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
    T data;
    Node* left;
    Node* right;

    //default constructor
    Node() : data(T()), left(nullptr), right(nullptr) {}

    Node(const T& value) : data(value), left(nullptr), right(nullptr){ } // Implemented constructor
};

#endif // NODE_H