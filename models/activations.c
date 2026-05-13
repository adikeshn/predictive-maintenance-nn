#include "headers/structs.h"
#include "headers/activations.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

double sigmoid(double inp)
{
    return 1 / (1 + exp(-inp));
}

double deriv_sigmoid(double activ)
{
    return activ * (1 - activ);
}

double ReLU(double inp)
{
    return inp > 0.0 ? inp : 0.0;
}

double deriv_ReLU(double inp)
{
    return inp > 0.0 ? 1.0 : 0.0;
}
