#include <iostream>
#include "util/list.h"
#include "util/linkedlist.h"

using namespace std;

int main() {
    List<char> *list = new LinkedList<char>({'a', 'b', 'c'});
    (*list) << 'A';
    delete list;
    return 0;
}
