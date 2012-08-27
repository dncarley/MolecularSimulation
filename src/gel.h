/*! \file gel.h
	\brief Defines gel class.
	
*/

#ifndef GEL_H_DEFINED
#define GEL_H_DEFINED

#include <map>
#include "oligo.h"
#include "datatypes.h"

//!  Stores a gel of oligos in a tube. 
/*!
  This class stores (oligo)nucleotides, sequences of DNA.
*/
class gel : public oligo
{
	public:	
		std::vector<oligo> tube;		///< store a vector of oligos

		gel();
		~gel();
		
		void clear();
		size_t size();
		void print();
		void printDNA();
		void mix(DNA s);
		void mix(oligo s);
		void mix(gel s);
		void append(DNA s);
		void append(dna32 s);
		void append(oligo s);
		void setNeuc(unsigned n, DNA s);		
		gel filterOthers(unsigned n, DNA s);
		gel filterOthers(variable inVar);
		gel filter(unsigned n, dna32 s);
		gel filter(unsigned n, DNA s);
		gel filter(variable inVar);
		void purifyGel();
};

#endif
