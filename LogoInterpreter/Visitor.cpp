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
	
	if (fun->get_parameters().size() != call_command.get_parameters().size())
		throw runtime_error("Function " + call_command.get_target_name()
			+ "does not have " + std::to_string(call_command.get_parameters().size()) + "parameters");


	
	//CommandsEnvironment nestedEnvironment = CommandsEnvironment::createNestedEnvironment(*this);
}

void CommandsVisitor::onVisit(const DeclareFunctionCommand& declare_function_command)
{
	if (!environment.tryAddNewFunction(declare_function_command.get_target()))
		throw std::runtime_error( "Multiple function declaration: " 
			+ declare_function_command.get_target()->get_name());
}
