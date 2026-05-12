#ifndef MY_INIT_H
#define MY_INIT_H

#include <stdio.h>
#include "structs.h"

net *read_net(char *file_name);
void write_net(char *file_name, net *net);
net *gen_rand(int num_features, int num_hidden, int *hidden_neurons, activation *activations, cost_funcs func);
void load_data(double ***X, double ***y, int num_entries, int num_features, int num_output);

#endif