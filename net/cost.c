#include "headers/cost.h"
#include "headers/structs.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

double categorical_cross_entropy(layer *pred, layer *exp)
{
    assert(pred);
    assert(exp);

    double c = 0.0;

    for (int i = 0; i < pred->size; i++)
    {
        c += log(pred->neurons[i].value) * exp->neurons[i].value;
    }
    return -c;
}

double binary_cross_entropy(layer *pred, layer *exp)
{
    double prediction = pred->neurons[0].value;
    double expected = exp->neurons[0].value;

    return -(expected * log(prediction) + (1 - expected) * log(1 - prediction));
}

double cost_dev(double pred, double exp)
{
    return pred - exp;
}
