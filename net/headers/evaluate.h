#ifndef MY_EVAL_H
#define MY_EVAL_H

#include <stdio.h>
#include "structs.h"

layer *forward_pass(net *net, layer *features);
net *back_prop(net *sums, net *net, layer *features, layer *exp, double learning_rate);

#endif