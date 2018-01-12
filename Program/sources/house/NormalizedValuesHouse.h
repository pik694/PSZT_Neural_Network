// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_NORMALIZEDVALUESHOUSE_H
#define PSZT_NEURAL_NETWORK_NORMALIZEDVALUESHOUSE_H

#include "House.h"
#include <thread>

const long MIN_DATE = 19000101;
const long MAX_DATE = 21001231;
const long MIN_PRICE = 0;
const long MAX_PRICE = 50000000;
const int MIN_BEDROOMS =  0;
const int MAX_BEDROOMS = 100;
const int MIN_BATHROOMS = 0;
const int MAX_BATHROOMS = 20;
const long MIN_SQFT_LIVING = 0;
const long MAX_SQFT_LIVING = 100000;
const long MIN_SQFT_LOT = 0;
const long MAX_SQFT_LOT = 10000000;
const int MIN_FLOORS = 0;
const int MAX_FLOORS = 10;
const int MIN_WATERFRONT = 0;
const int MAX_WATERFRONT = 1;
const int MIN_VIEW = 0;
const int MAX_VIEW = 5;
const int MIN_CONDITION = 0;
const int MAX_CONDITION = 5;
const int MIN_GRADE = 0;
const int MAX_GRADE = 20;
const int MIN_SQFT_ABOVE = 0;
const int MAX_SQFT_ABOVE = 50000;
const int MIN_SQFT_BASEMENT = 0;
const int MAX_SQFT_BASEMENT = 20000;
const int MIN_YR_BUILT = 1900;
const int MAX_YR_BUILT = 2100;
const int MIN_YR_RENOVATED = 1900;
const int MAX_YR_RENOVATED = 2100;
const long MIN_ZIPCODE = 0;
const int MAX_ZIPCODE = 99999;
const int MIN_LATITUDE = -180;
const int MAX_LATITUDE = 180;
const int MIN_LONGITUDE = -180;
const int MAX_LONGITUDE = 180;
const int MIN_SQFT_LIVING15 = 0;
const int MAX_SQFT_LIVING15 = 20000;
const int MIN_SQFT_LOT15 = 0;
const long MAX_SQFT_LOT15 = 10000000;

const unsigned THREADS_COUNT = std::thread::hardware_concurrency();

namespace house {
	class NormalizedValuesHouse {
	public:

		NormalizedValuesHouse() = default;

		NormalizedValuesHouse(const boost::gregorian::date &date, float price, int bedrooms, float bathrooms,
		                      int sqftLiving, int sqftLot, float floors, int waterfront, int view, int condition,
		                      int grade, int sqftAbove, int sqftBasement, int yrBuilt, int yrRenovated, int zipcode,
		                      float lat, float f_long, int sqftLiving15, int sqftLot15);


	private:
		double date_;
		double price_;
		double bedrooms_;
		double bathrooms_;
		double sqftLiving_;
		double sqftLot_;
		double floors_;
		double waterfront_;
		double view_;
		double condition_;
		double grade_;
		double sqftAbove_;
		double sqftBasement_;
		double yrBuilt_;
		double yrRenovated_;
		double zipcode_;
		double latitude_;
		double longitude_;
		double sqftLiving15_;
		double sqftLot15_;

	public:
		double getDate() const { return date_; }

		double getPrice() const { return price_; }

		double getBedrooms() const { return bedrooms_; }

		double getBathrooms() const { return bathrooms_; }

		double getSqftLiving() const { return sqftLiving_; }

		double getSqftLot() const { return sqftLot_; }

		double getFloors() const { return floors_; }

		double getWaterfront() const { return waterfront_; }

		double getView() const { return view_; }

		double getCondition() const { return condition_; }

		double getGrade() const { return grade_; }

		double getSqftAbove() const { return sqftAbove_; }

		double getSqftBasement() const { return sqftBasement_; }

		double getYrBuilt() const { return yrBuilt_; }

		double getYrRenovated() const { return yrRenovated_; }

		double getZipcode() const { return zipcode_; }

		double getLat() const { return latitude_; }

		double getLong() const { return longitude_; }

		double getSqftLiving15() const { return sqftLiving15_; }

		double getSqftLot15() const { return sqftLot15_; }
	};
}


#endif //PSZT_NEURAL_NETWORK_NORMALIZEDVALUESHOUSE_H
