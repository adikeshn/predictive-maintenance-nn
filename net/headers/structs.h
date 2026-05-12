#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>

typedef enum activation
{
    RELU = 0,
    SOFTMAX = 1,
    SIGMOID = 2,
    NONE = 3
} activation;

typedef enum cost_funcs
{
    CATEGORICAL_CROSS_ENTROPY = 0,
    BINARY_CROSS_ENTROPY = 1,
    NONE = 2,
} cost_funcs;

typedef struct matrix
{
    double **arr;
    int rows;
    int cols;
} matrix;

typedef struct neuron
{
    double bias;
    double *weights;
    double value;
    int weight_size;
} neuron;

typedef struct layer
{
    neuron *neurons;
    int size;
    activation activation;
} layer;

typedef struct net
{
    layer *layers;
    int num_layers;
    int num_features;
    cost_funcs cost;

} net;

#endif