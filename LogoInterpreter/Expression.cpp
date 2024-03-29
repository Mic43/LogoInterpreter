#include "Expression.h"
#include "CommandsEnvironment.h"
#include "Token.h"
#include <stdexcept>

#include "BinaryOperatorsTable.h"

std::shared_ptr<OperatorExpression> OperatorExpression::tryCreateFromToken(
	const Token& token,
	const std::shared_ptr<Expression>& oper1, 
	const std::shared_ptr<Expression>& oper2)
{
	
	auto operExp = 
		BinaryOperatorsTable::tryCreateOperatorExpression(token.get_type(),oper1, oper2);
	if(operExp == nullptr)
		throw std::runtime_error("invalid operator");
	return operExp;

}

double OperatorDiv::evaluate(const CommandsEnvironment& e) const
{
	return leftOperand->evaluate(e) / rightOperand->evaluate(e);
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

double OperatorGreaterEqual::evaluate(const CommandsEnvironment& e) const
{
	return leftOperand->evaluate(e) >= rightOperand->evaluate(e);
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
	auto var = environment.tryGetVariableValue(name);
	if (!var.has_value())
		throw std::runtime_error("variable not defined: " + name);
	return var.value();
}
