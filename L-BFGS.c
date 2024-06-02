#include <malloc.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "my_math.h"

#define MAX_ITER 100
#define STOPPER 1e-5
#define HISTORY_SIZE 10

// Структура для хранения истории шагов и градиентов
typedef struct
{
    double *d_W;
    double *d_grad;
    double rho;
} LbfgsHistory;

// Логарифмическая функция потерь
double loss(double **X, double *y, double *W, int count_person, int count_features)
{
    double total_loss = 0;
    for (int i = 0; i < count_person; ++i)
    {
        double pred = predict(X[i], W, count_features);
        if (pred == 0 || pred == 1)
        {
            return INFINITY; // Предотвращение log(0)
        }
        total_loss -= y[i] * log(pred) + (1 - y[i]) * log(1 - pred);
    }
    return total_loss / count_person;
}

// Градиент функции потерь
void gradient(double **X, double *y, double *W, double *grad, int count_person, int count_features)
{
    for (int i = 0; i < count_features; ++i)
    {
        grad[i] = 0;
    }

    for (int i = 0; i < count_person; ++i)
    {
        double pred = predict(X[i], W, count_features);
        for (int j = 0; j < count_features; ++j)
        {
            grad[j] += (pred - y[i]) * X[i][j];
        }
    }

    for (int j = 0; j < count_features; ++j)
    {
        grad[j] /= count_person;
    }
}

// Функция для определения весов W методом L-BFGS
void L_BFGS(double **X, double *y, double *W, int count_person, int count_features)
{
    double *grad = (double *)malloc(count_features * sizeof(double));
    double *g_old = (double *)malloc(count_features * sizeof(double));
    double *direction = (double *)malloc(count_features * sizeof(double));
    double *W_prev = (double *)malloc(count_features * sizeof(double));

    LbfgsHistory history[HISTORY_SIZE];
    int history_size = 0;

    // Инициализация градиента и направления
    gradient(X, y, W, grad, count_person, count_features);
    for (int i = 0; i < count_features; ++i)
    {
        direction[i] = -grad[i];
    }

    for (int iter = 0; iter < MAX_ITER; ++iter)
    {
        // Линейный поиск для определения оптимального шага
        double alpha = 1e-3; // Можно настроить линейный поиск для более устойчивого шага

        for (int i = 0; i < count_features; ++i)
        {
            W_prev[i] = W[i];
            W[i] += 12 * alpha * direction[i];
        }

        // Обновление градиента
        for (int i = 0; i < count_features; ++i)
        {
            g_old[i] = grad[i];
        }
        gradient(X, y, W, grad, count_person, count_features);

        // Проверка условия остановки
        if (norm(grad, count_features) < STOPPER)
        {
            break;
        }

        // Обновление истории
        if (history_size == HISTORY_SIZE)
        {
            free(history[0].d_W);
            free(history[0].d_grad);

            for (int i = 1; i < HISTORY_SIZE; ++i)
            {
                history[i - 1] = history[i];
            }

            history_size--;
        }

        history[history_size].d_W = (double *)malloc(count_features * sizeof(double));
        history[history_size].d_grad = (double *)malloc(count_features * sizeof(double));

        for (int i = 0; i < count_features; ++i)
        {
            history[history_size].d_W[i] = W[i] - W_prev[i];
            history[history_size].d_grad[i] = grad[i] - g_old[i];
        }

        history[history_size].rho = 1.0 / scalar_pr(history[history_size].d_grad, history[history_size].d_W, count_features);
        history_size++;

        // Двухцикловая рекурсия для вычисления нового направления
        double q[count_features], alpha_hist[HISTORY_SIZE];

        for (int i = 0; i < count_features; ++i)
        {
            q[i] = grad[i];
        }

        for (int i = history_size - 1; i >= 0; --i)
        {
            alpha_hist[i] = history[i].rho * scalar_pr(history[i].d_W, q, count_features);

            for (int j = 0; j < count_features; ++j)
            {
                q[j] -= alpha_hist[i] * history[i].d_grad[j];
            }
        }

        double gamma = scalar_pr(history[history_size - 1].d_W, history[history_size - 1].d_grad, count_features) /
                       scalar_pr(history[history_size - 1].d_grad, history[history_size - 1].d_grad, count_features);

        for (int i = 0; i < count_features; ++i)
        {
            direction[i] = gamma * q[i];
        }

        for (int i = 0; i < history_size; ++i)
        {
            double beta = history[i].rho * scalar_pr(history[i].d_grad, direction, count_features);

            for (int j = 0; j < count_features; ++j)
            {
                direction[j] += (alpha_hist[i] - beta) * history[i].d_W[j];
            }
        }

        for (int i = 0; i < count_features; ++i)
        {
            direction[i] = -direction[i];
        }
    }

    // Освобождение памяти
    for (int i = 0; i < history_size; ++i)
    {
        free(history[i].d_W);
        free(history[i].d_grad);
    }

    free(grad);
    free(g_old);
    free(direction);
    free(W_prev);
}