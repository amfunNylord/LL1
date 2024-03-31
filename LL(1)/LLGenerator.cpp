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

Table LLGenerator::FillTable() const
{
	Table table;
	for (size_t i = 0; i < m_nonTherminals.size(); ++i)
	{
		std::array<std::string, 8> row;
		std::string guidingSymbols;

		for (const auto& symbol : m_guidingSets[i])
			guidingSymbols += symbol + ",";

		if (!guidingSymbols.empty())
			guidingSymbols.pop_back();

		row[0] = std::to_string(i + 1);			// �����
		row[1] = m_nonTherminals[i];			// ������� ������
		row[2] = guidingSymbols;				// ������������ �������
		row[3] = NO;							// �����
		row[4] = YES;							// ������
		row[5] = "null";						// ���������
		row[6] = NO;							// ������� � ���� ����� ��������� ������
		row[7] = NO;							// ����� �������

		for (size_t j = i + 1; j < m_nonTherminals.size(); j++)
		{
			std::string currNonTerminal = m_nonTherminals[i];
			if (currNonTerminal == m_nonTherminals[j])
			{
				row[4] = NO;
			}
		}

		table.push_back(row);
	}

	return table;
}