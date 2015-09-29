#ifndef APARTAMENT_H
#define APARTAMENT_H

#include <string>
#include <iostream>

using namespace std;

class Apartament {

    static constexpr const char* undefined = "Undefined";

    string addr,
           requis,
           det;
    int sqr;

public:
    Apartament();
    Apartament(string const &address, string const &requisites, int const &square);
    Apartament(string const &address, string const &requisites, string const &details, int const &square);

    const string &address();
    const string &requisites();
    const string &details();
    const int &square();

    friend ostream &operator << (ostream &out, Apartament &app) {
        cout << "Apartament: " << app.addr << endl
             << "Square: " << app.sqr << " meters" << endl
             << "Details: " << app.det << endl
             << "Owner: " << app.requis << endl;
        return out;
    }

    bool operator == (Apartament &two) {
        return addr == two.addr
               && sqr == two.sqr;
    }
};

#endif // APARTAMENT_H
