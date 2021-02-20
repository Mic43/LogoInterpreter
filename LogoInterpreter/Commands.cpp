#include "Commands.h"
#include <iostream>
#include "CommandsVisitor.h"
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;


std::string Command::toString(int level) const
{
	string margin = "";
	for (int i = 0; i < level; ++i)
	{
		margin += "\t";
	}
	return margin + typeid(*this).name();//  +"| line: ";  +std::to_string(lineNumber);
}

 std::string SequentialCommand::toString(int level) const
{
	return command->toString(level) + "\n" + nextCommand->toString(level);
}

 std::string CallCommand::toString(int level) const
{
	return Command::toString(level) + ": " + get_target_name();
}

 std::string DeclareProcedureCommand::toString(int level) const
{
	return Command::toString(level) +": " + this->get_target()->get_name() + "\n"
	+ target->get_body().toString(level + 1);
}

 std::string IfCommand::toString(int level) const
{
	return Command::toString(level) + "\n" + body_->toString(level + 1);
}


std::string RepeatCommand::toString(int level) const
{
	return Command::toString(level) + "\n" + body_->toString(level + 1);

}

std::string AssignCommand::toString(int level) const
{
	return Command::toString(level) + ": " + this->get_variable_name();

}

void AssignCommand::accept(CommandsVisitorBase& v) const
{
	v.onVisit(*this);
}

void RepeatCommand::accept(CommandsVisitorBase& v) const
{
	v.onVisit(*this);
}


void SequentialCommand::accept(CommandsVisitorBase& v)const
{
	v.onVisit(*this);
}


void EmptyCommand::accept(CommandsVisitorBase& v) const
{
	v.onVisit(*this);
}

void CallCommand::accept(CommandsVisitorBase& v)const
{
	v.onVisit(*this);
}

void DeclareProcedureCommand::accept(CommandsVisitorBase& v)const
{
	v.onVisit(*this);
}

void TurtleCommand::accept(CommandsVisitorBase& v)const
{
	v.onVisit(*this);
}

void IfCommand::accept(CommandsVisitorBase& v)const
{
	v.onVisit(*this);

}

