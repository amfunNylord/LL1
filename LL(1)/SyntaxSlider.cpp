#include "SyntaxSlider.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <set>

// program = ( id * id + - id * id ) / нужно вводить через пробел
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
	std::stack<int> s;
	std::vector<std::string> program;
	std::stringstream ss(m_program);
	std::string terminal;
	while (ss >> terminal)
	{
		program.emplace_back(terminal);
	}
	int currIndex = 1;

	std::string currTerminal;
	if (program.empty())
	{
		currTerminal = "=";
	}
	else
	{
		currTerminal = program[0];
	}

	while (true)
	{
		if (s.empty() && program.empty() && m_table[currIndex - 1][7] == "1")
		{
			std::cout << "GOOD" << std::endl;
			break;
		}

		if (!IsInGuidingSets(m_table[currIndex - 1][2], currTerminal))
		{
			if (m_table[currIndex - 1][2] == "e")
			{
				if (!s.empty())
				{
					currIndex = s.top();
					s.pop();
					continue;
				}
			}
			if (m_table[currIndex - 1][4] == "1")
			{
				std::cout << "ERROR" << std::endl;
				break;
			}
			else
			{
				currIndex++;
				continue;
			}
		}

		// 3 - сдвиг
		// 4 - ошибка
		// 5 - указатель
		// 6 - в стек
		// 7 - конец2
		if (m_table[currIndex - 1][3] == "1")
		{
			program.erase(program.begin());
			if (program.empty())
			{
				currTerminal = "=";
			}
			else
			{
				currTerminal = program[0];
			}
		}
		if (m_table[currIndex - 1][6] == "1")
		{
			s.push(currIndex + 1);
		}
		if (m_table[currIndex - 1][5] != "NULL")
		{
			currIndex = std::stoi(m_table[currIndex - 1][5]);
		}
		else
		{
			if (!s.empty())
			{
				currIndex = s.top();
				s.pop();
			}
		}

	}
}

bool SyntaxSlider::IsInGuidingSets(const std::string& str, const std::string& terminal)
{
	std::set<std::string> guidingSet;

	size_t i = 0;
	std::string tempLine;
	while (i < str.size())
	{
		if (str[i] == ',')
		{
			guidingSet.insert(tempLine);
			tempLine.clear();
			i++;
		}
		tempLine += str[i];
		i++;
		if (i == str.size())
		{
			guidingSet.insert(tempLine);
		}
	}
	return guidingSet.find(terminal) != guidingSet.end();
}
