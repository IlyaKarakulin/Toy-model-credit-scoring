
// Логарифмическая функция потерь
double loss(double **X, double *y, double *W, int count_person, int count_features);

// Градиент функции потерь
void gradient(double **X, double *y, double *W, double *grad, int count_person, int count_features);

// Функция для определения весов W методом L-BFGS
void L_BFGS(double **X, double *y, double *W, int count_person, int count_features);