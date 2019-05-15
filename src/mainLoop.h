#include "FA.h"

int displayMainMenu();
int mainLoop();
void processAction(vector<FA*> *myFA, int action);
void showMyFA(vector<FA*> myFa);
void wordReco(vector<FA*> *myFA);
int askForFileNumber();
void addVectorFromFiles(vector<FA*> *myFA);
FA* pickFA(vector<FA*> *myFA);
int displayComputeMenu();
void processComputationFA(int a,FA *currentFA,vector<FA*> *myFA );
void completatationAndAdd(FA *currentFA,vector<FA*> *myFA);
void determinizeAndAdd(FA *currentFA,vector<FA*> *myFA);
void standardizeAndAdd(FA *currentFA,vector<FA*> *myFA);
void minimizeAndAdd(FA *currentFA,vector<FA*> *myFA);
void ComplementarizationAndAdd(FA *currentFA,vector<FA*> *myFA);

#ifndef FINITE_AUTOMATA_MATH_CS_MAINLOOP_H
#define FINITE_AUTOMATA_MATH_CS_MAINLOOP_H

#endif //FINITE_AUTOMATA_MATH_CS_MAINLOOP_H
