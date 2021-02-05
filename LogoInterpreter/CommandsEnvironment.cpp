#include "CommandsEnvironment.h"
#include <stdexcept>

Function* CommandsEnvironment::getFunction(const std::string& name) const
{
	auto res = functions.find(name);
	if (res == functions.end())
		throw std::runtime_error("Function not defined: " + name);
	return res->second;
}

 bool CommandsEnvironment::tryAddNewFunction(Function* newFunction)
{
	if (functions.find(newFunction->get_name()) != functions.end())
		return false;
	functions.emplace(newFunction->get_name(), newFunction);
	return true;
}

double CommandsEnvironment::getVariableValue(const std::string& name) const
{
	auto res = variables.find(name);
	if (res == variables.end())
		throw std::runtime_error("Variable not defined: " + name);
	return res->second;
}

CommandsEnvironment CommandsEnvironment::createNestedEnvironment(const CommandsEnvironment& base,
	const std::map<std::string, double>& newVariables)
{
	CommandsEnvironment ce;
	ce.functions = base.functions;
	ce.variables = newVariables;

	return ce;
}


