#include <stdio.h>
#include <malloc.h>
#include "my_math.h"

void normalization(int count_features, double *person, double *arr_min, double *arr_max)
{
    for (int j = 0; j < count_features; ++j)
    {
        person[j] = (person[j] - arr_min[j]) / (arr_max[j] - arr_min[j]);
    }
}

int main()
{
    FILE *in = fopen("parameters.txt", "r");
    FILE *test_data = fopen("data_test.txt", "r");

    int count_features = 0;
    int count_test_person = 0;

    fscanf(test_data, "%d", &count_test_person);
    fscanf(test_data, "%d", &count_features);

    double *arr_min = (double *)malloc(count_features * 8);
    double *arr_max = (double *)malloc(count_features * 8);

    double *person = (double *)malloc(count_features * 8);
    double *W = (double *)malloc(count_features * 8);
    double pred = 0.0;

    for (int i = 0; i < count_features; ++i)
    {
        fscanf(in, "%lf\n", &W[i]);
    }

    // for (int i = 0; i < count_features; ++i)
    // {
    //     printf("%lf ", W[i]);
    // }
    // printf("\n");

    for (int i = 0; i < count_features; ++i)
    {
        fscanf(in, "%lf %lf\n", &arr_min[i], &arr_max[i]);
    }

    fclose(in);

    int answer = 0;

    FILE *prediction = fopen("prediction.txt", "w");

    for (int i = 0; i < count_test_person; ++i)
    {
        // printf("%d | ", i);
        for (int j = 0; j < count_features; ++j)
        {
            fscanf(test_data, "%lf", &person[j]);
            // printf("%.0lf ", person[j]);
        }

        normalization(count_features, person, arr_min, arr_max);

        pred = predict(person, W, count_features);
        answer = (pred > 0.50 ? 1 : 0);

        // printf("PD = %lf (%d)\n", pred, answer);
        fprintf(prediction, "%d\n", answer);
    }

    return 0;
}
