#include "apartament.h"

Apartament::Apartament()
    : Apartament(undefined, undefined, 0) {

}

Apartament::Apartament(string const &address, string const &requisites, int const &square)
    : Apartament(address, requisites, undefined, square) {
}

Apartament::Apartament(string const &address, string const &requisites, string const &details, int const &square)
    : addr(address), requis(requisites), det(details), sqr(square) {
}

const string &Apartament::address() {
    return addr;
}

const string &Apartament::requisites() {
    return requis;
}

const string &Apartament::details() {
    return det;
}

const int &Apartament::square() {
    return sqr;
}
