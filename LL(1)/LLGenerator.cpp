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
		std::stringstream ss(line);
		std::string tempLine;

		std::getline(ss, tempLine, '-');
		Trim(tempLine);
		m_nonTerminals.emplace_back(tempLine);

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

int LLGenerator::CalculateCountOfSymbols(const std::string& rightSidesOfRule)
{
	std::stringstream ss(rightSidesOfRule);
	std::string element;
	int index = 0;
	while (std::getline(ss, element, ' '))
	{
		if (element == "|")
		{
			continue;
		}
		index++;
	}
	return index;
}

void LLGenerator::FillTable()
{
	int rowNumber = 1;

	// ����� ����� �������
	for (size_t i = 0; i < m_nonTerminals.size(); ++i)
	{
		std::array<std::string, 8> row;
		std::string guidingSymbols;

		for (const auto& symbol : m_guidingSets[i])
			guidingSymbols += symbol + ",";

		if (!guidingSymbols.empty())
			guidingSymbols.pop_back();

		row[0] = std::to_string(rowNumber++);	// �����
		row[1] = m_nonTerminals[i];			// ������� ������
		row[2] = guidingSymbols;				// ������������ �������
		row[3] = NO;							// �����
		row[4] = YES;							// ������
		row[5] = "";							// ���������
		row[6] = NO;							// ������� � ���� ����� ��������� ������
		row[7] = NO;							// ����� �������

		// �� ���� ������� ����������� ����� ��������� �������� ����, � ��������� ���.
		for (size_t j = i + 1; j < m_nonTerminals.size(); j++)
		{
			std::string currNonTerminal = m_nonTerminals[i];
			if (currNonTerminal == m_nonTerminals[j])
			{
				row[4] = NO;
			}
		}

		m_table.push_back(row);
	}


	if (m_rightSidesOfRule[0][m_rightSidesOfRule[0].size() - 1] != END_TERMINAL)
	{
		
		m_rightSidesOfRule[0] += " " + END_TERMINAL;
	}

	// ������ ����� �������
	for (size_t i = 0; i < m_nonTerminals.size(); ++i)
	{
		std::stringstream ss(m_rightSidesOfRule[i]);
		std::string element;
		int countOfSymbols = CalculateCountOfSymbols(m_rightSidesOfRule[i]);
		int index = 0;
		while (std::getline(ss, element, ' '))
		{
			index++;
			bool isTerminalSymbol = false;
			bool isEmptySymbol = false;
			bool isNonTerminalSymbol = false;

			if (element == "=")
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
				std::array<std::string, 8> row;

				std::string pointer;
				if (index == countOfSymbols)
				{
					pointer = "NULL";
				}

				row[0] = std::to_string(rowNumber++);	// �����
				row[1] = element;						// ������� ������
				row[2] = element;						// ������������ �������
				row[3] = YES;							// �����
				row[4] = YES;							// ������
				row[5] = pointer;					    // ���������
				row[6] = NO;							// ������� � ���� ����� ��������� ������
				row[7] = NO;							// ����� �������

				m_table.push_back(row);
			}

			if (isEmptySymbol) // ������ ������ ����� ��� =
			{
				std::array<std::string, 8> row;

				row[0] = std::to_string(rowNumber++);	// �����
				row[1] = element;						// ������� ������
				row[2] = element;						// ������������ �������
				row[3] = NO;							// �����
				row[4] = YES;							// ������
				row[5] = "NULL";						// ���������
				row[6] = NO;							// ������� � ���� ����� ��������� ������
				row[7] = YES;							// ����� �������

				m_table.push_back(row);
			}

			if (isNonTerminalSymbol)
			{
				std::array<std::string, 8> row;
				std::string guidingSymbols;

				// ��������� ������������ �������� ��� ����� �����������
				for (size_t j = 0; j < m_nonTerminals.size(); ++j)
				{
					if (m_nonTerminals[j] == element)
					{
						for (const auto& symbol : m_guidingSets[j])
						{
							guidingSymbols += symbol + ",";
						}
					}
				}
				if (!guidingSymbols.empty())
				{
					guidingSymbols.pop_back();
				}

				row[0] = std::to_string(rowNumber++);	// �����
				row[1] = element;						// ������� ������
				row[2] = guidingSymbols;				// ������������ �������
				row[3] = NO;							// �����
				row[4] = YES;							// ������
				row[5] = "null";						// ���������
				row[6] = (index == countOfSymbols) ? NO : YES; // ������� � ���� ����� ��������� ������							
				row[7] = NO;							// ����� �������

				m_table.push_back(row);
			}

		}
	}

	// ���������
	// ����� �����
	int index = int(m_nonTerminals.size()) + 1;
	for (size_t i = 0; i < m_nonTerminals.size(); ++i)
	{
		std::stringstream ss(m_rightSidesOfRule[i]);
		std::string element;
		int count = 0;
		while (std::getline(ss, element, ' '))
		{
			count++;
		}
		m_table[i][5] = std::to_string(index);
		index += count;
	}

	// ������ �����
	for (int i = int(m_nonTerminals.size()); i < rowNumber - 1; i++)
	{
		if (IsNonTerminal(m_table[i][1]))
		{
			for (size_t j = 0; j < m_nonTerminals.size(); j++)
			{
				if (m_table[j][1] == m_table[i][1])
				{
					m_table[i][5] = m_table[j][0];
					break;
				}
			}
		}
		else if (m_table[i][1] == "e")
		{
			m_table[i][5] = "NULL";
		}
		else if (m_table[i][5] != "NULL")
		{
			if (m_table[i][7] == "1")
			{
				continue;
			}
			m_table[i][5] = std::to_string(i + 2); 
		}
	}
}