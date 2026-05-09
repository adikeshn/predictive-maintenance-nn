#include "headers/structs.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

double random_double(double min, double max)
{
    double scale = (double)rand() / (double)RAND_MAX;
    return min + scale * (max - min);
}

double he_random_weight(int input_size)
{
    assert(input_size > 0);

    double limit = sqrt(6.0 / input_size);

    return random_double(-limit, limit);
}

net *read_net(char *file_name)
{
    FILE *fp = fopen(file_name, "rb");
    assert(fp);

    net *out = malloc(sizeof(net));
    fread(&out->num_features, sizeof(int), 1, fp);
    fread(&out->num_layers, sizeof(int), 1, fp);

    out->layers = malloc(sizeof(layer) * out->num_layers);
    int prev_size = out->num_features;
    for (int i = 0; i < out->num_layers; i++)
    {
        layer *curr = &out->layers[i];

        fread(&curr->size, sizeof(int), 1, fp);
        fread(&curr->activation, sizeof(int), 1, fp);
        curr->neurons = malloc(sizeof(neuron) * curr->size);

        for (int j = 0; j < curr->size; j++)
        {
            curr->neurons[j].weights = malloc(sizeof(double) * prev_size);
            curr->neurons[j].weight_size = prev_size;
            fread(&curr->neurons[j].bias, sizeof(double), 1, fp);
            for (int z = 0; z < prev_size; z++)
            {
                fread(&curr->neurons[j].weights[z], sizeof(double), 1, fp);
            }
        }
        prev_size = curr->size;
    }
    fclose(fp);
    return out;
}
void write_net(char *file_name, net *net)
{
    FILE *fp = fopen(file_name, "wb");
    assert(fp);

    fwrite(&net->num_features, sizeof(int), 1, fp);
    fwrite(&net->num_layers, sizeof(int), 1, fp);

    for (int i = 0; i < net->num_layers; i++)
    {
        layer *curr = &net->layers[i];

        fwrite(&curr->size, sizeof(int), 1, fp);
        fwrite(&curr->activation, sizeof(int), 1, fp);

        for (int j = 0; j < curr->size; j++)
        {
            fwrite(&curr->neurons[j].bias, sizeof(double), 1, fp);
            for (int z = 0; z < curr->neurons[j].weight_size; z++)
            {
                fwrite(&curr->neurons[j].weights[z], sizeof(double), 1, fp);
            }
        }
    }
}

net *gen_rand(int num_features, int num_hidden, int *hidden_neurons, activation *activations)
{

    net *out = malloc(sizeof(net));
    out->num_features = num_features;
    out->num_layers = num_hidden;
    out->layers = malloc(sizeof(layer) * out->num_layers);

    int prev_size = out->num_features;
    for (int i = 0; i < out->num_layers; i++)
    {
        layer *curr = &out->layers[i];
        curr->size = hidden_neurons[i];
        curr->activation = activations[i];
        curr->neurons = malloc(sizeof(neuron) * curr->size);

        for (int j = 0; j < curr->size; j++)
        {
            curr->neurons[j].weights = malloc(sizeof(double) * prev_size);
            curr->neurons[j].weight_size = prev_size;
            curr->neurons[j].bias = 0.0;
            for (int z = 0; z < prev_size; z++)
            {
                curr->neurons[j].weights[z] = he_random_weight(prev_size);
            }
        }
        prev_size = curr->size;
    }
    return out;
}
