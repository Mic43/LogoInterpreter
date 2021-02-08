#pragma once
#include <string>

class CommandsEnvironment;

class Expression
{
public:
	virtual ~Expression() = default;
	virtual double evaluate(const CommandsEnvironment&) = 0;
};

class OperatorExpression : public Expression
{
protected:
	Expression* leftOperand;
	Expression* rightOperand;

public:

	OperatorExpression(Expression* left_operand, Expression* right_operand)
		: leftOperand(left_operand),
		  rightOperand(right_operand)
	{
	}

	double evaluate(const CommandsEnvironment&) = 0 ;
};

class OperatorAdd : public OperatorExpression
{
public:
	OperatorAdd(Expression* left_operand, Expression* right_operand)
		: OperatorExpression(left_operand, right_operand)
	{
	}

	double evaluate(const CommandsEnvironment&) override;
};

class OperatorMul : public OperatorExpression
{
public:
	OperatorMul(Expression* left_operand, Expression* right_operand)
		: OperatorExpression(left_operand, right_operand)
	{
	}

	double evaluate(const CommandsEnvironment&) override;
};
class OperatorSub : public OperatorExpression
{
public:
	OperatorSub(Expression* left_operand, Expression* right_operand)
		: OperatorExpression(left_operand, right_operand)
	{
	}

	double evaluate(const CommandsEnvironment&) override;
};

class OperatorGreater : public OperatorExpression
{
public:
	OperatorGreater(Expression* left_operand, Expression* right_operand)
		: OperatorExpression(left_operand, right_operand)
	{
	}

	double evaluate(const CommandsEnvironment& e) override;
};

class OperatorLess : public OperatorExpression
{
public:
	OperatorLess(Expression* left_operand, Expression* right_operand)
		: OperatorExpression(left_operand, right_operand)
	{
	}

	double evaluate(const CommandsEnvironment& e) override;
};
class OperatorEqual : public OperatorExpression
{
public:
	OperatorEqual(Expression* left_operand, Expression* right_operand)
		: OperatorExpression(left_operand, right_operand)
	{
	}

	double evaluate(const CommandsEnvironment& e) override;
};
class OperatorNotEqual : public OperatorExpression
{
public:
	OperatorNotEqual(Expression* left_operand, Expression* right_operand)
		: OperatorExpression(left_operand, right_operand)
	{
	}

	double evaluate(const CommandsEnvironment& e) override;
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


	explicit VarExpresion(const std::string& name)
		: name(name)
	{
	}

	std::string get_name() const
	{
		return name;
	}
};
