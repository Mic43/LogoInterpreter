#pragma once
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include "Command.h"


class IdentifierToken;
class Token;

class Parser
{
	std::vector<std::shared_ptr<Token>> tokens;
	std::shared_ptr<Expression> parseExpression(std::vector<std::shared_ptr<Token>>::iterator& token);
	std::vector<std::shared_ptr<Expression>> parseParameterList(std::vector<std::shared_ptr<Token>>::iterator& token);

	void assumeNotLast(std::vector<std::shared_ptr<Token>>::iterator& token);

	// std::shared_ptr<Token> advanceNext( std::vector<std::shared_ptr<Token>>::iterator& token)
	// {
	// 	auto t = *token;
	// 	++token;
	// 	return t;
	// }
	// std::shared_ptr<Token> forceNext(std::vector<std::shared_ptr<Token>>::iterator& token)
	// {
	// 	auto t = *token;
	// 	++token;
	// 	return t;
	// }
	std::shared_ptr<Command> parse(std::vector<std::shared_ptr<Token>>::iterator& token);
public:


	explicit Parser(std::vector<std::shared_ptr<Token>>& tokens)
		: tokens(tokens)
	{
	}

	std::shared_ptr<Command> parse();	
};
