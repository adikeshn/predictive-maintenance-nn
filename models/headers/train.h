#ifndef MY_TRAIN_H
#define MY_TRAIN_H

#include <stdio.h>
#include "structs.h"

void fisher_shuffle(double **inp, double **out, int num_entries);

net *train_model(net *model, int epochs, int batch_size, int num_entries, double **X,
                 int num_features, double **y, int output_size, double rate, double train_percent);

double train_batch(double **training_data, int features, double **training_output, int output_size,
                   int batch_size, net *model, net *sums_net, double rate);
#endif