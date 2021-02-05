#pragma once
#include <string>

class CommandsEnvironment;

class Expression
{
public:
	virtual ~Expression() = default;
	virtual double evaluate(const CommandsEnvironment&) = 0;
};

class ConstantExpresion : public Expression
{
public:
	explicit ConstantExpresion(double value)
		: value(value)
	{
	}

	virtual double evaluate(const CommandsEnvironment&) override;
private:
	double value;

};
class VarExpresion : public Expression
{
private:
	std::string name;
public:
	virtual double evaluate(const CommandsEnvironment&) override;

};
