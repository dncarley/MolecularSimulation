
#include "oligo.h"

///
/// Default constructor for oligo.
///
oligo::oligo(){
	sequence.clear();		//! Clear contents of sequence.
	size = 0;				//! Set the size to zero.
}

///
/// Destructor for oligo.
///
oligo::~oligo(){

}

///
/// Print the contents of the sequence.  Every 32 nucleotides are followed by a newline `\n' character.
///
void oligo::printDNA(){
	
	for(size_t i = 0; i < sequence.size(); i++){
	
		sequence[i].printDNA();
		printf("\n");
	
	}
}

///
/// Clear the contents of the oligo.
///
void oligo::clear(){
	
	sequence.clear();		//! Clear the contents of sequence.
	size = 0;				//! Set the size to zero.
}

///
/// Append a DNA (s) to the oligo. 
///
void oligo::append(DNA s){

	unsigned block, cell;

	block = size >> 5;
	cell  = size & 31;
	
	if(cell == 0){				//! If there is not space, then resize the sequence.
		sequence.resize(sequence.size()+1);
	}
	sequence[block].set(cell, s);	
	size++;						//! Increment the sequence size.

}

///
/// Return true (1) if DNA (s) is located at position (n) in sequence.  Otherwise return false (0).
///
bool oligo::match(unsigned n, DNA s){

	bool returnValue;
	unsigned block, cell;
	
	block = n >> 5;
	cell  = n & 31;

	returnValue = sequence[block].match(cell, s);

	return returnValue;

}

///
/// Return a 32 character std::string of the oligo sequence.
///
std::string oligo::oligo2string(){

	std::string returnString;
	returnString = "";
	
	for(size_t i = 0; i < sequence.size(); i++){
	
		returnString += sequence[i].dna2string();
	
	}
		
	return returnString;

}

///
/// Convert a std::string (inString) to the sequence.  If the string contains less than 32 characters, the remaining bits will be set to zero.  If the string contains greater than 32 characters, then only the first 32 characters are stored.
///
void oligo::string2oligo(std::string inString){

	unsigned i, blocks;
	dna32 tempDNA;
	std::string tempString;
	blocks = inString.size() >>5;
	
	//// clear the oligo sequence
	sequence.clear();
	size = inString.size();

	if(blocks == 0){
		sequence.resize(1);
		sequence[0].string2dna(inString);
	}else{
		sequence.resize(blocks);
		for(i = 0; i < blocks; i++){
			tempString = inString.substr((i<<5), (i<<5)+32);
			sequence[i].string2dna(tempString);
		}
	}	
}
