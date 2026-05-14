#include "headers/init.h"
#include "headers/evaluate.h"
#include "headers/free_structs.h"
#include "headers/structs.h"
#include "headers/train.h"
#include "headers/util.h"
#include "headers/python_facing.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

double tr_weight = 14.7; // 14.7
double fl_weight = 0.52; // 0.52

double predict_percent(double *inp)
{
    const char *model_dir = getenv("MODEL_DIR");
    char path_model[512];
    char path_normalize[512];
    snprintf(path_model, sizeof(path_model), "%s/failure_percent_model.bin", model_dir);
    snprintf(path_normalize, sizeof(path_normalize), "%s/normalize.bin", model_dir);

    net *model = read_net(path_model);

    double *i[] = {inp};
    normalize_input(path_normalize, i, 1, 5);

    double **pred = predict(model, i, 1);
    double p = pred[0][0];
    free_2D(&pred, 1);
    free_net(model);

    return p;
}

int predict_category(double *inp)
{
    const char *model_dir = getenv("MODEL_DIR");
    char path_model[512];
    char path_normalize[512];
    snprintf(path_model, sizeof(path_model), "%s/failure_percent_model.bin", model_dir);
    snprintf(path_normalize, sizeof(path_normalize), "%s/normalize.bin", model_dir);

    net *model = read_net(path_model);

    double *i[] = {inp};
    normalize_input(path_normalize, i, 1, 5);

    double **pred = predict(model, i, 1);
    double max = 0.0;
    int index = 0;
    for (int j = 0; j < 5; j++)
    {
        if (pred[0][j] > max)
        {
            max = pred[0][j];
            index = j;
        }
    }
    free_2D(&pred, 1);
    free_net(model);
    return index;
}