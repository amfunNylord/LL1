#pragma once
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

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

	bool IsGuidingSetsFilled() const;

	void NonTerminalHandle(const std::string& el, const size_t& i);
	void EmptyHandle(const std::string& el, const size_t& guidingSetId, const size_t& elIndex);

	std::vector<std::string> m_nonTerminals;
	std::vector<std::string> m_rightSidesOfRule;
	std::vector<std::set<std::string>> m_guidingSets;
};