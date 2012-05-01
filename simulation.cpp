
#include "simulation.h"

/*! \mainpage Molecular Simulation
 *
 * \section int_sec Introduction
 *
 * \par This program is a simulated molecular lab for experimenting with DNA operations.  
 *
 * \par Execution of a directory of DIMACS CNF (*.cnf) expressions can be performed with the Perl runSimulation.pl.
 *
 * \section sys_sec System requirements
 *
 * \par MolecularSimulation requires the following software to be installed on your system:
 *   - GCC
 *   - Perl
 *
 *	\par Additional requirements for generating documentation:
 *   - Doxygen
 *
 * \par This program was designed to execute in a 64-bit *NIX environment.  It has been tested on Apple OS X 10.6.8.  The final build will execute natively on the RIT CS machines (portability of the Perl scripts is in progress).
 *
 * \section alg_sec Algorithms
 * \par There are three molecular Satisfiability algorithms implemented in this environment.
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
 * \par Automation of execution can be done simply by executing the perl script
 *
 * $ perl runSimulation.pl
 *
 * \par from the directory: project/implementation/molecularSimulation/
 *
 * \par This file will sequentially invoke `build.pl' and `executeMolecularSat.pl' 
 *
 * \subsection input_sec Input
 * 
 *  \par Input is provided as DIMACS CNF (*.cnf) to execute a specified algorithm.  Arguments may be provided to assist in debugging (-d) or write the simulation results to a file. 
 *
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
