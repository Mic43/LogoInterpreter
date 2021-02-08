#pragma once
#include <string>
#include <vector>
#include "Token.h"


class Scanner
{
	std::string input;
public:

	
	explicit Scanner(const std::string& input)
		: input(input)
	{
	}

	std::vector<Token> tokenize();
};
