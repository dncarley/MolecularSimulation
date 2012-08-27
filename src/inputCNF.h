/*! \file inputCNF.h
	\brief Defines class for CNF datatype.
	
*/

#ifndef INPUTCNF_H_INCLUDED
#define INPUTCNF_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "datatypes.h"


//!  CNF (Conjunctive Normal Form)
/*!
  Parse and store DIMACS CNF file for processing
*/
class CNF : public variable
{
	public:	
		std::vector< std::vector<literal> >  CNF_TABLE;		///< Store bit level assignments
		std::vector< std::vector<variable> > CNF_ORDER;		///< Store only variables
		unsigned numClause;									///< Number of clauses in expression
		unsigned numVar;									///< Number of variables in expression
	
		CNF();												
		~CNF();
		
		void parseCNF(const char* filename);
		void printCNF_table();
		void printCNF_order();
		void printCNF_orderLine(unsigned i);
};

#endif //INPUTCNF_H_INCLUDED
