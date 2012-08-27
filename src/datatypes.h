/*! \file datatypes.h
	\brief Defines classes for DNA, literal, and variable.
	
*/

#ifndef DATATYPES_H_DEFINED
#define DATATYPES_H_DEFINED

#include <inttypes.h>
#include <vector>
#include <stdio.h>

#define NEG   0						///< Define 0 as NEG
#define POS   1						///< Define 1 as POS

//! Define DNA
typedef enum {
	A,				///< A = 0
	C,				///< C = 1
	G,				///< G = 2
	T				///< T = 3
} DNA;

void printDNA(DNA neuc);

//!  Stores the status of a literal.
/*!
  Stores the property of an individual variable state. 
  Valid if (pos ^ neg == 1).
*/
class literal
{
	public:
		bool pos:1;			///< Positive literal
		bool neg:1;			///< Negative literal
		
		literal();
		~literal();
		void printLiteral();
		bool isValid();
};

/////////////////////////////////////////////////

//!  Stores the property of a variable state
/*!
  Stores the property of a variable state. Contains user adjustable properties.
*/
class variable : public literal
{
	public:	
		unsigned var;		///< Variable index
		literal	 pol;		///< Variable polarity
		unsigned perm_var;	///< Variable permutation index (user adjustable)
		DNA		 neuc;		///< Nucleotide type (user adjustable)		

		variable();
		~variable();
		variable(unsigned index, bool polarity);
		bool isEqual(variable arg);
};

#endif
