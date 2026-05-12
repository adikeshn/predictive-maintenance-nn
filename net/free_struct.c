#include "headers/structs.h"
#include "headers/free_structs.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

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
}

void free_neuron(neuron *a)
{
    free(a->weights);
    a->weights = NULL;
    a->weight_size = 0;
}

void free_net(net *a)
{
    for (int i = 0; i < a->num_layers; i++)
    {
        free_layer(&a->layers[i]);
    }
    free(a->layers);
    a->layers = NULL;
    free(a);
}

void free_2D(double ***arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}