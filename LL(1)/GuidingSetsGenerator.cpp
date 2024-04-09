#include "GuidingSetsGenerator.h"

std::vector<std::string> GuidingSetsGenerator::GetNonTerminals() const
{
	return m_nonTerminals;
}

std::vector<std::string> GuidingSetsGenerator::GetRightSidesOfRule() const
{
	return m_rightSidesOfRule;
}

std::vector<std::string> GuidingSetsGenerator::GetGuidingSets() const
{
	return m_guidingSets;
}

void GuidingSetsGenerator::Fill(const std::string& outputFileName)
{
	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		std::cerr << "Не удалось открыть файл для записи!" << std::endl;
		return;
	}

	if (m_nonTerminals.size() != m_rightSidesOfRule.size() || m_nonTerminals.size() != m_guidingSets.size())
	{
		std::cerr << "Размеры данных не совпадают!" << std::endl;
		return;
	}

	for (size_t i = 0; i < m_nonTerminals.size(); ++i)
	{
		outputFile << m_nonTerminals[i] << " - " << m_rightSidesOfRule[i] << " / " << m_guidingSets[i] << std::endl;
	}

	outputFile.close();
}

void GuidingSetsGenerator::Generate()
{
	for (size_t i = 0; i < m_nonTerminals.size(); ++i)
    {
		std::string currentNonTerminal = m_nonTerminals[i];
		std::string rightSide = m_rightSidesOfRule[i];
		std::stringstream ss(rightSide);
		std::string element;
		std::getline(ss, element, ' ');

		bool isTerminalSymbol = false;
		bool isEmptySymbol = false;
		bool isNonTerminalSymbol = false;

		if (element == "e")
		{
			isEmptySymbol = true;
		}
		else if (IsNonTerminal(element))
		{
			isNonTerminalSymbol = true;
		}
		else
		{
			isTerminalSymbol = true;
		}

		if (isTerminalSymbol)
		{
			m_guidingSets.emplace_back(element);
		}
		if (isEmptySymbol)
		{
			m_guidingSets.emplace_back("Пустой символ");
		}
		if (isNonTerminalSymbol)
		{
			m_guidingSets.emplace_back("Не терминальный символ");
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

	EliminateLeftRecursion();
}

void GuidingSetsGenerator::EliminateLeftRecursion()
{

}