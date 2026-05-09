#include "headers/init.h"
#include "headers/evaluate.h"
#include "headers/free_structs.h"
#include "headers/structs.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int num_features = 5;
    int num_layers = 2;
    int neurons[2] = {5, 5};
    activation actives[2] = {RELU, SOFTMAX};

    net *init = gen_rand(num_features, num_layers, neurons, actives);
    write_net("model.bin", init);
    net *read = read_net("model.bin");

    free_net(init);
    free_net(read);
}