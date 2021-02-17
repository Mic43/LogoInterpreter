#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

class Expression;
class OperatorExpression;

class BinaryOperatorsTable
{
public:
	
	//typedef std::shared_ptr<OperatorExpression>(*OperatorExpressionFactory) (const std::shared_ptr<Expression>&, const std::shared_ptr<Expression>&);
	static std::shared_ptr<OperatorExpression> tryCreateOperatorExpression(std::string symbol,
	                                                                       std::shared_ptr<Expression> par1,
	                                                                       std::shared_ptr<Expression> par2);
	static bool isOperatorSymbol(char c);
	typedef std::function < std::shared_ptr<OperatorExpression>(std::shared_ptr<Expression>, std::shared_ptr<Expression>)> OperatorExpressionCreator;
private:
	
	static const std::map<std::string, OperatorExpressionCreator> symbolMapping;
};
