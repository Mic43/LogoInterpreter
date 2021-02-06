
#include "Command.h"
#include "Visitor.h"



void main()
{	

	CommandsVisitor v;

	EmptyCommand empty;

	Command& c = empty;

	c.accept(v);
}