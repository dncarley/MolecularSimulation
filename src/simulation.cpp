/*! \file simulation.cpp
	\brief Defines simulation function and main() entry.

*/

#include "simulation.h"

/*! \mainpage Molecular Simulation
 *
 * \section int_sec Introduction
 *
 * \par Molecular Simulation implements molecular operators for simulation of molecular algorithms for Satisfiability.
 *
 * \section sys_sec System requirements
 *
 * \par MolecularSimulation requires the following software to be installed on your system:
 *   - GCC
 *   - Perl
 *
 *	\par Requirements for parallel execution:
 *   - Perl Parallel::ForkManager
 *
 *	\par Additional requirements for generating documentation:
 *   - Doxygen
 *
 * \par This program was designed to execute in a 64-bit *NIX environment.  Samples were executed on a 64-bit architecture with 4 GB of memory running Apple OS X 10.7.4.  
 *
 * \section alg_sec Algorithms
 * \par Molecular Simulation simulates the execution of three molecular algorithms for Satisfiability.
 *
 * \subsection lip_sec Lipton's algorithm  
 *
 *	\par Introduced in 1995 by Lipton, this algorithm creates an exponential search space for the CNF expression.  Once the space is created, each variable is evaluated and the space is reduced to only the solutions that satisfy all remaining strings.  This algorithm is analogous to a conventional brute-force search for all solutions.
 *
 * \subsection ogi_sec Ogihara and Ray's algorithm
 *
 *  \par Originally introduced in 1996 by Ogihara, and extended in 1997 with Ray, this algorithm builds a solution space with a breadth-first search evaluation.  Prior to execution to the algorithm, each of the clauses variable's in the CNF expression are sorted.  
 *
 * \subsection dis_sec Distribution algorithm
 *  
 * \par The distribution algorithm parses an input CNF expression into growing and self regulated set of possible combinations.  A possible combination begins with all members of the first clause, and subsequent variables from independent clauses are built upon the reduced state.  If there exist self-complementary assignments spanning a clause, then the clause is eliminated.  
 *
 * \section exe_sec Execution
 * 
 * \par Automation of execution can be done simply by executing the Perl script
 *
 * $ perl runSimulation.pl
 *
 * \par from the directory: MolecularSimulation/
 *
 * \par This file will sequentially invoke `build.pl' and `executeMolecularSat.pl' 
 *
 * \subsection input_sec Input
 * 
 *  \par Input is provided as DIMACS CNF (*.cnf) to execute a specified algorithm.  Arguments may be provided to assist in debugging (-d) or write the simulation results to a file. 
 *
 * \subsection output_sec Output
 *
 * \par Output consists of a summary of a test execution.  This output conforms to the SAT Competition format for the status of the `*.cnf' expression.  If desired, the output may be directed to a file.  Conditional formatting of comment fields provide execution details.
 */
 
///
/// Default constructor for simulation.
///
simulation::simulation(){

}

///
/// Destructor for simulation.
///
simulation::~simulation(){

}

///
/// Start simulation.
///
void simulation::start(int argc, char ** argv){

	arguments testArguments;

	// Set version revision number 	
	testArguments.versionNumber = (char*) malloc (10);
	strcpy(testArguments.versionNumber, "1.0.2");
	
	testArguments.parseArguments(argc, argv);					///< Parse user arguments
	testArguments.inputCNF.parseCNF( testArguments.filename);	///< Parse DIMACS CNF
	testArguments = executeTest(testArguments);					///< Execute algorithm
	testArguments.writeOutput();								///< Write output results

	// Print debug arguments
	if(testArguments.debug){
		testArguments.printArguments();
	}
}


///
/// main simulation entry
///
int main(int argc, char ** argv){		

	simulation myRun;
	
	myRun.start(argc, argv);
	
	return 0;	
}
