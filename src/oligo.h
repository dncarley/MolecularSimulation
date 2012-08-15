#ifndef OLIGO_H_DEFINED
#define OLIGO_H_DEFINED

#include <vector>
#include "dna32.h"

//!  Stores a gel of oligos in a tube. 
/*!
  This class stores oligos
*/
class oligo : public dna32
{	
	public:
		unsigned size;						///< Store the length of the sequence
		std::vector< dna32 > sequence;		///< Store an expandable sequence 
		
		oligo();
		~oligo();
		void printDNA();
		void clear();
		void append(DNA s);
		void setNeuc(unsigned n, DNA s);
		bool match(unsigned n, DNA s);
		std::string oligo2string();
		void string2oligo(std::string inString);	
};

#endif
