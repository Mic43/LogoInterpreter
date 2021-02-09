#include "CommandsEnvironment.h"
#include <stdexcept>

const Procedure& CommandsEnvironment::getProcedure(const std::string& name) const
{
	auto res = functions.find(name);
	if (res == functions.end())
		throw std::runtime_error("Function not defined: " + name);
	return *res->second;
}

 bool CommandsEnvironment::tryAddNewProcedure(std::shared_ptr<Procedure> newFunction)
{
	if (functions.find(newFunction->get_name()) != functions.end())
		return false;
	functions[newFunction->get_name()] =  newFunction;
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
	//TODO: possible errors here
	CommandsEnvironment ce;
	ce.functions = base.functions;
	ce.variables = newVariables;
	ce.turtle_state = base.turtle_state;
	return ce;
}


