#pragma once
#include <map>
#include <memory>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include "TurtleState.h"

class Command;
class Procedure
{
	std::vector<std::string> parameters;
	std::string name;
	Command* body;

public:
	Procedure(const std::vector<std::string>& parameters, const std::string& name, Command* body)
		: parameters(parameters),
		  name(name),
		  body(body)
	{
	}

	Command* get_body() const
	{
		return body;
	}

	const std::vector<std::string>& get_parameters() const
	{
		return parameters;
	}

	std::string get_name() const
	{
		return name;
	}
};

class CommandsEnvironment
{
	std::map<std::string, double> variables;
	std::map<std::string, Procedure*> functions;
	std::shared_ptr<TurtleState> turtle_state;


public:
	CommandsEnvironment(): turtle_state(std::make_shared<TurtleState>())
	{
	}
	
	TurtleState* get_turtle_state() const
	{
		return turtle_state.get();
	}

	const std::map<std::string, double>& get_variables() const
	{
		return variables;
	}

	const std::map<std::string, Procedure*>& get_functions() const
	{
		return functions;
	}

	Procedure* getProcedure(const std::string& name) const;
	bool tryAddNewProcedure(Procedure* newFunction);
	double getVariableValue(const std::string& name) const;

	static CommandsEnvironment createNestedEnvironment(
		const CommandsEnvironment& base, 
		const std::map<std::string, double>& newVariables);
	
	
	
};

