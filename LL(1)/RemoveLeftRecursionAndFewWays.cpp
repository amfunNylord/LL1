#include "RemoveLeftRecursionAndFewWays.h"
#include <vector>
#include <string>
#include <sstream>
#include "Utils.h"

void CheckFirstRule(std::vector<std::string>& rules)
{
	std::string firstRule = rules[0];
	std::stringstream ss(firstRule);
	std::string tempStr;
	std::getline(ss, tempStr, '-');
	
	std::string nonTerminal = tempStr;
	
	std::vector<std::string> ways;
	while (std::getline(ss, tempStr, '|'))
	{
		ways.emplace_back(tempStr);
	}

	if (ways.size() > 1)
	{
		Trim(nonTerminal);
		std::string newNonTerminal;
		for (size_t i = 0; i < nonTerminal.size(); i++)
		{
			if (nonTerminal[i] == '>')
			{
				newNonTerminal += '0';
			}
			newNonTerminal += nonTerminal[i];
		}
		std::string newRule = newNonTerminal + " - " + nonTerminal + " =";
		rules.insert(rules.begin(), newRule);
	}

	return;
}

void RemoveLeftRecursion(std::string& rule)
{
	std::stringstream ss(rule);
	std::string nonTerminal;
	std::getline(ss, nonTerminal, '-');
	Trim(nonTerminal);

	std::string way;
	std::getline(ss, way, '|');
	Trim(way);

	std::string firstSymbolWay;

	int index = 0;
	while (way[index] != ' ')
	{
		firstSymbolWay += way[index];
		index++;
	}

	if (nonTerminal == firstSymbolWay)
	{
		
	}
}

void RemoveLeftRecursionAndFewWays(std::ifstream& inputFile)
{
	std::vector<std::string> rules;
	std::string line;
	while (getline(inputFile, line))
	{
		rules.emplace_back(line);
	}
	CheckFirstRule(rules);

	for (size_t i = 0; i < rules.size(); i++)
	{
		RemoveLeftRecursion(rules[i]);
	}
}
