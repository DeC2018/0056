#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int comp(const void* a, const void* b) {
    return (*(int**)a)[0] - (*(int**)b)[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    qsort(intervals, intervalsSize, sizeof(int*), comp);

    int** stack = (int**)malloc(sizeof(int*) * intervalsSize);
    stack[0] = intervals[0];
    int top = 1;
    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i][0] <= stack[top - 1][1]) {
            stack[top - 1][1] = intervals[i][1] > stack[top - 1][1] ? intervals[i][1] : stack[top - 1][1];
        } else {
            stack[top++] = intervals[i];
        }
    }

    *returnSize = top;
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return stack;
}

int main() {
    int intervals1[][2] = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    int* intervals1Ptrs[] = {intervals1[0], intervals1[1], intervals1[2], intervals1[3]};
    int intervals1ColSize = 2;
    int returnSize1;
    int* returnColumnSizes1;
    int** result1 = merge(intervals1Ptrs, 4, &intervals1ColSize, &returnSize1, &returnColumnSizes1);
    printf("Input: intervals = [[1,3],[2,6],[8,10],[15,18]]\n");
    printf("Output: [");
    for (int i = 0; i < returnSize1; ++i) {
        printf("[%d,%d]", result1[i][0], result1[i][1]);
        if (i < returnSize1 - 1) printf(",");
    }
    printf("]\n");
    free(returnColumnSizes1);
    free(result1);

    int intervals2[][2] = {{1, 4}, {4, 5}};
    int* intervals2Ptrs[] = {intervals2[0], intervals2[1]};
    int intervals2ColSize = 2;
    int returnSize2;
    int* returnColumnSizes2;
    int** result2 = merge(intervals2Ptrs, 2, &intervals2ColSize, &returnSize2, &returnColumnSizes2);
    printf("Input: intervals = [[1,4],[4,5]]\n");
    printf("Output: [");
    for (int i = 0; i < returnSize2; ++i) {
        printf("[%d,%d]", result2[i][0], result2[i][1]);
        if (i < returnSize2 - 1) printf(",");
    }
    printf("]\n");
    free(returnColumnSizes2);
    free(result2);

    return 0;
}
