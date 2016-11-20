#include <iostream>
#include <stdexcept>
#include <random>
#include <ctime>

using namespace std;

const int MATRIX_MIN_SIZE = 1;

struct Matrix {
    int w;
    int h;
    int **data;
    int interval_from;
    int interval_to;

    void alloc() {
        data = new int*[w];
        for(int i = 0; i < w; i++) {
            data[i] = new int[h];
            for (int j = 0; j < h; j++) data[i][j] = 0;
        }
    }

    void unalloc() {
        for(int i = 0; i < h; i++) {
            delete [] data[i];
        }
        delete [] data;
    }
};

Matrix retrieve_data();
void print_matrix_data(Matrix &matrix, int step = -1);
void clean_input_buffer();
int get_new_state_for_cell(Matrix &matrix, int w, int h);

int main()
{
    Matrix matrix = retrieve_data();
    cout << "Enter iterations count: ";
    int steps;
    cin >> steps;
    clean_input_buffer();
    for (int step = 0; step < steps; step++) {
        for (int i = 0; i < matrix.w; i++) {
            for (int j = 0; j < matrix.h; j++) {
                matrix.data[i][j] = get_new_state_for_cell(matrix, i, j);
            }
        }
        print_matrix_data(matrix, step + 1);
    }
    matrix.unalloc();
    return 0;
}

int get_new_state_for_cell(Matrix &matrix, int w, int h) {
    int sum_near_cells = 0;
    if (w - 1 >= 0) sum_near_cells += matrix.data[w - 1][h];
    if (w + 1 < matrix.w) sum_near_cells += matrix.data[w + 1][h];
    if (h -1 >= 0) sum_near_cells += matrix.data[w][h - 1];
    if (h + 1 < matrix.h) sum_near_cells += matrix.data[w][h + 1];
    int sum = sum_near_cells + matrix.data[w][h];
    return sum <= matrix.interval_to && sum >= matrix.interval_from;
}

Matrix retrieve_data() {
    Matrix matrix;

    cout << "Enter width of matrix: ";
    cin >> matrix.w;

    cout << "Enter height of matrix: ";
    cin >> matrix.h;

    if (matrix.w < MATRIX_MIN_SIZE || matrix.h < MATRIX_MIN_SIZE) {
         throw runtime_error("Error. Width and height must be greater than " + to_string(MATRIX_MIN_SIZE) + "!");
    } else {
        matrix.alloc();
    }

    cout << "Select input matrix mode: \n\t0 - random (default)\n\t1 - manual input\n";
    clean_input_buffer();
    int mode = getchar();
    if (mode == '0' || mode == '\n') { // Random input
        mt19937 generator(time(0));
        uniform_int_distribution<int> distribution_w(0, matrix.w - 1);
        uniform_int_distribution<int> distribution_h(0, matrix.h - 1);
        uniform_int_distribution<int> distribution_count(1, matrix.w * matrix.h / 3);
        int init_points = distribution_count(generator);
        cout << "Run with init points:" << init_points << endl;
        while (init_points > 0) {
            int w = distribution_w(generator);
            int h = distribution_h(generator);
            if (!matrix.data[w][h]) {
                matrix.data[w][h] = 1;
                init_points--;
            }
        }
    } else if (mode == '1') { // Manual input
        cout << "Input count of True values in matrix: ";
        int init_points, w, h;
        cin >> init_points;
        for(int i = 0; i < init_points; i++) {
            cout << "Input point " << (i + 1) << endl;
            cout << "\tInput index by x axis: ";
            cin >> w;
            cout << "\tInput index by y axis: ";
            cin >> h;
            if (w < 0 || w > matrix.w - 1 || h < 0 || h > matrix.h - 1) {
                throw runtime_error("Error. Width or height index out of range!");
            }
            matrix.data[w][h] = 1;
        }
    } else {
        throw runtime_error("Error. Illegal input!");
    }

    print_matrix_data(matrix);

    cout << "Enter interval from (a): ";
    cin >> matrix.interval_from;
    cout << "Enter interval to (b): ";
    cin >> matrix.interval_to;
    if (matrix.interval_from < 0 || matrix.interval_to < 0 || matrix.interval_from > matrix.interval_to) {
         throw runtime_error("Error. Incorrect interval!");
    }

    return matrix;
}

void print_matrix_data(Matrix &matrix, int step) {
#ifdef __unix__
//    system("clear");
#endif
#ifdef _WIN32
    system("cls");
#endif
#ifdef _WIN64
    system("cls");
#endif
    if (step > -1) cout << "Matrix for step " << step << ":\n\n";
    else cout << "Matrix:\n\n";

    for(int i = 0; i < matrix.h; i++) {
        for (int j = 0; j < matrix.w; j++) {
            cout << matrix.data[j][i] << "\t";
        }
         cout << endl;
    }

    cout << endl << "Press <ENTER> to continue";
    do {
    } while (cin.get() != '\n');
}

void clean_input_buffer() {
    cin.clear();
    while (cin.get() != '\n') {}
}

