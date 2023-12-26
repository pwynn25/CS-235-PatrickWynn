#pragma once
#include <algorithm>

using namespace std;

template<class T>
class AVL {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;
        int height;

        Node(T v) : left(nullptr), right(nullptr), value(v), height(1) {}
    };

    AVL() {
        root = nullptr;
        count = 0;
        // implement the contructor here
    }

    ~AVL() {
       clear();
    }

    const Node* getRootNode() const {
        return root;
    }
    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    bool insertHelper(Node *&n, int val) {
        bool insrt = false;
        if (n == nullptr) {
            n = new Node(val);
            count++;
            return true;
        } else if (n->value == val) {
            return false;
        } else if (n->value < val) {
            insrt =  insertHelper(n->right, val);
            updateHeight(n);
            rebalance(n);
            return insrt;
        } else {
            insrt =  insertHelper(n->left, val);
            updateHeight(n);
            rebalance(n);
            return insrt;
        }

    }
    bool insert(T item) {
        return insertHelper(root,item);
    }
    bool removeHelper(Node *&n, T val) {
        bool rmv = false;
        if (n == nullptr) {
            return false;
        } else if (n->value > val) {
            //                begin rebalance
            rmv = removeHelper(n->left, val);
            updateHeight(n);
            rebalance(n);
            return rmv;
        } else if (n->value < val) {
            //                begin rebalance
           rmv = removeHelper(n->right, val);
           updateHeight(n);
           rebalance(n);
           return rmv;
        } else {
//            node found, implement removal logic
            if (n->left == nullptr) {
                Node *temp = n->right;
                delete n;
                count--;
//                begin rebalance

                n = temp;

                rebalance(n);
                return rmv;
            } else if (n->right == nullptr) {
                Node *temp = n->left;
                delete n;
                n = temp;
                count--;
//                begin rebalance
                rebalance(n);
                return rmv;
            } else {
                Node *temp = minValueNode(n->left);
                n->value = temp->value;
                return removeHelper(n->left, temp->value);
            }
        }

    }
    bool remove(T item) {
        return removeHelper(root, item);
    }
    bool findHelper(Node *n, int v) const {
        if (n == nullptr) {
            return false;
        }
        if (n->value == v) {
            return true;
        } else if (n->value > v) {
            return findHelper(n->left, v);
        } else {
            return findHelper(n->right, v);
        }
    }
    bool contains(T item) const {
        return findHelper(root, item);
    }

    void clear() {
        while (root != nullptr){
            remove(root->value);
        }
    }

    int size() const {
        return count;
    }
//    rebalance.h
    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

// Hint: you might find it helpful to write an update_height function that takes
    void updateHeight(Node* n) {
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
    }

// a Node* and updates its height field based on the heights of its children

    void promote_left(Node*& node) {
        Node* secondNode = node->left;
        node->left = secondNode->right;
        secondNode->right = node;

//    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        updateHeight(node);
//    secondNode->height = max(getHeight(secondNode->left), getHeight(secondNode->right)) + 1;
        updateHeight(secondNode);
        node = secondNode;
    }

// Function to balance the AVL tree


    void promote_right(Node*& node) {
        Node* secondNode = node->right;
        node->right = secondNode->left;
        secondNode->left = node;

//    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        updateHeight(node);
//    secondNode->height = max(getHeight(secondNode->left), getHeight(secondNode->right)) + 1;
        updateHeight(secondNode);
        node = secondNode;
    }

    int getBalance(Node* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    void rebalance(Node*& root) {
        if (root == nullptr) {
            return;
        }

        int balance = getBalance(root);

        // Left heavy
        if (balance > 1) {
//        left or right heavy?
            if (getBalance(root->left) < 0) {
                promote_right(root->left);
            }
            promote_left(root);
        }
            // Right heavy
        else if (balance < -1) {
            if (getBalance(root->right) > 0) {
                promote_left(root->right);
            }
            promote_right(root);
        }
    }
private:
    Node* root;
    int count;
    int height;
};
