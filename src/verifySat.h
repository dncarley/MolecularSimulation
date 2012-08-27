/*! \file verifySat.h
	\brief Defines function prototypes for Sat verifier.

*/

#ifndef SAT_VERIFY_H_DEFINED
#define SAT_VERIFY_H_DEFINED

#include "inputCNF.h"
#include "arguments.h"
#include "gel.h"

bool verifySat(const CNF inCNF, const std::vector<literal> satVector);
std::vector<literal> oligo2satVector(oligo inAssignment, int encoding);

#endif
