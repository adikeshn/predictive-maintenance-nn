#ifndef MY_COST_H
#define MY_COST_H

#include <stdio.h>
#include "structs.h"

double categorical_cross_entropy(layer *pred, layer *exp);
double cost_dev(double pred, double exp);
double binary_cross_entropy(layer *pred, layer *exp, double true_weight, double false_weight);

#endif