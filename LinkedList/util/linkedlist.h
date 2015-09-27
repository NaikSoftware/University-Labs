#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "list.h"
#include <iostream>
#include <initializer_list>
#include <memory>

using namespace std;

/**
 * @brief The implementation of List on linked list.
 */
template <typename T>
class LinkedList: public List<T> {

    struct Item {
        T val;
        const int position;
        Item *next = 0;
        Item(T val, const int position, Item *next = 0):
            val(val), position(position), next(next) {
        }
        ~Item() {
            cout << "Destructor item: " << val << endl;
        }
    };

    Item *head;
    int size;

public:

    LinkedList(List<T> &list) {
        cout << "LinkedList copy ctor " << list << endl;
        List<T>::pushAll(list);
    }

    LinkedList(initializer_list<T> list) {
        cout << "List from brace list" << endl;
        int position = 0;
        for (auto i = list.begin(); i != list.end(); i++) insert(const_cast<T*>(&*i), position++);
    }

    LinkedList(): head(0), size(0) {
    }

    shared_ptr<List<T>> clone() const {
        List<T> *cloned = new LinkedList(*this);
        return make_shared<LinkedList<T>>(*cloned);
    }

    size_t getSize() {
        return size;
    }

    Item* getItem(int n) {
        Item *curr = head;
        while (curr && curr->position < n) curr = curr->next;
        return curr && curr->position == n? curr : nullptr;
    }

    void append(const T& t, int position) {
        Item *item = getItem(position);
        if (!item) insert(const_cast<T*>(&t), position);
        else item->next = new Item(const_cast<T&>(t), position, item->next);
    }

    ~LinkedList() {
        cout << "LinkedList destructor" << endl;
        Item *curr;
        while (head) {
            curr = head;
            head = head->next;
            delete curr;
        }
    }

private:

    T* get(int n) {
        Item *item = getItem(n);
        return item? &item->val : nullptr;
    }

    void insert(T *t, int n) {
        cout << "Insert " << *t << " in " << n << endl;
        Item *curr = head, *prev = 0;
        while (curr && curr->position < n) {
            prev = curr;
            curr = curr->next;
        }
        cout << "after while: " << (curr && curr->position == n) << endl;
        if (curr && curr->position == n) curr->val = *t; // replace exists item value
        else insertBetween(prev, curr, t, n);           // else insert new
    }

    void insertBetween(Item *prev, Item *next, T *t, int pos) {
        char s = prev ? prev->val : '_',
             e = next ? next->val : '_';
        cout << "Insert between " << s << " " << *t << "(" << pos << ") " << e << endl;
        if (!prev) head = new Item(*t, 0, next), size = 1, cout << "\t create head" << endl;
        else if (!next) prev->next = new Item(*t, pos), size = pos + 1;
        else prev->next = new Item(*t, pos, next);
    }

};

#endif // LINKEDLIST_H
