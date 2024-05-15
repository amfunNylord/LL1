#pragma once
#include <fstream>

const std::string OUTPUT_FILE_NAME = "grammar.txt";

void RemoveLeftRecursionAndFewWays(std::ifstream& inputFile);