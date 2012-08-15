#ifndef ARGUMENT_PARSE_H_DEFINED
#define ARGUMENT_PARSE_H_DEFINED

#include "inputCNF.h"

//! Store internal state of algorithm execution.
/*!
	Store public data during the execution of an algorithm.
*/
class runtimeData
{

	public:

		time_t executionTime;		///< Execution time in seconds.
		size_t memoryUsage;			///< Simulation memory usage in bytes.
		size_t mixCount;			///< Accumulate number of mix operations.
		size_t extractCount;		///< Accumulate number of extract operations.
		size_t appendCount;			///< Accumulate number of append operations.
		size_t splitCount;			///< Accumulate number of split operations.
		size_t spliceCount;			///< Accumulate number of splice operations.
		size_t purifyCount;			///< Accumulate number of purify operations.

		runtimeData();
		~runtimeData();
};


//////////////////////////////////////////////////

//!  Process and store arguments
/*!
	Process and store state of arguments during execution
*/
class arguments
{
	public:
		int algorithmType;				///< 0 Lipton, 1 Ogihara-Ray, 2 Distribution
		int debug;						///< 0 No debug, 1 print debugging				
		int writeFile;					///< 0 Print to STDOUT, 1 write to outputfile
		int isSat;						///< 0 false, 1 true, 2 unknown 
		time_t executionTime;			///< Execution time in seconds.
		size_t memoryUsage;				///< Simulation memory usage in bytes.
		runtimeData myData;
		char * filename;				///< input DIMACS CNF filename
		char * outputfile;				///< output is written to file
		char * versionNumber;			///< Store version number
		CNF inputCNF;					///< Storage of CNF expression (initially unallocated)
		std::vector< std::vector<literal> > result;		///< result stored in [<0:numResults >[1:n]]
				
		arguments();
		~arguments();
		
		void parseArguments(int argc, char ** argv);
		void printArguments();
		void writeOutput();
		

};

#endif
