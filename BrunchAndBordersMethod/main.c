/* 
 * File:   main.c
 * Author: Naik
 *
 * Created on October 23, 2014, 4:30 PM
 * 
 * Пошук гамільтонового контура методом гілок та меж (задача комівояжера).
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) (a) < (b)? (a): (b)

struct NodeStruct {
    struct NodeStruct *childExclude, *childInclude, *parent;
    int isExclude;
    int **matrix, size;
    int *idxRows, *idxCols;
    int from, to, limit;
};
typedef struct NodeStruct Node;

int simplification(int**, int);
void mountChildNodes(Node*);
void freeNodes(Node*);
void cellExists(Node*, int, int, int*, int*);
Node* getBetterNode(Node*);

int main(int argc, char** argv) {
    int size, i, j, k;
    char path[80];
    printf("Введіть шлях до файлу даних:\n");
    scanf("%s", path);
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Помилка шляху!\n");
        return EXIT_FAILURE;
    }
    fscanf(file, "size=%d", &size);
    int **M = (int**) malloc(size * sizeof (int*));
    for (i = 0; i < size; i++) M[i] = (int*) malloc(size * sizeof (int));
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fscanf(file, "%d", &M[i][j]);
            if (M[i][j] == -1) M[i][j] = INT_MAX;
            if (i == j) M[i][j] = INT_MAX; // виключаємо петлі
        }
    }
    fclose(file);

    /* Створимо корненевий вузол */
    Node *rootNode = (Node*) calloc(1, sizeof (Node));
    rootNode->size = size;
    rootNode->matrix = M;

    int *idxRows = (int*) malloc(size * sizeof (int));
    int *idxCols = (int*) malloc(size * sizeof (int));
    for (i = 0; i < size; i++) idxRows[i] = idxCols[i] = i;
    rootNode->idxRows = idxRows, rootNode->idxCols = idxCols;
    rootNode->limit = simplification(M, size);

    int valid = 0;
    Node *closeNode = rootNode, *node;
    while (closeNode->size > 2) {
        mountChildNodes(closeNode);
        closeNode = getBetterNode(rootNode);
        valid = 0;
        for (i = 0; i < closeNode->size; i++) {
            for (j = 0; j < closeNode->size; j++) {
                if (closeNode->matrix[i][j] != INT_MAX) valid = 1;
            }
        }
        if (!valid) break; // Вся матриця заповнена нескінченністю
    }
    if (valid) {
        int start, end;
        int** arr = closeNode->matrix;
        if (arr[0][0] == 0) start = closeNode->idxRows[0], end = closeNode->idxCols[0];
        else start = closeNode->idxRows[0], end = closeNode->idxCols[1];
        if (arr[1][0] == 0) rootNode->from = closeNode->idxRows[1], rootNode->to = closeNode->idxCols[0];
        else rootNode->from = closeNode->idxRows[1], rootNode->to = closeNode->idxCols[1];

        /* Print Gamilton Contour */
        printf("\nКонтур: { %d\t%d", start + 1, end + 1);
        do {
            node = closeNode;
            while (end != node->from || node->isExclude) node = node->parent;
            end = node->to;
            printf("\t%d", end + 1);
        } while (start != end);
        printf(" }\nДовжина: %d\n\n", closeNode->limit);
    } else {
        printf("\nНеможливо побудувати Гамільтонів Контур!\n\n");
    }

    /* Complete, free memory */
    freeNodes(rootNode);
    return (EXIT_SUCCESS);
}

/*
 * @node - вузол, в якому потрібно створити дочірні
 */
