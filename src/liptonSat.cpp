/*! \file liptonSat.cpp
	\brief Defines functions for Lipton's algorithm.

*/

#include "liptonSat.h"

///
/// Implements Lipton's Satisfiability algorithm
///
arguments liptonSat(const arguments myArgs){

	arguments returnArgs;
	unsigned i, j, m, n;
	gel Ts, Tt, Tc;
	variable tempVariable;
	
	returnArgs = myArgs;
	
	Tt.clear();
	Tc.clear();	
	
	m = returnArgs.inputCNF.numClause;
	n = returnArgs.inputCNF.numVar;
			
	Ts = combinatorialGenerate(n, returnArgs.myData);
	
	for(i = 0; i < m; i++){
	
		Tc.clear();
		
		for(j = 0; j < myArgs.inputCNF.CNF_ORDER[i].size(); j++){
		
			tempVariable = myArgs.inputCNF.CNF_ORDER[i][j];			
			Tt.clear();
			
			Tt = Ts.filter(tempVariable);	
			returnArgs.myData.extractCount++;
			
			Tc.mix(Tt);
			returnArgs.myData.mixCount++;
		}
	
		Ts.clear();
		Ts.mix(Tc);
		returnArgs.myData.mixCount++;

		Ts.purifyGel();		/// eliminate duplicates
		returnArgs.myData.purifyCount++;
	}
	
	returnArgs.result.resize(Ts.size());
	for(i = 0; i < Ts.size(); i++){
		returnArgs.result[i].resize(n);
		returnArgs.result[i] = oligo2satVector(Ts.tube[i], 0);
	}

	// Set satisfiable flag in arguments
	if(returnArgs.result.size() >0){
		returnArgs.isSat = 1;
	}
	
	return returnArgs;
}


///
///	Generate a combinatorial space of 2^n unique oligo vectors
///
gel combinatorialGenerate(unsigned n, runtimeData & myData){

	unsigned i;
	gel combTube, tempTube;

	combTube.clear();
	combTube.mix(A);	combTube.mix(A);
	myData.mixCount +=2;

	for(unsigned i = 1; i <= n; i++){

		tempTube.clear();
		tempTube.mix(combTube);
		myData.splitCount +=1;
		
		combTube.append(T);
		tempTube.append(C);
		myData.appendCount +=2;

		combTube.mix(tempTube);
		myData.mixCount +=1;
	}
	combTube.purifyGel();
	myData.purifyCount +=1;

	return combTube;
}
