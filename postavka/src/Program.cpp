#include "Program.h"

Program::Program(SyntaxAnalysis &s) 
{
	syn = &s;
}

Program::~Program() {
	for (auto it = instructions.begin(); it != instructions.end(); it++) {
		delete *it;
	}
}

void Program::makeInstructions() 
{
	int count = 0;
	TokenList::iterator it = syn->lexicalAnalysis.getTokenList().begin();
	for (int j = 0; j < syn->lexicalAnalysis.getTokenList().size(); j++, it++) { // Token t : syn.lexicalAnalysis.getTokenList()
		Token t = *it; // mozda for auto it..., ili samo while it !=...end()...
		Instruction *i;
		Variable *mem;
		switch (t.getType()) {
		case T_MEM:
			advance(it, 1);
			mem = syn->findVariable(it->getValue());
			advance(it, 1);
			mem->value = stoi(it->getValue());
			advance(it, -2);
			break;
		case T_ADD:
			i = new Instruction();
			i->m_type = I_ADD;
			i->m_position = count;
			i->instr_string = "add\t\t`d, `s, `s";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, -5);
			instructions.push_back(i);
			count++;
			break;
		case T_ADDI: // ima literal
			i = new Instruction();
			i->m_type = I_ADDI;
			i->m_position = count;
			i->instr_string = "addi\t`d, `s, ";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->instr_string += it->getValue();
			advance(it, -5);
			instructions.push_back(i);
			count++;
			break;
		case T_SUB:
			i = new Instruction();
			i->m_type = I_SUB;
			i->m_position = count;
			i->instr_string = "sub\t\t`d, `s, `s";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, -5);
			instructions.push_back(i);
			count++;
			break;
		case T_LA:
			i = new Instruction();
			i->m_type = I_LA;
			i->m_position = count;
			i->instr_string = "la\t\t`d, `s";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, -3);
			instructions.push_back(i);
			count++;
			break;
		case T_LI:
			i = new Instruction();
			i->m_type = I_LI;
			i->m_position = count;
			i->instr_string = "li\t\t`d, ";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->instr_string += it->getValue();
			advance(it, -3);
			instructions.push_back(i);
			count++;
			break;
		case T_LW: // ima labelu
			i = new Instruction();
			i->m_type = I_LW;
			i->m_position = count;
			i->instr_string = "lw\t\t`d, ";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->instr_string += it->getValue() + "(";
			advance(it, 2);
			i->instr_string += "`s)";
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, -5);
			instructions.push_back(i);
			count++;
			break;
		case T_SW: // ima literal
			i = new Instruction();
			i->m_type = I_SW;
			i->m_position = count;
			i->instr_string = "sw\t\t`s, ";
			advance(it, 1);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->instr_string += it->getValue() + "(";
			advance(it, 2);
			i->instr_string += "`s)";
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, -5);
			instructions.push_back(i);
			count++;
			break;
		case T_BLTZ: // ima labelu
			i = new Instruction();
			i->m_type = I_BLTZ;
			i->m_position = count;
			i->instr_string = "bltz\t`s, ";
			advance(it, 1);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->instr_string += it->getValue();
			advance(it, -3);
			instructions.push_back(i);
			count++;
			break;
		case T_B: // ima labelu
			i = new Instruction();
			i->m_type = I_B;
			i->m_position = count;
			i->instr_string = "b\t\t";
			advance(it, 1);
			i->instr_string += it->getValue();
			advance(it, -1);
			instructions.push_back(i);
			count++;
			break;
		case T_AND:
			i = new Instruction();
			i->m_type = I_AND;
			i->m_position = count;
			i->instr_string = "and\t\t`d, `s, `s";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, -5);
			instructions.push_back(i);
			count++;
			break;
		case T_OR:
			i = new Instruction();
			i->m_type = I_OR;
			i->m_position = count;
			i->instr_string = "or\t\t`d, `s, `s";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, -5);
			instructions.push_back(i);
			count++;
			break;
		case T_LB: // ima literal
			i = new Instruction();
			i->m_type = I_LB;
			i->m_position = count;
			i->instr_string = "lb\t\t`d, ";
			advance(it, 1);
			i->m_dst.push_back(syn->findVariable(it->getValue()));
			advance(it, 2);
			i->instr_string += it->getValue() + "(";
			advance(it, 2);
			i->instr_string += "`s)";
			i->m_src.push_back(syn->findVariable(it->getValue()));
			advance(it, -5);
			instructions.push_back(i);
			count++;
			break;
		case T_NOP:
			i = new Instruction();
			i->m_type = I_NOP;
			i->m_position = count;
			i->instr_string = "nop";
			instructions.push_back(i);
			count++;
			break;
		}
	}
}

