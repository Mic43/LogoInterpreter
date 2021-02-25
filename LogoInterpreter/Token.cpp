#include "Token.h"
#include "CommadsParser.h"
#include "BinaryOperatorsTable.h"

Token::Token(const std::string& content, TokenType type): content(content), type(type)
{
}

std::string Token::get_content() const
{
	return content;
}

TokenType Token::get_type() const
{
	return type;
}

bool Token::isOperator(TokenType tt)
{
	return BinaryOperatorsTable::isBinaryOperator(tt);
}

bool Token::isExpressionPart(TokenType tt)
{
	return tt == TokenType::Identifier
		// || tt == TokenType::ClosePar
		// || tt == TokenType::OpenPar
		|| tt == TokenType::Number
		|| isOperator(tt);
		
}
