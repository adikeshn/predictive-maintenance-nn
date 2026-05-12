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

double tr_weight = 14.7;
double fl_weight = 0.52;
void train_models();
void test_models();

int main()
{
    train_models();
}
void test_models()
{
    net *model = read_net("model.bin");

    /**/

    free_net(model);
    model = NULL;
}
void train_models()
{
    srandom(2);
    int num_features = 5;
    int num_layers = 3;
    int neurons_each_layer[3] = {64, 32, 1};
    int epochs = 70;
    int batch_size = 64;
    double learning_rate = 0.01;
    double train_percent = 0.8;
    activation actives[3] = {RELU, RELU, SIGMOID};
    net *init = gen_rand(num_features, num_layers, neurons_each_layer, actives, BINARY_CROSS_ENTROPY);

    int num_entries = 10000;
    double **X = NULL;
    double **y = NULL;
    load_data(&X, &y, num_entries, num_features, neurons_each_layer[num_layers - 1]);
    double *means = malloc(sizeof(double) * num_features);
    double *stds = malloc(sizeof(double) * num_features);
    normalize(X, num_entries, num_features, means, stds);
    fisher_shuffle(X, y, num_entries);
    net *model = train_model(init, epochs, batch_size, num_entries, X,
                             num_features, y, neurons_each_layer[num_layers - 1], learning_rate, train_percent);

    write_net("model.bin", model);

    free_net(init);
    free_2D(&X, num_entries);
    free_2D(&y, num_entries);
    free(means);
    free(stds);
}
