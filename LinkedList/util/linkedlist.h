#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "list.h"
#include <iostream>
#include <initializer_list>

using namespace std;

/**
 * @brief The implementation of List on linked list.
 */
template <typename T>
class LinkedList: public List<T> {

    struct Item {
        T val;
        Item *next;
        Item(const T &val): val(val), next(0) {
        }
        Item(): next(0) {
        }
    };

    Item *head;
    int size;

public:
    LinkedList(initializer_list<T> list);
    size_t getSize();
    ~LinkedList();

private:
    T &get(int i);
    void insert(T &t, int n);

};

template <typename T>
LinkedList<T>::LinkedList(initializer_list<T> list) {
    cout << "LinkedList constructor" << endl;
    size = list.size();
    head = new Item(*list.begin());
    Item *curr = head;
    for (auto i = (list.begin() + 1); i != list.end(); i++) {
        curr->next = new Item(*i);
        curr = curr->next;
    }
}

template <typename T>
T &LinkedList<T>::get(int i) {
    cout << "LinkedList get from " << i << endl;
    return head->val;
}

/**
 * Insert T in position n
 */
template <typename T>
void LinkedList<T>::insert(T &t, int n) {
    cout << "LinkedList insert to " << n << " val " << t << endl;
    Item *curr = head, *prev;
    for (int i = 0; i < n; i++) {
        if (!curr) curr = new Item();
        prev = curr;
        curr = curr->next;
    }
    if (curr) {
        prev->next = new Item(t);
        prev->next->next = curr->next;
    } else {
        curr = new Item(t);
        if (prev) prev->next = curr;
    }
}

template <typename T>
size_t LinkedList<T>::getSize() {
    return size;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    cout << "LinkedList destructor" << endl;
}

#endif // LINKEDLIST_H
