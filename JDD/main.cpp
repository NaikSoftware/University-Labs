/*
 * File:   main.cpp
 * Author: N. Savchenko
 *
 * Created on 9 квітня 2015, 17:17
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <climits>


#define INF -1
#define ASCII_START 97

using namespace std;

int** getMatrix(string, int&, bool = true, string = "");
template <typename T> void printMatrix(T**, int, string = "");

inline bool empty(string &str) {
    return str.empty() or str.compare("0") == 0;
}

class Cell {

    vector<string> summa, new_summa;

public:

    void mult(string &str, Cell &other) {
        for (auto &str2 : other.summa) {
            new_summa.push_back(str + str2);
        }
    }

    void commit(string &row) {
        for (auto it = new_summa.begin();it != new_summa.end();it++) {
            if ((*it).find(row) != string::npos) {
                new_summa.erase(it);
                it--;
            }
        }
        summa = new_summa;
        new_summa.clear();
    }

    bool empty() {
        return summa.size() == 0;
    }

    int get_most_short(int **m, string &path) {
        cout << endl << "Select diagonal " << *this;
        int len = INT_MAX;
        for (auto &str : summa) {
            int tmp = 0;
            char prev = path[0];
            string buff(&prev, 1);
            for (char &ch : str) {
                tmp += m[prev - ASCII_START][ch - ASCII_START];
                prev = ch;
                buff += ch;
            }
            tmp += m[prev - ASCII_START][path[0] - ASCII_START]; // cycled path
            cout << endl << "\tPath " << str << " with length " << tmp;
            if (tmp < len) len = tmp, path.assign(buff);
        }
        return len;
    }

    void operator += (const string str) {
        summa.push_back(str);
    }

    friend ostream& operator << (ostream &output, Cell &cell) {
        for (size_t i = 0, size = cell.summa.size();i < size; i++) {
            output << cell.summa[i];
            if (i < size - 1) output << '+';
        }
        return output;
    }
};

void mult(string**, Cell**, int, bool=false);

/*
 * Пошук гамільтонових контурів методом Йоу, Даніельсона, Дхавана
 */
int main(int argc, char** argv) {

    // Зчитуємо матрицю суміжності ваг графа
    int size;
    int** m = getMatrix("Input matrix:", size, true, "/home/naik/data4.txt");
    printMatrix(m, size);

    // Створення матриці перетвореннь і результуючої
    string** v = new string*[size];
    Cell** p = new Cell*[size];
    for (int i = 0; i < size; i++) {
        v[i] = new string[size];
        p[i] = new Cell[size];
        for (int j = 0; j < size; j++) {
            char ch = m[i][j] > 0 ? ASCII_START + j : '0';
            v[i][j].assign(string(&ch, 1));
        }
    }

    printMatrix(v, size, "Matrix V:");

    // Обрахування першої результуючої матриці p2 (бо p1=m)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                if (not empty(v[i][k]) and m[k][j] != INF and i != j) {
                    p[i][j] +=  v[i][k];
                }
            }
        }
    }

    // Обчислення інших матриць P
    for (int i = 3;i <= size;i++) {
        if (i == size) {            // Якщо остання матриця P
            mult(v, p, size, true); // то рахуємо діагоналі
        } else mult(v, p, size);
        for (int j = 0;j < size;j++) {
            for (int k = 0;k < size;k++) {
                char ch(ASCII_START + j);
                string str(&ch, 1);
                p[j][k].commit(str);
            }
        }
    }

    string path("a"); // Начиная с первой точки "a"
    int len = p[0][0].get_most_short(m, path);
    cout << endl << endl << "Shortest path: " << (path += "a") << " Length: " << len
         << endl << endl;

    for (int i = 0; i < size; i++) {
        delete [] m[i];
        delete [] v[i];
    }
    delete [] m;
    delete [] v;
    return 0;
}

/*
 * Перемножити матрицi
 */
void mult(string **v, Cell **p, int size, bool calc_diag) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                if (not empty(v[i][k]) and not p[k][j].empty()
                        and (i !=  j or calc_diag)) {
                    p[i][j].mult(v[i][k], p[k][j]);
                }
            }
        }
    }
}

/*
 * Зчитати матрицю з потоку вводу або файлу (якщо задано path)
 */
int** getMatrix(string prompt, int& size, bool excl_diag, string path) {
    cout << prompt << endl;
    istream *in;
    if (!path.empty()) {
        in = new ifstream(path.c_str());
        if (in->fail()) {
            cout << "File not found " << path << endl;
            exit(1);
        }

        cout << "Read from " << path << endl;
    } else {
        in = &cin;
        cout << "size: ";
    }
    *in >> size;
    int** arr = new int*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new int[size];
        if (path.empty()) cout << "row " << i + 1 << endl;
        for (int j = 0; j < size; j++) {
            *in >> arr[i][j];
            if (i == j && excl_diag) arr[i][j] = INF;
        }
    }
    if (dynamic_cast<ifstream*>(in)) delete in;
    return arr;
}

template<typename T> void printMatrix(T** m, int size, string prompt) {
    cout << prompt << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
}
