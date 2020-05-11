#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "rapidxml.hpp"
#include <fstream>
#include <iterator>

// Learning Tests for RapidXML

SCENARIO( "xml can be read", "[RapidXML]" ) {

    GIVEN( "The file containing the NPTG-metadata.xml" ) {

        std::ifstream theFile("NPTG-metadata.xml");
        std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');
		REQUIRE(buffer.size() > 0);
		
        rapidxml::xml_document<> doc;
	    doc.parse<0>(&buffer[0]);
        
        WHEN( "searching for the correct root node" ) {
            rapidxml::xml_node<> * root;
	        root = doc.first_node("Metadata");
            
            THEN( "the root node should be found" ) {
                REQUIRE(root);
            }
        }

    }
}