#ifndef __IR__
#define __IR__

#include "Types.h"
using namespace std;

/**
 * This class represents one variable from program code.
 */
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign), rang(0) {}
	Variable(std::string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign), rang(0) {}
//private:
	VariableType m_type;
	std::string m_name;
	int m_position; // position in interference matrix
	Regs m_assignment; // which register allocated, if reg_var
	int rang; // if reg_var
	int value; // if mem_var
};

/**
* This type represents list of variables from program code.
*/
typedef std::list<Variable*> Variables;

/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE) {}
	Instruction (int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src) {}
// private:
	int m_position;
	InstructionType m_type;
	string instr_string;
	
	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;
};


/**
 * This type represents list of instructions from program code.
 */
typedef std::list<Instruction*> Instructions;

struct Label {
	string name;
	int pos; // ovo ako se poklapa sa pozicijom neke instrukcije, onda je ta instrukcija prva instrukcija te labele
	Instruction *first_instruction;
	Label() {};
	Label(string n) : name(n) {};
};

typedef std::list<Label*> Labels;

struct Func { // funkcija
	string name;
	int pos;
	//Instruction *first_instruction;
	Func() {};
	Func(string n) : name(n) {};
};

typedef std::list<Func*> Funcs;


#endif
