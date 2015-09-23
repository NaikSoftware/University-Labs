#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <ostream>

using namespace std;

/**
 * @brief The base List class with overloaded operations
 */
template <typename T>
class List {

public:
    List();

    friend List<T> &operator << (List<T> &list, T t) {
        list.insert(t, list.getSize());
        return list;
    }

    virtual ~List() {
        cout << "List destructor" << endl;
    }

protected:
    virtual void insert(T &t, int i) = 0;
    virtual T &get(int i) = 0;
    virtual size_t getSize() = 0;

};

template <typename T>
List<T>::List() {
    cout << "List constructor" << endl;
}

#endif // LIST_H
