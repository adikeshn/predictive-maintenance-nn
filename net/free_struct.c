#include "headers/structs.h"
#include "headers/free_structs.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

void free_matrix(matrix **a)
{
    matrix *b = *a;
    for (int i = 0; i < b->rows; i++)
    {
        free(b->arr[i]);
    }
    free(b->arr);

    b->arr = NULL;
    free(b);
}

void free_layer(layer **a)
{
    layer *b = *a;

    for (int i = 0; i < b->size; i++)
    {
        free(b->neurons[i]);
    }
    free(b->neurons);
    b->neurons = NULL;
    free(b);
}

void free_neuron(neuron **a)
{
    neuron *b = *a;
    free(b->weights);
    b->weights = NULL;
    free(b);
}