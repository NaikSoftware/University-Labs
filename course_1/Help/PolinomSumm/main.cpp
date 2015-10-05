#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Polinom {

private:

    string name;
    static double x; // статичний х - один для всіх поліномів
    vector<double> *coeficients;

    vector<double>* getCoefs() {
        vector<double> *vec = new vector<double>();
        cout << "Введіть кофіцієнти полінома " << name << " через пробіл та натисніть [Enter]:" << endl;
        string str;
        getline(cin, str);
        stringstream ss(str);
        double coef;
        while (ss >> coef) {
            vec->push_back(coef);
        }
        return vec;
    }

public:

    Polinom(string name_) {
        name = name_;
        if (!x) {
            cout << "Введіть 'x': ";
            cin >> x;
            cin.get(); // забираємо символ \n з потоку вводу
        }
        coeficients = getCoefs();
    }

    const vector<double>* coefs() {
        return coeficients;
    }

    ~Polinom() {
        delete coeficients;
    }
};
double Polinom::x = 0;

int main()
{
    Polinom *a = new Polinom("a");
    Polinom *b = new Polinom("b");
    if (a->coefs()->size() < b->coefs()->size()) {
        swap(a, b);
    }
    vector<double> resultCoefs;
    for (int i = 0; i < a->coefs()->size() - b->coefs()->size(); i++)
        resultCoefs.push_back(a->coefs()->at(i));
    for (int i = a->coefs()->size() - b->coefs()->size(); i < a->coefs()->size(); i++)
        resultCoefs.push_back(a->coefs()->at(i) + b->coefs()->at(i - a->coefs()->size() + b->coefs()->size()));
    int p = a->coefs()->size() - 1;
    cout << endl << "Степінь утвореного полінома: " << p;
    cout << endl << "Коефіцієнти нового полінома:" << endl;
    for (int i = 0; i < resultCoefs.size(); i++) cout << ' ' << resultCoefs.at(i);
    cout << endl << endl;
    delete a;
    delete b;
    return 0;
}

