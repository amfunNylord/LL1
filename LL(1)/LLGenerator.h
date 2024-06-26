#pragma once
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <sstream>
#include "Utils.h"

const char YES = '1';
const char NO = '0';
const std::string HEADERS = "�;"
							"������� ������;"
							"������������ �������;"
							"�����;"
							"������;"
							"���������;"
							"������� � ���� ����� ��������� ������;"
							"����� �������\n";
const int TABLE_WIDTH = 8;
const char END_TERMINAL = '=';

using Table = std::vector<std::array<std::string, TABLE_WIDTH>>;

class LLGenerator
{
public:
	Table GetTable() const;
	void FillTable();
	void ReadRulesAndGuidingSets(std::ifstream& inputFile);

private:
	int CalculateCountOfSymbols(const std::string& rightSidesOfRule);

	Table m_table;
	std::vector<std::string> m_nonTerminals;
	std::vector<std::string> m_rightSidesOfRule;
	std::vector<std::set<std::string>> m_guidingSets;
};
