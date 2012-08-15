		<center> README </center> 
---------------------------------------------------------------
		<center> Molecular Simulation 1.0.2 </center>
---------------------------------------------------------------

# Overview


This directory contains the source to MolecularSimulation, a simulation
environment for experimentation with DNA computation.

Three molecular algorithms to solve Satsfiability are included in the
implementation.  These are:

	Liptons's algorithm 			(Brute force) 
	Ogihara and Ray's algorithm 	(Branching heuristics) 
	Distribution algorithm			(Constructive)

# License


Molecular Simulation is released under the MIT license.  

See LICENSE for details.

# Introduction


Molecular Simulation implements molecular operators for simulation of molecular algorithms for Satisfiability.

# System requirements


MolecularSimulation requires the following software to be installed on your system:

        GCC
        Perl

Requirements for parallel execution:

        Perl Parallel::ForkManager

Additional requirements for generating documentation:

        Doxygen

This program was designed to execute in a 64-bit *NIX environment. Samples were executed on a 64-bit architecture with 4 GB of memory running Apple OS X 10.7.4.

# Algorithms


Molecular Simulation simulates the execution of three molecular algorithms for Satisfiability.

Lipton's algorithm

Introduced in 1995 by Lipton, this algorithm creates an exponential search space for the CNF expression. Once the space is created, each variable is evaluated and the space is reduced to only the solutions that satisfy all remaining strings. This algorithm is analogous to a conventional brute-force search for all solutions.

Ogihara and Ray's algorithm

Originally introduced in 1996 by Ogihara, and extended in 1997 with Ray, this algorithm builds a solution space with a breadth-first search evaluation. Prior to execution to the algorithm, each of the clauses variable's in the CNF expression are sorted.

Distribution algorithm

The distribution algorithm parses an input CNF expression into growing and self regulated set of possible combinations. A possible combination begins with all members of the first clause, and subsequent variables from independent clauses are built upon the reduced state. If there exist self-complementary assignments spanning a clause, then the clause is eliminated.

# Execution


Automation of execution can be done simply by executing the Perl script

$ perl runSimulation.pl

from the directory: MolecularSimulation/

This file will sequentially invoke `build.pl' and `executeMolecularSat.pl'

# Input

Input is provided as DIMACS CNF (*.cnf) to execute a specified algorithm. Arguments may be provided to assist in debugging (-d) or write the simulation results to a file.

# Output

Output consists of a summary of a test execution. This output conforms to the SAT Competition format for the status of the `*.cnf' expression. If desired, the output may be directed to a file. Conditional formatting of comment fields provide execution details.