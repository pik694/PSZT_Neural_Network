#include <iostream>
#include <boost/timer/timer.hpp>
#include <cmath>


int main() {


	boost::timer::cpu_timer timer;

	for (int i = 0; i < 100000000; ++i){
		std::pow(1.234, i);
	}

    std::cout << timer.format() << std::endl;


    return 0;
}
