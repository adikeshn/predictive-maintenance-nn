#include "headers/structs.h"
#include "headers/matrix_ops.h"
#include "headers/activations.h"
#include "headers/free_structs.h"

#include <stdio.h>
#include <math.h>

layer *evaluate(net net, double *init_data, int init_data_size)
{
    assert(net);
    assert(init_data);

    neuron *neurons = malloc(sizeof(neuron) * init_data_size);
    assert(neurons);

    for (int i = 0; i < init_data_size; i++)
    {
        neurons[i].value = init_data[i];
    }

    layer *inp = malloc(sizeof(layer));
    assert(inp);

    inp->activation = NONE;
    inp->size = init_data_size;
    inp->neurons = neurons;

    layer *prev = inp;
    layer curr;
    for (int i = 0; i < net.num_layers; i++)
    {
        curr = net.layers[i];

        matrix *weights = get_weights_matrix(curr, *prev);
        matrix *features = get_feature_matrix(*prev);

        matrix *updated = matrix_mult(weights, features);

        free_matrix(&weights);
        free_matrix(&features);
        weights = NULL;
        features = NULL;

        for (int j = 0; j < updated->rows; j++)
        {
            updated->arr[j][0] += curr.neurons[i].bias;
        }
        apply_activation(updated, curr.activation);

        free_layer(prev);
        prev = create_layer(updated);
        free_matrix(updated);
        updated = NULL;
    }
    return prev;
}
