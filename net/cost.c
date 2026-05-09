#include "headers/cost.h"
#include "headers/structs.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

double categorical_cross_entropy(layer *pred, layer *exp)
{
    assert(pred);
    assert(exp);

    double cost = 0.0;

    for (int i = 0; i < pred->size; i++)
    {
        cost += log(pred->neurons[i].value) * exp->neurons[i].value;
    }
    return cost;
}
