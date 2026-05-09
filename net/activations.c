#include "headers/structs.h"
#include "headers/activations.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

double sigmoid(double inp)
{
    return 1 / (1 + exp(-inp));
}

double ReLU(double inp)
{
    return inp > 0.0 ? inp : 0.0;
}

double *softmax(double *vals, int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += exp(vals[i]);
    }

    double *ret = malloc(sizeof(double) * size);
    assert(ret);
    for (int i = 0; i < size; i++)
    {
        ret[i] = exp(vals[i]) / sum;
    }
    return ret;
}
