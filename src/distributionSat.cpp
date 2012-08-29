/*! \file distributionSat.cpp
	\brief Defines function for Distribution algorithm.

*/

#include "distributionSat.h"

///
/// Implements Distribution algorithm for Satisfiability
///
arguments distributionSat(const arguments myArgs){

	DNA otherSeq, selectSeq;
	unsigned tempVar;
	arguments returnArgs;
	gel Ts, Tc, Tv;
	
	returnArgs = myArgs;

	Ts.clear();
	Ts.mix(A);
	for(size_t i = 0; i < returnArgs.inputCNF.CNF_ORDER.size(); i++){

		Tc.clear();
			
		for(size_t j = 0; j < returnArgs.inputCNF.CNF_ORDER[i].size(); j++){
		
			tempVar = returnArgs.inputCNF.CNF_ORDER[i][j].var;			
		
			if(returnArgs.inputCNF.CNF_ORDER[i][j].pol.pos){
				otherSeq = G;
				selectSeq = T;
			}else{
				otherSeq = T;
				selectSeq = G;			
			}

			Tv = Ts.filterOthers( tempVar, otherSeq);
			Tv.setNeuc( tempVar, selectSeq);
			Tc.mix( Tv);

			returnArgs.myData.splitCount +=1;
			returnArgs.myData.extractCount +=2;
			returnArgs.myData.appendCount +=1;
			returnArgs.myData.mixCount +=1;
			
		}
		
		Ts.clear();
		Ts.mix(Tc);
		Ts.purifyGel();
		
		returnArgs.myData.mixCount +=1;
		returnArgs.myData.purifyCount +=1;
		
		if( Ts.size() == 0){
			break;
		}
		
	}
		
	returnArgs.result.resize(Ts.size());
	for(size_t i = 0; i < Ts.size(); i++){
		returnArgs.result[i].resize(returnArgs.inputCNF.numVar);
		returnArgs.result[i] = oligo2satVector(Ts.tube[i], 1);
		
	}

	// Set satisfiable flag in arguments
	if(Ts.size() > 0){
		returnArgs.isSat = 1;
	}		

	return returnArgs;
}
