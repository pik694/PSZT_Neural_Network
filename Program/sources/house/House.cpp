#include "House.h"

using namespace house;

House::House(boost::gregorian::date date, float price, int bedrooms, float bathrooms, int sqftLiving, int sqftLot,
             float floors,
             int waterfront, int view, int condition, int grade, int sqftAbove, int sqftBasement, int yrBuilt,
             int yrRenovated,
             int zipcode, float lat, float f_long, int sqftLiving15, int sqftLot15) {
	date_ = date;
	price_ = price;
	bedrooms_ = bedrooms;
	bathrooms_ = bathrooms;
	sqftLiving_ = sqftLiving;
	sqftLot_ = sqftLot;
	floors_ = floors;
	waterfront_ = waterfront;
	view_ = view;
	condition_ = condition;
	grade_ = grade;
	sqftAbove_ = sqftAbove;
	sqftBasement_ = sqftBasement;
	yrBuilt_ = yrBuilt;
	yrRenovated_ = yrRenovated;
	zipcode_ = zipcode;
	lat_ = lat;
	long_ = f_long;
	sqftLiving15_ = sqftLiving15;
	sqftLot15_ = sqftLot15;
}

House::~House() = default;
