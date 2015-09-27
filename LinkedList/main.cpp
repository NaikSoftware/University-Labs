#include <iostream>
#include "util/list.h"
#include "util/linkedlist.h"

#define EOL << endl << endl

using namespace std;

int main() {
    List<char> *list = new LinkedList<char>({ 'a', 'b', 'c' });
    cout << "Init list: " << *list << endl << endl;

    (*list) << 'A' << 'Z' << 'W';
    cout << "Insert in end: " << *list << endl << endl;
    cout << "Element 99 is null? " << (&(*list)[99] == nullptr ? "yes" : "no") EOL;

    (*list)[0] = 'M';
    list->append('K', 10);
    cout << "Insert to different places: " << *list EOL;

    List<char> *list2 = new LinkedList<char>(*list);
    cout << "Copy: " << *list2 << endl << endl;

    (*list2)[0] = '^';
    (*list2)[4] = 'P';
    cout << "Changed copy:" << *list2 EOL;

    cout << endl << endl;
    cout << "Summ: " << *(*list + *list2) << endl;
    cout << "List: " << *list << endl;
    cout << "List2:" << *list2 EOL;

    delete list, delete list2;
    return 0;
}
