#include "Parser.h"
#include "Token.h"
#include <algorithm>
#include <stdexcept>
#include "CommandsEnvironment.h"
using namespace std;

std::vector<shared_ptr<Expression>> Parser::parseParameterList(std::vector<shared_ptr<Token>>::iterator& token)
{
	if (token == tokens.end())	
		throw runtime_error("Unexpected end of file");	
	if ((*token)->get_type() != TokenType::OpenPar)
		throw runtime_error("badly formed parameter list");
	++token;
	
	vector<shared_ptr<Expression>> res;	
	while(token != tokens.end() && (*token)->get_type() != TokenType::ClosePar)
	{
		auto tok = (*token);
		switch (tok->get_type())
		{
			case TokenType::Identifier:
				res.push_back(make_shared<VarExpression>(tok->get_content()));
				break;
			case TokenType::Number:
				res.push_back(make_shared<ConstantExpresion>(stod(tok->get_content())));
				break;						
			default: ;
				throw runtime_error("badly formed parameter list");
		}
		auto nextToken = token + 1;
		if(nextToken == tokens.end())
			throw runtime_error("badly formed parameter list");
		if ((*nextToken)->get_type() == TokenType::ClosePar)
		{
			token += 2;
			break;
		}

		if ((*nextToken)->get_type() != TokenType::Comma)
			throw runtime_error("badly formed parameter list");

		token += 2;		
		
	}
	return res;
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
			vector<shared_ptr<Expression>> parameters = parseParameterList(++token);			
			if (token == tokens.end())
				throw runtime_error("unexpected end of file");
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

			vector<string> paramNames(parameters.size());
			std::transform(parameters.begin(), parameters.end(), paramNames.begin(), 
				[](auto exp)
				{
					std::shared_ptr<VarExpression> varExp = std::dynamic_pointer_cast<VarExpression>(exp);
					if (varExp)
					{
						return varExp->get_name();
					}
					throw runtime_error("error parsing procedure definition");
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
	if ((*token)->get_type() == TokenType::EndBlock)
	{
		++token;
		return res;
	}
	return std::make_shared<SequentialCommand>(res, parse(token));
}
