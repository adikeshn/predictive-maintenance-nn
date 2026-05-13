#include "headers/cost.h"
#include "headers/structs.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

double categorical_cross_entropy(layer *pred, layer *exp)
{
    double c = 0;
    double eps = 1e-7;
    for (int i = 0; i < pred->size; i++)
    {
        double p = fmax(eps, fmin(1.0 - eps, pred->neurons[i].value));
        c += exp->neurons[i].value * log(p);
    }
    return -c;
}

double binary_cross_entropy(layer *pred, layer *exp, double true_weight, double false_weight)
{
    double prediction = pred->neurons[0].value;
    double expected = exp->neurons[0].value;
    double eps = 1e-7;
    prediction = fmax(eps, fmin(1.0 - eps, prediction));
    return -(true_weight * expected * log(prediction) + false_weight * (1 - expected) * log(1 - prediction));
}

double cost_dev(double pred, double exp)
{
    return pred - exp;
}

double weighted_cost_dev(double p, double y, double w_pos, double w_neg)
{
    double eps = 1e-7;
    p = fmax(eps, fmin(1.0 - eps, p));
    return w_pos * y * (p - 1.0) + w_neg * (1.0 - y) * p;
}