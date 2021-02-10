#pragma once
#include <sstream>
#include <string>
#include <vector>
#include "Token.h"

class Scanner
{
	std::string input;

	bool hasNext(const std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it);
	char nextChar(std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it);

	bool isOperator(char c)
	{
		return c == '+' || c == '-' || c == '*' || c == '=' || c == '>' || c == '<';
	}

	bool isWhiteSpace(char c)
	{
		return iswspace(c);
	}

	bool isEndBlock(const std::string& word)
	{
		return word == "end";
	}

	bool isIfKeyword(const std::string& word)
	{
		return word == "if";
	}

	bool isNumber(const std::string& s)
	{		
		auto result = double();
		auto i = std::istringstream(s);

		i >> result;
		return !i.fail() && i.eof();
	}

	bool isIdentifier(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isalnum(*it))
			++it;
		return !s.empty() && !isdigit(s[0]) && it == s.end();
	}

	bool isSemicolon(char c)
	{
		return c == ';';
	}

	bool isOpenPar(char c)
	{
		return c == '(';
	}

	bool isClosePar(char c)
	{
		return c == ')';
	}

	bool isComma(char c)
	{
		return c == ',';
	}

	int isDecimalSeparator(char c)
	{
		return c == '.';
	}

public:

	
	explicit Scanner(const std::string& input)
		: input(input)
	{
	}

	
	std::vector<Token> tokenize();
};
