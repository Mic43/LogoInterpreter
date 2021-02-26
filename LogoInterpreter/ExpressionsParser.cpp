#include "ExpressionsParser.h"
#include <exception>
#include <stdexcept>

#include "BinaryOperatorsTable.h"

using namespace std;

Token ExpressionsParser::current() const
{
	return *currentToken;
}

void ExpressionsParser::advance()
{
	moveToNextSignificant();
}

std::vector<Token>::const_iterator& ExpressionsParser::moveToNextSignificant()
{
	do
	{
		++currentToken;
		if (!hasNext() || currentToken->get_type() != TokenType::EndLine)
			break;

		if (currentToken->get_type() == TokenType::EndLine)
		{
			currentLineNumber++;
		}
	}
	while (true);
	return currentToken;
}

void ExpressionsParser::throwParsingError() const
{
	throw runtime_error("Invalid expression, line: " + std::to_string(currentLineNumber));
}

std::shared_ptr<Expression> ExpressionsParser::parseSymbol()
{
	if(current().get_type() == TokenType::OpenPar)
	{
		advance();
		auto res = parse(0);
		if (current().get_type() != TokenType::ClosePar)
			throwParsingError();
		advance();
		return res;
	}
	auto leaf =  parseValue(current());
	advance();
	return leaf;
}

std::shared_ptr<Expression> ExpressionsParser::parseValue(const Token& token) const
{
	switch (token.get_type())
	{
	case TokenType::Identifier:
		return (make_shared<VarExpression>(token.get_content()));
	case TokenType::Number:
		return make_shared<ConstantExpresion>(stod(token.get_content()));
	default:
		throwParsingError();
	}
}


shared_ptr<Expression> ExpressionsParser::parse(int minPrecedence)
{
	auto ret = parseSymbol();

	while (hasNext()
		&& BinaryOperatorsTable::isBinaryOperator(current().get_type())
		&& BinaryOperatorsTable::getPrecedence(current().get_type()) >= minPrecedence)
	{
		Token oper = current();
		advance();
		const auto operand2 = parse(BinaryOperatorsTable::getPrecedence(oper.get_type()));
		ret = BinaryOperatorsTable::tryCreateOperatorExpression(oper.get_type(), ret, operand2);
	}
	return ret;
}

shared_ptr<Expression> ExpressionsParser::parse()
{
	currentToken = input.begin();
	
	auto res =  parse(0);
	if (currentToken != input.end())
		throwParsingError();
	return  res;
}
