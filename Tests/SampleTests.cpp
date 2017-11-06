//
// Created by Piotr Żelazko on 06.11.2017.
//

#include <boost/test/unit_test.hpp>
#include "../SampleClass.hpp"

BOOST_AUTO_TEST_SUITE(SAMPLE_TEST_SUITE)

	BOOST_AUTO_TEST_CASE(Sample_Test_Case){

		BOOST_CHECK_EQUAL(1,1);
		
		

	}

	BOOST_AUTO_TEST_CASE(Another_Test_Case){
		BOOST_REQUIRE_EQUAL(1,2);
	}

	BOOST_AUTO_TEST_CASE(Another_Test_Case2){

		SampleClass foo;

		BOOST_CHECK_EQUAL(1, foo.SomeMethod());


	}

BOOST_AUTO_TEST_SUITE_END()
