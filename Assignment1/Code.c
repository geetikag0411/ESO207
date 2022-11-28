#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int Rfib(long long int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return (Rfib(n - 1) + Rfib(n - 2)) % 2022;
}
int Ifib(long long int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
    {
        int a = 0;
        int b = 1;
        for (int i = 2; i <= n; i++)
        {
            int temp = b;
            b = (a + b) % 2022;
            a = temp;
        }
        return b;
    }
}
int **power(int t)
{
    if (t == 1)
    {
        int **arr = (int **)malloc(2 * sizeof(int *));
        for (int i = 0; i < 2; i++)
        {
            arr[i] = (int *)malloc(2 * sizeof(int));
        }
        arr[0][0] = 1;
        arr[0][1] = 1;
        arr[1][0] = 1;
        arr[1][1] = 0;
        return arr;
    }
    int **new = power(t / 2);
    int a = new[0][0];
    int b = new[0][1];
    int c = new[1][0];
    int d = new[1][1];
    new[0][0] = ((a * a) % 2022 + (b * c) % 2022) % 2022;
    new[0][1] = ((a * b) % 2022 + (b * d) % 2022) % 2022;
    new[1][0] = ((a * c) % 2022 + (d * c) % 2022) % 2022;
    new[1][1] = ((c * b) % 2022 + (d * d) % 2022) % 2022;
    if (t % 2 == 0)
    {
        return new;
    }
    else if (t % 2 == 1)
    {
        a = new[0][0];
        b = new[0][1];
        c = new[1][0];
        d = new[1][1];
        new[0][0] = (a + b) % 2022;
        new[0][1] = a % 2022;
        new[1][0] = (c + d) % 2022;
        new[1][1] = c % 2022;
        return new;
    }
}
int cleverfib(long long int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
    {
        int **arr = power(n - 1);
        return arr[0][0];
    }
}
int main()
{
    long long int n;
    scanf("%lld", &n);
    clock_t start, end;
    double total;

    start = clock();

    Rfib(n);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total time taken in Rfib is %f\n", total);

    start = clock();
    Ifib(n);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total time taken in Ifib is %f\n", total);

    start = clock();
    cleverfib(n);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total time taken in cleverfib is %f\n", total);
}
