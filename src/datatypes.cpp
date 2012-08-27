/*! \file datatypes.cpp
	\brief Defines functions for literal and variable classes.

*/

#include "datatypes.h"

///
/// Print the type of nucleotide {A, C, G, T}.
///
void printDNA(DNA neuc){

	switch(neuc){
		case A:
			printf("A");		//< Print `A' for Adenine	
			break;
		case C:
			printf("C");		//< Print `C' for Cytosine		
			break;
		case G:
			printf("G");		//< Print `G' for Guanine
			break;
		case T:
			printf("T");		//< Print `T' for Thymine		
			break;
		default:
			printf("Q");		//< Print `Q' for invalid neuc
			break;		
	}
}

/////////////////////////////////////////////////

///
/// Default literal constructor.
///
literal::literal(){

	pos = 0;
	neg = 0;
}

///
/// Destructor for literal.
///
literal::~literal(){

}

///
/// Print the binary pair of literals [pos|neg].
///
void literal::printLiteral(){

	printf("%i%i", (int)pos, (int)neg); 	//< print [pos|neg] as binary

}

///
/// Determine if a variable is valid (exactly one bit set).
///
bool literal::isValid(){

	if( pos ^ neg  == 1) return 1;		//< Return true if (pos XOR neg == 1)
	else				 return 0;		

}

/////////////////////////////////////////////////

///
/// Default class constructor for variable.
///
variable::variable(){
	
	var 	 = 0;	//< (default var 	  = 0)
	pol.pos	 = 0;	//< (default pol.pos  = 0)
	pol.neg  = 0;	//< (default pol.neg  = 0)
	perm_var = 0;	//< (default perm_var = 0)
	neuc	 = A;   //< (default neuc     = A)
}

///
/// Overloaded class constructor for variable (set default index and polarity POS/NEG).
///
variable::variable(unsigned index, bool polarity){

	var 	 = index;			//< set variable to index
	perm_var = 0;				//< User adjustable permutation variable

	if( polarity == POS){		//< if (polarity == POS), then 
		pol.pos  = 1;
		pol.neg  = 0;
		neuc 	 = T;
	}else{						//< otherwise, (polarity == NEG)
		pol.pos  = 0;
		pol.neg  = 1;
		neuc 	 = C;
	}
}

///
/// Destructor for variable.
///
variable::~variable(){

}

///
/// Compares two variables; returns 1 if equal, 0 otherwise. 
/// (Note: only compares index and polarity)
///
bool variable::isEqual(variable arg){

	if(var == arg.var)
		if( pol.isValid() && arg.pol.isValid())
			if(pol.pos == arg.pol.pos)
				if(pol.neg == arg.pol.neg)
					return 1;
	return 0;

}
