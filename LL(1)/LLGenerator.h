#pragma once
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <sstream>
#include "StringTrim.cpp"

const int TABLE_WIDTH = 8;

using Table = std::vector<std::array<std::string, TABLE_WIDTH>>;

class LLGenerator
{
public:
	Table GetTable() const;
	void ReadRulesAndGuidingSets(std::ifstream& inputFile);
	std::vector<std::string> GetNonThermals() const;
	std::vector<std::string> GetRightSidesOfRule() const;
	std::vector<std::set<std::string>> GetGuidingSets() const;

private:
	Table m_table;
	std::vector<std::string> m_nonThermals;
	std::vector<std::string> m_rightSidesOfRule;
	std::vector<std::set<std::string>> m_guidingSets;
};
