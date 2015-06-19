#include <iostream>
#include <cstdlib>

using namespace std;

void print(int**, int rows, int columns);
int** get(int columns, int rows);
int row_mult(int** matrix, int rows, int column);
void selection_sort_columns(int** matrix, int rows, int columns);
void swap_columns(int** matrix, int rows, int column_1, int column_2);

int main()
{
    const int columns = 10;
    const int rows = 5;
    int **matrix = get(columns, rows);
    print(matrix, rows, columns);
    selection_sort_columns(matrix, rows, columns);
    cout << "Відсортовано" << endl;
    print(matrix, rows, columns);
    for (int i = 0; i < rows; i++) delete [] matrix[i];
    delete matrix;
    return 0;
}

void print(int** matrix, int rows, int columns) {
    cout << "Matrix: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j =0; j < columns; j++) {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

int** get(int columns, int rows) {
    int **matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
        for (int j =0; j < columns; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

int row_mult(int** matrix, int rows, int column) {
    int mult = 1;
    for (int i = 0; i < rows; i++) {
        mult *= matrix[i][column];
    }
    return mult;
}

void selection_sort_columns(int** matrix, int rows, int columns) {
    for (int i = 0; i < columns - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < columns; j++) {
            if (row_mult(matrix, rows, j) < row_mult(matrix, rows, min_idx)) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            swap_columns(matrix, rows, i, min_idx);
        }
    }
}

void swap_columns(int** matrix, int rows, int column_1, int column_2) {
    for (int i = 0; i < rows; i++) {
        swap(matrix[i][column_1], matrix[i][column_2]);
    }
}
