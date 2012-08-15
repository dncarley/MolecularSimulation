
#include "executeTest.h"

///
/// Executes the test configured with the provided arguments
/// Records statistics and status of the CNF input 
///
arguments executeTest(const arguments myArgs){

	arguments returnArgs;
	clock_t s0, s1;

	s0 = clock();

	switch(myArgs.algorithmType){
		case 0:
			returnArgs = liptonSat(myArgs);
			break;
		case 1:
			returnArgs = ogiharaRaySat(myArgs);
			break;
		case 2:
			returnArgs = distributionSat(myArgs);
			break;
		default:
			returnArgs = liptonSat(myArgs);
			break;	
	}
	
	s1 = clock( );
	returnArgs.myData.executionTime = ((float)s1-s0)/CLOCKS_PER_SEC;
	
	returnArgs.memoryUsage = 0;
	for(size_t i = 0; i < returnArgs.result.size(); i++){
		for(size_t j = 0; j < returnArgs.result[i].size(); i++){
			returnArgs.myData.memoryUsage += sizeof(literal);
		}
	}
	
	return returnArgs;
}
