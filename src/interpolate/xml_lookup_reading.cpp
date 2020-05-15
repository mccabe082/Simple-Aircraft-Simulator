#include "xml_lookup_reading.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "bilinear_lookup.h"
#include <exception>
#include <iostream>
#include <string>
#include <string_view>

namespace
{
	using namespace rapidxml;
	using NodePtr = xml_node<>*;
	using XMLDoc = xml_document<>;

	void tokenise(const std::string& csvStr, std::vector<double>& values)
	{
		std::vector<double> constructionValues;
		static constexpr char* whitespaces = " \t\f\v\n\r";
		try
		{
			std::string::size_type currentPos = 0;
			std::string::size_type cumulativePos = 0;
			std::string::size_type finalPos = csvStr.find_last_not_of(whitespaces);
			while (cumulativePos < finalPos)
			{
				double token = std::stod(csvStr.substr(cumulativePos), &currentPos);
				cumulativePos += currentPos;
				constructionValues.push_back(token);
			}

			values = std::move(constructionValues);
		}
		catch (...)
		{
			throw (std::runtime_error("malformed token (#" + std::to_string(constructionValues.size() + 1) + ")"));
		}
	}
}

namespace interp
{
	namespace XMLLookupReading
	{
		void readColumnHeaderElement(const NodePtr lookupTable2DNode, Lookup2DTable& table)
		{
			try
			{
				NodePtr columnHeaderNode = lookupTable2DNode->first_node("Column");
				if (columnHeaderNode)
				{
					std::string_view rowDescription = columnHeaderNode->first_attribute("description")->value();
					std::string columnDataStr = columnHeaderNode->value();
					tokenise(columnDataStr, table.xSamples);
					return;
				}
			}
			catch (...)
			{
				throw (std::runtime_error("missing or malformed <Column> element"));
			}
		}

		void readRowHeaderElement(const NodePtr lookupTable2DNode, Lookup2DTable& table)
		{
			try
			{
				NodePtr rowHeaderNode = lookupTable2DNode->first_node("Row");
				if (rowHeaderNode)
				{
					std::string_view rowDescription = rowHeaderNode->first_attribute("description")->value();
					std::string_view rowDataStr = rowHeaderNode->value();
					return;
				}
			}
			catch (...)
			{
				throw (std::runtime_error("missing or malformed <Row> element"));
			}
		}

		void readValuesElement(const NodePtr lookupTable2DNode, Lookup2DTable& table)
		{
			try
			{
				NodePtr valuesNode = lookupTable2DNode->first_node("Values");
				if (valuesNode)
				{
					std::string_view xDataStr = valuesNode->value();
				}
			}
			catch (std::runtime_error ex)
			{
				throw (std::runtime_error("reading <Values> element: " + std::string(ex.what())));
			}
			catch (...)
			{
				throw (std::runtime_error("missing or malformed <Values> element"));
			}
		}

		void readLookupTable2DElement(const XMLDoc& doc, Lookup2DTable& table)
		{
			try
			{
				NodePtr lookupTable2DNode = doc.first_node("LookupTable2D");
				if (lookupTable2DNode)
				{
					std::string_view tableDescription = lookupTable2DNode->first_attribute("description")->value();

					readColumnHeaderElement(lookupTable2DNode, table);
					readRowHeaderElement(lookupTable2DNode, table);
					readValuesElement(lookupTable2DNode, table);
				}
			}
			catch (std::runtime_error ex)
			{
				throw (std::runtime_error("reading <LookupTable2D> element: " + std::string(ex.what())));
			}
			catch (...)
			{
				throw (std::runtime_error("missing or malformed <LookupTable2D> element"));
			}
		}

		void readRowElement(const NodePtr valuesNode, Lookup2DTable& table)
		{
			try
			{
				NodePtr rowNode = valuesNode->first_node("Row");
				while (rowNode)
				{
					std::string_view xDataStr = rowNode->value();
					rowNode = rowNode->next_sibling("Row");
				}
			}
			catch (...)
			{
				throw (std::runtime_error("missing or malformed Row element"));
			}
		}

		bool readFile(const std::string& filename, Lookup2DTable& table)
		{
			try
			{
				rapidxml::file<> xmlFile(filename.c_str());
				rapidxml::xml_document<> doc;
				doc.parse<0>(xmlFile.data());

				readLookupTable2DElement(doc, table);

				return true;
			}
			catch (std::runtime_error ex)
			{
				std::cerr << "reading '" + filename + "': " + std::string(ex.what()) << std::flush;
			}
			catch (...)
			{
				std::cerr << "missing or malformed input file: '" + filename + "'" << std::flush;
			}

			std::exit(EXIT_FAILURE);

			return false;
		}
	}
}