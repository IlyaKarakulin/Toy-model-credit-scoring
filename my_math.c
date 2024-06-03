#include <math.h>

// функция нахождения скалярного произведения двух векторов
double scalar_pr(double *v1, double *v2, int count_features)
{
    double sum = 0;
    for (int i = 0; i < count_features; ++i)
    {
        sum += v1[i] * v2[i];
    }
    return sum;
}

// вычисление нормы вектора
double norm(double *v, int count_features)
{
    double sum = 0;
    for (int i = 0; i < count_features; ++i)
    {
        sum += v[i] * v[i];
    }
    return sqrt(sum);
}

// разложение экспоненты в ряд Тейлора
double taylor_exp(double x)
{
    double sum = 1.0;
    double term = 1.0;

    for (int i = 1; i < 200; i++)
    {
        term *= x / i;
        sum += term;
    }

    return sum;
}

// Функция сигмоиды. По ней определяется вероятность дефолта
double sigmoid(double x)
{
    return 1.0 / (1.0 + taylor_exp(-x));
}

// Вероятность того, что пользователь объявит дефолт
double predict(double *x, double *W, int count_features)
{
    double res = scalar_pr(W, x, count_features);
    return sigmoid(res);
}
