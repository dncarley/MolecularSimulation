#ifndef DISTRIBUTION_SAT_DEFINED
#define DISTRIBUTION_SAT_DEFINED

#include "executeTest.h"

std::string vector2string( std::vector<variable> inVector);
std::vector<variable> string2vector( std::string inString);

std::vector< std::vector<variable> > uniqueSpace( std::vector< std::vector<variable> > S);

std::vector<variable> insertVariable(variable inVar, std::vector<variable> inVector, runtimeData & myData);
arguments distributionSat(const arguments myArgs);

#endif
