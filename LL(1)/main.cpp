#include "LLGenerator.h"
#include <fstream>
#include <iostream>

int main()
{
	LLGenerator generator;
	std::ifstream input("grammar.txt");
	generator.ReadRulesAndGuidingSets(input);

	int l;
	std::cin >> l;
	return 0;
}