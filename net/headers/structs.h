#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>

typedef enum activation
{
    RELU,
    SOFTMAX,
    SIGMOID,
    NONE
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
} net;

#endif