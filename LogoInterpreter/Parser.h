#pragma once
#include <string>
#include <vector>
#include "Command.h"


class IdentifierToken;
class Token;

class Parser
{
	std::vector<Token*> tokens;
	
	std::shared_ptr<Command> parse(std::vector<Token*>::iterator& token);
public:
	
	explicit Parser(const std::vector<Token*>& tokens)
		: tokens(tokens)
	{
	}

	std::vector<Expression*> parseParameterList(const std::vector<Token*>::iterator& token);
	std::shared_ptr<Command> parse();	
};
