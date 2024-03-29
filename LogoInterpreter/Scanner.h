﻿#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "BinaryOperatorsTable.h"
#include "Token.h"

class Scanner
{
	std::string input;

	std::map<std::string, TokenType> keywords = {
		{"end",TokenType::EndBlockKeyword},
		{"if",TokenType::IfKeyword},
		{"repeat",TokenType::RepeatKeyword},
		{"let",TokenType::LetKeyword},
	};
	std::map<std::string, TokenType> operators = {
		{"+",TokenType::OperatorAdd},
		{ "-",TokenType::OperatorSub},
		{ "*",TokenType::OperatorMul},
		{ "/",TokenType::OperatorDiv},
		{ "=",TokenType::OperatorEqual},
		{ ">",TokenType::OperatorGreater},
		{ ">=",TokenType::OperatorGreater},
		{ "<",TokenType::OperatorLess},
		{ "<=",TokenType::OperatorLessEqual},
		{ "<>",TokenType::OperatorNotEqual } };

	bool hasNext(const std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it);
	char nextChar(std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it);
	Token createToken(const std::string&  s)
	{
		return Token(s,operators.find(s)->second);
	}
	
	bool isOperatorSymbol(char c)
	{
		return std::any_of(operators.begin(), operators.end(),
			[&c](auto entry) {return entry.first.find(c) != std::string::npos; });
	}

	bool isOperatorSequence(const std::string& s)
	{
		if (s.empty())
			return true;
		std::string::const_iterator it = s.begin();
		while (it != s.end() && isOperatorSymbol(*it))
			++it;
		return it == s.end();
	}

	bool isWhiteSpace(char c)
	{
		return iswspace(c);
	}


	bool isLineComment(char c)
	{
		return c == '\'';
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

	bool isEndLine(char c)
	{
		return c == '\n';
	}

public:


	explicit Scanner(const std::string& input)
		: input(input)
	{
	}


	bool isKeyword(const std::string& word);
	Token keywordTokenFromString(const std::string& stack);
	std::vector<Token> tokenize();
};
