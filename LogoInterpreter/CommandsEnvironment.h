#pragma once
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

class Command;

class Function
{
	std::vector<std::string> parameters;
	std::string name;


public:
	const std::vector<std::string>& get_parameters() const
	{
		return parameters;
	}

	std::string get_name() const
	{
		return name;
	}
};

class CompiledFunction : public Function
{

};

class UserDefinedFunction : public Function
{
	Command* body;
};

class CommandsEnvironment
{
	std::map<std::string, double> variables;
	std::map<std::string, Function*> functions;

public:
	const std::map<std::string, double>& get_variables() const
	{
		return variables;
	}

	const std::map<std::string, Function*>& get_functions() const
	{
		return functions;
	}

	Function* getFunction(const std::string& name) const;
	bool tryAddNewFunction(Function* newFunction);
	double getVariableValue(const std::string& name) const;

	static CommandsEnvironment createNestedEnvironment(
		const CommandsEnvironment& base, 
		const std::map<std::string, double>& newVariables);
	
	
	
};

