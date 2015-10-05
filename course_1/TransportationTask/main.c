/* 
 * File:   main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) (a) < (b)? (a): (b)
#define max(a, b) (a) > (b)? (a): (b)

typedef enum {
    LEFT, UP, RIGHT, DOWN
} Direct;

typedef struct {
    int cost;
    int items;
    int label;
} Cell;

typedef struct {
    int items;
    int P;
} Pair;

struct Params {
    Cell **matrix;
    Pair *capacity, *demand;
    int *checkpoint, *rows, *cols, *startX, *startY;
};

void logMatrix(struct Params*);
void assignNW(struct Params*);
void assignFogel(struct Params*);
void calcUV(int, int, Direct, struct Params*);
int findCircuit(int, int, struct Params*);

int main(int argc, char** argv) {
    const int infinity = INT_MAX;
    int rows, cols;
    int i, j, tmp, overpay, checkpoint, startX, startY;
    Cell **matrix;
    Pair *capacity, *demand;
    struct Params p;
    struct Params *params = &p;
    printf("\t---ТРАНСПОРТНА ЗАДАЧА---\n\n");
    // Ввід даних
    printf("Введіть шлях до файлу даних:\n");
    char path[80];
    scanf("%s", path);
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Помилка шляху!\n");
        return EXIT_FAILURE;
    }
    fscanf(file, "rows=%d columns=%d", &rows, &cols);
    if (rows < 2 || cols < 2) return EXIT_FAILURE;

    matrix = (Cell**) calloc(rows, sizeof (Cell*));
    for (i = 0; i < rows; i++) {
        matrix[i] = (Cell*) calloc(cols, sizeof (Cell));
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix[i][j].cost);
        }
    }

    capacity = (Pair*) calloc(rows, sizeof (Pair));
    demand = (Pair*) calloc(cols, sizeof (Pair));

    int b1 = 0, b2 = 0;
    for (i = 0; i < rows; i++) {
        fscanf(file, "%d", &capacity[i].items);
        b1 += capacity[i].items;
    }
    for (i = 0; i < cols; i++) {
        fscanf(file, "%d", &demand[i].items);
        b2 += demand[i].items;
    }

    fclose(file);

    if (b1 != b2) {
        printf("Задача не збалансована!\n");
    } else {
        params->matrix = matrix;
        params->capacity = capacity;
        params->demand = demand;
        params->rows = &rows;
        params->cols = &cols;
        params->checkpoint = &checkpoint;
        params->startX = &startX;
        params->startY = &startY;
        printf("Баланс %d\n", b1);
        printf("Виберіть тип початкового розподілу матриці:\n 1 - північно-захiдного кута\n 2 - метод Фогеля\n");
        scanf("%d", &tmp);
        if (tmp == 1) assignNW(params);
        else assignFogel(params);
        int ok = 0;
        while (!ok) {
            for (i = 0; i < rows; i++) capacity[i].P = infinity;
            for (i = 0; i < cols; i++) demand[i].P = infinity;
            j = 0;
            while (!matrix[0][j].items) j++;
            demand[j].P = 0;
            (*params->checkpoint) = 0;
            calcUV(0, j, RIGHT, params);
            if ((*params->checkpoint) < (rows + cols - 1)) {
                printf("Виявлена виродженість в задачі!\n");
            } else {
                overpay = 0;
                // Визначаємо потенціали пустих клітинок.
                for (i = 0; i < rows; i++) {
                    for (j = 0; j < cols; j++) {
                        if (!matrix[i][j].items) {
                            tmp = capacity[i].P + demand[j].P - matrix[i][j].cost;
                            if (overpay < tmp) {
                                overpay = tmp;
                                startX = i;
                                startY = j;
                            }
                        } else {
                            // Також обнуляємо мітки заповнених клітинок.
                            matrix[i][j].label = 0;
                        }
                    }
                }
                if (overpay > 0) {
                    matrix[startX][startY].label = 3; //start cell
                    if ((tmp = findCircuit(0, startY, params))) {
                        for (i = 0; i < rows; i++) {
                            for (j = 0; j < cols; j++) {
                                if (matrix[i][j].items) {
                                    if (matrix[i][j].label == -1)
                                        matrix[i][j].items -= tmp;
                                    else if (matrix[i][j].label == 1)
                                        matrix[i][j].items += tmp;
                                }
                            }
                        }
                        matrix[startX][startY].items = tmp;
                        continue;
                    }
                }
            }
            ok = 1;
        }
        logMatrix(params);
    }
    // Очищення пам’яті і завершення.
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
    free(capacity);
    free(demand);
    return (EXIT_SUCCESS);
}

/**
 *  i - ітерація, n - номер рядка або стовпчика.
 *  Вертає мінімальній елемент послідовності або 0 при невдачі.
 */
int findCircuit(int i, int n, struct Params *params) {
    static int rows, cols, startX, startY, result;
    static Cell **matrix;
    if (params) {
        rows = *params->rows, cols = *params->cols;
        matrix = params->matrix;
        startX = *params->startX, startY = *params->startY;
        result = INT_MAX;
    }
    int count = i % 2 ? cols : rows;
    int idx_1, idx_2;
    for (int j = 0; j < count; j++) {
        idx_1 = i % 2 ? n : j;
        idx_2 = i % 2 ? j : n;
        if (i > 0 && idx_1 == startX && idx_2 == startY && i % 2) {
            return result;
        }
        if (matrix[idx_1][idx_2].items
                && matrix[idx_1][idx_2].label == 0) {
            matrix[idx_1][idx_2].label = (i % 2 ? 1 : -1);
            if (findCircuit(i + 1, j, 0)) {
                if (!(i % 2)) result = min(result, matrix[idx_1][idx_2].items);
                return result;
            } else {
                matrix[idx_1][idx_2].label = 0;
            }
        }
    }
    return 0;
}

