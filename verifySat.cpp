
#include "verifySat.h"


bool verifySat(const CNF inCNF, const std::vector<literal> satVector){

	unsigned i, j;
	bool 	 returnValue, test;
	variable tempVariable;
	
	returnValue = 1;			/// assume satisfiable 
	
	/// verify that the satVector is valid
	for(i = 1; i < satVector.size(); i++){
		if( satVector[i].pos == 1 && satVector[i].neg == 1) return 0;
	}
	
	/// verify the clauses
	for(i = 0; i < inCNF.CNF_ORDER.size(); i++){
	
		test = 0;
		for(j = 0; j < inCNF.CNF_ORDER[i].size(); j++){
		
			tempVariable = inCNF.CNF_ORDER[i][j];

			if(tempVariable.pol.pos == 1 && satVector[tempVariable.var].pos == 1 ){
				test = 1;				
				break;
			}
			if(tempVariable.pol.neg == 1 && satVector[tempVariable.var].neg == 1 ){
				test = 1;
				break;
			}

		}
		returnValue &= test;
		if(returnValue == 0) break;		/// do not continue if unsatisfiable
		
	}
	return returnValue;
}

std::vector<literal> oligo2satVector(oligo inAssignment, int encoding){

	std::vector<literal> resultVector;
	literal tempLit;
	unsigned i;

	if(encoding == 0){
	
		resultVector.resize(inAssignment.size);
		
		for( i = 1; i < inAssignment.size; i++){

			if(inAssignment.match(i, T)){
				tempLit.pos = 1;
				tempLit.neg = 0;			
			}else if(inAssignment.match(i, C)){
				tempLit.pos = 0;
				tempLit.neg = 1;			
			}else{
				tempLit.pos = 0;
				tempLit.neg = 0;			
			}

			resultVector[i] = tempLit;
		}
	
	}else if(encoding == 1){
	
	
	
	}else{
	
		fprintf(stderr, "Provide a valid encoding for conversion\n");
	
	}
	
	return resultVector;

}



