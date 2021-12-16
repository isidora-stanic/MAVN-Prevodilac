#pragma once
#include "Program.h"

string getRegister(Variable *v);
string getInstruction(Instruction *i);
void printProgram(Program& p, string filename);

void printInstructionsPos(Instructions& instrs);
void printVariablesNames(Variables& variables);
string stringType(InstructionType t);
void printInstruction(Instruction* instr);

void printInterferenceMatrix(InterferenceGraph& ig);