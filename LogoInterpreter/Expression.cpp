#include "Expression.h"
#include "CommandsEnvironment.h"

double OperatorAdd::evaluate(const CommandsEnvironment& e)
{
	return leftOperand->evaluate(e) + rightOperand->evaluate(e);
}

double OperatorMul::evaluate(const CommandsEnvironment& e)
{
	return leftOperand->evaluate(e) * rightOperand->evaluate(e);

}

double OperatorSub::evaluate(const CommandsEnvironment& e)
{
	return leftOperand->evaluate(e) - rightOperand->evaluate(e);

}

double OperatorGreater::evaluate(const CommandsEnvironment& e)
{
	return leftOperand->evaluate(e) > rightOperand->evaluate(e);
}

double OperatorLess::evaluate(const CommandsEnvironment& e)
{
	return leftOperand->evaluate(e) < rightOperand->evaluate(e);

}

double OperatorEqual::evaluate(const CommandsEnvironment& e)
{
	return leftOperand->evaluate(e) == rightOperand->evaluate(e);
}

double OperatorNotEqual::evaluate(const CommandsEnvironment& e)
{
	return leftOperand->evaluate(e) != rightOperand->evaluate(e);

}

double ConstantExpresion::evaluate(const CommandsEnvironment&)
{
	return value;
}

double VarExpresion::evaluate(const CommandsEnvironment& environment)
{
	return environment.getVariableValue(name);
}
