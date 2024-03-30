#include "LLGenerator.h"

Table LLGenerator::GetTable() const
{
	return m_table;
}

std::vector<std::string> LLGenerator::GetNonThermals() const
{
	return m_nonThermals;
}

std::vector<std::string> LLGenerator::GetRightSidesOfRule() const
{
	return m_rightSidesOfRule;
}

std::vector<std::set<std::string>> LLGenerator::GetGuidingSets() const
{
	return m_guidingSets;
}

void LLGenerator::ReadRulesAndGuidingSets(std::ifstream& inputFile)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::stringstream ss(line);
		std::string tempLine;

		std::getline(ss, tempLine, '-');
		Trim(tempLine);
		m_nonThermals.emplace_back(tempLine);

		std::getline(ss, tempLine, '/');
		Trim(tempLine);
		m_rightSidesOfRule.emplace_back(tempLine);

		std::set<std::string> guidingSet;
		while (std::getline(ss, tempLine, ','))
		{
			Trim(tempLine);
			guidingSet.insert(tempLine);
		}
		m_guidingSets.emplace_back(guidingSet);
	}
}