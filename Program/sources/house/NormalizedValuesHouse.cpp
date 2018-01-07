//
// Created by Piotr Żelazko on 07.01.2018.
//

#include "NormalizedValuesHouse.h"

house::NormalizedValuesHouse::NormalizedValuesHouse(const boost::gregorian::date &date, float price, int bedrooms,
                                                    float bathrooms, int sqftLiving, int sqftLot, float floors,
                                                    int waterfront, int view, int condition, int grade, int sqftAbove,
                                                    int sqftBasement, int yrBuilt, int yrRenovated, int zipcode,
                                                    float lat, float f_long, int sqftLiving15, int sqftLot15) : House(
		date, price, bedrooms, bathrooms, sqftLiving, sqftLot, floors, waterfront, view, condition, grade, sqftAbove,
		sqftBasement, yrBuilt, yrRenovated, zipcode, lat, f_long, sqftLiving15, sqftLot15) {}
