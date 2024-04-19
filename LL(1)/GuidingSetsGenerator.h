#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <set>
#include "Utils.h"

class GuidingSetsGenerator
{
public:
	void Generate();
	void ReadRules(std::ifstream& inputFile);
	void WriteResult(std::ofstream& outputFile);

	std::vector<std::string> GetNonTerminals() const;
	std::vector<std::string> GetRightSidesOfRule() const;
	std::vector<std::set<std::string>> GetGuidingSets() const;

private:
	std::string GetEl(const std::string& line);
	void RemoveEl(std::string& line, const std::string& el);
	void GetGuidingSetsOfNonTerminal(size_t row);
	void GetGuidingSetsForEmpty(const std::string& nonTerminal, const size_t& row);
	std::set<std::string> GetGuidingSet(const std::string& nonTerminal);

	std::vector<std::string> m_nonTerminals;
	std::vector<std::string> m_rightSidesOfRule;
	std::vector<std::set<std::string>> m_guidingSets;
};
