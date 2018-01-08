#include "NormalizedValuesHouse.h"

house::NormalizedValuesHouse::NormalizedValuesHouse(const boost::gregorian::date &date, float price, int bedrooms,
                                                    float bathrooms, int sqftLiving, int sqftLot, float floors,
                                                    int waterfront, int view, int condition, int grade, int sqftAbove,
                                                    int sqftBasement, int yrBuilt, int yrRenovated, int zipcode,
                                                    float lat, float f_long, int sqftLiving15, int sqftLot15 ) {

	date_ = ( ( date.year() * 10000 + date.month() * 100 + date.day() ) - MIN_DATE ) / (double)( MAX_DATE - MIN_DATE );
	price_ = ( price - MIN_PRICE ) / (double) ( MAX_PRICE - MIN_PRICE );
	bedrooms_ = ( bedrooms - MIN_BEDROOMS ) / (double) ( MAX_BEDROOMS - MIN_BEDROOMS );
	bathrooms_ = ( bathrooms - MIN_BATHROOMS ) / (double) ( MAX_BATHROOMS - MIN_BATHROOMS );
	sqftLiving_ = ( sqftLiving - MIN_SQFT_LIVING ) / (double) ( MAX_SQFT_LIVING - MIN_SQFT_LIVING );
	sqftLot_ = ( sqftLot - MIN_SQFT_LOT ) / (double) ( MAX_SQFT_LOT - MIN_SQFT_LOT );
	floors_ = ( floors - MIN_FLOORS ) / (double) ( MAX_FLOORS - MIN_FLOORS );
	waterfront_ = ( waterfront - MIN_WATERFRONT ) / (double) ( MAX_WATERFRONT - MIN_WATERFRONT );
	view_ = ( view - MIN_VIEW ) / (double) ( MAX_VIEW - MIN_VIEW );
	sqftBasement_ = ( sqftBasement - MIN_SQFT_BASEMENT ) / (double) ( MAX_SQFT_BASEMENT - MIN_SQFT_BASEMENT );
	yrBuilt_ = ( yrBuilt - MIN_YR_BUILT ) / (double) ( MAX_YR_BUILT - MIN_YR_BUILT );
	condition_ = ( condition - MIN_CONDITION ) / (double) ( MAX_CONDITION - MIN_CONDITION );
	grade_ = ( grade - MIN_GRADE ) / (double) ( MAX_GRADE - MIN_GRADE );
	sqftAbove_ = ( sqftAbove - MIN_SQFT_ABOVE ) / (double) ( MAX_SQFT_ABOVE - MIN_SQFT_ABOVE );
	yrRenovated_ = ( yrRenovated - MIN_YR_RENOVATED ) / (double) ( MAX_YR_RENOVATED - MIN_YR_RENOVATED );
	zipcode_ = ( zipcode - MIN_ZIPCODE ) / (double) ( MAX_ZIPCODE - MIN_ZIPCODE );
	latitude_ = ( lat - MIN_LATITUDE ) / (double) ( MAX_LATITUDE - MIN_LATITUDE );
	longitude_ = ( f_long - MIN_LONGITUDE ) / (double) ( MAX_LONGITUDE - MIN_LONGITUDE );
	sqftLiving15_ = ( sqftLiving15 - MIN_SQFT_LIVING15 ) / (double) ( MAX_SQFT_LIVING15 - MIN_SQFT_LIVING15 );
	sqftLot15_ = ( sqftLot15 - MIN_SQFT_LOT15 ) / (double) ( MAX_SQFT_LOT15 - MIN_SQFT_LOT15 );
}
