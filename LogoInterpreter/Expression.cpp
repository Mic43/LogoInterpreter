#include "Expression.h"
#include "CommandsEnvironment.h"

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
