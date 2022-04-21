#include <catch2/catch_test_macros.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "wwiseaudiotools.h"

std::string convert(std::string path) {
		std::ifstream filein(path);

		std::stringstream indata;
		indata << filein.rdbuf();

		std::string outdata = wem_to_ogg(indata.str());
		return outdata;
}

TEST_CASE( "Compare WEM converted with the Wwise Audio Tools to those converted with the individual standalone tools ", "[wwise-audio-tools]") {
	std::ifstream ogg_in("testdata/test1.ogg");
	std::stringstream ogg_in_s;
	ogg_in_s << ogg_in.rdbuf();

	REQUIRE( convert("testdata/test1.wem") ==  ogg_in_s.str() );
}
