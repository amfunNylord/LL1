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
		m_nonTherminals.emplace_back(tempLine);

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

void LLGenerator::FillTable()
{
	int rowNumber = 1;

	// ����� ����� �������
	for (size_t i = 0; i < m_nonTherminals.size(); ++i)
	{
		std::array<std::string, 8> row;
		std::string guidingSymbols;

		for (const auto& symbol : m_guidingSets[i])
			guidingSymbols += symbol + ",";

		if (!guidingSymbols.empty())
			guidingSymbols.pop_back();

		row[0] = std::to_string(rowNumber++);	// �����
		row[1] = m_nonTherminals[i];			// ������� ������
		row[2] = guidingSymbols;				// ������������ �������
		row[3] = NO;							// �����
		row[4] = YES;							// ������
		row[5] = "null";						// ���������
		row[6] = NO;							// ������� � ���� ����� ��������� ������
		row[7] = NO;							// ����� �������

		// �� ���� ������� ����������� ����� ��������� �������� ����, � ��������� ���.
		for (size_t j = i + 1; j < m_nonTherminals.size(); j++)
		{
			std::string currNonTerminal = m_nonTherminals[i];
			if (currNonTerminal == m_nonTherminals[j])
			{
				row[4] = NO;
			}
		}

		m_table.push_back(row);
	}

	// ������ ����� �������
	for (size_t i = 0; i < m_nonTherminals.size(); ++i)
	{
		std::stringstream ss(m_rightSidesOfRule[i]);
		std::string element;
		while (std::getline(ss, element, ' '))
		{
			bool isTerminalSymbol = false;
			bool isEmptySymbol = false;
			bool isNonTerminalSymbol = false;

			if (element == "=")
			{
				isEmptySymbol = true;
			}
			else if (element.size() >= 2 && element[0] == '<' && element[element.size() - 1] == '>')
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

				row[0] = std::to_string(rowNumber++);	// �����
				row[1] = element;						// ������� ������
				row[2] = element;						// ������������ �������
				row[3] = YES;							// �����
				row[4] = YES;							// ������
				row[5] = "null";						// ���������
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
				row[5] = "null";						// ���������
				row[6] = NO;							// ������� � ���� ����� ��������� ������
				row[7] = NO;							// ����� �������

				m_table.push_back(row);
			}

			if (isNonTerminalSymbol)
			{
				std::array<std::string, 8> row;
				std::string guidingSymbols;

				// ��������� ������������ �������� ��� ����� �����������
				for (size_t j = 0; j < m_nonTherminals.size(); ++j)
				{
					if (m_nonTherminals[j] == element)
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
				row[3] = YES;							// �����
				row[4] = YES;							// ������
				row[5] = "null";						// ���������
				row[6] = NO;							// ������� � ���� ����� ��������� ������
				row[7] = NO;							// ����� �������

				m_table.push_back(row);
			}
		}
	}
}