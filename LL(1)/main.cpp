#include "LLGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>

const char YES = '1';
const char NO = '0';
const std::string HEADERS = "№;"
							"Текущий символ;"
							"Направляющие символы;"
							"Сдвиг;"
							"Ошибка;"
							"Указатель;"
							"Занести в Стек адрес следующей строки;"
							"Конец разбора\n";

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

Table FillTable(const LLGenerator& generator)
{
	const auto& nonTerminals = generator.GetNonThermals();
	const auto& guidingSets = generator.GetGuidingSets();
	const auto& rightSides = generator.GetRightSidesOfRule();
	Table table;

	for (size_t i = 0; i < nonTerminals.size(); ++i)
	{
		std::array<std::string, TABLE_WIDTH> row;
		std::string guidingSymbols;

		for (const auto& symbol : guidingSets[i])
			guidingSymbols += symbol + ",";

		if (!guidingSymbols.empty())
			guidingSymbols.pop_back();

		for (size_t j = 3; j < TABLE_WIDTH; ++j)
			row[j] = NO;

		row[0] = std::to_string(i + 1);				// Номер
		row[1] = nonTerminals[i];					// Текущий символ
		row[2] = guidingSymbols;					// Направляющие символы
		row[4] = YES;								// Ошибка
		row[5] = "null";							// Указатель

		table.push_back(row);
	}

	return table;
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

	Table table = FillTable(generator);

	 if (!WriteOutputFile(table, outputFileName))
		return -1;

	return 0;
}