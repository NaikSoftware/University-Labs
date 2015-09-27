#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <ostream>
#include <initializer_list>
#include <memory>

using namespace std;

/**
 * @brief The base List class with overloaded operations
 */
template <typename T>
class List {

public:
    List() {
    }

    virtual shared_ptr<List<T>> clone() const = 0;
    virtual size_t getSize() = 0;
    virtual void insert(T *t, int i) = 0;
    virtual void append(const T& t, int position) = 0;
    virtual T* get(int i) = 0;

    friend List<T> &operator << (List<T> &list, const T& t) {
        list.insert(const_cast<T*>(&t), list.getSize());
        return list;
    }

    T& operator [] (int i) {
        return *get(i);
    }

    shared_ptr<List<T>> operator + (List<T> &other) {
        auto result = this->clone();
        result->pushAll(other);
        return result;
    }

    friend ostream &operator << (ostream &out, List<T> &list) {
        size_t size = list.getSize();
        cout << "(" << size << ") [ ";
        for (int i = 0; i < size; i++) {
            if (list.get(i)) cout << *list.get(i);
            if (i != size - 1) cout << ", ";
        }
        cout << " ]";
        return out;
    }

    virtual ~List() {
    }

protected:

    void pushAll(List<T> &list) {
        int start = getSize();
        for (int i = 0; i < list.getSize(); i++) {
            T *t = list.get(i);
            if (t) insert(list.get(i), start + i);
        }
    }
};

#endif // LIST_H
