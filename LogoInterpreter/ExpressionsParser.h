#pragma once
#include <vector>

#include "Expression.h"
#include "Token.h"

class ExpressionsParser
{
	std::vector<Token> input;
	std::vector<Token>::const_iterator currentToken;
	int currentLineNumber;

public:
	[[nodiscard]] int get_current_line_number() const
	{
		return currentLineNumber;
	}

private:
	Token current() const;
	void advance();
	void throwParsingError() const;
	bool hasNext() const
	{
		return currentToken != input.end();
	}
	std::shared_ptr<Expression> parseValue(const Token& token) const;
	std::shared_ptr<Expression> parseSymbol();
	std::shared_ptr<Expression> parse(int precedence);


	std::vector<Token>::const_iterator& moveToNextSignificant();

public:

	explicit ExpressionsParser(std::vector<Token> input,int currentLineNumber)
		: input(std::move(input)), currentLineNumber(currentLineNumber)
	{
	}

	std::shared_ptr<Expression> parse();
};

