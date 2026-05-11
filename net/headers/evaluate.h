#ifndef MY_EVAL_H
#define MY_EVAL_H

#include <stdio.h>
#include "structs.h"

net *forward_pass(net *net, layer *features);
net *back_prop(net *net, layer *exp, double learning_rate);

#endif