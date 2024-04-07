#include "GuidingSetsGenerator.h"
#include "StringTrim.cpp"

void GuidingSetsGenerator::Fill()
{
}

void GuidingSetsGenerator::Generate()
{
	std::vector<std::string> row;
	for (size_t i = 0; i < m_nonTherminals.size(); i++)
	{
		row.emplace_back(m_nonTherminals[i]);
		std::vector<std::string> tempRow = { m_nonTherminals[i] };
		m_table.emplace_back(tempRow);
	}
	m_table.insert(m_table.begin(), row);
}

void GuidingSetsGenerator::ReadRules(std::ifstream& inputFile)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::stringstream ss(line);
		std::string tempStr;

		std::getline(ss, tempStr, '-');
		Trim(tempStr);
		m_nonTherminals.emplace_back(tempStr);
		
		std::getline(ss, tempStr);
		Trim(tempStr);
		m_rightSidesOfRule.emplace_back(tempStr);
	}
}
