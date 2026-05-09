#include "headers/structs.h"
#include "headers/matrix_ops.h"
#include "headers/activations.h"
#include "headers/free_structs.h"
#include "headers/evaluate.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

layer *evaluate(net *net, layer *features)
{
    assert(net);

    layer *prev = features;
    layer curr;
    for (int i = 0; i < net->num_layers; i++)
    {
        curr = net->layers[i];

        matrix *weights = get_weights_matrix(curr, *prev);
        matrix *features = get_feature_matrix(*prev);

        matrix *updated = matrix_mult(weights, features);

        free_matrix(weights);
        free_matrix(features);
        weights = NULL;
        features = NULL;

        for (int j = 0; j < updated->rows; j++)
        {
            updated->arr[j][0] += curr.neurons[j].bias;
        }
        apply_activation(updated, curr.activation);

        free_layer(prev);
        free(prev);
        prev = create_layer(updated);
        free_matrix(updated);
        updated = NULL;
    }
    return prev;
}
