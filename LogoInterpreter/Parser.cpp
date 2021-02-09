#include "Parser.h"
#include "Token.h"
#include <algorithm>
#include <stdexcept>
#include "CommandsEnvironment.h"
using namespace std;

std::vector<shared_ptr<Expression>> Parser::parseParameterList(const std::vector<shared_ptr<Token>>::iterator& token)
{
	return vector<std::shared_ptr<Expression>>();
}

std::shared_ptr<Command> Parser::parse()
{
	auto token = tokens.begin();
	return parse(token);
}

shared_ptr<Command> Parser::parse(vector<shared_ptr<Token>>::iterator& token)
{
	//shared_ptr<Command> res = make_shared<EmptyCommand>();

	shared_ptr<SingleCommand> res = make_shared<EmptyCommand>();
	switch ((*token)->get_type())
	{		
		case TokenType::Identifier:
		{
			string name = (*token)->get_content();
			vector<shared_ptr<Expression>> parameters = parseParameterList(token);
			++token;
				
			if ((*token)->get_type() == TokenType::Semicolon)
			{
				++token;
				auto tc = TurtleCommand::tryCreate(name, parameters);
			
				if (!tc)									
					res =  std::make_shared<CallCommand>(CallCommand(parameters, name));				
				else
					res = tc;
				
				break;
			}

			vector<string> paramNames;			
			std::transform(parameters.begin(), parameters.end(), paramNames.begin(), 
				[](auto exp)
				{
					std::shared_ptr<VarExpression> varExp = std::dynamic_pointer_cast<VarExpression>(exp);
					if (varExp)
					{
						return varExp->get_name();
					}
					throw runtime_error("");
				});

			auto body = parse(token);
			res = std::make_shared<DeclareProcedureCommand>(std::make_shared<Procedure>(paramNames, name, body));
			break;
		}
		case TokenType::IfKeyword:			
			break;
		case TokenType::Semicolon: 
			res = std::make_shared<EmptyCommand>();
			++token;
			break;
		default: ;
			throw runtime_error("error");
	}
	if(token == tokens.end())
		return res;
	return std::make_shared<SequentialCommand>(res, parse(token));
}
