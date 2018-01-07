//
// Created by Piotr Żelazko on 07.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_NORMALIZEDVALUESHOUSE_H
#define PSZT_NEURAL_NETWORK_NORMALIZEDVALUESHOUSE_H

#include "House.h"

namespace house {
	class NormalizedValuesHouse : public House {
	public:
		NormalizedValuesHouse(const boost::gregorian::date &date, float price, int bedrooms, float bathrooms,
		                      int sqftLiving, int sqftLot, float floors, int waterfront, int view, int condition,
		                      int grade, int sqftAbove, int sqftBasement, int yrBuilt, int yrRenovated, int zipcode,
		                      float lat, float f_long, int sqftLiving15, int sqftLot15);



		// wszystkie wartosci maja sie miescic miedzy 0 a 1 (double)
		// na chwile obecna taki sam interfejs co klasa House
	};
}


#endif //PSZT_NEURAL_NETWORK_NORMALIZEDVALUESHOUSE_H
