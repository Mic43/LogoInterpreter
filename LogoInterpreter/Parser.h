#pragma once
#include <string>
#include <vector>


#include "Command.h"
#include "Scanner.h"

class Parser
{
	std::vector<Token> tokens;
	//parseInternal(std::vector<Token>)
public:

	explicit Parser(const std::vector<Token>& tokens)
		: tokens(tokens)
	{
	}
	Command& parse();	
};
