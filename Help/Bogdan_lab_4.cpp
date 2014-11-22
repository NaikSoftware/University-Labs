#include <stdlib.h>
#include <stdio.h>

int* inputSet(int&, int* = 0, int = 0);
void printSet(int*, int);
int have(int*, int, int);
void printUnion(int*, int, int*, int);
void printIntersect(int*, int, int*, int);
void printDiff(int*, int, int*, int);
void printInverse(int*, int, int*, int);
void printLinearMultiply(int*, int, int*, int);


int main() {
    int nU, nX, nY; // Довжина універсалу, множин X, Y
    printf("Введіть універсальну множину");
    int* universal = inputSet(nU);
    printf("\nВведіть множину Х");
    int* x = inputSet(nX, universal, nU);
    printf("\nВведіть множину У");
    int *y = inputSet(nY, universal, nU);

    printf("\nОтримані множини:");
    printSet(universal, nU);
    printSet(x, nX);
    printSet(y, nY);

    printUnion(x, nX, y, nY);
    printIntersect(x, nX, y, nY);
    printDiff(x, nX, y, nY);
    printDiff(y, nY, x, nX);
    printInverse(x, nX, universal, nU);
    printInverse(y, nY, universal, nU);
    printLinearMultiply(x, nX, y, nY);

    free(universal);
    free(x);
    free(y);
}

/* Об'єднання множин */
void printUnion(int *x, int nX, int *y, int nY) {
    printf("\nОб`єднання множин:\n { ");
    for (int k = 0; k < nX; k++) {
        printf("%d ", x[k]);
    }
    for (int k = 0; k < nY; k++) {
        if (!have(x, y[k], nX)) printf("%d ", y[k]);
    }
    printf("}");
}

/* Перетин множин */
void printIntersect(int *x, int nX, int *y, int nY) {
    printf("\nПеретин множин:\n { ");
    for (int k = 0; k < nX; k++) {
        if (have(y, x[k], nY)) printf("%d ", x[k]);
    }
    printf("}");
}

/* Різниця множин (x - y) */
void printDiff(int *x, int nX, int *y, int nY) {
    printf("\nРізниця множин:\n { ");
    for (int k = 0; k < nX; k++) {
        if (!have(y, x[k], nY)) printf("%d ", x[k]);
    }
    printf("}");
}

/* Доповнення до множини */
void printInverse(int *x, int nX, int *u, int nU) {
    printf("\nДоповнення множини:\n { ");
    for (int k = 0; k < nU; k++) {
        if (!have(x, u[k], nX)) printf("%d ", u[k]);
    }
    printf("}");
}

/* Прямий добуток множин */
void printLinearMultiply(int *x, int nX, int *y, int nY) {
    printf("\nПрямий добуток множин:\n { ");
    for (int k = 0; k < nX; k++) {
        for (int j = 0; j < nY; j++) {
            printf("(%d, %d) ", x[k], y[j]);
        }
    }
    printf("}");
}

int* inputSet(int &n, int* universal, int sizeUniv) {
    printf("\nВведіть кількість елементів множини: ");
    scanf("%d", &n);
    int *set = (int*)malloc(n * sizeof(int));
    int in;
    for (int k = 0; k < n; k++) {
        printf("Введіть елемент №%d: ", k);
        scanf("%d", &in);
        if (have(set, in, k)) {
            printf("Елемент зі значенням %d уже існує, повторіть введення!\n", in);
            k--;
            continue;
        } else if (universal && !have(universal, in, sizeUniv)) {
            printf("Елемент %d не знайдено в універсалі, повторіть введення!\n", in);
            k--;
            continue;
        } else {
            set[k] = in;
        }
    }
    return set;
}

void printSet(int *set, int size) {
    printf("\n{ ");
    for (int k = 0; k < size; k++) printf("%d ", set[k]);
    printf("}\n");
}

int have(int *set, int elem, int size) {
    for (int k = 0; k < size; k++) {
        if (set[k] == elem) return 1;
    }
    return 0;
}
