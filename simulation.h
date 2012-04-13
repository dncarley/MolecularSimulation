#ifndef SIMULATION_H_DEFINED
#define SIMULATION_H_DEFINED

#include <iostream>
#include <queue>
#include <vector>
#include <inttypes.h>

#include "arguments.h"
#include "inputCNF.h"
#include "executeTest.h"
#include "verifySat.h"

//!  Execute the simulation for a Satisfiability expression
/*!
	This class implements start(int argc, char ** argv), a function that 
	will parse command line arguments, read a DIMACS CNF file, invoke the 
	test with a specified algorithm, and write the results to a file.
*/
class simulation : public arguments
{

	public:
		simulation();
		~simulation();
		void start(int argc, char ** argv);
};



#endif
