gcc -c ./training.c ./L-BFGS.c ./my_math.c ./main.c
gcc -o training ./training.o ./L-BFGS.o ./my_math.o -lm
./training

gcc -o main ./main.o ./my_math.o -lm
./main

gcc count_mistakes.c -o count_mistakes
./count_mistakes

echo quality_metric.txt

rm *.o