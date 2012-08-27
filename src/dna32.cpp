/*! \file dna32.cpp
	\brief Defines functions for dna32 class.

*/

#include "dna32.h"

///
/// Default constructor for dna32. 
///
dna32::dna32(){
	sequence = 0L;		//! Set sequence to (uint64_t) 0.
};
		
///
/// Destructor for dna32.
///
dna32::~dna32(){

};

///
/// Clear the contents of sequence.  
///
void dna32::clear(){
	sequence = 0L;
}

///
/// Print the sequence as binary 63 downto 0, with a space each 16 bits.
///
void dna32::print(){

	for(int i = 63; i>=0; i--) {
		if((1L<<i)&sequence) printf("1");
		else			printf("0");
		if(i%16 == 0) 	printf(" ");
	}
}

///
/// Print the sequence as DNA 31 downto 0.
///
void dna32::printDNA(){
	
	uint64_t temp;
	
	for(int i = 31; i >= 0; i--) {
	
		temp = sequence;
		temp = temp >> ((i<<1));
		temp &= 3L;
		
		switch(temp){
			case 0L:
				printf("A");		//! Print A			
				break;
			case 1L:
				printf("C");		//! Print C		
				break;
			case 2L:
				printf("G");		//! Print G
				break;
			case 3L:
				printf("T");		//! Print T
				break;
			default:
				printf("Q");		//! Never reach default state.
				break;		
		}
	}
}

///
/// Set sequence position (n) from 31 downto 0 with neuc.
///
void dna32::set(unsigned n, DNA neuc){
	
	uint64_t shift;
	
	switch(neuc){
		case A:
			shift = 0L;
			break;
		case C:
			shift = 1L;
			break;
		case G:
			shift = 2L;
			break;
		case T:
			shift = 3L;
			break;
		default:
			shift = 0L;
			break;
	}
	sequence &= ~(3L << (62 - (n<<1)));	
	sequence |= (shift << (62 - (n<<1)));
}

///
/// Set sequence to dna32 value (s2).  
///
void dna32::set(dna32 s2){
	sequence = s2.sequence;
}

///
/// Get the DNA at position (n) in sequence.
///
DNA dna32::get(unsigned n){

	uint64_t temp;
	
	temp = (sequence >> ((31-n)<<1)) & 3L;
	switch(temp){
		case 0L:
			return A;
		case 1L:
			return C;
		case 2L:
			return G;
		case 3L:
			return T;
		default:
			return A;
	}
	
}

///
/// Return true (1) if (neuc) is located at position (n) in sequence.  Otherwise return false (0).
///
bool dna32::match(unsigned n, DNA neuc){

	uint64_t 	temp;
	
	temp = sequence; 
	temp = temp >> (62-(n<<1));
	temp &= 3L;
		
	if((int)temp == (int)neuc) return 1;
	else					   return 0;
	
}

///
/// Return true (1) if (s2) matches sequence.  Otherwise return false (0).
///
bool dna32::match(dna32 s2){

	if(sequence == s2.sequence) return 1;
	else						return 0;

}

///
/// Return true (1) if (s2.sequence & mask ) matches (sequence & mask).  Otherwise returns false (0).
///
bool dna32::match(dna32 s2, uint64_t mask){

	uint64_t t1, t2;
	
	t1 = sequence & mask;
	t2 = s2.sequence & mask;

	if(t1 == t2)	return 1;
	else			return 0;
	
}

///
/// Return a 32 character std::string of the sequence.
///
std::string dna32::dna2string(){

	uint64_t temp;
	std::string returnString;
	returnString = "";
	
	for(int i = 31; i >= 0; i--) {
	
		temp = sequence;
		temp = temp >> ((i<<1));
		temp &= 3L;
		
		switch(temp){
			case 0L:
				returnString +="A";		//! Add A to the string
				break;
			case 1L:
				returnString +="C";		//! Add C to the string
				break;
			case 2L:
				returnString +="G";		//! Add G to the string
				break;
			case 3L:
				returnString +="T";		//! Add T to the string
				break;
			default:
				returnString +="Q";		//! Never reach default case.
				break;		
		}
	}
	return returnString;

}

///
/// Convert a std::string (inString) to the sequence.  If the string contains less than 32 characters, the remaining bits will be set to zero.  If the string contains greater than 32 characters, then only the first 32 characters are stored.
///
void dna32::string2dna(std::string inString){
	
	std::string processString;
	processString = inString;
	
	if(processString.size() < 32){		// ensure that there are 32 nucleotides
		processString.append(32 -processString.size(), 'A');	
	}

	for(unsigned i = 0; i < 32; i++){	
		switch(processString[i]){
			case 'A':
				set(i, A);
				break;
			case 'C':
				set(i, C);
				break;
			case 'G':
				set(i, G);
				break;
			case 'T':
				set(i, T);
				break;
			default:
				set(i, A);
				break;
		}	
	}
}