void mountChildNodes(Node *node) {
    /* Find high-priced zero */
    int col, row, price = 0, i, j, k, oldSize, newSize, minInRow, minInCol;
    int zeroRow, zeroCol;
    oldSize = node->size;
    int **arr = node->matrix;
    for (i = 0; i < oldSize; i++) {
        for (j = 0; j < oldSize; j++) {
            if (arr[i][j] != 0) continue;
            minInRow = minInCol = INT_MAX;
            for (k = 0; k < oldSize; k++) {
                if (k != j) minInRow = min(minInRow, arr[i][k]);
                if (k != i) minInCol = min(minInCol, arr[k][j]);
            }
            if (minInRow == INT_MAX || minInCol == INT_MAX) {
                minInRow = 0, minInCol = INT_MAX; // захист від переповнення
            }
            if (price <= (minInRow + minInCol)) {
                price = minInRow + minInCol;
                zeroRow = i, zeroCol = j;
                row = node->idxRows[i], col = node->idxCols[j];
            }
        }
    }
    /* Create 'include' child */
    Node *childIncl = (Node*) calloc(1, sizeof (Node));
    newSize = (oldSize - 1);
    childIncl->size = newSize;
    childIncl->from = row;
    childIncl->to = col;
    childIncl->parent = node;
    /* Create new matrix without one row and column */
    int *idxRows = (int*) malloc(newSize * sizeof (int));
    int *idxCols = (int*) malloc(newSize * sizeof (int));
    int **m = (int**) malloc(newSize * sizeof (int*));
    int offsetRow = 0, offsetCol;
    for (i = 0; i < oldSize; i++) {
        if (node->idxRows[i] == row) {
            offsetRow = 1;
            continue;
        }
        idxRows[i - offsetRow] = node->idxRows[i];
        m[i - offsetRow] = (int*) malloc(newSize * sizeof (int));
        offsetCol = 0;
        for (j = 0; j < oldSize; j++) {
            if (node->idxCols[j] == col) {
                offsetCol = 1;
                continue;
            }
            idxCols[j - offsetCol] = node->idxCols[j];
            m[i - offsetRow][j - offsetCol] = node->matrix[i][j];
        }
    }
    childIncl->idxRows = idxRows;
    childIncl->idxCols = idxCols;
    childIncl->matrix = m;
    /* Exclude short cycle */
    int start = childIncl->from, end = childIncl->to, realRow, realCol;
    Node *nCurr = childIncl;
    while (nCurr != 0) {
        if (start == nCurr->to) start = nCurr->from;
        else if (end == nCurr->from) end = nCurr->to;
        cellExists(childIncl, end, start, &realRow, &realCol);
        if (realRow != -1 && realCol != -1) {
            m[realRow][realCol] = INT_MAX;
            break;
        }
        nCurr = nCurr->parent;
    }
    /* Simplificate and set limit */
    k = simplification(m, newSize); // захист від переповнення
    if (k == INT_MAX || node->limit == INT_MAX) childIncl->limit = INT_MAX;
    else childIncl->limit = (node->limit + k);
    node->childInclude = childIncl;
    /* Create 'exclude' child (just copy parent matrix and modify) */
    Node *childExcl = (Node*) calloc(1, sizeof (Node));
    childExcl->size = node->size;
    childExcl->from = row;
    childExcl->to = col;
    childExcl->parent = node;
    childExcl->isExclude = 1;
    childExcl->idxRows = node->idxRows;
    childExcl->idxCols = node->idxCols;
    childExcl->matrix = node->matrix;
    childExcl->matrix[zeroRow][zeroCol] = INT_MAX;
    simplification(node->matrix, oldSize);
    if (price == INT_MAX || node->limit == INT_MAX) childExcl->limit = INT_MAX;
    else childExcl->limit = (node->limit + price);
    node->childExclude = childExcl;
}

/* Вертає суму констант приведення */
int simplification(int **arr, int size) {
    int min, i, j, downLimit = 0;
    for (int k = 0; k < 2; k++) {
        for (i = 0; i < size; i++) {
            min = INT_MAX;
            for (j = 0; j < size; j++) {
                if (k == 0) min = min(min, arr[i][j]); // по рядках
                else min = min(min, arr[j][i]); // по стовпчиках
            }
            if (downLimit == INT_MAX || min == INT_MAX) {
                downLimit = INT_MAX;
            } else {
                downLimit += min;
            }
            for (j = 0; j < size; j++) {
                if (k == 0 && arr[i][j] != INT_MAX) arr[i][j] -= min;
                else if (k == 1 && arr[j][i] != INT_MAX) arr[j][i] -= min;
            }
        }
    }
    return downLimit;
}

void cellExists(Node *node, int row, int col, int *realRow, int *realCol) {
    int size = node->size;
    *realRow = *realCol = -1;
    for (int i = 0; i < size; i++) {
        if (node->idxRows[i] == row) *realRow = i;
        if (node->idxCols[i] == col) *realCol = i;
    }
}

Node* getBetterNode(Node *node) {
    if (!node->childExclude) { // якщо листок
        return node;
    } else { // якщо вузол дерева
        Node* node1 = getBetterNode(node->childExclude);
        Node* node2 = getBetterNode(node->childInclude);
        if (node1->limit > node2->limit) return node2;
        else return node1;
    }
}

void freeNodes(Node *node) {
    if (!node->childExclude) { // листок (немає дочірніх елементів)
        free(node);
        return;
    }
    freeNodes(node->childExclude);
    freeNodes(node->childInclude);
    if (!node->isExclude) {
        for (int i = 0; i < node->size; i++) free(node->matrix[i]);
        free(node->matrix);
        free(node->idxRows);
        free(node->idxCols);
    }
    free(node);
}