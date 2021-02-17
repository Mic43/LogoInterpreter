#include "CommandsEnvironment.h"
#include <stdexcept>
#include <optional>

std::optional< std::reference_wrapper<Procedure>> CommandsEnvironment::getProcedure(const std::string& name) const
{	
	auto res = functions.find(name);
	if (res == functions.end())
		return std::nullopt;
	return std::make_optional(std::ref(*res->second));}

 bool CommandsEnvironment::tryAddNewProcedure(std::shared_ptr<Procedure> newFunction)
{
	if (functions.find(newFunction->get_name()) != functions.end())
		return false;
	functions[newFunction->get_name()] =  newFunction;
	return true;
}

std::optional<double> CommandsEnvironment::getVariableValue(const std::string& name) const
{
	auto res = variables.find(name);
	if (res == variables.end())
		return std::nullopt;
		//throw std::runtime_error("Variable not defined: " + name);
	return std::make_optional (res->second);
}

CommandsEnvironment CommandsEnvironment::createNestedEnvironment(const CommandsEnvironment& base,
	const std::map<std::string, double>& newVariables)
{
	//TODO: possible errors here
	CommandsEnvironment ce(base.turtle_state);
	ce.functions = base.functions;
	ce.variables = newVariables;
	return ce;
}


