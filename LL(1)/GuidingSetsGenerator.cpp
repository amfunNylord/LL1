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

bool GuidingSetsGenerator::IsGuidingSetsFilled() const
{
	bool isFilled = true;
	for (size_t i = 0; i < m_guidingSets.size(); i++)
	{
		if (m_guidingSets[i].empty())
		{
			isFilled = false;
			break;
		}
	}
	return isFilled;
}
void GuidingSetsGenerator::NonTerminalHandle(const std::string& el, const size_t& i)
{
	std::set<std::string> set;
	bool isOkay = true;
	for (size_t j = 0; j < m_guidingSets.size(); j++)
	{
		if (m_nonTerminals[j] == el)
		{
			if (m_guidingSets[j].empty())
			{
				isOkay = false;
				break;
			}
			set.insert(m_guidingSets[j].begin(), m_guidingSets[j].end());
		}
	}
	if (isOkay)
	{
		m_guidingSets[i].insert(set.begin(), set.end());
	}
}
void GuidingSetsGenerator::EmptyHandle(const std::string& el, const size_t& guidingSetId, const size_t& elIndex)
{
	std::set<std::string> set;
	for (size_t j = 0; j < m_rightSidesOfRule.size(); j++)
	{
		std::string rightSide = m_rightSidesOfRule[j];

		while (!rightSide.empty())
		{
			std::string element = GetEl(rightSide);
			RemoveEl(rightSide, element);
			if (!rightSide.empty())
			{
				rightSide.erase(0, 1);
			}
			if (m_nonTerminals[j] == element)
			{
				break;
			}
			if (element == m_nonTerminals[elIndex] )
			{
				std::string nextElement = GetEl(rightSide);
				if (nextElement.empty())
				{
					EmptyHandle(m_nonTerminals[j], j, elIndex);
				}
				else if (IsNonTerminal(nextElement))
				{
					std::set<std::string> s;
					bool isOkay = true;
					for (size_t k = 0; k < m_guidingSets.size(); k++)
					{
						if (m_nonTerminals[k] == nextElement)
						{
							if (m_guidingSets[k].empty())
							{
								isOkay = false;
								break;
							}
							s.insert(m_guidingSets[k].begin(), m_guidingSets[k].end());
						}
					}
					if (isOkay)
					{
						set.insert(s.begin(), s.end());
					}
				}
				else
				{
					set.insert(nextElement);
				}
				break;
			}
		}
	}
	m_guidingSets[guidingSetId].insert(set.begin(), set.end());
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

	while (!IsGuidingSetsFilled())
	{
		for (size_t i = 0; i < m_guidingSets.size(); i++)
		{
			std::string el = GetEl(m_rightSidesOfRule[i]);
			if (el == "e")
			{
				std::string searchingTerminal = m_nonTerminals[i];
				std::set<std::string> set;
				for (size_t j = 0; j < m_rightSidesOfRule.size(); j++)
				{
					std::string rightSide = m_rightSidesOfRule[j];
					while (!rightSide.empty())
					{
						std::string element = GetEl(rightSide);
						RemoveEl(rightSide, element);

						if (!rightSide.empty())
						{
							rightSide.erase(0, 1);
						}
						if (m_nonTerminals[j] == element)
						{
							break;
						}
						if (element == searchingTerminal)
						{
							std::string nextElement = GetEl(rightSide);
							if (nextElement.empty())
							{
								EmptyHandle(m_nonTerminals[j], i, j);
							}
							else if (IsNonTerminal(nextElement))
							{
								std::set<std::string> s;
								bool isOkay = true;
								for (size_t k = 0; k < m_guidingSets.size(); k++)
								{
									if (m_nonTerminals[k] == nextElement)
									{
										if (m_guidingSets[k].empty())
										{
											isOkay = false;
											break;
										}
										s.insert(m_guidingSets[k].begin(), m_guidingSets[k].end());
									}
								}
								if (isOkay)
								{
									set.insert(s.begin(), s.end());
								}
							}
							else
							{
								set.insert(nextElement);
							}
							break;
						}
					}
				}
				m_guidingSets[i].insert(set.begin(), set.end());
			} 
			else if (IsNonTerminal(el))
			{
				NonTerminalHandle(el, i);
			}
		}
	}

	return;
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