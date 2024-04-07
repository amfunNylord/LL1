#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class GuidingSetsGenerator
{
public:
	void Fill();
	void Generate();
	void ReadRules(std::ifstream& inputFile);

private:
	std::vector<std::string> m_nonTherminals;
	std::vector<std::string> m_rightSidesOfRule;
	std::vector<std::vector<std::string>> m_table;
};
