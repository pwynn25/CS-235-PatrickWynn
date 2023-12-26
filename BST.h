#pragma once

template<class T>
class BST {
public:
//    this struct here defines a new variable type
    struct Node {
        Node *left;
        Node *right;
        T value;

        Node(T v) : left(nullptr), right(nullptr), value(v) {}
    };

    BST() {
        root = nullptr;
        count = 0;
    }

    ~BST() {
//        clear();
    }

//    Now we can start writing functions
// Do we need this?
//    Node* GetNewNode(int data) {
//        Node* newNode = new Node();
//        newNode->value = data;
//        newNode->left = nullptr;
//        newNode->right = nullptr;
//        return newNode;
//    }

    const Node *getRootNode() const {
        return root;
    }



//    . . . Insert . . .

    bool insertHelper(Node *&n, int val) {
        if (n == nullptr) {
            n = new Node(val);
            count++;
            return true;
        } else if (n->value == val) {
            return false;
        } else if (n->value < val) {
            return insertHelper(n->right, val);
        } else {
            return insertHelper(n->left, val);
        }

    }

    bool insert(T item) {
        return insertHelper(root, item);
    }


//    . . . Remove . . .



    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    bool removeHelper(Node *&n, T val) {
        if (n == nullptr) {
            return false;
        } else if (n->value > val) {
            return removeHelper(n->left, val);
        } else if (n->value < val) {
            return removeHelper(n->right, val);
        } else {
//            node found, implement removal logic
            if (n->left == nullptr) {
                Node *temp = n->right;
                delete n;
                count--;
                n = temp;
                return true;
            } else if (n->right == nullptr) {
                Node *temp = n->left;
                delete n;
                n = temp;
                count--;
                return true;
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


//    . . . . Find . . . .


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


    //    . . . CLear . . .

    void clear() {
        while (root != nullptr){
            remove(root->value);
        }

    }

//    . . . Size . . .


//    int countHelper(Node* node) {
//        if (node == nullptr) {
//            return 0; // Return 0 if the tree is empty, or we've reached a leaf node
//        }
//
//        // Recursively count nodes in left and right subtrees, and add 1 for the current node
//        return 1 + size(node->left) + size(node->right);
//}
    int size() const {
        return count;
    }

    private:
    Node* root;
    int count;
};
