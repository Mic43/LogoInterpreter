
#include <fstream>
#include <iostream>

#include "Command.h"
#include "Parser.h"
#include "Scanner.h"
#include "Token.h"
#include "Visitor.h"
#include <string>

using namespace std;

void writeResult(CommandsVisitor visitor, string out)
{
	ofstream of(out);
	
	auto turtle_state = visitor.get_environment().get_turtle_state();
	
	for (int i = 0; i < turtle_state->get_board_size(); ++i)
	{
		for (int j = 0; j < turtle_state->get_board_size(); ++j)
		{
			of << (turtle_state->getState(j,i) ? "*" : " ");
		}
		of << endl;
	}
	of.close();
}

string loadFromFile(char* path)
{
	ifstream is(path);
	if (!is.is_open())
	{
		cout << "No file";
		exit(-1);
	}
	std::stringstream strStream;
	strStream << is.rdbuf();
	std::string str = strStream.str();
	is.close();
	return str;
}

int main(int argc, char* argv[])
{
	if (argc < 7)
	{
		cout << " Not enough params";
		return -1;
	}
		
	string input; // "foo(x,n) if (n > 0) przod(x); lewo(45);foo(x*0.75,n-1);prawo(90);;foo(x*0.75,n-1);lewo(45);tyl(x);end;end; foo(20,3);";
	int boardSize = 100;
	string out;

	//vector<string> params(argc-1);
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i] == string("-i"))
		{
			input = loadFromFile(argv[++i]);
		}
		if (argv[i] == string("-o"))
		{
			out = argv[++i];
		}
		if (argv[i] == string("-s"))
		{
			boardSize = std::stoi(argv[++i]);
		}		
	}
	
	CommandsVisitor visitor(std::make_shared<TurtleState>(boardSize));
	try
	{
		Scanner s(input);
		auto tokens = s.tokenize();

		cout << "Tokenization successful!" <<endl;
		Parser p(tokens);
		auto program = p.parse();
		cout << "Parsing successful! "<<endl;

		cout << "Running program: " << endl;
		cout << program->toString() << endl;		
		program->accept(visitor);
	}
	catch (runtime_error& e)
	{
		cout << "ERROR :" << e.what();
		return -1;
	}
	cout << "OK";
	writeResult(visitor, out);
}
