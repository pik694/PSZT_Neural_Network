//
// Created by Marcin Dziedzic on 06/01/2018.
//

#ifndef PSZT_NEURAL_NETWORK_FUNCTIONSBANK_H
#define PSZT_NEURAL_NETWORK_FUNCTIONSBANK_H

#define EULER_NUMBER 2.71828

#include <math.h>
#include <functional>


namespace neural_network {

	namespace functions {

		enum class ActivationFunctions_E {
			step,
			fastSigmoid,
			logistic,
			hyperbolicTangent,
			specificAlgebraic
		};

		class ActivationFunctionsBank {

		public:

			using functions_pair_t =
			std::pair<std::function<double(double)>, std::function<double(double)>>;

			static functions_pair_t getFunctionAndDerivative(ActivationFunctions_E);

			static double stepFunction(double x);

			static double stepFunctionDerivative(double);

			static double fastSigmoidFunction(double x);

			static double fastSigmoidFunctionDerivative(double x);

			static double logisticFunction(double x);

			static double logisticFunctionDerivative(double x);

			static double hyperbolicTangentFunction(double x);

			static double hyperbolicTangentFunctionDerivative(double x);

			static double specificAlgebraicFunction(double x);

			static double specificAlgebraicFunctionDerivative(double x);

		};
	}
}


#endif //PSZT_NEURAL_NETWORK_FUNCTIONSBANK_H
