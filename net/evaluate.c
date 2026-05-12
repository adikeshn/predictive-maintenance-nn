#include "headers/structs.h"
#include "headers/util.h"
#include "headers/activations.h"
#include "headers/free_structs.h"
#include "headers/evaluate.h"
#include "headers/cost.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

net *forward_pass(net *net, layer *features)
{
    assert(net);

    layer *prev = features;
    layer *curr;
    for (int i = 0; i < net->num_layers; i++)
    {
        curr = &net->layers[i];

        matrix *weights = get_weights_matrix(*curr, *prev);
        matrix *features_matrix = get_feature_matrix(*prev);

        matrix *updated = matrix_mult(weights, features_matrix);

        free_matrix(weights);
        free_matrix(features_matrix);
        weights = NULL;
        features_matrix = NULL;

        for (int j = 0; j < updated->rows; j++)
        {
            updated->arr[j][0] += curr->neurons[j].bias;
        }
        apply_activation(updated, curr->activation);

        prev = create_layer(updated, curr);
        free_matrix(updated);
        updated = NULL;
    }

    return prev;
}

net *back_prop(net *sums, net *net, layer *features, layer *exp, double learning_rate)
{
    assert(net);
    int layer_index = net->num_layers - 1;
    layer *curr;
    for (int i = 0; i < net->num_layers; i++)
    {
        curr = &net->layers[layer_index - i];
        layer *sums_layer = &sums->layers[layer_index - i];
        int weight_size = curr->neurons[0].weight_size;
        for (int j = 0; j < curr->size; j++)
        {
            if (i == 0)
            {
                curr->neurons[j].value = cost_dev(curr->neurons[j].value, exp->neurons[j].value);
            }
            else
            {
                double partial = 0.0;
                for (int z = 0; z < (curr + 1)->size; z++)
                {
                    partial += (curr + 1)->neurons[z].weights[j] * (curr + 1)->neurons[z].value;
                }
                if (curr->activation == SIGMOID)
                {
                    partial *= deriv_sigmoid(curr->neurons[j].value);
                }
                else if (curr->activation == RELU)
                {
                    partial *= deriv_ReLU(curr->neurons[j].value);
                }
                curr->neurons[j].value = partial;
            }
            for (int z = 0; z < weight_size; z++)
            {
                double partial_weight = (i == net->num_layers - 1) ? features->neurons[z].value : (curr - 1)->neurons[z].value;
                sums_layer->neurons[j].weights[z] += learning_rate * partial_weight * curr->neurons[j].value;
            }
            sums_layer->neurons[j].bias += learning_rate * curr->neurons[j].value;
        }
    }

    return sums;
}