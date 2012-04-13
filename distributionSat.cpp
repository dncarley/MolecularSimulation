
#include "distributionSat.h"

///
/// Convert a std::vector<variable> (inVector) to a std::string.
///
std::string vector2string( std::vector<variable> inVector){

	std::string returnValue;
	char * cStringBuffer;
	int n;
	
	returnValue = "";	
	cStringBuffer = new char[20+1];

	for( size_t i = 0; i < inVector.size(); i++){
	
		if( inVector[i].pol.isValid()){
					
			if(inVector[i].pol.pos == 1){
				returnValue.append("+");
			}else{
				returnValue.append("-");	
			}
			n = sprintf (cStringBuffer, "%u ", inVector[i].var);
			returnValue.append(cStringBuffer, cStringBuffer + n);
		}else{
			fprintf( stderr, "Invalid variable detected\n");
			exit(1);
		}
	}
	
	delete [] cStringBuffer;
	
	return returnValue;
}



///
/// Convert a std::string (inString) to std::vector<variable>.
///
std::vector<variable> string2vector( std::string inString){

	char *cString, *p, *index;
	std::vector<variable> returnVector;
	variable tempVariable;
	
	returnVector.clear();
	
	cString = new char[inString.size()+1];
	strcpy (cString, inString.c_str());
	
	
	// Split 
	p=strtok (cString," ");

	while(p != NULL){
	
		if (p[0] == '+'){
			tempVariable.var = (unsigned) atoi(p);
			tempVariable.pol.pos = 1;
			tempVariable.pol.neg = 0;
		}else if( p[0]  == '-'){
			tempVariable.var = (unsigned) (-1*atoi(p));
			tempVariable.pol.pos = 0;
			tempVariable.pol.neg = 1;				
		}else{
			fprintf( stderr, "not well formed string representation of vector\n");
			exit(1);
		}
		
		returnVector.push_back(tempVariable);
		p=strtok(NULL, " ");				
	}

	delete[] cString;  
	
	return returnVector;	
}

///
/// Return a unique vector with no duplicate assignments from S.  
///
std::vector< std::vector<variable> > uniqueSpace( std::vector< std::vector<variable> > S){

	size_t i, j;
	std::string tempString;
	std::map<std::string, unsigned> uniqueMap;
	std::map<std::string, unsigned>::iterator it;
	std::vector< variable> tempVector;
	std::vector< std::vector<variable> > returnVector;
	
	// convert S to a unique hashmap
	for(i = 0; i < S.size(); i++){
		tempString = vector2string( S[i]);
		uniqueMap.insert(std::pair<std::string, unsigned>(tempString, S[i].size()));
	}
	
	returnVector.clear();
	returnVector.resize( uniqueMap.size());		// reserve memory for unique elements
	
	// convert the unique hashmap back to an indexed tube
	for(i = 0, it = uniqueMap.begin(); it != uniqueMap.end(); i++, it++){

		tempVector = string2vector(it->first);
		returnVector[i].clear();

		for(j = 0; j < tempVector.size(); j++){

			returnVector[i].push_back( tempVector[j]);
		}
    }
	return returnVector;  
}


///
/// Insert variable is a subroutine for `distributionSat' 
///
std::vector<variable> insertVariable(variable inVar, std::vector<variable> inVector, runtimeData & myData){

	std::vector<variable> returnValue;
	std::vector<variable> tempVector;	
	
	returnValue = inVector;
	tempVector.clear();
	
	if( returnValue.size() == 0){
	
		returnValue.push_back(inVar);
		myData.appendCount += 1;
		
	}else if( inVar.var < returnValue.front().var ){
	
		tempVector.push_back(inVar);
		returnValue.insert(returnValue.begin(), tempVector.begin(), tempVector.end());		
		myData.appendCount += 1;
		
	}else if( inVar.var > returnValue.back().var ){

		returnValue.push_back(inVar);	
		myData.appendCount += 1;
	
	}else{
	
		for(std::vector<variable>::iterator it=returnValue.begin(); it!=returnValue.end(); ++it){

			if( it->var == inVar.var ){
			
				if(it->pol.pos == inVar.pol.pos && it->pol.neg == inVar.pol.neg ){
					return returnValue;
				}else{						//// eliminate this distribution path
					returnValue.clear();
					return returnValue;
				}
			
			}else if( it->var > inVar.var ){
			
				tempVector.push_back(inVar);
				returnValue.insert(it, tempVector.begin(), tempVector.end());

				myData.spliceCount  += 1;
				myData.appendCount += 2;
	
				return returnValue;			
			}
		}
	}
	return returnValue;
}

///
/// Implements Distribution algorithm for Satisfiability.
/// 
arguments distributionSat(const arguments myArgs){

	arguments returnArgs;
	unsigned i, j, k;
	unsigned m, n;
	variable tempVariable;
	std::vector< std::vector<variable> > solutionSpace;
	std::vector< std::vector< std::vector<variable> > > tempSpace;	

	std::string myString;

	returnArgs = myArgs;

	solutionSpace.clear();
	solutionSpace.resize(3);
	
	// setup initial conditions
	for(i = 0; i < myArgs.inputCNF.CNF_ORDER[0].size(); i++){
		solutionSpace[i] = insertVariable(myArgs.inputCNF.CNF_ORDER[0][i], solutionSpace[i], returnArgs.myData);
	}	
	
	tempSpace.resize(3);
	
	// execute for the remaining clauses 
	for(i = 1; i < myArgs.inputCNF.CNF_ORDER.size(); i++){
		for(j = 0; j < myArgs.inputCNF.CNF_ORDER[i].size(); j++){

			tempSpace[j].clear();
			tempSpace[j] = solutionSpace;
			returnArgs.myData.splitCount += 1;
			returnArgs.myData.mixCount += 1;
			
			tempVariable = returnArgs.inputCNF.CNF_ORDER[i][j];

			for(k = 0; k < tempSpace[j].size(); k++){
				myString = vector2string( tempSpace[j][k]);
				tempSpace[j][k] = insertVariable(tempVariable, tempSpace[j][k], returnArgs.myData);					
			}
		}
		
		//// merge the temp space into the solution space
		solutionSpace.clear();
		for(j = 0; j < 3; j++){
			for(k = 0; k < tempSpace[j].size(); k++){
				if( tempSpace[j][k].size() > 0){
					solutionSpace.push_back(tempSpace[j][k]);
				}
			}		
		}

		solutionSpace = uniqueSpace( solutionSpace);
		returnArgs.myData.purifyCount += 1;
	}
	
	
	//// Copy output to returnArgs
	returnArgs.result.resize(solutionSpace.size());
	for(i = 0; i < solutionSpace.size(); i++){	
		returnArgs.result[i].resize( returnArgs.inputCNF.numVar+1);	
		for(j = 0; j < solutionSpace[i].size(); j++){
			returnArgs.result[i][ solutionSpace[i][j].var].pos = solutionSpace[i][j].pol.pos;
			returnArgs.result[i][ solutionSpace[i][j].var].neg = solutionSpace[i][j].pol.neg;
		}
	}
	
	// Set satisfiable flag in arguments
	if(returnArgs.result.size() >0){
		returnArgs.isSat = 1;
	}
	
	return returnArgs;
}
