#include "Parser.h"
#include "Token.h"
#include <algorithm>
using namespace std;

std::vector<Expression*> Parser::parseParameterList(const std::vector<Token*>::iterator& token)
{
	return vector<Expression*>();
}

std::shared_ptr<Command> Parser::parse()
{
	auto token = tokens.begin();
	return parse(token);
}

shared_ptr<Command> Parser::parse(std::vector<Token*>::iterator& token)
{
	//shared_ptr<Command> res = make_shared<EmptyCommand>();
	
	//auto token = tokens.begin();	

	shared_ptr<SingleCommand> res = make_shared<EmptyCommand>();
	switch ((*token)->get_type())
	{		
		case TokenType::Identifier:
		{
			string name = (*token)->get_content();
			vector<Expression*> parameters = parseParameterList(token);
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
				[](Expression* exp)
				{
					auto varExp = dynamic_cast<VarExpresion*> (exp);
					if (varExp)
					{
						return varExp->get_name();
					}
					throw runtime_error("");
				});

			auto body = parse(token);
			res = std::make_shared<DeclareProcedureCommand>(std::make_shared<Procedure>(paramNames, name, body.get()).get());
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
	return std::make_shared<SequentialCommand>(res.get(), parse(token).get());
}
