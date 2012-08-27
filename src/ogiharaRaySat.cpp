/*! \file ogiharaRaySat.cpp
	\brief Defines functions for Ogihara and Ray's algorithm.

*/

#include "ogiharaRaySat.h"

///
///	Filters partial assignments contained in set T
///
gel get_UV_Sat( gel T, variable u, variable v, runtimeData & myData){

	gel T_uT, T_uF, T_vT, T_T;
	
	/// Clear the gel contents
	T_uT.clear();	T_uF.clear();	T_vT.clear();	T_T.clear();
	
	T_uT = T.filter(u);				
	T_uF = T.filterOthers(u);
	T_vT = T_uF.filter(v);
	myData.extractCount += 3;

	T_T.mix( T_uT);		
	T_T.mix( T_vT);
	myData.mixCount += 2;
	
	T_T.purifyGel();
	myData.purifyCount += 1;
	
	return T_T;
}

///
///	Implements Ogihara and Ray Satisfiability algorithm
///
arguments ogiharaRaySat (const arguments myArgs){

	arguments	returnArgs;
	oligo 		tempOligo;
	gel  		T, T_T, T_F, T_wF, T_wT;
	variable 	varU, varV, varW, X_k, nX_k;
	unsigned	k, j, m, n;	
	
	/// init return value
	returnArgs = myArgs;
	
	T.clear();
	T_T.clear();	T_F.clear();
	T_wF.clear();	T_wT.clear();	
	
	/// Variables are presorted during DIMACS CNF parse
		// no sort required
		
	n = returnArgs.inputCNF.numVar;
	m = returnArgs.inputCNF.numClause;
	
	/// init tube T;
	tempOligo.string2oligo("ATT"); T.mix(tempOligo);
	tempOligo.string2oligo("ATC"); T.mix(tempOligo);
	tempOligo.string2oligo("ACT"); T.mix(tempOligo);
	tempOligo.string2oligo("ACC"); T.mix(tempOligo);
	
	for( k = 3; k <= n; k++){
		
		/// amplify the incoming tube
		T_wF.clear();	T_wT.clear();
		T_wF.mix(T);	T_wT.mix(T);

		returnArgs.myData.splitCount += 1;
		returnArgs.myData.mixCount += 2;

		/// assign positive and negative variables for comparison		
		X_k  = variable(k, POS);
		nX_k = variable(k, NEG);
						
		/// Evaluate each clause
		for( j = 0; j < m; j++){
		
			varU = returnArgs.inputCNF.CNF_ORDER[j][0];
			varV = returnArgs.inputCNF.CNF_ORDER[j][1];
			varW = returnArgs.inputCNF.CNF_ORDER[j][2];
			
			if( varW.isEqual( X_k )) T_wF = get_UV_Sat( T_wF, varU, varV, returnArgs.myData);
			if( varW.isEqual( nX_k)) T_wT = get_UV_Sat( T_wT, varU, varV, returnArgs.myData);
		}
		
		/// append partial assignments
		T_T.clear();			T_F.clear();
		T_T = T_wT;				T_F = T_wF;
		T_T.append( X_k.neuc);	T_F.append( nX_k.neuc);
		
		returnArgs.myData.appendCount += 2;
		
		/// mix the partial assignments for the next iteration
		T.clear();
		T.mix(T_T);		T.mix(T_F);
		
		returnArgs.myData.mixCount += 2;
		
		T.purifyGel();
		
		returnArgs.myData.purifyCount++;
	}

	//// Copy output to returnArgs
	returnArgs.result.resize(T.size());
	for(k = 0; k < T.size(); k++){	
		returnArgs.result[k].resize(n);	
		returnArgs.result[k] = oligo2satVector(T.tube[k], 0);
	}
	
	// Set satisfiable flag in arguments
	if(returnArgs.result.size() >0){
		returnArgs.isSat = 1;
	}

	return returnArgs;
}
