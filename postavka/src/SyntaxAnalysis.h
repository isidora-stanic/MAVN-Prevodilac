#pragma once

#include "LexicalAnalysis.h"
#include "Token.h"
#include "IR.h"

class SyntaxAnalysis
{
public:

	/**
	* Constructor
	*/
	SyntaxAnalysis(LexicalAnalysis& lex);

	~SyntaxAnalysis();

	/**
	* Method which performs lexical analysis
	*/
	bool Do();

	void printVariables();
	void printLabels();
	void printFunctions();

	Variable* findVariable(string name);
	Label* findLabel(string name);
	Func* findFunc(string name);

	Variables vars;
	Variable *active_var;

	Labels labels;
	Label *active_label;

	Funcs funcs;
	Func *active_func;

	int count;

	/**
	* Reference to lexical analysis module
	*/
	LexicalAnalysis& lexicalAnalysis;

private:
	/**
	* Prints the error message, and token that caused the syntax error
	*/
	void printSyntaxError(Token token);

	/**
	* Eats the current token if its type is "t"
	* otherwise reports syntax error
	*
	* param[in] - t - the expected token type
	*/
	void eat(TokenType t);

	/**
	* Returns the next token from the token list
	*/
	Token getNextToken();

	/**
	* Nonterminal Q
	*/
	void Q();

	/**
	* Nonterminal S
	*/
	void S();

	/**
	* Nonterminal L
	*/
	void L();

	/**
	* Nonterminal E
	*/
	void E();

	/**
	* Syntax error indicator
	*/
	bool errorFound;

	/**
	* Iterator to the token list which represents the output of the lexical analysis
	*/
	TokenList::iterator tokenIterator;

	/**
	* Current token that is being analyzed
	*/
	Token currentToken;
};