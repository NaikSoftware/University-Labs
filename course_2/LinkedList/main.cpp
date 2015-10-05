#include <iostream>
#include <algorithm>
#include <functional>

#include "util/list.h"
#include "util/linkedlist.h"
#include "apartament.h"

#define EOL << endl << "==================" << endl << endl

using namespace std;

void query(List<Apartament> &list, function<bool(Apartament&)> predicate);

int main() {

    List<Apartament> &list = *(new LinkedList<Apartament>({
           Apartament(),
           Apartament("London, Lenina, 52", "+1238746297 (John)", 150),
           Apartament("Egypt, Mr. Mohamed Ahmed Mahmoud, 30", "Vasya", "To sea 20 m!", 29),
           Apartament("Washington, Massachusetts Avenue NW, 25", "John", "Google office", 467)
    }));

    cout << "Квартиры с площадью больше 100 м.кв." EOL;
    query(list, [&] (Apartament &apartament) {
        return apartament.square() > 100;
    });

    Apartament empty;
    cout << "Квартиры без заполненных данных" EOL;
    query(list, [&] (Apartament &apartament) {
        return apartament == empty;
    });

    cout << "Квартиры John'a " EOL;
    query(list, [&] (Apartament &apartament) {
        return apartament.requisites().find("John") != string::npos;
    });

    delete &list;
    return 0;
}

void query(List<Apartament> &list, function<bool(Apartament&)> predicate) {
    for (size_t i = 0; i < list.getSize(); i++)
        if (predicate(list[i])) cout << list[i] << endl;
}
