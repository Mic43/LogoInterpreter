#pragma once
#include "Parser.h"

enum class TokenType
{
	Identifier,OpenPar,ClosePar,Number,IfKeyword,Semicolon,Comma,EndBlock
};

class Token
{
private:
	std::string content;
	TokenType type;
public:

	explicit Token(const std::string& content,TokenType type)
		: content(content), type(type)
	{
	}

	std::string get_content() const
	{
		return content;
	}

	TokenType get_type() const
	{
		return type;
	}
};