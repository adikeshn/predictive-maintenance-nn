#include "headers/structs.h"
#include "headers/free_structs.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

void free_matrix(matrix *a)
{
    for (int i = 0; i < a->rows; i++)
    {
        free(a->arr[i]);
    }
    free(a->arr);

    a->arr = NULL;
    free(a);
}

void free_layer(layer *a)
{

    for (int i = 0; i < a->size; i++)
    {
        free_neuron(&a->neurons[i]);
    }
    free(a->neurons);
    a->neurons = NULL;
    free(a);
}

void free_neuron(neuron *a)
{
    assert(a);
    free(a->weights);
    a->weights = NULL;
    a->weight_size = 0;
}