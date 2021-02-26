#pragma once
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "BinaryOperatorsTable.h"
#include "Token.h"

class Lexer
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
		{ "==",TokenType::OperatorEqual},		
		{ ">",TokenType::OperatorGreater},
		{ ">=",TokenType::OperatorGreater},
		{ "<",TokenType::OperatorLess},
		{ "<=",TokenType::OperatorLessEqual},
		{ "!=",TokenType::OperatorNotEqual},
		{ "=",TokenType::OperatorAssign},

	};

	bool hasNext(const std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it);	
	Token createOperatorToken(const std::string&  s)
	{
		return Token(s,operators.find(s)->second);
	}
	
	bool isOperatorSymbol(char c)
	{
		 return std::any_of(operators.begin(), operators.end(),
		 	[&c](auto entry) {return entry.first.find(c) != std::string::npos; });
	}
	bool isOperator(const std::string& s)
	{
		return operators.find(s) != operators.end();
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

	Token parseIdentifier(std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it);
	Token parseNumber(std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it);
	Token parseOperator(std::_String_iterator<std::_String_val<std::_Simple_types<char>>>& it);
	Token createToken(char symbol, TokenType tokenType);
	bool isKeyword(const std::string& word);
	Token keywordTokenFromString(const std::string& stack);

public:


	explicit Lexer(const std::string& input)
		: input(input)
	{
	}

	std::vector<Token> tokenize();
	//std::vector<Token> tokenize2();

};
