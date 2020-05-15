#include "data_table_2d.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <exception>
#include <iostream>

namespace
{
	using namespace rapidxml;
	using NodePtr = xml_node<>*;
	using XMLDoc = xml_document<>;
}

namespace interp
{
	void readColumnHeaderElement(const NodePtr lookupTable2DNode, Column& values)
	{
		try
		{
			NodePtr columnHeaderNode = lookupTable2DNode->first_node("Column");
			if (columnHeaderNode)
			{
				std::string rowDescription = columnHeaderNode->first_attribute("description")->value();
				std::string columnDataStr = columnHeaderNode->value();
				return;
			}
		}
		catch (...)
		{
			throw (std::runtime_error("missing or malformed <Column> element"));
		}
	}

	void readRowHeaderElement(const NodePtr lookupTable2DNode, Row& values)
	{
		try
		{
			NodePtr rowHeaderNode = lookupTable2DNode->first_node("Row");
			if (rowHeaderNode)
			{
				std::string rowDescription = rowHeaderNode->first_attribute("description")->value();
				std::string rowDataStr = rowHeaderNode->value();
				return;
			}
		}
		catch (...)
		{
			throw (std::runtime_error("missing or malformed <Row> element"));
		}
	}

	void readValuesElement(const NodePtr lookupTable2DNode, DataTable2D* values)
	{
		try
		{
			NodePtr valuesNode = lookupTable2DNode->first_node("Values");
			if (valuesNode)
			{
				std::string xDataStr = valuesNode->value();
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

	void readLookupTable2DElement(const XMLDoc& doc, DataTable2D* values)
	{
		try
		{
			NodePtr lookupTable2DNode = doc.first_node("LookupTable2D");
			if (lookupTable2DNode)
			{
				std::string tableDescription = lookupTable2DNode->first_attribute("description")->value();

				readColumnHeaderElement(lookupTable2DNode, values->xSamples);
				readRowHeaderElement(lookupTable2DNode, values->ySamples);
				readValuesElement(lookupTable2DNode, values);
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

	void readRowElement(const NodePtr valuesNode, DataTable2D* values)
	{
		try
		{
			NodePtr rowNode = valuesNode->first_node("Row");
			while (rowNode)
			{
				std::string xDataStr = rowNode->value();
				rowNode = rowNode->next_sibling("Row");
			}
		}
		catch (...)
		{
			throw (std::runtime_error("missing or malformed Row element"));
		}
	}

	DataTable2D::DataTable2D(const std::string& filename)
	{
		try
		{
			rapidxml::file<> xmlFile(filename.c_str());
			rapidxml::xml_document<> doc;
			doc.parse<0>(xmlFile.data());

			readLookupTable2DElement(doc, this);

			return;
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
	}

	double DataTable2D::lookup(size_t row, size_t column) const { return fRows[row][column]; }

	double& DataTable2D::lookup(size_t row, size_t column) { return fRows[row][column]; }
}