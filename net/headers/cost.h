#ifndef MY_COST_H
#define MY_COST_H

#include <stdio.h>
#include "structs.h"

cost categorical_cross_entropy(layer *pred, layer *exp);
double cost_dev(double pred, double exp);
cost binary_cross_entropy(layer *pred, layer *exp);

#endif