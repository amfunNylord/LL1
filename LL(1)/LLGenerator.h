#pragma once
#include <array>
#include <vector>
#include <string>
#include <fstream>

const int TABLE_WIDTH = 8;

using Table = std::vector<std::array<std::string, TABLE_WIDTH>>;

class LLGenerator
{
public:
	Table GetTable() const;
	void ReadRulesAndGuidingSets(std::ifstream& inputFile);

private:
	Table m_table;
	std::vector<std::string> m_nonThermals;
	std::vector<std::string> m_rightSidesOfRule;
	std::vector<std::string> m_guidingSets;
};
