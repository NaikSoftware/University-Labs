/* 
 * File:   main.c
 * Author: Naik
 *
 * Created on October 18, 2014, 2:30 PM
 * 
 * Input:
 * size=5
 * -1	 4	-1	6	-1
 * 9	 -1	4	-1	1
 * 10	 5	-1	-1	12
 * 15	 5	30	-1	30
 *  2	 -1	2	-1	-1
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int n, last;
} Cell;

void findPathsShimbel(Cell**, int);

int main(int argc, char** argv) {
    int size, i, j;
    char path[80];
    printf("Введіть шлях до файлу даних:\n");
    scanf("%s", path);
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Помилка шляху!\n");
        return EXIT_FAILURE;
    }
    fscanf(file, "size=%d", &size);
    Cell **M = (Cell**) malloc(size * sizeof (Cell*)); // C-matrix
    for (i = 0; i < size; i++) M[i] = (Cell*) malloc(size * sizeof (Cell));
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fscanf(file, "%d", &M[i][j].last);
            if (M[i][j].last == -1) M[i][j].last = INT_MAX;
            if (i == j) M[i][j].last = 0;
        }
    }
    fclose(file);
    findPathsShimbel(M, size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) printf("%d\t", M[i][j].last);
        printf("\n");
    }
    printf("\n\n");
    for (i = 0; i < size; i++) free(M[i]);
    free(M);
    return (EXIT_SUCCESS);
}

void findPathsShimbel(Cell **M, int n) {
    int run = 1, min, i, j, k, sum;
    while (run) {
        run = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                min = INT_MAX;
                for (k = 0; k < n; k++) {
                    if (M[i][k].last == INT_MAX || M[k][j].last == INT_MAX)
                        sum = INT_MAX;
                    else sum = M[i][k].last + M[k][j].last;
                    min = min > sum ? sum : min;
                }
                if (min < M[i][j].last) {
                    run = 1;
                    M[i][j].n = min;
                } else M[i][j].n = M[i][j].last;
            }
        }
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                M[i][j].last = M[i][j].n;
            }
        }
    }
}

