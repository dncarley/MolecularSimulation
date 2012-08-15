#ifndef DNA32_H_DEFINED
#define DNA32_H_DEFINED

#include <iostream>
#include <string>
#include "datatypes.h"

//!  Stores 32 DNA nucleotides 
/*!
  This class stores 32 DNA nucleotides as an uint64_t datatype.
  Operations for operating directly are provided.  
  It is recommended to construct an oligo for extendable manipulation of DNA.
*/
class dna32
{

	public:
		uint64_t sequence;			///< stores 32 DNA nucleotides
		
		dna32();		
		~dna32();
		void clear();
		void print();
		void printDNA();
		void set(unsigned n, DNA neuc);
		void set(dna32 s2);
		DNA get(unsigned n);
		bool match(unsigned n, DNA neuc);
		bool match(dna32 s2);
		bool match(dna32 s2, uint64_t mask);		
		std::string dna2string();
		void string2dna(std::string inString);
		
};

#endif
