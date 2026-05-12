#include "headers/init.h"
#include "headers/evaluate.h"
#include "headers/free_structs.h"
#include "headers/structs.h"
#include "headers/cost.h"
#include "headers/util.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void fisher_shuffle(double **inp, double **out, int num_entries)
{
    for (int i = num_entries - 1; i > 0; i--)
    {
        int swap_index = rand() % (i + 1);

        double *temp = inp[i];
        inp[i] = inp[swap_index];
        inp[swap_index] = temp;

        temp = out[i];
        out[i] = out[swap_index];
        out[swap_index] = temp;
    }
}

net *train_model(net *model, int epochs, int batch_size, int num_entries, double **training_features,
                 int num_features, double **training_output, int output_size, double rate)
{
    assert(model);

    net *sums_net = malloc(sizeof(net));
    sums_net->num_features = model->num_features;
    sums_net->num_layers = model->num_layers;
    sums_net->layers = malloc(sizeof(layer) * sums_net->num_layers);
    for (int i = 0; i < model->num_layers; i++)
    {
        sums_net->layers[i].size = model->layers[i].size;
        sums_net->layers[i].neurons = calloc(model->layers[i].size, sizeof(neuron));

        for (int j = 0; j < sums_net->layers[i].size; j++)
        {
            sums_net->layers[i].neurons[j].weight_size = i == 0 ? model->num_features : model->layers[i - 1].size;
            sums_net->layers[i].neurons[j].weights = calloc(sums_net->layers[i].neurons[j].weight_size, sizeof(double));
        }
    }
    for (int i = 0; i < epochs; i++)
    {
        fisher_shuffle(training_features, training_output, num_entries);
        int batches = 0;
        for (int j = 0; j < num_entries; j += batch_size)
        {
            int batch = j + batch_size >= num_entries ? num_entries - j : batch_size;
            double cost = train_batch((training_features + j), num_features, (training_output + j), output_size, batch, model, sums_net, rate);
            printf("\rEpoch %d/%d, Batch %d, Loss %.6f", i + 1, epochs, batches, cost);
            fflush(stdout);
            batches++;
        }
    }

    free_net(sums_net);
    return model;
}

double train_batch(double **training_data, int features, double **training_output, int output_size,
                   int batch_size, net *model, net *sums_net, double rate)
{
    assert(model);
    assert(training_data);

    for (int i = 0; i < sums_net->num_layers; i++)
    {
        for (int j = 0; j < sums_net->layers[i].size; j++)
        {
            memset(sums_net->layers[i].neurons[j].weights, 0.0, sums_net->layers[i].neurons[j].weight_size * sizeof(double));
            sums_net->layers[i].neurons[j].bias = 0.0;
        }
    }
    double cost = 0.0;
    for (int i = 0; i < batch_size; i++)
    {
        double *entry = training_data[i];
        layer *features_layer = get_feature_layer(entry, features);
        layer *pred = forward_pass(model, features_layer);
        layer *exp_layer = get_feature_layer(training_output[i], output_size);
        if (model->cost == BINARY_CROSS_ENTROPY)
        {
            cost += binary_cross_entropy(pred, exp_layer);
        }
        else if (model->cost == CATEGORICAL_CROSS_ENTROPY)
        {
            cost += categorical_cross_entropy(pred, exp_layer);
        }
        back_prop(sums_net, model, features_layer, exp_layer, rate);
        free_layer(features_layer);
        free(features_layer);
        features_layer = NULL;
        free_layer(exp_layer);
        free(exp_layer);
        exp_layer = NULL;
        free_layer(pred);
        free(pred);
        pred = NULL;
    }

    for (int i = 0; i < model->num_layers; i++)
    {
        for (int j = 0; j < model->layers[i].size; j++)
        {
            model->layers[i].neurons[j].bias -= sums_net->layers[i].neurons[j].bias / batch_size;
            for (int z = 0; z < model->layers[i].neurons->weight_size; z++)
            {
                model->layers[i].neurons[j].weights[z] -= sums_net->layers[i].neurons[j].weights[z] / batch_size;
            }
        }
    }

    return cost / batch_size;
}