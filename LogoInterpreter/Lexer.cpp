#include "Lexer.h"

bool Lexer::hasNext(const std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it)
{
	return it != input.end();
}

bool Lexer::isKeyword(const std::string& word)
{
	return keywords.find(word) != keywords.end();
}

Token Lexer::keywordTokenFromString(const std::string& word)
{
	return Token(word, keywords[word]);
}

Token Lexer::parseIdentifier(
	std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it)
{
	std::string stack;
	do
	{
		stack.push_back(*it);
		++it;
	} while (hasNext(it) && isalnum(*it));
	return Token(stack, TokenType::Identifier);
}

Token Lexer::parseNumber(std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it)
{
	std::string stack;
	do
	{		
		stack.push_back(*it);
		++it;
	} while (hasNext(it) && (isDecimalSeparator(*it) || isdigit(*it)));
	
	if(!isNumber(stack))
		throw std::runtime_error("not a number: " + stack);

	return Token(stack, TokenType::Number);
}

Token Lexer::parseOperator(std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it)
{
	std::string stack;
	do
	{
		stack.push_back(*it);
		++it;
	} while (hasNext(it) && isOperatorSymbol(*it));

	if(!isOperator(stack))
		throw std::runtime_error("not an operator: " + stack);
	return createOperatorToken(stack);
}
Token Lexer::createToken(char symbol,TokenType tokenType)
{
	return Token(std::string(1, symbol), tokenType);
}
std::vector<Token> Lexer::tokenize()
{
	std::vector<Token> output;
		
	auto it = input.begin();
	while (it != input.end())
	{
		const char symbol = *it;
		
		std::unique_ptr<Token> newToken;
		if (isalpha(symbol))
		{
			newToken = std::make_unique<Token>(parseIdentifier(it));
			if(isKeyword(newToken->get_content()))
				newToken = std::make_unique<Token>(keywordTokenFromString(newToken->get_content()));
		}
		else if (isdigit(symbol))
			newToken = std::make_unique<Token>(parseNumber(it));
		else if (isOperatorSymbol(symbol))
			newToken = std::make_unique<Token>(parseOperator(it));
		else
		{
			if (isEndLine(symbol))
				newToken = std::make_unique<Token>(createToken(symbol, TokenType::EndLine));
			else if (isLineComment(symbol))
				newToken = std::make_unique<Token>(createToken(symbol, TokenType::LineComment));
			else if (isSemicolon(symbol))
				newToken = std::make_unique<Token>(createToken(symbol, TokenType::Semicolon));
			else if (isOpenPar(symbol))
				newToken = std::make_unique<Token>(createToken(symbol, TokenType::OpenPar));
			else if (isClosePar(symbol))
				newToken = std::make_unique<Token>(createToken(symbol, TokenType::ClosePar));
			else if (isComma(symbol))
				newToken = std::make_unique<Token>(createToken(symbol, TokenType::Comma));
			else if (isWhiteSpace(symbol))
				;
			else
				throw std::runtime_error("symbol not recognized: " + std::to_string(symbol));

			++it;
		}
		if (newToken != nullptr)
			output.push_back(*newToken);
	}
	

	return output;
}

