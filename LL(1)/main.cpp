#include "LLGenerator.h"
#include <iostream>
#include <fstream>
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
	setlocale(LC_ALL, "Russian");
	LLGenerator generator;

	std::string inputFileName = "../GrammarExamples/grammar1.txt";
	std::string outputFileName = "output.csv";

    if (!ReadInputFile(generator, inputFileName))
		return -1;

	Table table = generator.FillTable();

	if (!WriteOutputFile(table, outputFileName))
		return -1;

	return 0;
}