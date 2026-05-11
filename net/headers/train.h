#ifndef MY_TRAIN_H
#define MY_TRAIN_H

#include <stdio.h>
#include "structs.h"

net *train_model(net *model, int epochs, int batch_size, double **training_data);

#endif