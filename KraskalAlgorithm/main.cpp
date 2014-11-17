/*
 * File:   main.cpp
 * Author: Naik
 *
 * Created on Nowember 17, 2014, 18:45 PM
 *
 * Побудова остового дерева методом Краскала.
 */

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

struct Node {
    struct Node **contacts;
};

void findMin(int**, int, int&, int&);
void printArray(int**, int);

int main() {
    int size, i, j;
    char path[80];
    cout << "Введіть шлях до файлу даних:" << endl;
    cin >> path;
    fstream fis(path, ios::in);
    if (!fis.is_open()) {
        cout << "Помилка шляху!" << endl;
        return 1;
    }
    int in;
    fis >> size;
    Node *nodes = new Node[size];
    int **M = new int*[size];
    for (i = 0; i < size; i++) {
        nodes[i].contacts = new Node*[size];
        M[i] = new int[size];
        for (j = i; j < size; j++) {
            fis >> in;
            if (in == -1) in = INT_MAX;
            if (i == j) in = INT_MAX; // виключаємо петлі
            M[i][j] = in;
        }
    }
    fis.close();
    printArray(M, size);

    //Algo begin
    int x, y;
    do {
        findMin(M, size, x, y);
        if (x < 0 || y < 0) break;
        cout << x << " " << y << endl;
        M[x][y] = INT_MAX;
    } while (1);
    //Algo end

    for (i = 0; i < size; i++) delete [] M[i];
    delete [] M;
    delete [] nodes;

}

void findMin(int **arr, int l, int& x, int& y) {
    int min = arr[0][0];
    x = -1, y = -1;
    for (int i = 0; i < l; i++) {
        for (int j = i; j < l; j++) {
            if (arr[i][j] < min) {
                min = arr[i][j];
                x = i, y = j;
            }
        }
    }
}

void printArray(int **arr, int l) {
    for (int i = 0; i < l; i++) {
        for (int j = i; j < l; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}
