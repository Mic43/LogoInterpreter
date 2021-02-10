#include "Scanner.h"

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
				if (isEndBlock(stack))
				{
					tokens.push_back(Token(stack, TokenType::EndBlock));
				}
				else if (isIfKeyword(stack))
				{
					tokens.push_back(Token(stack, TokenType::IfKeyword));
				}
				else if(isOperatorSequence(stack))
				{
					tokens.push_back(Token(stack, TokenType::Operator));
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
			
			if (isWhiteSpace(c))			
				continue;			
			if (isSemicolon(c))
				tokens.push_back(Token(std::string(1,c), TokenType::Semicolon));
			else if (isOperatorSymbol(c))
				tokens.push_back(Token(std::string(1, c), TokenType::Operator));
			else if (isOpenPar(c))
				tokens.push_back(Token(std::string(1, c), TokenType::OpenPar));
			else if (isClosePar(c))
				tokens.push_back(Token(std::string(1, c), TokenType::ClosePar));
			else if (isComma(c))
				tokens.push_back(Token(std::string(1, c), TokenType::Comma));
			else
				throw std::runtime_error("symbol not recognized: " + c);
		}				
	}
	
	return tokens;
}
