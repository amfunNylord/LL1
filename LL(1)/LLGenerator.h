#pragma once
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <sstream>
#include "StringTrim.cpp"

const char YES = '1';
const char NO = '0';
const std::string HEADERS = "№;"
							"Текущий символ;"
							"Направляющие символы;"
							"Сдвиг;"
							"Ошибка;"
							"Указатель;"
							"Занести в Стек адрес следующей строки;"
							"Конец разбора\n";
const int TABLE_WIDTH = 8;

using Table = std::vector<std::array<std::string, TABLE_WIDTH>>;

class LLGenerator
{
public:
	Table GetTable() const;
	void FillTable();
	void ReadRulesAndGuidingSets(std::ifstream& inputFile);

private:
	bool IsNonTherminal(const std::string& el);
	int CalculateCountOfSymbols(const std::string& rightSidesOfRule);

	Table m_table;
	std::vector<std::string> m_nonTherminals;
	std::vector<std::string> m_rightSidesOfRule;
	std::vector<std::set<std::string>> m_guidingSets;
};
