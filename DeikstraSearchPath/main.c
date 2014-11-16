/* 
 * File:   main.c
 * Author: Naik
 *
 * Created on October 16, 2014, 5:49 PM
 * 
 * Input:
 * ~~~~~~~~
 * size=5 start=0 end=4
 * -1	4	6	11	-1
 * 4	-1	10	6	-1
 * 6	10	-1	3	8
 * 11	6	3	-1	4
 * -1	-1	8	4	-1
 * ~~~~~~~~
 * -1 означає нескінченність.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Cell {
    int closed; //          A
    int passability; //     B
    struct Cell *parent; // Ind
    char name[5];
};

int main(int argc, char** argv) {
    int size, i, j, start, end, min, idx;
    char path[80];
    printf("Введіть шлях до файлу даних:\n");
    scanf("%s", path);
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Помилка шляху!\n");
        return EXIT_FAILURE;
    }
    fscanf(file, "size=%d start=%d end=%d", &size, &start, &end);
    struct Cell *row = (struct Cell*) malloc(size * sizeof (struct Cell));
    int **C = (int**) malloc(size * sizeof (int*)); // C-matrix
    for (i = 0; i < size; i++) C[i] = (int*) malloc(size * sizeof (int));
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fscanf(file, "%d", &C[i][j]);
            if (C[i][j] == -1) C[i][j] = INT_MAX;
        }
    }
    fclose(file);

    // First part (init)
    row[start].parent = 0;
    row[start].passability = 0;
    row[start].closed = 1;
    for (i = 0; i < size; i++) {
        sprintf(row[i].name, "X%d", i);
        if (i != start) {
            row[i].parent = &row[start];
            row[i].passability = C[start][i];
            row[i].closed = 0;
        }
    }

    // Second part (cycle)
    for (i = 0; i < (size - 2); i++) {
        min = INT_MAX, idx = -1;
        for (j = 0; j < size; j++) {
            if (row[j].closed) continue;
            if (min > row[j].passability) {
                min = row[j].passability, idx = j;
            }
        }
        row[idx].closed = 1;
        for (j = 0; j < size; j++) {
            if (row[j].closed) continue;
            if (row[j].passability > (C[idx][j] == INT_MAX ? INT_MAX : C[idx][j] + row[idx].passability)) {
                row[j].passability = row[idx].passability + C[idx][j];
                row[j].parent = &row[idx];
            }
        }
    }
    printf("Довжина шляху з %d до %d становить %d\nШлях: ", start, end, row[end].passability);
    struct Cell *cell = &row[end];
    while (cell != 0) {
        printf("%s, ", cell->name);
        cell = cell->parent;
    }
    printf("\n\n");
    for (i = 0; i < size; i++) free(C[i]);
    free(C);
    free(row);
    return (EXIT_SUCCESS);
}