void assignNW(struct Params *params) {
    Cell **matrix = params->matrix;
    Pair *capacity = params->capacity, *demand = params->demand;
    int rows = *params->rows;
    int cols = *params->cols;
    int cap, dem, j = 0, rest = 0;
    for (int i = 0; i < rows; i++) {
        cap = capacity[i].items;
        while (cap > 0) {
            dem = demand[j].items - rest;
            cap -= dem;
            if (cap > 0) {
                matrix[i][j].items = dem;
                j++;
                rest = 0;
            }
        }
        if (cap == 0) {
            matrix[i][j].items = dem;
            rest = 0;
            j++;
        } else {
            rest = cap + dem + rest;
            matrix[i][j].items = rest;
        }
    }
}

void assignFogel(struct Params *params) {
    int rows = *params->rows, cols = *params->cols;
    Pair *capacity = params->capacity, *demand = params->demand;
    Cell **matrix = params->matrix;
    const int infinity = INT_MAX;
    int i, j, tmp, k;
    int *tmpCap = (int*) malloc(rows * sizeof (int));
    int *tmpDem = (int*) malloc(cols * sizeof (int));
    for (i = 0; i < rows; i++) tmpCap[i] = capacity[i].items;
    for (i = 0; i < cols; i++) tmpDem[i] = demand[i].items;
    int maxDiff, min[2] = {0, 0}, minIdx, addIdx;
    int addLoc, addMode; // 1=row, -1=column
    int cycle_1, cycle_2;
    Cell cell;
    while (1) {
        maxDiff = -1;
        for (k = 0; k < 2; k++) {
            cycle_1 = k ? cols : rows;
            cycle_2 = k ? rows : cols;
            for (i = 0; i < cycle_1; i++) {
                min[0] = infinity;
                min[1] = infinity;
                if (k && !tmpDem[i]) continue;
                if (!k && !tmpCap[i]) continue;
                for (j = 0; j < cycle_2; j++) {
                    if (k && !tmpCap[j]) continue;
                    if (!k && !tmpDem[j]) continue;
                    cell = matrix[k ? j : i][k ? i : j];
                    tmp = min[0];
                    min[1] = min(min[1], max(min[0], cell.cost));
                    min[0] = min(min[0], cell.cost);
                    if (tmp != min[0]) minIdx = j;
                }
                if (maxDiff < (min[1] - min[0])) {
                    if (!(min[1] == infinity && maxDiff != -1)) {
                        maxDiff = (min[1] == infinity) ? 0 : min[1] - min[0];
                        addMode = k ? -1 : 1;
                        addLoc = i;
                        addIdx = minIdx;
                    }
                }
            }
        }
        if (maxDiff == -1) break;
        if (addMode == -1) {
            tmp = min(tmpDem[addLoc], tmpCap[addIdx]);
            tmpDem[addLoc] -= tmp;
            tmpCap[addIdx] -= tmp;
            matrix[addIdx][addLoc].items = tmp;
        } else {
            tmp = min(tmpCap[addLoc], tmpDem[addIdx]);
            tmpDem[addIdx] -= tmp;
            tmpCap[addLoc] -= tmp;
            matrix[addLoc][addIdx].items = tmp;
        }
    }
    free(tmpCap);
    free(tmpDem);
}

void calcUV(int i, int j, Direct direct, struct Params *params) {
    static int infinity = INT_MAX, rows, cols;
    static struct Params *p;
    static Cell **matrix;
    static Pair *capacity, *demand;
    if (params) {
        p = params;
        rows = *p->rows, cols = *p->cols;
        matrix = p->matrix;
        capacity = p->capacity, demand = p->demand;
    }
    if (i < 0 || i >= rows || j < 0 || j >= cols) return;
    if (!matrix[i][j].items) {
        switch (direct) {
            case LEFT: j--;
                break;
            case UP: i--;
                break;
            case RIGHT: j++;
                break;
            case DOWN: i++;
                break;
        }
        calcUV(i, j, direct, 0);
    } else {
        (*p->checkpoint)++;
        if (capacity[i].P == infinity)
            capacity[i].P = matrix[i][j].cost - demand[j].P;
        else demand[j].P = matrix[i][j].cost - capacity[i].P;
        if (direct != LEFT) calcUV(i, j + 1, RIGHT, 0);
        if (direct != UP) calcUV(i + 1, j, DOWN, 0);
        if (direct != RIGHT) calcUV(i, j - 1, LEFT, 0);
        if (direct != DOWN) calcUV(i - 1, j, UP, 0);
    }
}

void logMatrix(struct Params *params) {
    Cell **matrix = params->matrix;
    int rows = *params->rows;
    int cols = *params->cols;
    int summa = 0;
    printf("\nОптимальній графік (рядки - поставщики, стовпчики - споживачі):\n\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j].items);
            summa += (matrix[i][j].cost * matrix[i][j].items);
        }
        printf("\n");
    }
    printf("\nЦіна %d\n\n", summa);
}