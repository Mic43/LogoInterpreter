#include "Visitor.h"
#include "Command.h"
#include <iostream>
#include <stdexcept>
#include "CommandsEnvironment.h"
#include "TurtleState.h"

using namespace std;


void CommandsVisitor::onVisit(const IfCommand& command)
{
	if (command.get_condition().evaluate(environment))
		command.get_body().accept(*this);
}

void CommandsVisitor::onVisit(const EmptyCommand& e)
{
	// Do nothing
}

void CommandsVisitor::onVisit(const SequentialCommand& command)
{	
	command.get_command().accept(*this);
	command.get_next_command().accept(*this);
}

void CommandsVisitor::onVisit(const CallCommand& call_command)
{
	const Procedure& procedure = environment.getProcedure(call_command.get_target_name());
	
	const std::vector<std::shared_ptr<Expression>>& parameters = call_command.get_parameters();
	
	if (procedure.get_parameters().size() != parameters.size())
		throw runtime_error("Procedure " + call_command.get_target_name()
			+ " does not have " + std::to_string(parameters.size()) + " parameter(s)");
	
	map<string, double> nestedVariables;
		
	auto paramName = procedure.get_parameters().begin();
	
	for (const auto& parameterExp : parameters)
	{
		nestedVariables[*paramName] = parameterExp->evaluate(environment);
		++paramName;
	}	
	auto nestedEnvironment = 
		CommandsEnvironment::createNestedEnvironment(this->environment,nestedVariables);
	auto nestedVisitor = createNestedVisitor(nestedEnvironment);
	
	procedure.get_body().accept(nestedVisitor);
}

void CommandsVisitor::onVisit(const DeclareProcedureCommand& declare_function_command)
{
	if (!environment.tryAddNewProcedure(declare_function_command.get_target()))
		throw std::runtime_error( "Multiple procedure declaration: " 
			+ declare_function_command.get_target()->get_name());
}

CommandsVisitor CommandsVisitor::createNestedVisitor(const CommandsEnvironment& nestedEnvironment)
{
	 CommandsVisitor v(nestedEnvironment);	 
	 return v;
}

void CommandsVisitor::onVisit(const TurtleCommand& turtle_command)
{
	double val = turtle_command.get_parameter().evaluate(environment);
	auto ts =  environment.get_turtle_state();
	//environment.get_turtle_state()->move(static_cast<int>(val), turtle_command.get_type());
	switch (turtle_command.get_type())
	{
		case TurtleCommand::Type::Left: 
			ts->turn(-val);
			break;
		case TurtleCommand::Type::Right:
			ts->turn(val);
			break;
		case TurtleCommand::Type::Forward:
			ts->forward(val);
			break;
		case TurtleCommand::Type::Backward:
			ts->backward(val);
			break;
		default: ;
	}
}