void Program::managmentFlowGraph() {
	map<int, Instruction*> instrMap;
	map<string, int> lblMap; // naziv labele --> pozicija na kojoj se nalazi (prva instrukcija)
	//map<string, int> funMap; -- kad bude instrukcija poziva funkcije, uvezuje se kao labela
	for (auto it = instructions.begin(); it != instructions.end(); it++) {
		instrMap[(*it)->m_position] = *it;
	}
	for (auto it = syn->labels.begin(); it != syn->labels.end(); it++) {
		lblMap[(*it)->name] = (*it)->pos;
	}
	//for (auto it = syn->funcs.begin(); it != syn->funcs.end(); it++) { -- kad bude instrukcija poziva funkcije, uvezuje se kao labela
	//	funMap[(*it)->name] = (*it)->pos;
	//}
	for (int i = 0; i < instructions.size(); i++) {
		// popunjavanje m_def i m_use skupova
		for (Variable *v : instrMap[i]->m_dst) {
			if (v->m_type == Variable::REG_VAR) {
				instrMap[i]->m_def.push_back(v);
			}
		}
		for (Variable *v : instrMap[i]->m_src) {
			if (v->m_type == Variable::REG_VAR) {
				instrMap[i]->m_use.push_back(v);
			}
		}

		// uvezivanje grafa upravljanja toka ili kako vec
		if (i == 0) {
			instrMap[i]->m_succ.push_back(instrMap[i + 1]);
		}
		else if (i == instructions.size() - 1) {
			instrMap[i]->m_pred.push_back(instrMap[i - 1]);
		}
		else {
			instrMap[i]->m_succ.push_back(instrMap[i + 1]);
			instrMap[i]->m_pred.push_back(instrMap[i - 1]);			
		}
		string lbl;
		int comma;
		int nextInstrPos;
		// neka provera za funkcije?? ne znam...

		switch (instrMap[i]->m_type)
		{
		case I_B:
			// b label
			lbl = instrMap[i]->instr_string.substr(2, instrMap[i]->instr_string.length() - 2);
			if (lblMap.count(lbl) > 0) {
				nextInstrPos = lblMap[lbl];
				instrMap[i]->m_succ.push_back(instrMap[nextInstrPos]);
				instrMap[nextInstrPos]->m_pred.push_back(instrMap[i]);
			}
			else {
				throw runtime_error("Label not defined!");
			}
			break;
		case I_BLTZ:
			// bltz rs, label
			comma = instrMap[i]->instr_string.find(",");
			lbl = instrMap[i]->instr_string.substr(comma + 2, instrMap[i]->instr_string.length() - (comma + 2));
			if (lblMap.count(lbl) > 0) {
				nextInstrPos = lblMap[lbl];
				instrMap[i]->m_succ.push_back(instrMap[nextInstrPos]);
				instrMap[nextInstrPos]->m_pred.push_back(instrMap[i]);
			}
			else {
				throw runtime_error("Label not defined!");
			}
			break;
		default:
			// druge instrukcije ne primaju labelu
			break;
		}
	}
}

void Program::livenessAnalysis()
{
	bool doItAgain = true;

	while (doItAgain) {
		doItAgain = false;

		Instructions::reverse_iterator rit = instructions.rbegin();
		for (; rit != instructions.rend(); rit++) {
			// 0. in' = in, out' = out
			Variables& out = (*rit)->m_out;
			Variables& in = (*rit)->m_in;
			Variables newOut;
			Variables newIn;

			// 1. newOut = U succIn
			Instructions& successors = (*rit)->m_succ;
			Instructions::iterator succIt = successors.begin();
			for (; succIt != successors.end(); succIt++) {
				Variables& succIn = (*succIt)->m_in;
				newOut.insert(newOut.end(), succIn.begin(), succIn.end());
			}
			newOut.sort();
			newOut.unique();

			// 2. newIn = use U (out/def)
			Variables& use = (*rit)->m_use;
			Variables& def = (*rit)->m_def;

			Variables outMinusDef;
			Variables::iterator varIt = out.begin();
			for (; varIt != out.end(); varIt++) {
				if (!existsVar((*varIt)->m_name, def)) { // ako ne postoji variabla u def
					outMinusDef.push_back(*varIt);
				}
			}

			newIn = use;
			newIn.insert(newIn.end(), outMinusDef.begin(), outMinusDef.end());
			newIn.sort();
			newIn.unique();

			if (newIn != in || newOut != out) {
				doItAgain = true;
			}

			in = newIn;
			out = newOut;
		}
	}
}

