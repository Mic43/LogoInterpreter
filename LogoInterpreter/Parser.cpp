#include "Parser.h"

using namespace std;
Command& Parser::parse()
{
	shared_ptr<Command> res = make_shared<EmptyCommand>();
	return *res;
}
