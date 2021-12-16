#include <iostream>
#include <iomanip>

#include "SyntaxAnalysis.h"

using namespace std;


SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex)
	: lexicalAnalysis(lex), errorFound(false), tokenIterator(lexicalAnalysis.getTokenList().begin()), count(0),
	active_func(NULL), active_label(NULL), active_var(NULL)
{
}

SyntaxAnalysis::~SyntaxAnalysis()
{
	for (auto it = vars.begin(); it != vars.end(); it++) {
		delete *it;
	}
	for (auto it = labels.begin(); it != labels.end(); it++) {
		delete *it;
	}
	for (auto it = funcs.begin(); it != funcs.end(); it++) {
		delete *it;
	}
}

bool SyntaxAnalysis::Do()
{
	currentToken = getNextToken();
	Q();
	if (funcs.empty() || findFunc("main") == NULL)
		errorFound = true;
	return !errorFound;
}

Variable* SyntaxAnalysis::findVariable(string name) {
	for (Variable *v : vars) {
		if (v->m_name == name) {
			return v;
		}
	}
	return NULL;
}

Label* SyntaxAnalysis::findLabel(string name) {
	for (Label *l : labels) {
		if (l->name == name)
			return l;
	}
	return NULL;
}

Func* SyntaxAnalysis::findFunc(string name) {
	for (Func *f : funcs) {
		if (f->name == name)
			return f;
	}
	return NULL;
}

void SyntaxAnalysis::printVariables() {
	for (auto it = vars.begin(); it != vars.end(); it++) {
		cout << (*it)->m_name << endl;
	}
}

void SyntaxAnalysis::printLabels() {
	for (auto it = labels.begin(); it != labels.end(); it++) {
		cout << (*it)->name << " " << (*it)->pos << endl;
	}
}

void SyntaxAnalysis::printFunctions() {
	for (auto it = funcs.begin(); it != funcs.end(); it++) {
		cout << (*it)->name << " " << (*it)->pos << endl;
	}
}

void SyntaxAnalysis::printSyntaxError(Token token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
}


void SyntaxAnalysis::eat(TokenType t)
{
	if (errorFound == false)
	{
		if (currentToken.getType() == t)
		{
			switch (t) {
			case T_FUNC:
				active_func = new Func();
				active_func->pos = count;
				break;
			case T_ID:
				if (active_func != NULL) {
					active_func->name = currentToken.getValue();
				}
				else {
					if (findFunc(currentToken.getValue()) == NULL) {
						active_label = new Label(currentToken.getValue());
						active_label->pos = count;
					}
					else {
						printSyntaxError(currentToken);
						errorFound = true;
						throw runtime_error("");
					}
				}
				break;
			case T_REG:
				active_var = new Variable();
				active_var->m_type = Variable::REG_VAR;
				break;
			case T_R_ID:
				if (active_var != NULL && active_var->m_type == Variable::REG_VAR) {
					active_var->m_name = currentToken.getValue();
				}
				else {
					active_var = findVariable(currentToken.getValue());
					if (active_var) {
						active_var = NULL;
					}
					else {
						printSyntaxError(currentToken);
						errorFound = true;
						throw runtime_error("");
					}
				}
				break;
			case T_MEM:
				active_var = new Variable();
				active_var->m_type = Variable::MEM_VAR;
				break;
			case T_M_ID:
				if (active_var != NULL  && active_var->m_type == Variable::MEM_VAR) {
					active_var->m_name = currentToken.getValue();
					active_var == NULL;
				}
				else {
					active_var = findVariable(currentToken.getValue());
					if (active_var) {
						active_var = NULL;
					}
					else {
						printSyntaxError(currentToken);
						errorFound = true;
						throw runtime_error("");
					}
				}
				break;
			default:
				break;
			}
			if (t != T_END_OF_FILE)
				currentToken = getNextToken();
		}
		else
		{
			printSyntaxError(currentToken);
			errorFound = true;
			throw runtime_error("");
		}
	}
}


Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached"); // ASK: da li treba da se baca greska ili da se eof tretira kao da je sve u redu
	return *tokenIterator++;
}


void SyntaxAnalysis::Q()
{
	// Q -> S ; L
	S();
	eat(T_SEMI_COL);
	L();
}


void SyntaxAnalysis::S()
{
	// S -> _mem mid num
	// S -> _reg rid
	// S -> _func id
	// S -> id: E
	// S -> E
	switch (currentToken.getType())
	{
	case T_MEM:
		eat(T_MEM);
		eat(T_M_ID);
		eat(T_NUM);
		vars.push_back(active_var);
		active_var = NULL;
		break;
	case T_REG:
		eat(T_REG);
		eat(T_R_ID);
		vars.push_back(active_var);
		active_var = NULL;
		break;
	case T_FUNC:
		eat(T_FUNC);
		eat(T_ID);
		funcs.push_back(active_func);
		active_func = NULL;
		break;
	case T_ID:
		eat(T_ID);
		eat(T_COL);
		E();
		labels.push_back(active_label);
		break;
	default:
		E();
	}
}


void SyntaxAnalysis::L()
{
	// L -> eof
	// L -> Q
	switch (currentToken.getType()) {
	case T_END_OF_FILE:
		eat(T_END_OF_FILE);
		break;
	default:
		Q();
	}
}


void SyntaxAnalysis::E()
{
	// E -> add rid, rid, rid
	// E -> addi rid, rid, num
	// E -> sub rid, rid, rid
	// E -> la rid, mid
	// E -> lw rid, num(rid)
	// E -> li rid, num
	// E -> sw rid, num(rid)
	// E -> b id
	// E -> bltz rid, id
	// E -> nop
	//---dodate instrukcije---
	// E -> and rid, rid, rid
	// E -> or rid, rid, rid
	// E -> lb rid, num(rid)
	switch (currentToken.getType())
	{
	case T_ADD:
		eat(T_ADD);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		break;
	case T_ADDI:
		eat(T_ADDI);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		break;
	case T_SUB:
		eat(T_SUB);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		break;
	case T_LA:
		eat(T_LA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_M_ID);
		break;
	case T_LW:
		eat(T_LW);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		eat(T_L_PARENT);
		eat(T_R_ID);
		eat(T_R_PARENT);
		break;
	case T_LI:
		eat(T_LI);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		break;
	case T_SW:
		eat(T_SW);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		eat(T_L_PARENT);
		eat(T_R_ID);
		eat(T_R_PARENT);
		break;
	case T_B:
		eat(T_B);
		eat(T_ID);
		break;
	case T_BLTZ:
		eat(T_BLTZ);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_ID);
		break;
	case T_AND:
		eat(T_AND);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		break;
	case T_OR:
		eat(T_OR);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		break;
	case T_LB:
		eat(T_LB);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		eat(T_L_PARENT);
		eat(T_R_ID);
		eat(T_R_PARENT);
		break;
	default:
		eat(T_NOP);
	}
	count++;
}