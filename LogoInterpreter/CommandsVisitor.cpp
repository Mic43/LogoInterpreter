#include "CommandsVisitor.h"
#include "Commands.h"
#include <iostream>
#include <stdexcept>
#include "CommandsEnvironment.h"
#include "TurtleState.h"

using namespace std;


void CommandsVisitor::throwExecutionError(const std::string& message,const Command& command) const
{
	throw runtime_error(message + ", line: " + std::to_string(command.get_line_number()));
}

void CommandsVisitor::onVisit(const IfCommand& command)
{
	if (command.get_condition().evaluate(environment))
		command.get_body().accept(*this);
}

void CommandsVisitor::onVisit(const RepeatCommand& repeat_command)
{
	int count = repeat_command.get_count().evaluate(environment);
	for (int i = 0; i < count; ++i)
	{
		repeat_command.get_body().accept(*this);
	}
}

void CommandsVisitor::onVisit(const AssignCommand& assign_command)
{
	if (environment.tryGetVariableValue(assign_command.get_variable_name()).has_value())
		throwExecutionError("Variable " + assign_command.get_variable_name() + " already defined", assign_command);
	environment.addNewVariable(assign_command.get_variable_name(),
		assign_command.get_initialization_expression()->evaluate(environment));
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
	auto proc = environment.tryGetProcedure(call_command.get_target_name());
	if (!proc.has_value())
		throwExecutionError("Command not defined: " + call_command.get_target_name(),call_command);
	auto procedure = proc.value().get();
	
	const std::vector<std::shared_ptr<Expression>>& parameters = call_command.get_parameters();
	
	if (proc.value().get().get_parameters().size() != parameters.size())
		throwExecutionError("Procedure " + call_command.get_target_name()
			+ " does not have " + std::to_string(parameters.size()) + " parameter(s)",call_command);
	
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
		throwExecutionError( "Multiple procedure declaration: "
			+ declare_function_command.get_target()->get_name(),declare_function_command);
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

