#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "L-BFGS.h"
#include "my_math.h"

void search_min_max(int count_person, int count_features, double **X_data, double *arr_min, double *arr_max)
{
    for (int i = 0; i < count_person; ++i)
    {
        for (int j = 0; j < count_features; ++j)
        {
            if (X_data[i][j] < arr_min[j])
            {
                arr_min[j] = X_data[i][j];
            }
            if (X_data[i][j] > arr_max[j])
            {
                arr_max[j] = X_data[i][j];
            }
        }
    }
}

void normalization(int count_person, int count_features, double **X_data, double *arr_min, double *arr_max)
{
    for (int i = 0; i < count_person; ++i)
    {
        for (int j = 0; j < count_features; ++j)
        {
            X_data[i][j] = (X_data[i][j] - arr_min[j]) / (arr_max[j] - arr_min[j]);
        }
    }
}

void init(int count_person, int count_features, double *targets, double **X_data, double **W)
{
    for (int i = 0; i < count_person; ++i)
    {
        X_data[i] = (double *)malloc((count_features) * 8);

        for (int j = 0; j < count_features; ++j)
        {
            scanf("%lf", &X_data[i][j]);
        }

        scanf("%lf\n", &targets[i]);
    }

    *W = (double *)malloc(count_features * sizeof(double));

    for (int i = 0; i < count_features; ++i)
    {
        (*W)[i] = 0.0;
    }
}

int main()
{
    freopen("data.txt", "r", stdin);

    int count_person = 0;
    int count_features = 0;

    scanf("%d %d\n", &count_person, &count_features);

    double *targets = (double *)malloc(count_person * 8);
    double **X_data = (double **)malloc(count_person * 8);
    double *W = NULL;

    init(count_person, count_features, targets, X_data, &W);

    double *arr_min = (double *)malloc(count_features * 8);
    double *arr_max = (double *)malloc(count_features * 8);

    for (int i = 0; i < count_features; ++i)
    {
        arr_min[i] = X_data[0][i];
    }

    search_min_max(count_person, count_features, X_data, arr_min, arr_max);

    // for (int i = 0; i < count_features; ++i)
    // {
    //     printf("%lf %lf\n", arr_min[i], arr_max[i]);
    // }

    normalization(count_person, count_features, X_data, arr_min, arr_max);

    L_BFGS(X_data, targets, W, count_person, count_features);

    // printf("%d\n", count_features);

    // for (int i = 0; i < count_features; ++i)
    // {
    //     printf("%lf ", W[i]);
    // }
    // printf("\n");

    freopen("parameters.txt", "w", stdout);

    for (int i = 0; i < count_features; ++i)
    {
        printf("%lf ", W[i]);
    }
    printf("\n");

    for (int i = 0; i < count_features; ++i)
    {
        printf("%lf %lf\n", arr_min[i], arr_max[i]);
    }

    free(W);

    return 0;
}
