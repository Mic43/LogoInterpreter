﻿#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "Token.h"

class Expression;
class OperatorExpression;

class BinaryOperatorsTable
{
public:
	
	//typedef std::shared_ptr<OperatorExpression>(*OperatorExpressionFactory) (const std::shared_ptr<Expression>&, const std::shared_ptr<Expression>&);
	static std::shared_ptr<OperatorExpression> tryCreateOperatorExpression(TokenType tokenType,
	                                                                       std::shared_ptr<Expression> par1,
	                                                                       std::shared_ptr<Expression> par2);
	static bool isOperatorSymbol(char c);
	static bool isBinaryOperator(TokenType token);
	static int getPrecedence(TokenType token);
	typedef std::function < std::shared_ptr<OperatorExpression>(std::shared_ptr<Expression>, std::shared_ptr<Expression>)> OperatorExpressionCreator;
private:
	
	static const std::map<TokenType, OperatorExpressionCreator> symbolMapping;
	static const std::map<TokenType, int> precedenceTable;

};
