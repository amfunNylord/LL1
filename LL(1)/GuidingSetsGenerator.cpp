#include "GuidingSetsGenerator.h"

std::vector<std::string> GuidingSetsGenerator::GetNonTerminals() const
{
	return m_nonTerminals;
}

std::vector<std::string> GuidingSetsGenerator::GetRightSidesOfRule() const
{
	return m_rightSidesOfRule;
}

std::vector<std::set<std::string>> GuidingSetsGenerator::GetGuidingSets() const
{
	return m_guidingSets;
}

std::string GuidingSetsGenerator::GetEl(const std::string& line)
{
	size_t i = 0;
	std::string el;
	while (i < line.size() && line[i] != ' ')
	{
		el += line[i];
		i++;
	}
	return el;
}

void GuidingSetsGenerator::RemoveEl(std::string& line, const std::string& el)
{
	line.erase(0, el.size());
}

void GuidingSetsGenerator::GetGuidingSetsOfNonTerminal(size_t row)
{
	if (m_guidingSets[row].empty())
	{
		bool isNonTerminalSymbol = false;
		std::string el = GetEl(m_rightSidesOfRule[row]);
		for (size_t i = 0; i < m_nonTerminals.size(); i++)
		{
			if (m_nonTerminals[i] == el)
			{
				if (m_guidingSets[i].empty())
				{
					GetGuidingSetsOfNonTerminal(i);
					m_guidingSets[row].insert(m_guidingSets[i].begin(), m_guidingSets[i].end()); 
					break;
				}
				else
				{
					m_guidingSets[row].insert(m_guidingSets[i].begin(), m_guidingSets[i].end()); 
				}
			}
		}
	}
}

void GuidingSetsGenerator::GetGuidingSetsForEmpty(const std::string& nonTerminal, const size_t& row)
{
	for (size_t i = 0; i < m_rightSidesOfRule.size(); i++)
	{
		std::string rightSideOfRule = m_rightSidesOfRule[i];
		while (!rightSideOfRule.empty())
		{
			std::string element = GetEl(rightSideOfRule);
			RemoveEl(rightSideOfRule, element);
			if (!rightSideOfRule.empty())
			{
				rightSideOfRule.erase(0, 1); // убираем пробел
			}
			if (nonTerminal == element && m_nonTerminals[i] != nonTerminal)
			{
				element = GetEl(rightSideOfRule);
				if (element.empty())
				{
					std::set<std::string> guidingSet = GetGuidingSet(m_nonTerminals[i]);

					m_guidingSets[row].insert(guidingSet.begin(), guidingSet.end());
				}
				else if (!IsNonTerminal(element))
				{
					m_guidingSets[row].insert(element);
				}
				else
				{
					std::vector<size_t> indexesOfNonTerminal;
					for (size_t j = 0; j < m_nonTerminals.size(); j++)
					{
						if (m_nonTerminals[i] == nonTerminal)
						{
							indexesOfNonTerminal.emplace_back(i);
						}
					}
					for (const auto& index : indexesOfNonTerminal)
					{
						m_guidingSets[row].insert(m_guidingSets[index].begin(), m_guidingSets[index].end());
					}
				}
				break;
			}
		}
	}
}

std::set<std::string> GuidingSetsGenerator::GetGuidingSet(const std::string& nonTerminal)
{
	std::set<std::string> returnableSet;
	for (size_t i = 0; i < m_rightSidesOfRule.size(); i++)
	{
		std::string rightSideOfRule = m_rightSidesOfRule[i];
		while (!rightSideOfRule.empty())
		{
			std::string element = GetEl(rightSideOfRule);
			RemoveEl(rightSideOfRule, element);
			if (!rightSideOfRule.empty())
			{
				rightSideOfRule.erase(0, 1); // убираем пробел
			}
			if (nonTerminal == element && m_nonTerminals[i] != nonTerminal)
			{
				element = GetEl(rightSideOfRule);
				if (element.empty())
				{
					std::set<std::string> guidingSet = GetGuidingSet(m_nonTerminals[i]);
					
					returnableSet.insert(guidingSet.begin(), guidingSet.end());
				}
				else if (!IsNonTerminal(element))
				{
					returnableSet.insert(element);
				}
				else
				{
					std::vector<size_t> indexesOfNonTerminal;
					for (size_t j = 0; j < m_nonTerminals.size(); j++)
					{
						if (m_nonTerminals[j] == element)
						{
							indexesOfNonTerminal.emplace_back(j);
						}
					}
					for (const auto& index : indexesOfNonTerminal)
					{
						returnableSet.insert(m_guidingSets[index].begin(), m_guidingSets[index].end());
					}
				}
			}
		}
	}
	return returnableSet;
}

void GuidingSetsGenerator::Generate()
{
	m_guidingSets.resize(m_nonTerminals.size());
	
	for (size_t i = 0; i < m_rightSidesOfRule.size(); i++)
	{
		std::string el = GetEl(m_rightSidesOfRule[i]);
		if (el != "e" && !IsNonTerminal(el))
		{
			std::set<std::string> s = { el };
			m_guidingSets[i] = s;
		}
	}

	// вызываем для первого нетерминала
	GetGuidingSetsOfNonTerminal(0);

	// заполняем для пустых переходов
	for (size_t i = 0; i < m_rightSidesOfRule.size(); i++)
	{
		if (m_rightSidesOfRule[i] == "e")
		{
			GetGuidingSetsForEmpty(m_nonTerminals[i], i);
		}
	}
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
		m_nonTerminals.emplace_back(tempStr);
		
		std::getline(ss, tempStr);
		Trim(tempStr);
		m_rightSidesOfRule.emplace_back(tempStr);
	}
}

void GuidingSetsGenerator::WriteResult(std::ofstream& outputFile)
{
	for (size_t i = 0; i < m_nonTerminals.size(); i++)
	{
		outputFile << m_nonTerminals[i] << " - " << m_rightSidesOfRule[i] << " / ";
		size_t index = 0;
		for (const auto& el : m_guidingSets[i])
		{
			index++;
			outputFile << el;
			if (index != m_guidingSets[i].size())
			{
				outputFile << ", ";
			}
		}
		outputFile << std::endl;
	}
}
