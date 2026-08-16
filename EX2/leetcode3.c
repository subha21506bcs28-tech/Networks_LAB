#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int subarrayBitwiseORs(int* arr, int arrSize)
{
    int cur[32], next[32];
    int curSize = 0;

    int *all = malloc(arrSize * 32 * sizeof(int));
    int allSize = 0;

    for (int i = 0; i < arrSize; i++)
    {
        int nextSize = 0;
        next[nextSize++] = arr[i];
        for (int j = 0; j < curSize; j++)
        {
            int x = cur[j] | arr[i];

            if (x != next[nextSize - 1])
                next[nextSize++] = x;
        }

        curSize = nextSize;

        for (int j = 0; j < curSize; j++)
        {
            cur[j] = next[j];
            all[allSize++] = cur[j];
        }
    }
    qsort(all, allSize, sizeof(int), cmp);
    int answer = 0;

    for (int i = 0; i < allSize; i++)
    {
        if (i == 0 || all[i] != all[i - 1])
            answer++;
    }
    free(all);

    return answer;
}