bool existsVar(string name, Variables &vars) {
	for (Variable *v : vars) {
		if (v->m_name == name)
			return true;
	}
	return false;
}

void Program::buildInterferenceGraph()
{
	InterferenceMatrix matrix;
	Variables *regVars = new Variables();
	int count = 0;
	for (Variable *v : syn->vars) {
		if (v->m_type == Variable::REG_VAR) {
			v->m_position = count;
			count++;
			regVars->push_back(v);
		}
	}
	for (Variable *v : *regVars) {
		matrix.push_back(vector<int>(regVars->size(), __EMPTY__));
	}

	for (Instruction *i : instructions) {
		for (Variable *v1 : i->m_def) { // svakako ima samo registre
			for (Variable *v2 : i->m_out) { // svakako ima samo registre
				if (v1 != v2) {
					if (matrix[v1->m_position][v2->m_position] != __INTERFERENCE__) {
						matrix[v1->m_position][v2->m_position] = __INTERFERENCE__;
						matrix[v2->m_position][v1->m_position] = __INTERFERENCE__;
						v1->rang++; v2->rang++;
					}
				}
			}
		}
	}
	ig.variables = regVars;
	ig.matrix = matrix;
	//return ig;
}


Variables save;


int getColor(Variable * notColoredVariable, InterferenceGraph * ig) {
	Variables::iterator iter;
	Variables temp;

	// get variable from stack which are interference with notColoredVariable
	for (iter = save.begin(); iter != save.end(); iter++) {
		Variable * variable = (*iter);

		if (ig->matrix[notColoredVariable->m_position][variable->m_position] == __INTERFERENCE__) {
			temp.push_back(variable);
		}
		else {
			// nothing
		}
	}

	// find diffrent color
	bool find;

	for (int color = 1; color < __REG_NUMBER__ + 1; color++) {

		find = true;

		for (iter = temp.begin(); iter != temp.end(); iter++) {
			if (color == (*iter)->m_assignment) {
				find = false;
			}
		}

		if (find == true) {
			return color;
			break;
		}
	}

	return Regs::no_assign;
}

bool Program::haveInterference(Variable& v1, Variable& v2) {
	return ig.matrix[v1.m_position][v2.m_position] == __INTERFERENCE__;
}

std::stack<Variable*>* Program::doSimplification(int degree) {

	Variables helping(*ig.variables);
	std::stack<Variable*>* stackVars = new std::stack<Variable*>();
	while (stackVars->size() < ig.variables->size()) {
		Variable* hasMaxRang = helping.front();
		for (Variable *v : *ig.variables) {
			if (v->rang > hasMaxRang->rang && v->rang < degree && find(helping.begin(), helping.end(), v) != helping.end()) {
				hasMaxRang = v;
			}
		}
		stackVars->push(hasMaxRang);
		helping.remove(hasMaxRang); // proveri da ne skida iz niza varijabli...
		for (Variable *v1 : *ig.variables) {
			if (v1 != hasMaxRang && haveInterference(*v1, *hasMaxRang)) {// ako ima smetnju s njim, smanji mu rang
				v1->rang--;
			}
		}
	}
	return stackVars;
}

bool Program::doResourceAllocation(stack<Variable *> * simplificationStack) {

	Variable *currentVariable, *previusVariable;

	previusVariable = NULL;

	int counter = 1;

	while (simplificationStack->size() > 0) {

		currentVariable = simplificationStack->top();
		simplificationStack->pop();

		save.push_back(currentVariable);

		if (previusVariable == NULL) {
			// first variable on stact
			currentVariable->m_assignment = (Regs)counter;
		}
		else {
			// other varables
			int color = getColor(currentVariable, &ig);
			if (color == Regs::no_assign) {
				return false;
			}
			else {
				currentVariable->m_assignment = (Regs)color;
			}
		}

		previusVariable = currentVariable;
	}

	ig.variables = &save;

	delete simplificationStack;

	return true;
}