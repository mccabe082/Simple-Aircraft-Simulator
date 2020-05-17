#include "xml_lookup_table_1d_reading.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "linear_interpolation.h"
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <limits>
#include <memory>

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

	bool notSorted(std::vector<double>& values)
	{
		return !std::is_sorted(values.begin(), values.end());
	}
}

namespace interp
{
	namespace XMLLookupReading
	{
		void readInputElement(const NodePtr lookupTable1DNode, LookupTable1D& table)
		{
			try
			{
				NodePtr inputNode = lookupTable1DNode->first_node("Input");
				if (inputNode)
				{
					std::string_view inputDescription = lookupTable1DNode->first_attribute("description")->value();
					std::vector<double> values;
					tokenise(std::string(inputNode->value()), values);
					if (notSorted(values)) throw std::runtime_error("row header data isn't strictly increasing");

					table.resize(values.size());

					size_t iVal = 0;
					for (auto value : values)
					{
						table[iVal++].x = value;
					}

					return;
				}
			}
			catch (std::runtime_error ex)
			{
				throw std::runtime_error("reading <Input> element: " + std::string(ex.what()));
			}
			catch (...)
			{
				throw std::runtime_error("missing or malformed <Input> element");
			}
		}

		void readOutputElement(const NodePtr lookupTable1DNode, LookupTable1D& table)
		{
			try
			{
				NodePtr outputNode = lookupTable1DNode->first_node("Output");
				if (outputNode)
				{
					std::string_view outputDescription = lookupTable1DNode->first_attribute("description")->value();
					std::vector<double> values;
					tokenise(std::string(outputNode->value()), values);
					if (values.size()!=table.size()) throw std::runtime_error("no. of output data values does not match no. of input data values");

					size_t iVal = 0;
					for (auto value : values)
					{
						table[iVal++].f = value;
					}

					return;
				}
			}
			catch (std::runtime_error ex)
			{
				throw std::runtime_error("reading <Output> element: " + std::string(ex.what()));
			}
			catch (...)
			{
				throw std::runtime_error("missing or malformed <Output> element");
			}
		}

		std::unique_ptr<LookupTable1D> readInterpolationMethod(const NodePtr lookupTable1DNode)
		{
			auto* pDescriptionAttribute = lookupTable1DNode->first_attribute("method");

			if (!pDescriptionAttribute) throw std::runtime_error("missing \"method\" attribute");

			std::string interpolationMethod = pDescriptionAttribute->value();

			if (interpolationMethod == "linear")
			{
				return std::make_unique<LinearInterpolation>();
			}

			throw std::runtime_error("unrecognised interpolation method (" + interpolationMethod + ")");

			return nullptr;
		}

		std::unique_ptr<LookupTable1D> readLookupTable1DElement(const XMLDoc& doc)
		{
			try
			{
				NodePtr lookupTable1DNode = doc.first_node("LookupTable1D");
				if (lookupTable1DNode)
				{
					std::string_view tableDescription = lookupTable1DNode->first_attribute("description")->value();

					std::unique_ptr<LookupTable1D> pTable = readInterpolationMethod(lookupTable1DNode);

					readInputElement(lookupTable1DNode, *pTable);
					readOutputElement(lookupTable1DNode, *pTable);

					return pTable;
				}
			}
			catch (std::runtime_error ex)
			{
				throw std::runtime_error("reading <LookupTable1D> element: " + std::string(ex.what()));
			}
			catch (...)
			{
				throw std::runtime_error("missing or malformed <LookupTable1D> element");
			}
			
			return nullptr;
		}

		std::unique_ptr<LookupTable1D> load(const std::string& filename)
		{
			try
			{
				rapidxml::file<> xmlFile(filename.c_str());
				rapidxml::xml_document<> doc;
				doc.parse<0>(xmlFile.data());

				return readLookupTable1DElement(doc);
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

			return nullptr;
		}
	}
}