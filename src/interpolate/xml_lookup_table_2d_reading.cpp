#include "xml_lookup_table_2d_reading.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "bilinear_interpolation.h"
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

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
		void readColumnHeaderElement(const NodePtr lookupTable2DNode, LookupTable2D& table)
		{
			try
			{
				NodePtr columnHeaderNode = lookupTable2DNode->first_node("Column");
				if (columnHeaderNode)
				{
					std::string_view rowDescription = columnHeaderNode->first_attribute("description")->value();
					std::string columnDataStr = columnHeaderNode->value();
					tokenise(columnDataStr, table.xSamples);
					if (notSorted(table.xSamples)) throw std::runtime_error("column header data isn't strictly increasing");
					return;
				}
			}
			catch (std::runtime_error ex)
			{
				throw std::runtime_error("reading <Column> header element: " + std::string(ex.what()));
			}
			catch (...)
			{
				throw std::runtime_error("missing or malformed <Column> element");
			}
		}

		void readRowHeaderElement(const NodePtr lookupTable2DNode, LookupTable2D& table)
		{
			try
			{
				NodePtr rowHeaderNode = lookupTable2DNode->first_node("Row");
				if (rowHeaderNode)
				{
					std::string_view rowDescription = rowHeaderNode->first_attribute("description")->value();
					tokenise(std::string(rowHeaderNode->value()), table.ySamples);
					if (notSorted(table.ySamples)) throw std::runtime_error("row header data isn't strictly increasing");
					return;
				}
			}
			catch (std::runtime_error ex)
			{
				throw std::runtime_error("reading <Row> header element: " + std::string(ex.what()));
			}
			catch (...)
			{
				throw std::runtime_error("missing or malformed <Row> element");
			}
		}

		void readRowElements(const NodePtr valuesNode, LookupTable2D& table)
		{
			const size_t ROWS = table.xSamples.size();
			const size_t COLS = table.ySamples.size();

			table.fRows.resize(COLS, LookupTable2D::Row(ROWS, 0.));

			try
			{
				size_t iRow = 0;
				LookupTable2D::Row rowOnFile;
				NodePtr rowNode = valuesNode->first_node("Row");

				while (rowNode)
				{
					if (iRow >= ROWS) throw std::runtime_error("too many rows in lookup table");

					tokenise(std::string(rowNode->value()), rowOnFile);

					if (rowOnFile.size() < COLS) throw std::runtime_error("too many columns in lookup table, row #" + iRow);
					if (rowOnFile.size() > COLS) throw std::runtime_error("too few columns in lookup table" + iRow);

					for (size_t iCol = 0; iCol < COLS; ++iCol)
					{
						table.fRows[iCol][iRow] = rowOnFile[iCol];
					}
					iRow++;
					rowNode = rowNode->next_sibling("Row");
				}

				if (iRow < ROWS) throw std::runtime_error("too few row in lookup table");


			}
			catch (std::runtime_error ex)
			{
				throw std::runtime_error("reading <Row> elements: " + std::string(ex.what()));
			}
			catch (...)
			{
				throw std::runtime_error("missing or malformed Row elements");
			}
		}

		void readValuesElement(const NodePtr lookupTable2DNode, LookupTable2D& table)
		{
			try
			{
				NodePtr valuesNode = lookupTable2DNode->first_node("Values");
				if (valuesNode)
				{
					return readRowElements(valuesNode, table);
				}
			}
			catch (std::runtime_error ex)
			{
				throw std::runtime_error("reading <Values> element: " + std::string(ex.what()));
			}
			catch (...)
			{
				throw std::runtime_error("missing or malformed <Values> element");
			}
		}

		void readLookupTable2DElement(const XMLDoc& doc, LookupTable2D& table)
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
				throw std::runtime_error("reading <LookupTable2D> element: " + std::string(ex.what()));
			}
			catch (...)
			{
				throw std::runtime_error("missing or malformed <LookupTable2D> element");
			}
		}

		bool readFile(const std::string& filename, LookupTable2D& table)
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