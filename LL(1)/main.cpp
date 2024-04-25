#include "GuidingSetsGenerator.h"
#include "LLGenerator.h"
#include "SyntaxSlider.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool ReadInputFile(LLGenerator& generator, const std::string& inputFileName)
{
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		std::cerr << "Ошибка открытия файла для чтения!\n";
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
		std::cerr << "Ошибка открытия файла для записи!\n";
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
	GuidingSetsGenerator guidingSetsGenerator;
	std::string inputFileName = "../GuidingSetsExamples/grammar1.txt";
	std::ifstream inputFile(inputFileName);
	guidingSetsGenerator.ReadRules(inputFile);
	std::string outputFileName = "output.txt";
	std::ofstream outputFile(outputFileName);
	guidingSetsGenerator.Generate();
	guidingSetsGenerator.WriteResult(outputFile);
	outputFile.close();

	setlocale(LC_ALL, "Russian");
	LLGenerator generator;

	inputFileName = "output.txt";
	outputFileName = "output2.csv";

	if (!ReadInputFile(generator, inputFileName))
		return -1;

	generator.FillTable();
	Table table = generator.GetTable();

	if (!WriteOutputFile(table, outputFileName))
		return -1;

	std::string program;
	std::cout << "Enter program: ";
	getline(std::cin, program);

	std::ifstream inputTable("output2.csv");
	SyntaxSlider syntaxSlider(inputTable, program);
	syntaxSlider.Parse();

	return 0;
}