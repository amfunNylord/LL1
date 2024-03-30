#include "LLGenerator.h"
#include <fstream>
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");

	LLGenerator generator;
	std::ifstream input("../GrammarExamples/grammar1.txt");
	generator.ReadRulesAndGuidingSets(input);

	if (!input.is_open())
	{
		std::cerr << "������ �������� �����!\n";
		return -1;
	}

	std::vector<std::string> nonTerminals = generator.GetNonThermals();
	std::cout << "�� ���������:\n";
	for (const auto& nonTerminal : nonTerminals)
	{
		std::cout << nonTerminal << '\n';
	}

	std::vector<std::string> rightSidesOfRule = generator.GetRightSidesOfRule();
	std::cout << "������ ����� ������:\n";
	for (const auto& rightSide : rightSidesOfRule)
	{
		std::cout << rightSide << '\n';
	}

	std::vector<std::set<std::string>> guidingSets = generator.GetGuidingSets();
	std::cout << "������������ ���������:\n";
	for (const auto& guidingSet : guidingSets)
	{
		for (const auto& element : guidingSet)
		{
			std::cout << element << ", ";
		}
		std::cout << '\n';
	}

	return 0;
}