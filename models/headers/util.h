#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include "structs.h"
#include <stdio.h>

void normalize_input(double **x, int size, int num_features);
double *layer_to_array(layer *layer);
matrix *matrix_mult(matrix *a, matrix *b);
matrix *get_weights_matrix(layer curr, layer prev);
matrix *get_feature_matrix(layer prev);
matrix *apply_activation(matrix *a, activation activation);
layer *create_layer(matrix *inp, layer *layer);
layer *get_feature_layer(double *entry, int size);
void normalize(double **X, int num_entries, int num_features,
               double *means, double *stds);
#endif