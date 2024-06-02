gcc -c training.c L-BFGS.c my_math.c main.c
gcc -o training.exe training.o L-BFGS.o my_math.o
training

gcc -o main.exe main.o my_math.o
main.exe
del *.o

gcc count_mistakes.c -o count_mistakes.exe
count_mistakes.exe
more quality_metric.txt