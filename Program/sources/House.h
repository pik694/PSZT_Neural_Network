//Created by Daniel Bigos 

#include <iostream>
#include <vector>
#include "boost/date_time/gregorian/gregorian.hpp"

const int ISO_DATE_LENGTH = 8;
const int POS_0 = 0;

const unsigned ID = 0;
const unsigned DATE = 1;
const unsigned PRICE = 2;
const unsigned BEDROOMS = 3;
const unsigned BATHROOMS = 4;
const unsigned SQFT_LIVING = 5;
const unsigned SQFT_LOT = 6;
const unsigned FLOORS = 7;
const unsigned WATERFRONT = 8;
const unsigned VIEW = 9;
const unsigned CONDITION = 10;
const unsigned GRADE = 11;
const unsigned SQFT_ABOVE = 12;
const unsigned SQFT_BASEMENT = 13;
const unsigned YR_BUILT = 14;
const unsigned YR_RENOVATED = 15;
const unsigned ZIPCODE = 16;
const unsigned LAT = 17;
const unsigned LONG = 18;
const unsigned SQFT_LIVING15 = 19;
const unsigned SQFT_LOT15 = 20;

class House
{
private:
	boost::gregorian::date date_;
	float price_;
	int bedrooms_;
	float bathrooms_;
	int sqftLiving_;
	int sqftLot_;
	float floors_;
	int waterfront_;
	int view_;
	int condition_;
	int grade_;
	int sqftAbove_;
	int	sqftBasement_;
	int	yrBuilt_;
	int yrRenovated_;
	int zipcode_;
	float lat_;
	float long_;
	int sqftLiving15_;
	int sqftLot15_;

public:
	boost::gregorian::date getDate() { return date_; }
	float getPrice() { return price_; }
	int getBedrooms() { return bedrooms_; }
	float getBathrooms() { return bathrooms_; }
	int getSqftLiving() { return sqftLiving_; }
	int getSqftLot() { return sqftLot_; }
	float getFloors() { return floors_; }
	int getWaterfront() { return waterfront_; }
	int getView() { return view_; }
	int getCondition() { return condition_; }
	int getGrade() { return grade_; }
	int getSqftAbove() { return sqftAbove_; }
	int	getSqftBasement() { return sqftBasement_; }
	int	getYrBuilt() { return yrBuilt_; }
	int getYrRenovated() { return yrRenovated_; }
	int getZipcode() { return zipcode_; }
	float getLat() { return lat_; }
	float getLong() { return long_; }
	int getSqftLiving15() { return sqftLiving15_; }
	int getSqftLot15() { return sqftLot15_; }
	
	House(	boost::gregorian::date date, float price, int bedrooms, float bathrooms, int sqftLiving, int sqftLot,
			float floors, int waterfront, int view, int condition, int grade, int sqftAbove, int sqftBasement,
			int	yrBuilt, int yrRenovated, int zipcode, float lat, float f_long, int sqftLiving15, int sqftLot15 );
	~House();
};

