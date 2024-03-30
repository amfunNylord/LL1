#include "LLGenerator.h"

Table LLGenerator::GetTable() const
{
	return m_table;
}

void LLGenerator::ReadRulesAndGuidingSets(std::ifstream& inputFile)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		size_t i = 0;
		size_t lineLen = line.size();
		while (i < lineLen)
		{
			std::string tempLine;
			while (line[i] != '-')
			{
				tempLine += line[i];
				i++;
			}	
			m_nonThermals.emplace_back(tempLine);
			tempLine.clear();
			i++;
			while (line[i] != '/')
			{
				tempLine += line[i];
				i++;
			}
			m_rightSidesOfRule.emplace_back(tempLine);
			i++;
			tempLine.clear();
			std::set<std::string> guidingSet;
			while (true)
			{
				if (i == lineLen)
				{
					guidingSet.insert(tempLine);
					break;
				}
				tempLine += line[i];
				i++;
				if (line[i] == ',')
				{
					guidingSet.insert(tempLine);
					i++;
					tempLine.clear();
				}
			}
			m_guidingSets.emplace_back(guidingSet);
		}
	}
}
