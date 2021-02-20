#pragma once

#include <string>

enum class TokenType
{
	Identifier,OpenPar,ClosePar,Number,IfKeyword,RepeatKeyword,Semicolon,Comma,EndBlockKeyword,Operator,
	EndLine,LineComment,LetKeyword
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