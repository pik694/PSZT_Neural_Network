//
// Created by Marcin Dziedzic on 06/01/2018.
//

#include "FunctionsBank.h"

double FunctionsBank::stepFunction(double x) {
    if (x < 0.5) {
        return 0;
    } else {
        return 1;
    }
}

double FunctionsBank::stepFunctionDerivative(double x) {
    return 0;
}

double FunctionsBank::fastSigmoidFunction(double x) {
    return x / (1 + abs(x));
}

double FunctionsBank::fastSigmoidFunctionDerivative(double x) {
    return 1 / pow(abs(x) + 1, 2);
}

double FunctionsBank::logisticFunction(double x) {
    return 1 / (1 + pow(EULER_NUMBER, -x));
}

double FunctionsBank::logisticFunctionDerivative(double x) {
    return pow(EULER_NUMBER, x) / pow((pow(EULER_NUMBER, x) + 1), 2);
}

double FunctionsBank::hyperbolicTangentFunction(double x) {
    return tanh(x);
}

double FunctionsBank::hyperbolicTangentFunctionDerivative(double x) {
    return 1.0 - x * x;
}

double FunctionsBank::specificAlgebraicFunction(double x) {
    return x / sqrt(1+pow(x,2));
}

double FunctionsBank::specificAlgebraicFunctionDerivative(double x) {
    return 1 / pow((pow(x,2) + 1), 3/2);
}
