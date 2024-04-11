#include "LLGenerator.h"
#include "GuidingSetsGenerator.h"
#include "SyntaxSlider.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool ReadInputFile(LLGenerator& generator, const std::string& inputFileName)
{
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		std::cerr << "������ �������� ����� ��� ������!\n";
		return false;
	}

	generator.ReadRulesAndGuidingSets(inputFile);
	inputFile.close();
	return true;
}

bool WriteOutputFile(const Table& table, const std::string& outputFileName)
{
	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		std::cerr << "������ �������� ����� ��� ������!\n";
		return false;
	}

	outputFile << HEADERS;
	for (const auto& row : table)
	{
		std::copy(row.begin(), row.end(), std::ostream_iterator<std::string>(outputFile, ";"));
		outputFile << "\n";
	}

	outputFile.close();
	return true;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	/* LLGenerator generator;

	std::string inputFileName = "../GrammarExamples/grammar1.txt";
	std::string outputFileName = "output.csv";

    if (!ReadInputFile(generator, inputFileName))
		return -1;

	generator.FillTable();
	Table table = generator.GetTable();

	if (!WriteOutputFile(table, outputFileName))
		return -1;*/

	/*GuidingSetsGenerator gen;
	std::string inputFileName = "../GuidingSetsExamples/grammar1.txt";
	std::ifstream inputFile(inputFileName);
	gen.ReadRules(inputFile);
	gen.Generate();*/

	std::string program;
	std::cout << "Enter program: ";
	std::cin >> program;
	
	std::ifstream inputTable("output.csv");
	SyntaxSlider syntaxSlider(inputTable, program);

	return 0;
}