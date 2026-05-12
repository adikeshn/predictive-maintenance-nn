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

int main()
{
    srandom(0);
    int num_features = 5;
    int num_layers = 3;
    int neurons_each_layer[3] = {16, 16, 1};
    int epochs = 50;
    int batch_size = 32;
    double learning_rate = 0.01;
    activation actives[3] = {RELU, RELU, SIGMOID};
    net *init = gen_rand(num_features, num_layers, neurons_each_layer, actives, BINARY_CROSS_ENTROPY);

    int num_entries = 10000;
    double **X = NULL;
    double **y = NULL;
    load_data(&X, &y, num_entries, num_features, neurons_each_layer[num_layers - 1]);
    double *means = malloc(sizeof(double) * num_features);
    double *stds = malloc(sizeof(double) * num_features);
    normalize(X, num_entries, num_features, means, stds);
    net *model = train_model(init, epochs, batch_size, num_entries, X, num_features, y, neurons_each_layer[num_layers - 1], learning_rate);
    write_net("model.bin", model);
    net *read = read_net("model.bin");

    free_net(init);
    free_net(read);
    free_2D(&X, num_entries);
    free_2D(&y, num_entries);
    free(means);
    free(stds);
}