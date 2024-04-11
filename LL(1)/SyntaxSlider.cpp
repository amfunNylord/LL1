#include "SyntaxSlider.h"
#include <fstream>
#include <iostream>

SyntaxSlider::SyntaxSlider(std::ifstream& table, const std::string& program)
	: m_program(program)
{
	int count = 0;
	std::string line;
	bool isFirst = true;
	while (getline(table, line))
	{
		if (isFirst)
		{
			isFirst = false;
			continue;
		}
		
		std::array<std::string, 8> row;
		size_t i = 0;
		int index = 0;
		std::string tempLine;
		while (i < line.size())
		{
			if (line[i] == ';')
			{
				row[index] = tempLine;
				i++;
				index++;
				tempLine.clear();
			}
			tempLine += line[i];
			i++;
		}
		count++;
		m_table.emplace_back(row);
	}
}

void SyntaxSlider::Parse()
{
}
