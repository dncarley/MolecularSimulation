/*! \file inputCNF.cpp
	\brief Defines functions for CNF class.

*/

#include "inputCNF.h"

///
/// Default constructor for CNF.
///
CNF::CNF(){

}

///
/// Destructor for CNF.
///
CNF::~CNF(){

}

///
/// Parse DIMACS CNF file.  Sets CNF properties from DIMACS CNF input: numVar = n, numClause = m.
/// Constructs equivalent structures store the input.  
///
/// CNF_TABLE directly stores each set bit of a literal, indexing a vector 
/// of 0 <= clause < numClause.  Each row consists of a vector of 0 < 1 <= variable <= numVar.  
///
/// CNF_ORDER stores a variable representation of the clauses.  The variable.var index is sorted
/// by non-decreasing integers.
///
void CNF::parseCNF(const char* filename){
	
	unsigned m, n;
	std::string line;
	char * cString;
	char * token;
	long temp;
	unsigned lineNumber, varNumber;
	variable tempVariable;
	
	std::ifstream myfile(filename);
	if (myfile.is_open()){
    	while ( myfile.good()){
			getline(myfile, line);
			
			switch(line[0]){
				case 'c':
					#ifdef VERBOSE
						printf("COMMENT == ");
					#endif
					break;
				case 'p':
					#ifdef VERBOSE
						printf("FORMAT  == ");
					#endif
					cString = new char[line.size()+1];
					strcpy (cString, line.c_str());		// convert to cstring
					temp = 0;							// count the split occurrences

					token = strtok(cString," ");
					while(token != NULL){
						if(temp == 2) n = atoi(token);
						if(temp == 3) m = atoi(token);
						token = strtok (NULL, " ");
						temp++;
					}
					
					// Include argument size in CNF structure
					numVar 	= n;
					numClause = m;
					
					// Allocate and init table for CNF_TABLE storage
					lineNumber = 0;
					CNF_TABLE.resize(m);
					
					//	resize the vector for CNF formula
					for(int i = 0; i < m; i++){
						CNF_TABLE[i].resize(n+1);
						for(int j = 0; j < CNF_TABLE[i].size(); j++){
							CNF_TABLE[i][j].pos = 0;
							CNF_TABLE[i][j].neg = 0;						
						}
					}
										
					delete[] cString;  
					break;
				default:
					cString = new char[line.size()+1];
					strcpy(cString, line.c_str());		// convert to cstring
					temp = 0;							// count the split occurances

					token = strtok(cString," ");
					while (token != NULL){
						temp = atoi(token);
									
						if(temp > 0){
							CNF_TABLE[lineNumber][temp].pos = 1;
						}else if(temp < 0){
							CNF_TABLE[lineNumber][-temp].neg = 1;
						}
						else{
							break;
						}
				
						token = strtok(NULL, " ");
					}

					delete[] cString;  
					lineNumber++;
					break;
			}
		}
		myfile.close();
	}
	else{
		fprintf(stderr, "Unable to open file\n"); 
		exit(1);
	}
	
	// construct ordered CNF expression

	CNF_ORDER.resize(m);
	
	for(unsigned i = 0; i < m; i++){	///	resize the vector for CNF formula
		CNF_ORDER[i].clear();
		for(unsigned j = 1; j < CNF_TABLE[i].size(); j++){
			if(CNF_TABLE[i][j].pos == 1 || CNF_TABLE[i][j].neg == 1){
			
				tempVariable.var = j;
				tempVariable.pol = CNF_TABLE[i][j];
				if(tempVariable.pol.pos == 1){
					tempVariable.neuc = T;
				}
				if(tempVariable.pol.neg == 1){
					tempVariable.neuc = C;				
				}

				CNF_ORDER[i].push_back(tempVariable);				
			}
		}
	}
}

///
///	Print table of CNF.  Each row begins with a clause number, followed by n literals.
///
void CNF::printCNF_table(){

	printf("\t\t\t    +-+-+-      +-+-+-      +-+-+-      +-+-+-\n");
	for(int i = 0; i < CNF_TABLE.size(); i++){
		printf("line: %.2i\t", i);
			printf("---%i\t", i<<6);
		
		CNF_TABLE[i][0].printLiteral();		printf("::");
		for(int j = 1; j < CNF_TABLE[i].size(); j++){
			
			CNF_TABLE[i][j].printLiteral();
		}
		printf("\n");
	}
}

///
/// Print ordered clauses.  Each row begins with a clause number, followed by a sequence
/// of ordered integers.  Polarity is designated by (+) and (-).
///
void CNF::printCNF_order(){

	for(unsigned i = 0; i < CNF_ORDER.size(); i++){
		printf("line: %.2i\t", i);
		printCNF_orderLine(i);

	}
}

///
/// Prints a sequence of ordered integers.  Polarity is designated by (+) and (-).
///
void CNF::printCNF_orderLine(unsigned i){

	for(unsigned j = 0; j < CNF_ORDER[i].size(); j++){
		if(CNF_ORDER[i][j].pol.pos == 1){
			printf("+");
		}else{
			printf("-");			
		}
		printf("%u\t", CNF_ORDER[i][j].var);
	}
	printf("\n");
}
