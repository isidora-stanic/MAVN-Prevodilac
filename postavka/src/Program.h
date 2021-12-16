#pragma once
#include "SyntaxAnalysis.h"

/**
* This type represents matrix of integers.
*/
typedef std::vector<std::vector<int>> InterferenceMatrix;

/**
* This type represents interference graph.
*/
typedef struct InterferenceGraphStruct
{
	Variables* variables;		// all variables from instructions
	InterferenceMatrix matrix;	// interference matrix

								/**
								* Default construction.
								*/
	InterferenceGraphStruct()
	{
	}
} InterferenceGraph;


class Program { // generisaje instrukcija
public:
	Instructions instructions;
	InterferenceGraph ig;
	SyntaxAnalysis *syn;
	Program(SyntaxAnalysis &s);
	~Program();

	/**
	* Initializes list of instructions
	*/
	void makeInstructions();

	/**
	* Management flow graph
	*/
	void managmentFlowGraph();

	/**
	* Liveness analysis
	*/
	void livenessAnalysis();

	/**
	* Builds interference graph
	*/
	void buildInterferenceGraph();

	/**
	* Checks if given two variables have interferance in interferance matrix
	*/
	bool haveInterference(Variable& v1, Variable& v2);

	/**
	* Simplification algorithm
	* @param degree numer of registers on hardware platform
	* @return simplification stack
	*/
	stack<Variable*>* doSimplification(int degree);

	/**
	* Resource allocation
	* @param simplificationStack stack with variables
	* @return true if allocation was successful
	*/
	bool doResourceAllocation(stack<Variable*>* simplificationStack);
};

bool existsVar(string name, Variables &vars);