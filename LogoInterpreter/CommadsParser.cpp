﻿#include "CommadsParser.h"
#include "Token.h"
#include <algorithm>
#include <stack>
#include <stdexcept>
#include "CommandsEnvironment.h"
#include <string>

#include "BinaryOperatorsTable.h"
#include "ExpressionsParser.h"

using namespace std;

std::vector<Token>::iterator CommadsParser::findExpressionEnd(const std::vector<Token>::iterator& token)
{
	std::vector<Token>::iterator res = token;
	while (res != tokens.end() 
		&& (Token::isExpressionPart(res->get_type()) || res->get_type() == TokenType::EndLine))
	{
		++res;
	}
	return res;
}

std::shared_ptr<Expression> CommadsParser::parseExpression(std::vector<Token>::iterator& token, bool& endReached)
{

	auto expEnd = findExpressionEnd(token);
	vector<Token> expInput(token, expEnd);
	ExpressionsParser ep(expInput,currentLineNumber);
			
	
	auto result =  ep.parse();
	token = expEnd;
	endReached = token->get_type() != TokenType::Comma;
	moveToNextSignificant(token);
	currentLineNumber = ep.get_current_line_number();
	return result;
}

std::vector<shared_ptr<Expression>> CommadsParser::parseParameterList(std::vector<Token>::iterator& token)
{
	assumeNotEnd(token);
	if (token->get_type() != TokenType::OpenPar)
		throwParsingError("badly formed parameter list");

	moveToNextSignificant(token);

	vector<shared_ptr<Expression>> res;
	bool end_reached = false;
	while (token != tokens.end() && !end_reached)
	{
		res.push_back(parseExpression(token, end_reached));
	}
	return res;
}

void CommadsParser::assumeNotEnd(std::vector<Token>::iterator& token)
{
	if (isEnd(token))
		throwParsingError("Unexpected end of file");
}

std::shared_ptr<Command> CommadsParser::parse()
{
	auto token = tokens.begin();
	currentLineNumber = 1;
	return parse(token, "");
}

void CommadsParser::throwParsingError(const string& message) const
{
	throw runtime_error(message + ", line: " + std::to_string(currentLineNumber));
}

void CommadsParser::assumeNextIs(std::vector<Token>::iterator& token, TokenType tokenType)
{
	moveToNextSignificant(token);
	assumeNotEnd(token);
	if (token->get_type() != tokenType)
		throwParsingError("unexpected token type");
}

std::vector<Token>::iterator& CommadsParser::moveToNextSignificant(std::vector<Token>::iterator& token, int* currentLineNumber)
{
	do
	{
		++token;
		if (isEnd(token) || token->get_type() != TokenType::EndLine)
			break;

		if (token->get_type() == TokenType::EndLine)
		{
			currentLineNumber++;
		}

	} while (true);
	return token;
}

std::vector<Token>::iterator& CommadsParser::moveToNextSignificant(std::vector<Token>::iterator& token)
{
	return moveToNextSignificant(token, &this->currentLineNumber);
}

shared_ptr<Command> CommadsParser::parse(vector<Token>::iterator& token, string blockName)
{
	if (isEnd(token))
		return std::make_shared<EmptyCommand>(currentLineNumber);

	const Token& current = *token;

	shared_ptr<SingleCommand> currentCommand;
	switch (current.get_type())
	{
	case TokenType::Identifier:
	{
		string name = token->get_content();
		vector<shared_ptr<Expression>> parameters = parseParameterList(moveToNextSignificant(token));
		assumeNotEnd(token);

		// handle call
		if (token->get_type() == TokenType::Semicolon)
		{
			moveToNextSignificant(token);
			auto tc = TurtleCommand::tryCreate(name, parameters, currentLineNumber);

			if (!tc)
				currentCommand = std::make_shared<CallCommand>(CallCommand(parameters, name, currentLineNumber));
			else
				currentCommand = tc;

			break;
		}

		// handle procedure declaration
		vector<string> paramNames(parameters.size());
		std::transform(parameters.begin(), parameters.end(), paramNames.begin(),
			[this](auto exp)
			{
				std::shared_ptr<VarExpression> varExp = std::dynamic_pointer_cast<VarExpression>(exp);
				if (varExp)
				{
					return varExp->get_name();
				}
				throwParsingError("error parsing procedure definition");
			});
		int curLineNumberTemp = currentLineNumber;
		auto body = parse(token, name);
		currentCommand = std::make_shared<DeclareProcedureCommand>(
			std::make_shared<Procedure>(paramNames, name, body),
			curLineNumberTemp);
		break;
	}
	case TokenType::LetKeyword:
	{
		assumeNextIs(token, TokenType::Identifier);
		string varName = token->get_content();
		assumeNextIs(token, TokenType::OperatorEqual);
		moveToNextSignificant(token);
		bool end;
		auto exprssion = parseExpression(token, end);
		if (!end)
			throwParsingError("malformed expression");
		currentCommand = std::make_shared<AssignCommand>(varName, exprssion, currentLineNumber);
		//assumeNextIs(token,TokenType::Semicolon);
		break;
	}
	case TokenType::RepeatKeyword:
	{
		moveToNextSignificant(token);
		int curLineNumberTemp = currentLineNumber;
		assumeNotEnd(token);
		if (token->get_type() != TokenType::OpenPar)
			throwParsingError("expected expression");

		bool end;

		auto expression = parseExpression(moveToNextSignificant(token), end);
		if (!end)
			throwParsingError("malformed expression");

		auto body = parse(token, "repeat");
		currentCommand = make_shared<RepeatCommand>(expression, body, curLineNumberTemp);
		break;
	}
	case TokenType::IfKeyword:
	{
		moveToNextSignificant(token);
		int curLineNumberTemp = currentLineNumber;
		assumeNotEnd(token);
		if (token->get_type() != TokenType::OpenPar)
			throwParsingError("expected condition");


		bool end;
		auto expression = parseExpression(moveToNextSignificant(token), end);
		if (!end)
			throwParsingError("malformed if condition");

		auto body = parse(token, "if");
		currentCommand = make_shared<IfCommand>(expression, body, curLineNumberTemp);
		break;
	}
	case TokenType::LineComment:
		while (!isEnd(token) && token->get_type() != TokenType::EndLine)
		{
			++token;
		}
		return parse(token, blockName);
	case TokenType::Semicolon:
		currentCommand = std::make_shared<EmptyCommand>(currentLineNumber);
		moveToNextSignificant(token);
		break;
	case TokenType::EndLine:
		currentLineNumber++;
		return parse(++token, blockName);
		// = std::make_shared<EmptyCommand>();		 			
	case TokenType::EndBlockKeyword:
		if ((moveToNextSignificant(token))->get_content() != blockName)
			throwParsingError("malformed end block");

		if ((moveToNextSignificant(token))->get_type() != TokenType::Semicolon)
			throwParsingError("malformed end block");

		moveToNextSignificant(token);
		return std::make_shared<EmptyCommand>(currentLineNumber);
	case TokenType::OpenPar:
	case TokenType::ClosePar:
	case TokenType::Number:
	case TokenType::Comma:
	case TokenType::OperatorAdd:
	case TokenType::OperatorSub:
	case TokenType::OperatorMul:
	case TokenType::OperatorDiv:
		throwParsingError("Symbol not expected");
		break;

	default:
		throwParsingError("Not recognized token type");
	}

	auto nextCommand = parse(token, blockName);
	return std::make_shared<SequentialCommand>(currentCommand, nextCommand, currentLineNumber);
}
