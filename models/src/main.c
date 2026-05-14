#include "headers/init.h"
#include "headers/evaluate.h"
#include "headers/free_structs.h"
#include "headers/structs.h"
#include "headers/train.h"
#include "headers/util.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

void train_models();
void test_models();

int main()
{
    test_models();
}
void test_models()
{
    net *model = read_net("failure_percent.bin");
    // cases
    double borderline_1[] = {301.5, 311.2, 1420, 58.0, 120};
    double borderline_2[] = {299.0, 309.3, 1480, 44.0, 160};
    double borderline_3[] = {300.2, 310.0, 1350, 62.0, 90};

    // normal
    double safe_1[] = {298.5, 308.8, 1600, 35.0, 10};
    double safe_2[] = {299.1, 309.2, 1720, 30.0, 25};
    double safe_3[] = {298.3, 308.5, 1580, 38.0, 5};

    // failure
    double critical_1[] = {306.0, 315.0, 1100, 85.0, 250};
    double critical_2[] = {300.5, 310.8, 1050, 90.0, 200};
    double critical_3[] = {307.2, 316.1, 1300, 70.0, 245};

    double *test_inputs[] = {
        borderline_1, borderline_2, borderline_3,
        safe_1, safe_2, safe_3,
        critical_1, critical_2, critical_3};

    char *labels[] = {
        "Borderline", "Borderline", "Borderline",
        "Safe", "Safe", "Safe",
        "Critical", "Critical", "Critical"};

    int n = 9;

    normalize_input("normalize.bin", test_inputs, n, 5);

    double **preds = predict(model, test_inputs, n);

    for (int i = 0; i < n; i++)
        printf("%-12s → risk: %.4f\n", labels[i], preds[i][0]);
}

void train_models()
{
    srandom(2);
    int num_features = 5;
    int num_layers = 3;
    int neurons_each_layer[3] = {32, 16, 5};
    int epochs = 150;
    int batch_size = 16;
    double learning_rate = 0.008;
    double train_percent = 0.8;
    activation actives[3] = {RELU, RELU, SOFTMAX};
    net *init = gen_rand(num_features, num_layers, neurons_each_layer, actives, CATEGORICAL_CROSS_ENTROPY);

    int num_entries = 10000;
    double **X = NULL;
    double **y = NULL;
    load_data(&X, &y, num_entries, num_features, neurons_each_layer[num_layers - 1]);
    double *means = malloc(sizeof(double) * num_features);
    double *stds = malloc(sizeof(double) * num_features);
    normalize(X, num_entries, num_features, means, stds);
    fisher_shuffle(X, y, num_entries);

    int fail_count = 0;
    for (int i = 0; i < num_entries; i++)
    {
        int flags = 0;
        for (int j = 0; j < 5; j++)
            flags += (int)y[i][j];
        if (flags == 1)
            fail_count++;
    }

    double **X_fail = malloc(sizeof(double *) * fail_count);
    double **y_fail = malloc(sizeof(double *) * fail_count);
    int idx = 0;
    for (int i = 0; i < num_entries; i++)
    {
        int flags = 0;
        for (int j = 0; j < 5; j++)
            flags += (int)y[i][j];
        if (flags == 1)
        {
            X_fail[idx] = X[i];
            y_fail[idx] = y[i];
            idx++;
        }
    }
    printf("%d\n", fail_count);
    net *model = train_model(init, epochs, batch_size, fail_count, X_fail,
                             num_features, y_fail, neurons_each_layer[num_layers - 1], learning_rate, train_percent);

    write_net("category_model.bin", model);

    free_net(init);
    free_2D(&X, num_entries);
    free_2D(&y, num_entries);
    free(means);
    free(stds);
}
