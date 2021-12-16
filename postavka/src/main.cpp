#include <iostream>
#include <exception>

#include "Program.h"
#include "Print.h"

using namespace std;


int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\multiply.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			//cout << "Lexical analysis finished successfully!" << endl;
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		SyntaxAnalysis syntax(lex);

		bool retSynVal = syntax.Do();

		if (retSynVal)
		{
			//cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}

		Program p(syntax);

		p.makeInstructions();
		//cout << "Instructions made successfully!" << endl;
		p.managmentFlowGraph();
		//cout << "Managment flow graph made successfully!" << endl;

		p.livenessAnalysis();
		//cout << "Liveness analysis finished successfully!" << endl;

		p.buildInterferenceGraph();
		//cout << "Interference graph made successfully!" << endl;

		std::stack<Variable*>* stackVars = p.doSimplification(__REG_NUMBER__); //
		//cout << "Simplification stack made successfully!" << endl;
		 
		if (!p.doResourceAllocation(stackVars)) 
		{
			throw runtime_error("\nException! Resource allocation failed!\n");
			
		}
		else
		{
			//cout << "Resource allocation finished successfully!" << endl;
			cout << "Program translated successfully!" << endl;
			printProgram(p, "result.s"); // ili neki drugi fajl
		}

		//printInterferenceMatrix(p.ig);

		//for (Instruction *i : p.instructions) {
			//printInstruction(i);
		//}

	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
