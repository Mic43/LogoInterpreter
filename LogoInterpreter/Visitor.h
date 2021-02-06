#pragma once

#include <map>
#include "Command.h"
#include "CommandsEnvironment.h"

class CommandsVisitorBase
{
public:
	//virtual void onVisit(const Command& command) = 0;	
	virtual void onVisit(const SequentialCommand& ) = 0;
	virtual void onVisit(const EmptyCommand&) = 0;
	virtual void onVisit(const CallCommand& call_command) = 0;
	virtual void onVisit(const DeclareProcedureCommand& call_command) = 0;
	virtual void onVisit(const TurtleCommand& turtle_command) = 0;

};


class CommandsVisitor : public CommandsVisitorBase
{
private:
	CommandsEnvironment environment;

public:
	CommandsEnvironment get_environment() const
	{
		return environment;
	}

	// Inherited via VisitorBase	

	void onVisit(const EmptyCommand&) override;
	void onVisit(const SequentialCommand& ) override;
	void onVisit(const CallCommand& call_command) override;
	void onVisit(const DeclareProcedureCommand& call_command) override;
	void onVisit(const TurtleCommand& turtle_command) override;


	static CommandsVisitor createNestedVisitor(const CommandsEnvironment& nestedEnvironment);
};

