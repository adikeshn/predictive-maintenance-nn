#ifndef MY_FREE_H
#define MY_FREE_H

#include <stdio.h>
#include "structs.h"

void free_matrix(matrix **a);
void free_layer(layer **a);
void free_neuron(neuron **a);

#endif