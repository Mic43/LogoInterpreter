#include "Expression.h"
#include "CommandsEnvironment.h"

double ConstantExpresion::evaluate(const CommandsEnvironment&)
{
	return value;
}

double VarExpresion::evaluate(const CommandsEnvironment& environment)
{
	return environment.getVariableValue(name);
}
