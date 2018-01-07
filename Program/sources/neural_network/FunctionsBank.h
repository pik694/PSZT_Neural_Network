//
// Created by Marcin Dziedzic on 06/01/2018.
//

#ifndef PSZT_NEURAL_NETWORK_FUNCTIONSBANK_H
#define PSZT_NEURAL_NETWORK_FUNCTIONSBANK_H

#define EULER_NUMBER 2.71828

#include <math.h>

class FunctionsBank {

public:

    static double stepFunction(double x);
    static double stepFunctionDerivative(double x);

    static double fastSigmoidFunction(double x);
    static double fastSigmoidFunctionDerivative(double x);

    static double logisticFunction(double x);
    static double logisticFunctionDerivative(double x);

    static double hyperbolicTangentFunction(double x);
    static double hyperbolicTangentFunctionDerivative(double x);

    static double specificAlgebraicFunction(double x);
    static double specificAlgebraicFunctionDerivative(double x);

};


#endif //PSZT_NEURAL_NETWORK_FUNCTIONSBANK_H
