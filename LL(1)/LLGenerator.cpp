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

	// Левая часть правила
	for (size_t i = 0; i < m_nonTherminals.size(); ++i)
	{
		std::array<std::string, 8> row;
		std::string guidingSymbols;

		for (const auto& symbol : m_guidingSets[i])
			guidingSymbols += symbol + ",";

		if (!guidingSymbols.empty())
			guidingSymbols.pop_back();

		row[0] = std::to_string(rowNumber++);	// Номер
		row[1] = m_nonTherminals[i];			// Текущий символ
		row[2] = guidingSymbols;				// Направляющие символы
		row[3] = NO;							// Сдвиг
		row[4] = YES;							// Ошибка
		row[5] = "null";						// Указатель
		row[6] = NO;							// Занести в Стек адрес следующей строки
		row[7] = NO;							// Конец разбора

		// Во всех строках альтернатив кроме последней ставится «нет», в последнюю «Да».
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

	// Правая часть правила
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

				row[0] = std::to_string(rowNumber++);	// Номер
				row[1] = element;						// Текущий символ
				row[2] = element;						// Направляющие символы
				row[3] = YES;							// Сдвиг
				row[4] = YES;							// Ошибка
				row[5] = "null";						// Указатель
				row[6] = NO;							// Занести в Стек адрес следующей строки
				row[7] = NO;							// Конец разбора

				m_table.push_back(row);
			}

			if (isEmptySymbol) // Пустой символ пишем как =
			{
				std::array<std::string, 8> row;

				row[0] = std::to_string(rowNumber++);	// Номер
				row[1] = element;						// Текущий символ
				row[2] = element;						// Направляющие символы
				row[3] = NO;							// Сдвиг
				row[4] = YES;							// Ошибка
				row[5] = "null";						// Указатель
				row[6] = NO;							// Занести в Стек адрес следующей строки
				row[7] = NO;							// Конец разбора

				m_table.push_back(row);
			}

			if (isNonTerminalSymbol)
			{
				std::array<std::string, 8> row;
				std::string guidingSymbols;

				// Множество направляющих символов для этого нетерминала
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

				row[0] = std::to_string(rowNumber++);	// Номер
				row[1] = element;						// Текущий символ
				row[2] = guidingSymbols;				// Направляющие символы
				row[3] = YES;							// Сдвиг
				row[4] = YES;							// Ошибка
				row[5] = "null";						// Указатель
				row[6] = NO;							// Занести в Стек адрес следующей строки
				row[7] = NO;							// Конец разбора

				m_table.push_back(row);
			}
		}
	}
}