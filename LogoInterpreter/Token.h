#pragma once

#include <string>

enum class TokenType
{
	Identifier,OpenPar,ClosePar,Number,IfKeyword,RepeatKeyword,Semicolon,Comma,EndBlockKeyword,
	OperatorPlus,OperatorMinus,OperatorMul,OperatorDiv,OperatorGreater,OperatorGreaterEqual,OperatorLess,OperatorLessEqual,OperatorEqual,OperatorNotEqual,
	EndLine,LineComment,LetKeyword,
	Operator
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
	static bool isOperator(TokenType tt)
	{
		return tt == TokenType::OperatorPlus || tt == TokenType::OperatorMinus
			|| tt == TokenType::OperatorMul || tt == TokenType::OperatorDiv;
	}
};