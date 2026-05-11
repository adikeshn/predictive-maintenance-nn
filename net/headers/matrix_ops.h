#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include "structs.h"
#include <stdio.h>

matrix *matrix_mult(matrix *a, matrix *b);
matrix *get_weights_matrix(layer curr, layer prev);
matrix *get_feature_matrix(layer prev);
matrix *apply_activation(matrix *a, activation activation);
layer *create_layer(matrix *inp, layer *layer);

#endif