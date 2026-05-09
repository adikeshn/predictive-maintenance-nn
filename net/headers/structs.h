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
} net;

#endif