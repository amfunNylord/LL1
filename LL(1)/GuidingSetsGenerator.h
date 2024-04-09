#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Utils.h"

class GuidingSetsGenerator
{
public:
	void Fill(const std::string& outputFileName);
	void Generate();
	void ReadRules(std::ifstream& inputFile);
	void EliminateLeftRecursion();

	std::vector<std::string> GetNonTerminals() const;
	std::vector<std::string> GetRightSidesOfRule() const;
	std::vector<std::string> GetGuidingSets() const;

private:
	std::vector<std::string> m_nonTerminals;
	std::vector<std::string> m_rightSidesOfRule;
	std::vector<std::string> m_guidingSets;
};
