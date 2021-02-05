#include "Visitor.h"
#include "Command.h"
#include <iostream>
#include <stdexcept>

using namespace std;


void CommandsVisitor::onVisit(const EmptyCommand& e)
{
	// Do nothing
}

void CommandsVisitor::onVisit(const SequentialCommand& command)
{
	CommandsVisitor v = *this;
	command.get_command()->accept(*this);
	command.get_next_command()->accept(v);
}

void CommandsVisitor::onVisit(const CallCommand& call_command)
{
	Function* fun = environment.getFunction(call_command.get_target_name());

	vector<Expression*> parameters = call_command.get_parameters();
	
	if (fun->get_parameters().size() != parameters.size())
		throw runtime_error("Function " + call_command.get_target_name()
			+ "does not have " + std::to_string(parameters.size()) + "parameters");


	
	map<string, double> nestedVariables;
	auto paramName = fun->get_parameters().begin();
	
	for (auto* parameterExp : parameters)
	{
		nestedVariables.emplace(*paramName, parameterExp->evaluate(environment));
		++paramName;
	}	
	CommandsEnvironment nestedEnvironment = CommandsEnvironment::createNestedEnvironment(this->environment,nestedVariables);
	auto nestedVisitor = createNestedVisitor(nestedEnvironment);	
}

void CommandsVisitor::onVisit(const DeclareFunctionCommand& declare_function_command)
{
	if (!environment.tryAddNewFunction(declare_function_command.get_target()))
		throw std::runtime_error( "Multiple function declaration: " 
			+ declare_function_command.get_target()->get_name());
}

CommandsVisitor CommandsVisitor::createNestedVisitor(const CommandsEnvironment& nestedEnvironment)
{
	 CommandsVisitor v;
	 v.environment = nestedEnvironment;
	 return v;
}

