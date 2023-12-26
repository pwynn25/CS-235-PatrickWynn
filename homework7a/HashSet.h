#pragma once
#include <string>
#include <functional>
#include <vector>
#include <list>

template<class T>
class HashSet {
private:
    size_t hashModifier;
    size_t numItems;

    struct Node {
        T data;
        Node* next;
        Node(const T& item) : data(item), next(nullptr) {}
    };

    std::vector<std::list<Node*>> buckets;

public:
    HashSet() {
        hashModifier = 10;
        numItems = 0;
        buckets.resize(10);
    }

    ~HashSet() {
        clear();
    }

    bool insert(const T& item) {
        size_t index = getHashIndex(item);
        for (Node* current : buckets[index]) {
            if (current->data == item) {
                return false;
            }
        }
        Node* newNode = new Node(item);
        newNode->next = (*buckets[index].begin());
        buckets[index].push_front(newNode);
        ++numItems;

        if (static_cast<double>(numItems) / hashModifier > 0.75) {
            rehash();
        }
        return true;
    }

    bool remove(T item) {
        // Get hash index (bucket index) to find bucket it would be
        size_t index = getHashIndex(item);
        // Iterate over the list to find if the data exists in the bucket
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            // If found
            if ((*it)->data == item) {
                // delete pointer
                delete *it;
                // Remove from list, like a 2D array
                buckets[index].erase(it);
                //Reduce size
                --numItems;
                //if found return true
                return true;
            }
        }
        // If not found return false
        return false;
    }

    bool contains(T item) const {
        // Get hash index
        size_t index =  getHashIndex(item);
        // Check each item in the list and see if one matches
        for (const Node* current : buckets[index]) {
            if (current->data == item) {
                // return true if item is in the set, false otherwise
                return true;
            }
        }
        return false;
    }

    void clear() {
        for (auto& bucket : buckets) {
            for (Node* current : bucket) {
                delete current;
            }
            bucket.clear();
        }
        numItems = 0;
    }

    int size() const {
        return static_cast<int>(numItems);
    }

private:
    size_t getHashIndex(T item) const {
        size_t hashCode = std::hash<T>{}(item);
        return hashCode % hashModifier;
    }

    void rehash() {
        size_t newModifier = hashModifier * 2;
        std::vector<std::list<Node*>> newBuckets(newModifier);
        for (const auto& bucket : buckets) {
            for (const Node* current : bucket) {
                size_t newHash = std::hash<T>{}(current->data) % newModifier;
                Node* newNode = new Node(current->data);
                newNode->next = (*newBuckets[newHash].begin());
                newBuckets[newHash].push_front(newNode);
            }
        }
        std::swap(hashModifier, newModifier);
        std::swap(buckets, newBuckets);
    }

};
