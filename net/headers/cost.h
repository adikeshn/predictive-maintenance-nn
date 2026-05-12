#ifndef MY_COST_H
#define MY_COST_H

#include <stdio.h>
#include "structs.h"

double categorical_cross_entropy(layer *pred, layer *exp);
double cost_dev(double pred, double exp);
double binary_cross_entropy(layer *pred, layer *exp, double true_weight, double false_weight);
double weighted_cost_dev(double p, double y, double w_pos, double w_neg);

#endif