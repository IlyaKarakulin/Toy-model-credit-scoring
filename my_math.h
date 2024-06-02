
// скалярное произведение векторов
double scalar_pr(double *v1, double *v2, int count_features);

// норма вектора
double norm(double *v, int count_features);

// сигмоида
double sigmoid(double x);

// Вероятность того, что пользователь объявит дефолт
double predict(double *x, double *W, int count_features);

// Длинна строки
int strLen(char *str);

// Перевод строки в int
int toInt(char *str);

// Разложение експоненты в ряд тейлора
double taylor_exp(double x);
