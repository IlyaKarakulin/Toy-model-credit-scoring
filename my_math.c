#include <math.h>

double scalar_pr(double *v1, double *v2, int count_features)
{
    double sum = 0;
    for (int i = 0; i < count_features; ++i)
    {
        sum += v1[i] * v2[i];
    }
    return sum;
}

double norm(double *v, int count_features)
{
    double sum = 0;
    for (int i = 0; i < count_features; ++i)
    {
        sum += v[i] * v[i];
    }
    return sqrt(sum);
}

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

int strLen(char *str)
{
    int len = 0;
    while (*str++ != 0)
    {
        ++len;
    }
    return len - 1;
}

int toInt(char *str)
{
    int res = 0, base = 1, len = 0, flag = 0;
    len = strLen(str);

    if (*str == '-')
    {
        flag = 1;
    }

    while (len >= flag)
    {
        res += (str[len--] - 48) * base;
        base *= 10;
    }

    return flag == 1 ? -1 * res : res;
}
