#include <stdio.h>

int main()
{
    freopen("quality_metric.txt", "w", stdout);

    FILE *targets = fopen("targets_for_test_data.txt", "r");
    FILE *pred_f = fopen("prediction.txt", "r");

    int count_true_positiv = 0;
    int count_true_negativ = 0;
    int count_false_positiv = 0;
    int count_false_negativ = 0;

    int count_targets = 0;

    int pred = 0, target = 0;

    fscanf(targets, "%d", &count_targets);

    for (int i = 0; i < count_targets; ++i)
    {
        fscanf(pred_f, "%d", &pred);
        fscanf(targets, "%d", &target);

        if (pred && target)
            ++count_true_positiv;
        if (pred && !target)
            ++count_false_positiv;
        if (!pred && !target)
            ++count_true_negativ;
        if (!pred && target)
            ++count_false_negativ;
    }

    double TP = (double)count_true_positiv / count_targets;
    double FP = (double)count_false_positiv / count_targets;
    double TN = (double)count_true_negativ / count_targets;
    double FN = (double)count_false_negativ / count_targets;

    printf("TP - %lf\nFP - %lf\nTN - %lf\nFN - %lf\n", TP, FP, TN, FN);
    return 0;
}