#pragma once
#include <string>
#include <vector>


class Token
{
	
};
class IdentifierToken : public Token
{
	
};
class OpenParToken : public Token
{
	
};
class CloseParToken : public Token
{
	
};
class NumberToken : public Token
{
	
};
class OperatorToken: public Token
{
	
};
class EndBlockToken: public Token
{
	
};
class SemicolonToken : public Token
{
	
};
class IfCommandToken : public Token
{
	
};


class Scanner
{
	std::string input;
public:

	
	explicit Scanner(const std::string& input)
		: input(input)
	{
	}

	std::vector<Token> tokenize();
};
