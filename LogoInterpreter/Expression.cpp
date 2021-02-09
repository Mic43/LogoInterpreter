#include "Expression.h"
#include "CommandsEnvironment.h"
#include "Token.h"
#include <stdexcept>

std::shared_ptr<OperatorExpression> OperatorExpression::tryCreateFromToken(
	const Token& token,
	const std::shared_ptr<Expression>& oper1, 
	const std::shared_ptr<Expression>& oper2)
{
	if (token.get_type() == TokenType::Operator)
	{
		if (token.get_content() == "+")
			return std::make_shared<OperatorAdd>(oper1, oper2);
		if (token.get_content() == "-")
			return std::make_shared<OperatorSub>(oper1, oper2);
		if (token.get_content() == "*")
			return std::make_shared<OperatorMul>(oper1, oper2);		
		if (token.get_content() == "=")
			return std::make_shared<OperatorEqual>(oper1, oper2);
		if (token.get_content() == ">")
			return std::make_shared<OperatorGreater>(oper1, oper2);
		if (token.get_content() == "<")
			return std::make_shared<OperatorLess>(oper1, oper2);
		if (token.get_content() == "<>")
			return std::make_shared<OperatorNotEqual>(oper1, oper2);
		throw std::runtime_error("invalid operator");
	}
	throw std::runtime_error("invalid expression");
}

double OperatorAdd::evaluate(const CommandsEnvironment& e) const
{
	return leftOperand->evaluate(e) + rightOperand->evaluate(e);
}

double OperatorMul::evaluate(const CommandsEnvironment& e) const
{
	return leftOperand->evaluate(e) * rightOperand->evaluate(e);

}

double OperatorSub::evaluate(const CommandsEnvironment& e)const
{
	return leftOperand->evaluate(e) - rightOperand->evaluate(e);

}

double OperatorGreater::evaluate(const CommandsEnvironment& e)const
{
	return leftOperand->evaluate(e) > rightOperand->evaluate(e);
}

double OperatorLess::evaluate(const CommandsEnvironment& e)const
{
	return leftOperand->evaluate(e) < rightOperand->evaluate(e);

}

double OperatorEqual::evaluate(const CommandsEnvironment& e)const
{
	return leftOperand->evaluate(e) == rightOperand->evaluate(e);
}

double OperatorNotEqual::evaluate(const CommandsEnvironment& e)const
{
	return leftOperand->evaluate(e) != rightOperand->evaluate(e);

}

double ConstantExpresion::evaluate(const CommandsEnvironment&)const
{
	return value;
}

double VarExpression::evaluate(const CommandsEnvironment& environment)const
{
	return environment.getVariableValue(name);
}
