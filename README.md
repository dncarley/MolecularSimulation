
		<center> Molecular Simulation 1.0.2 </center>
---------------------------------------------------------------

# Overview


This directory contains the source to MolecularSimulation, a simulation
environment for experimentation with DNA computation.

Three molecular algorithms to solve Satsfiability are included in the
implementation.  These are:

	* Liptons's algorithm 			(Brute force) 
	* Ogihara and Ray's algorithm 	(Branching heuristics) 
	* Distribution algorithm			(Constructive)

# License

Molecular Simulation is released under the MIT license.  

See LICENSE for details.

# System requirements

MolecularSimulation requires the following software to be installed on your system:

	* [GCC](http://gcc.gnu.org/)
	* [Perl](http://www.perl.org/)

Requirements for parallel execution:

	* [Perl Parallel::ForkManager](http://search.cpan.org/~dlux/Parallel-ForkManager-0.7.5/ForkManager.pm)

Additional requirements for generating documentation:

	* [Doxygen](http://www.stack.nl/~dimitri/doxygen/)

This program was designed to execute in a 64-bit *NIX environment. Samples were executed on a 64-bit architecture with 4 GB of memory running Apple OS X 10.7.4.

# Algorithms

Molecular Simulation simulates the execution of three molecular algorithms for Satisfiability.

## Lipton's algorithm

Introduced in 1995 by Lipton, this algorithm creates an exponential search space for the CNF expression. Once the space is created, each variable is evaluated and the space is reduced to only the solutions that satisfy all remaining strings. This algorithm is analogous to a conventional brute-force search for all solutions.

## Ogihara and Ray's algorithm

Originally introduced in 1996 by Ogihara, and extended in 1997 with Ray, this algorithm builds a solution space with a breadth-first search evaluation. Prior to execution to the algorithm, each of the clauses variable's in the CNF expression are sorted.

## Distribution algorithm

The distribution algorithm parses an input CNF expression into growing and self regulated set of possible combinations. A possible combination begins with all members of the first clause, and subsequent variables from independent clauses are built upon the reduced state. If there exist self-complementary assignments spanning a clause, then the clause is eliminated.

# Execution

Automation of execution can be done simply by executing the Perl script from the directory: <code>MolecularSimulation/</code>

	*<code>$ perl runSimulation.pl</code>

This file will sequentially invoke <code>build.pl</code> and <code>executeMolecularSat.pl</code>

# Input

<table border="1">
  <tr>
    <td>Argument</td>
    <td>Parameters</td>
    <td>Description</td>
  </tr>
  <tr>
    <td> <code>-d</code> </td>
    <td> </td>
    <td> Distribution algorithm</td>
  </tr>
  <tr>
    <td> <code>-l</code> </td>
    <td> </td>
    <td> Lipton's algorithm</td>
  </tr>  
  <tr>
    <td> <code>-o</code> </td>
    <td> </td>
    <td> Ogihara and Ray's algorithm</td>
  </tr>    
  <tr>
    <td> <code>-debug</code> </td>
    <td> </td>
    <td> Debug</td>
  </tr>    
  <tr>
    <td> <code>-p</code> </td>
    <td> <code> [CNF file path] </code> </td>
    <td> Specify CNF file path.</td>
  </tr>    
  <tr>
    <td> <code>-f</code> </td>
    <td> </td>
    <td> Write output to file.</td>
  </tr>    
</table>

# Output

Output consists of a summary of the execution for a DIMACS CNF file. This output conforms to the SAT Competition format for the status of the <code>*.cnf</code> expression. If desired, the output may be directed to a file. Conditional formatting of comment fields provide execution details.