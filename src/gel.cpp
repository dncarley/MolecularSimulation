
#include <vector>
#include "gel.h"
#include "dna32.h"

///
/// Default gel constructor (empty).
///
gel::gel(){

	tube.clear();

}

///
/// Gel destructor.
///
gel::~gel(){


}

///
/// Clear gel contents
///
void gel::clear(){

	tube.clear();

}

///
/// Return the number of oligos in the gel.
///
size_t gel::size(){

	return tube.size();

}

///
/// Print the contents of the gel. No 5'--- 3' separation of oligos.
///
void gel::print(){

	for(size_t i = 0; i < tube.size(); i++){
		for(size_t j = 0; j < tube[i].sequence.size(); j++){
				tube[i].sequence[j].printDNA();
				printf("\n");
		}
	}

}

///
/// Print the contents of the gel with 5'--- 3' separation of oligos.
///
void gel::printDNA(){


	printf("TUBE::::::\n");
	for(size_t i = 0; i < tube.size(); i++){
		printf("----5'\n");
		tube[i].printDNA();
		printf("----3'\n\n");
	}
	printf("\n");



}

///
///	Mix a DNA nucleotide (s) into the gel.  Creates an oligo for storage.
///
void gel::mix(DNA s){

	oligo temp;
	temp.append(s);
	tube.push_back(temp);

}

///
/// Mix an oligo (s) into the gel.
///
void gel::mix(oligo s){

	tube.push_back(s);

}

///
/// Mix a gel (s) into the gel.
///
void gel::mix(gel s){

	tube.insert(tube.end(), s.tube.begin(), s.tube.end());

}

///
/// Append a DNA nucleotide (s) to each oligo in the gel.
///
void gel::append(DNA s){
	
	for(size_t i = 0; i < tube.size(); i++){
		tube[i].append(s);
	
	}

}

///
/// Append a dna32 sequence (s) to each oligo in the gel.
///
void gel::append(dna32 s){

	for(size_t i = 0; i < tube.size(); i++){
		tube[i].sequence.push_back(s);
		
	}

}

///
/// Append an oligo (s) to each oligo in the gel.
///
void gel::append(oligo s){

	if(tube.size() == 0){
		tube.push_back(s);
	}else{
		for(size_t i = 0; i < tube.size(); i++){		
			tube[i].sequence.insert(tube[i].sequence.end(), s.sequence.begin(), s.sequence.end());
		}
	}

}

/// 
/// Filters all oligos that are not equal to the DNA (s) at location (n).
///
gel gel::filterOthers(unsigned n, DNA s){

	gel returnValue;
	size_t i;

	returnValue.clear();
	
	for( i = 0; i < tube.size(); i++){
		if( tube[i].match(n, s) == 0){
			returnValue.mix( tube[i]);
		}
	}
	return returnValue;
}

/// 
/// Filters all oligos that does not have variable attributes for (inVar).
/// Note: inVar contains position and polarity.
///
gel gel::filterOthers(variable inVar){
	return filterOthers(inVar.var, inVar.neuc);
}

///
/// Filter a block (s) starting at position (n).
///
gel gel::filter(unsigned n, dna32 s){

	gel returnValue;

	returnValue.clear();
	
	for(size_t i = 0; i < tube.size(); i++){
		if(s.sequence == tube[i].sequence[n].sequence){
			returnValue.mix(tube[i]);
			tube.erase(tube.begin() + i);
		}	
	}
	return returnValue;
}

///
/// Filter by position (n) and polarity (s).
///
gel gel::filter(unsigned n, DNA s){


	gel returnValue;
	returnValue.clear();
	
	for(size_t i = 0; i < tube.size(); i++){

		if( tube[i].match(n, s) == 1){
			returnValue.mix( tube[i]);
			
		}
		
	}
	
	return returnValue;

}

///
/// Filter by variable.  
/// Note: inVar contains position and polarity.
///
gel gel::filter(variable inVar){

	return filter(inVar.var, inVar.neuc);

}

///
/// Eliminate any duplicate oligos in the gel.  
///
void gel::purifyGel(){

	size_t i;
	std::map<std::string, unsigned> uniqueMap;
	std::map<std::string, unsigned>::iterator it;
	oligo tempOligo;
	
	
	/// convert the tube to a unique hashmap
	for(i = 0; i < tube.size(); i++){
		uniqueMap.insert(std::pair<std::string, unsigned>(tube[i].oligo2string(), tube[i].size));
	}
	
	tube.clear();
	tube.reserve(uniqueMap.size());		// reserve memory for unique elements
	
	/// convert the unique hashmap back to an indexed tube
	for(it = uniqueMap.begin(); it != uniqueMap.end(); it++){
		tempOligo.string2oligo(it->first);
		tempOligo.size = it->second;
		tube.push_back(tempOligo);
    }
}
