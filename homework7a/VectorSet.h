#pragma once
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
class VectorSet {
private:
  std::vector<T> myVector;
public:
    bool contains(T item) const {
        // implement contains here
        // return true if item is in the set and false if not
        auto it = std::find(myVector.begin(), myVector.end(), item);

        if (it != myVector.end()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool insert(T item) {
        // implement insert here
// use pushback, check if it is already in the vector
        // return true if item is inserted and false if item is already in the
        // set
        auto it = std::find(myVector.begin(), myVector.end(), item);

        if (it != myVector.end()) {
            // Value found, remove it using erase()
            return false;
        }
        else {
            myVector.push_back(item);
            return true;
        }
    }

    bool remove(T item) {
        // implement remove here
        bool removed = false;
        for (int i = myVector.size() - 1; i >= 0; i--) {
            if (myVector[i] == item) {
                myVector.erase(myVector.begin() + i);
                removed = true;
            }
        }
        return removed;
        // return true if item is removed and false if item wasn't in the set
    }

    int size() const {
        return myVector.size();
    }

    bool empty() const {
        // implement empty here
            if (myVector.empty()) {
                return true;
            }
            else {
                return false;
            }
        // return true if the set is empty and return false otherwise
    }

    void clear() {
        // implement clear here
        myVector.clear();
        // remove all items from the set
    }
};
