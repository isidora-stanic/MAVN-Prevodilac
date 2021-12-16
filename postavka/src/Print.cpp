#include "Print.h"

/**
* Returns name of assigned register
*/
string getRegister(Variable *v) {
	string s = "$t" + to_string(v->m_assignment - 1); // ovo je sigurno dobro
	return s;
}

/**
* Returns string which represents instruction
* String contains source and destination registers etc.
*/
string getInstruction(Instruction *i) {
	string instr = i->instr_string;
	for (Variable *v : i->m_dst) {
		if (v->m_type == Variable::REG_VAR) {
			instr.replace(instr.find("`d"), 2, getRegister(v));
		}
		else {
			instr.replace(instr.find("`d"), 2, v->m_name);
		}
	}
	for (Variable *v : i->m_src) {
		if (v->m_type == Variable::REG_VAR) {
			instr.replace(instr.find("`s"), 2, getRegister(v));
		}
		else {
			instr.replace(instr.find("`s"), 2, v->m_name);
		}
	}
	return instr;
}

/**
* Prints translated code into given file
*/
void printProgram(Program& p, string filename) {
	string globl = "";
	string data = ".data\n";
	string text = ".text\n";
	for (Func *f : p.syn->funcs) {
		globl += ".globl " + f->name + "\n";
	}
	for (Variable *mem : p.syn->vars) {
		if (mem->m_type == Variable::MEM_VAR) {
			data += mem->m_name + ":\t\t.word  " + to_string(mem->value) + "\n";
		}
	}
	Instructions::iterator it = p.instructions.begin();
	for (int i = 0; i < p.instructions.size(); i++, it++) {
		for (Func *f : p.syn->funcs) {
			if (f->pos == i) {
				text += f->name + ":\n";
			}
		}
		for (Label *l : p.syn->labels) {
			if (l->pos == i) {
				text += l->name + ":\n";
			}
		}
		text += "\t" + getInstruction(*it) + "\n";
	}

	string prg = globl + "\n" + data + "\n" + text;
	ofstream out(filename);
	out << prg;
	out.close();
}

/**
* Prints positions of instructions from given list
*/
void printInstructionsPos(Instructions& instrs)
{
	Instructions::iterator iter;

	for (iter = instrs.begin(); iter != instrs.end(); iter++)
	{
		cout << (*iter)->m_position;
	}
}

/**
* Prints names of variables from given list
*/
void printVariablesNames(Variables& variables)
{
	Variables::iterator iter;

	for (iter = variables.begin(); iter != variables.end(); iter++)
	{
		cout << (*iter)->m_name << " ";
	}
}

/**
* Returns name of instruction type
*/
string stringType(InstructionType t)
{
	switch (t) {
	case I_ADD:		return "add";
	case I_ADDI:	return "addi";
	case I_AND:		return "and";
	case I_B:		return "b";
	case I_BLTZ:	return "bltz";
	case I_LA:		return "la";
	case I_LB:		return "lb";
	case I_LI:		return "li";
	case I_LW:		return "lw";
	case I_NOP:		return "nop";
	case I_OR:		return "or";
	case I_SUB:		return "sub";
	case I_SW:		return "sw";
	default:		return "";
	}
}

/**
* For given instruction prints names of variables from lists:
*	type
*	dst
*	src
*	pred
*	succ
*	use
*	def
*	in
*	out
*/
void printInstruction(Instruction* instr)
{
	cout << "Pos: "<< instr->m_position << endl;

	cout << "Type:\t" << stringType(instr->m_type) << endl;

	cout << "Dst:\t";
	printVariablesNames(instr->m_dst);
	cout << endl;

	cout << "Src:\t";
	printVariablesNames(instr->m_src);
	cout << endl;

	cout << "Pred:\t";
	printInstructionsPos(instr->m_pred);
	cout << endl;

	cout << "Succ:\t";
	printInstructionsPos(instr->m_succ);
	cout << endl;

	cout << "Use:\t";
	printVariablesNames(instr->m_use);
	cout << endl;

	cout << "Def:\t";
	printVariablesNames(instr->m_def);
	cout << endl;

	cout << "In:\t";
	printVariablesNames(instr->m_in);
	cout << endl;

	cout << "Out:\t";
	printVariablesNames(instr->m_out);
	cout << endl;

	cout << "---------------------------------------------------" << endl;
}

void printInterferenceMatrix(InterferenceGraph& ig)
{
	if (ig.matrix.size() == 0)
	{
		cout << "There is nothing to print!" << endl;
		return;
	}

	cout << "==========================================" << endl;
	cout << "Interference matrix:" << endl;
	cout << "==========================================" << endl;

	// print existing variables in order to mark rows and columns
	for (auto varIt = ig.variables->begin(); varIt != ig.variables->end(); varIt++)
	{
		cout << "\t" << (*varIt)->m_name;
	}
	cout << endl;

	auto varIt = ig.variables->begin();
	for (auto it1 = ig.matrix.begin(); it1 != ig.matrix.end(); it1++)
	{
		cout << (*varIt++)->m_name;
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			cout << "\t" << *it2;
		}
		cout << endl;
	}
	cout << "  ";
	for (auto varIt = ig.variables->begin(); varIt != ig.variables->end(); varIt++)
	{
		cout << "\t" << (*varIt)->rang;
	}
	cout << endl;
	cout << "==========================================" << endl;
}