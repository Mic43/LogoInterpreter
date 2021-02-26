#pragma once

#include <string>

enum class TokenType
{
	Identifier,
	OpenPar,
	ClosePar,
	Number,
	IfKeyword,
	RepeatKeyword,
	Semicolon,
	Comma,
	EndBlockKeyword,
	OperatorAdd,
	OperatorSub,
	OperatorMul,
	OperatorDiv,
	OperatorGreater,
	OperatorGreaterEqual,
	OperatorLess,
	OperatorLessEqual,
	OperatorEqual,
	OperatorNotEqual,
	EndLine,
	LineComment,
	LetKeyword,
	OperatorAssign,
};

class Token
{
private:
	std::string content;
	TokenType type;
public:

	explicit Token(const std::string& content, TokenType type);

	std::string get_content() const;

	TokenType get_type() const;

	static bool isOperator(TokenType tt);

	static bool isExpressionPart(TokenType tt);
};