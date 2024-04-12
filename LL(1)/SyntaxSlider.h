#pragma once
#include "Utils.h"
#include <array>
#include <vector>

using Table = std::vector<std::array<std::string, 8>>;

class SyntaxSlider
{
public:
	SyntaxSlider(std::ifstream& table, const std::string& program);
	void Parse();

private:
	bool IsInGuidingSets(const std::string& str, const std::string& terminal);

	std::string m_program;
	Table m_table;
};
