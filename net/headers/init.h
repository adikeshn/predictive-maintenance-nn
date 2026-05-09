#ifndef MY_INIT_H
#define MY_INIT_H

#include <stdio.h>
#include "structs.h"

net *read_net(char *file_name);
void write_net(char *file_name, net *net);
net *gen_rand(int num_features, int num_hidden, int *hidden_neurons, activation *activations);

#endif