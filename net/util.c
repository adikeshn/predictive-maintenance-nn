#include "headers/structs.h"
#include "headers/util.h"
#include "headers/activations.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

layer *get_feature_layer(double *entry, int size)
{
    layer *layer = malloc(sizeof(layer));
    layer->size = size;
    layer->activation = NONE;
    layer->neurons = malloc(sizeof(neuron) * size);
    for (int i = 0; i < size; i++)
        layer->neurons[i].value = entry[i];
    return layer;
}

layer *create_layer(matrix *inp, layer *layer)
{

    for (int i = 0; i < inp->rows; i++)
    {
        layer->neurons[i].value = inp->arr[i][0];
    }

    return layer;
}

matrix *apply_activation(matrix *a, activation activation)
{

    if (activation == RELU || activation == SIGMOID)
    {
        for (int i = 0; i < a->rows; i++)
        {
            a->arr[i][0] = activation == RELU ? ReLU(a->arr[i][0]) : sigmoid(a->arr[i][0]);
        }
    }
    else if (activation == SOFTMAX)
    {
        double sum = 0;
        for (int i = 0; i < a->rows; i++)
        {
            sum += exp(a->arr[i][0]);
        }

        for (int i = 0; i < a->rows; i++)
        {
            a->arr[i][0] = exp(a->arr[i][0]) / sum;
        }
    }
    return a;
}

matrix *get_weights_matrix(layer curr, layer prev)
{

    matrix *weights = malloc(sizeof(matrix));
    assert(weights);

    weights->rows = curr.size;
    weights->cols = prev.size;

    weights->arr = malloc(sizeof(double *) * weights->rows);
    assert(weights->arr);
    for (int i = 0; i < weights->rows; i++)
    {
        weights->arr[i] = malloc(sizeof(double) * weights->cols);
        assert(weights->arr[i]);
        for (int j = 0; j < weights->cols; j++)
        {
            weights->arr[i][j] = curr.neurons[i].weights[j];
        }
    }

    return weights;
}

matrix *get_feature_matrix(layer prev)
{
    matrix *features = malloc(sizeof(matrix));
    assert(features);

    features->rows = prev.size;
    features->cols = 1;

    features->arr = malloc(sizeof(double *) * features->rows);
    assert(features->arr);

    for (int i = 0; i < features->rows; i++)
    {
        features->arr[i] = malloc(sizeof(double) * features->cols);
        assert(features->arr[i]);
        for (int j = 0; j < features->cols; j++)
        {
            features->arr[i][j] = prev.neurons[i].value;
        }
    }
    return features;
}

matrix *matrix_mult(matrix *a, matrix *b)
{
    assert(a->cols == b->rows);

    matrix *out = malloc(sizeof(matrix));
    assert(out);
    out->rows = a->rows;
    out->cols = b->cols;

    out->arr = malloc(sizeof(double *) * out->rows);
    assert(out->arr);
    for (int i = 0; i < out->rows; i++)
    {
        (out->arr)[i] = malloc(sizeof(double) * out->cols);
        assert(out->arr);
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int k = 0; k < b->cols; k++)
        {
            double sum = 0;
            for (int j = 0; j < a->cols; j++)
            {
                sum += a->arr[i][j] * b->arr[j][k];
            }
            out->arr[i][k] = sum;
        }
    }
    return out;
}
