#pragma once
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include "Command.h"


class IdentifierToken;
class Token;

class Parser
{
	std::vector<std::shared_ptr<Token>> tokens;
	std::shared_ptr<Expression> parseValue(const Token& token) const;
	std::shared_ptr<Expression> parseOperator(
		const Token& oper,
		const Token& operand1, const Token& operand2) const;
	std::shared_ptr<Expression> parseExpression(std::vector<std::shared_ptr<Token>>::iterator& token, bool& endReached);
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
