#include "LLGenerator.h"
#include "GuidingSetsGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string inputFileName = "../GuidingSetsExamples/grammar1.txt";
	std::string outputFileName = "guidingSets.txt";
	GuidingSetsGenerator generator;

	std::ifstream inputFile(inputFileName);
	generator.ReadRules(inputFile);
	generator.Generate();
	generator.Fill(outputFileName);

	auto nonTerminals = generator.GetNonTerminals();
	auto rightSidesOfRule = generator.GetRightSidesOfRule();
	auto guidingSets = generator.GetGuidingSets();

    std::cout << "Список нетерминальных символов:" << std::endl;
	for (size_t i = 0; i < nonTerminals.size(); ++i)
	{
		std::cout << i + 1 << ". " << nonTerminals[i] << std::endl;
	}

	std::cout << "Правые части правил:" << std::endl;
	for (size_t i = 0; i < rightSidesOfRule.size(); ++i)
	{
		std::cout << i + 1 << ". ";
		for (const auto& symbol : rightSidesOfRule[i])
		{
			std::cout << symbol;
		}
		std::cout << std::endl;
	}

	std::cout << "Направляющие множества:" << std::endl;
	for (size_t i = 0; i < guidingSets.size(); ++i)
	{
		std::cout << i + 1 << ". " << guidingSets[i] << std::endl;
	}

	return 0;
}