#pragma once
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include "Commands.h"
#include "Token.h"


class IdentifierToken;
class Token;

class CommadsParser
{
	int currentLineNumber;
	std::vector<Token> tokens;
	std::vector<Token>::iterator findExpressionEnd(const std::vector<Token>::iterator& token);
	// std::shared_ptr<Expression> parseValue(const Token& token) const;
	// std::shared_ptr<Expression> parseOperator(
	// 	const Token& oper,
	// 	const Token& operand1, const Token& operand2) const;
	std::shared_ptr<Expression> parseExpression(std::vector<Token>::iterator& token, bool& endReached);
	std::vector<std::shared_ptr<Expression>> parseParameterList(std::vector<Token>::iterator& token);

	void assumeNotEnd(std::vector<Token>::iterator& token);

	bool isEnd(std::vector<Token>::iterator& token)
	{
		return token == tokens.end();
	}
	bool hasNext(std::vector<Token>::iterator& tokenIt)
	{
		return (tokenIt + 1) != tokens.end();
	}
	
	void throwParsingError(const std::string& message) const;
	void assumeNextIs(std::vector<Token>::iterator& token, TokenType tt);
	std::vector<Token>::iterator& moveToNextSignificant(std::vector<Token>::iterator& token);
	std::vector<Token>::iterator& moveToNextSignificant(std::vector<Token>::iterator& token, int* currentLineNumber);
	std::shared_ptr<Command> parse(std::vector<Token>::iterator& token, std::string blockName);
public:


	explicit CommadsParser(std::vector<Token>& tokens)
		: currentLineNumber(0), tokens(tokens)
	{
	}

	std::shared_ptr<Command> parse();
};
