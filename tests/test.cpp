#include <catch2/catch_test_macros.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "wwiseaudiotools.h"

std::string convert(std::string path) {
		std::ifstream filein(path, std::ios::binary);

		// reserve memory upfront
		std::string indata;
		filein.seekg(0, std::ios::end);
		indata.reserve(filein.tellg());
		filein.seekg(0, std::ios::beg);

		indata.assign(
			(std::istreambuf_iterator<char>(filein)),
        	std::istreambuf_iterator<char>()
		);

		std::string outdata = wem_to_ogg(indata);
		return outdata;
}

TEST_CASE( "Compare WEM converted with the Wwise Audio Tools to those converted with the individual standalone tools ", "[wwise-audio-tools]") {
	std::ifstream ogg_in("testdata/test1.ogg", std::ios::binary);
	std::stringstream ogg_in_s;
	ogg_in_s << ogg_in.rdbuf();

	REQUIRE( convert("testdata/test1.wem") ==  ogg_in_s.str() );
}
