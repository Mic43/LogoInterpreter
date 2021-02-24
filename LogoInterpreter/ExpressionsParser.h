#pragma once
#include <vector>

#include "Expression.h"
#include "Token.h"

class ExpressionsParser
{
	std::vector<Token> input;
	std::vector<Token>::const_iterator currentToken;
	Token next();
	void advance();
	void throwParsingError() const;
	bool hasNext() const
	{
		return currentToken != input.end();
	}
	std::shared_ptr<Expression> parseValue(const Token& token) const;
	std::shared_ptr<Expression> parseSymbol();
	std::shared_ptr<Expression> parse(int precedence);


public:

	explicit ExpressionsParser(std::vector<Token> input)
		: input(std::move(input))
	{
	}

	std::shared_ptr<Expression> parse();
};

