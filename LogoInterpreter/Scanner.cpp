﻿#include "Scanner.h"

bool Scanner::hasNext(const std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it)
{
	return it != input.end();
}

char Scanner::nextChar(std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it)
{
	char r = *it;
	++it;
	return r;
}

bool Scanner::isKeyword(const std::string& word)
{
	return keywords.find(word) != keywords.end();
}

Token Scanner::keywordTokenFromString(const std::string& word)
{
	return Token(word, keywords[word]);
}

std::vector<Token> Scanner::tokenize()
{
	std::vector<Token> tokens;
	std::string stack;

	input.push_back(' ');
	auto it = input.begin();
	while(hasNext(it))
	{
		char c = nextChar(it);

		if (isalnum(c) || isDecimalSeparator(c) || (isOperatorSymbol(c) &&  isOperatorSequence(stack)))
		{
			stack.push_back(c);
		}
		else
		{
			if (!stack.empty())
			{
				if(isKeyword(stack))
				{
					tokens.push_back(keywordTokenFromString(stack));
				}				
				else if(isOperatorSequence(stack))
				{
					tokens.push_back(createToken(stack));
				}
				else if (isNumber(stack))
				{
					tokens.push_back(Token(stack, TokenType::Number));
				}
				else if (isIdentifier(stack))
				{
					tokens.push_back(Token(stack, TokenType::Identifier));
				}
				else
				{
					throw std::runtime_error("sequence not recognized:" + stack);
				}
				stack.clear();
			}
			if(isEndLine(c))
				tokens.push_back(Token(std::string(1, c), TokenType::EndLine));
			if (isLineComment(c))			
				tokens.push_back(Token(std::string(1, c), TokenType::LineComment));
			else if (isSemicolon(c))
				tokens.push_back(Token(std::string(1,c), TokenType::Semicolon));
			else if (isOperatorSymbol(c))
				tokens.push_back(createToken(std::string(1, c)));
			else if (isOpenPar(c))
				tokens.push_back(Token(std::string(1, c), TokenType::OpenPar));
			else if (isClosePar(c))
				tokens.push_back(Token(std::string(1, c), TokenType::ClosePar));
			else if (isComma(c))
				tokens.push_back(Token(std::string(1, c), TokenType::Comma));
			else if (isWhiteSpace(c))
				continue;
			else
				throw std::runtime_error("symbol not recognized: " + c);
		}				
	}
	
	return tokens;
}
