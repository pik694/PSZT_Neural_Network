#include "TrainingDataFactory.h"

TrainingDataFactory::TrainingDataFactory()
{
}

void TrainingDataFactory::run( std::vector< std::string >* file_rows, const char* separator, std::vector< std::shared_ptr< House > >* training_data )
{
	
	for ( unsigned thread_id = 0; thread_id < THREADS_COUNT; ++thread_id )
		threads_.push_back( std::thread( createHouseFromRow, thread_id, file_rows, separator, training_data ) );

	for ( unsigned thread_id = 0; thread_id < THREADS_COUNT; ++thread_id )
		threads_[ thread_id ].join();
		
	( *file_rows ).clear();
}

void TrainingDataFactory::createHouseFromRow( unsigned thread_id, std::vector< std::string >* file_rows, const char* separator,
												std::vector< std::shared_ptr< House > >* training_data )
{
	boost::char_separator< char > b_separator( separator );
	for ( unsigned index = thread_id; index < ( *file_rows ).size(); index += THREADS_COUNT )
	{
		bool error_occured = false;
		boost::gregorian::date date; 
		float floors, price, bathrooms, f_long, lat ;
		int bedrooms, sqftLiving, sqftLot, waterfront, view, condition, grade, sqftAbove, yrBuilt,
			yrRenovated, zipcode, sqftBasement, sqftLiving15, sqftLot15;

		boost::tokenizer< boost::char_separator< char > > b_tokenizer( ( *file_rows )[ index ], b_separator );
		boost::tokenizer< boost::char_separator< char > >::iterator it = b_tokenizer.begin(), it_end = b_tokenizer.end();
		for ( unsigned record_pos = 0; it != it_end; ++record_pos, ++it )
		{
			if ( error_occured )
				break;
			try
			{
				switch ( record_pos )
				{
				case DATE:
					date = boost::gregorian::date_from_iso_string( boost::replace_all_copy( *it, "\"", "" ).substr( POS_0, ISO_DATE_LENGTH ) );
					break;
				case PRICE:
					std::istringstream( *it ) >> std::scientific >> price;
					break;
				case BEDROOMS:
					std::istringstream( *it ) >> std::scientific >> bedrooms;
					break;
				case BATHROOMS:
					std::istringstream( *it ) >> std::scientific >> bathrooms;
					break;
				case SQFT_LIVING:
					std::istringstream( *it ) >> std::scientific >> sqftLiving;
					break;
				case SQFT_LOT:
					std::istringstream( *it ) >> std::scientific >> sqftLot;
					break;
				case FLOORS:
					std::istringstream( boost::replace_all_copy( *it, "\"", "" ) ) >> std::scientific >> floors;
					break;
				case WATERFRONT:
					std::istringstream( *it ) >> std::scientific >> waterfront;
					break;
				case VIEW:
					std::istringstream( *it ) >> std::scientific >> view;
					break;
				case CONDITION:
					std::istringstream( *it ) >> std::scientific >> condition;
					break;
				case GRADE:
					std::istringstream( *it ) >> std::scientific >> grade;
					break;
				case SQFT_ABOVE:
					std::istringstream( *it ) >> std::scientific >> sqftAbove;
					break;
				case SQFT_BASEMENT: 
					std::istringstream( *it ) >> std::scientific >> sqftBasement;
					break;
				case YR_BUILT:
					std::istringstream( *it ) >> std::scientific >> yrBuilt;
					break;
				case YR_RENOVATED: 
					std::istringstream( *it ) >> std::scientific >> yrRenovated;
					break;
				case ZIPCODE:
					std::istringstream( boost::replace_all_copy( *it, "\"", "" ) ) >> std::scientific >> zipcode;
					break;
				case LAT:
					std::istringstream( *it ) >> std::scientific >> lat;
					break;
				case LONG: 
					std::istringstream( *it ) >> std::scientific >> f_long;
					break;
				case SQFT_LIVING15:
					std::istringstream( *it ) >> std::scientific >> sqftLiving15;
					break;
				case SQFT_LOT15:
					std::istringstream( *it ) >> std::scientific >> sqftLot15;
					break;
				}
			}
			catch ( ... )
			{
				error_occured = true;
				std::cerr << "Failed to parse row: " << index+1 << std::endl;
			}
		}		
		if( error_occured )
			continue;

		( *training_data )[ index ] = std::make_shared< House >( date, price, bedrooms, bathrooms, sqftLiving, sqftLot, floors, waterfront,
			view, condition, grade, sqftAbove, sqftBasement, yrBuilt, yrRenovated, zipcode, lat, f_long, sqftLiving15, sqftLot15 );
	}
}

TrainingDataFactory::~TrainingDataFactory()
{
}
