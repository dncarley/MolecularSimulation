
#include "arguments.h"

///
/// Default constructor for runtimeData.
///
runtimeData::runtimeData(){

	executionTime = 0;
	memoryUsage   = 0;
	mixCount      = 0;
	extractCount  = 0;
	appendCount   = 0;
	splitCount    = 0;
	spliceCount   = 0;
	purifyCount   = 0;
}

///
/// Destructor for runtimeData.
///
runtimeData::~runtimeData(){

}

///////////////////////////////////////////////////////////

///
/// Default constructor for arguments.
///
arguments::arguments(){

		algorithmType = 0;
		debug		  = 0;
		writeFile	  = 0;
		isSat		  = 0;
		//char * filename;
		//char * outputfile;
		//char * versionNumber;
		//CNF inputCNF;
		//std::vector< std::vector<lit> > result;		// result stored in [<0:numResults >[1:n]]
}

///
/// Destructor for arguments.
///
arguments::~arguments(){

	// add destructors.
	
}

///
/// Parse command line arguments.
///
void arguments::parseArguments(int argc, char ** argv){

	int i;

	algorithmType = 0;							// set defaults
	debug		  = 0;
			
	if(argc > 1){		
		for ( i = 1; i < argc; i++) {
	
			if (strcmp(argv[i], "-a") == 0){	// parse optional arguments
				if (i + 1 <= argc){
					if		(strcmp(argv[i+1], "l") == 0){
						algorithmType = 0;
					}else if(strcmp(argv[i+1], "o") == 0){
						algorithmType = 1;
					}else if(strcmp(argv[i+1], "d") == 0){
						algorithmType = 2;
					}else if(strcmp(argv[i+1], "b") == 0){
						algorithmType = 3;
					}else{
						algorithmType = 0;
					}
				}else{
					fprintf( stderr, "Usage algorithm: -a <options>\n");
					fprintf( stderr, "\tl --- Lipton\n\to --- Ogihara\n\td --- Distribution\n");
					exit(1);
				}
			}else if(strcmp(argv[i], "-d") == 0){
				debug = 1;
			}else if(strcmp(argv[i], "i") == 0){
				if(i + 1 <= argc){
					filename = (char*) malloc (strlen(argv[i+1])+1);
					strcpy(filename, argv[i+1]);
				}else{
					fprintf(stderr, "Provide an input CNF expression\n");
					exit(1);
				}

			}else if(strcmp(argv[i], "-w") == 0){
				if(i + 1 <= argc){
					writeFile = 1;					// set writeFile flag
					outputfile = (char*) malloc (strlen(argv[i+1])+1);
					strcpy(outputfile, argv[i+1]);
				}else{
					fprintf(stderr, "Provide an output filename\n");
					exit(1);
				}
			}
		}
	}else{
		fprintf(stderr, "usage:\nrequires at least a `*_filename.cnf'\n'");
	}
}

///
/// Prints a block of information about the current argument state.
///
void arguments::printArguments(){

	printf("algorithmType :\t%i\n", algorithmType);
	printf("debug         :\t%i\n", debug);
	printf("debug         :\t%i\n", writeFile);
	printf("isSat         :\t%i\n", isSat);
	printf("executionTime :\t%lu\n", (unsigned long)myData.executionTime);
	printf("memoryUsage   :\t%lu\n", (unsigned long)myData.memoryUsage);
	printf("filename      :\t%s\n", filename);
	printf("outputfile    :\t%s\n", outputfile);
	printf("version       :\t%s\n", versionNumber);
	printf("inputCNF      :\t(not shown)\n");
	printf("result        :\t(not shown)\n");

}

///
/// Write the output for the simulation.  If arguments::writeFile flag is set, output is written
/// to arguments::outputfile.  Otherwise the output is directed to stdout.
///
void arguments::writeOutput(){
	
	size_t i;
	time_t rawtime;
	struct tm * timeinfo;
	char * writeTime;
	FILE *fp;
	std::string algorithmName;
	
	time( &rawtime);
	timeinfo = localtime( &rawtime);
	writeTime = asctime(timeinfo) ;
  
	if(writeFile == 1){
		fp = fopen (outputfile, "w");
	}else{
		fp = stdout;
	}
	
	// update version number access
	fprintf(fp, "c \nc MolecularSimulation %s\n", versionNumber);
	fprintf(fp, "c Simulation written: %s", writeTime);
	fprintf(fp, "c Test: ");
	
	switch(algorithmType){
		case 0:
			fprintf(fp, "Lipton\n");
			algorithmName = "Lipton";
			break;	
		case 1:
			fprintf(fp, "Ogihara-Ray\n");
			algorithmName = "Ogihara-Ray";
			break;
		case 2:
			fprintf(fp, "Distribution\n");
			algorithmName = "Distribution";
			break;
		default:
			break;
	}
	fprintf(fp, "c Input: %s\n", filename);
	fprintf(fp, "c \ns ");
	switch(isSat){
		case 0:
			fprintf(fp, "UNSATISFIABLE\n");
			break;
		case 1:
			fprintf(fp, "SATISFIABLE\n");
			break;
		case 2:
			fprintf(fp, "UNKNOWN\n");
			break;
		default:
			fprintf(fp, "UNKNOWN\n");
			break;	
	}
	
	// print sat vector
	fprintf(fp, "v ");	
	if(result.size() >0){
		for(i = 1; i < result[0].size(); i++){
			if( result[0][i].isValid() ){
				if(result[0][i].neg == 1)
					fprintf(fp, "-");			
				fprintf(fp, "%lu ", (unsigned long)i);
			}
		}
	}
	fprintf(fp, "0\n");

	// print details about execution
	fprintf(fp, "c algorithmType:  %s\n",  algorithmName.c_str());
	fprintf(fp, "c algorithmTime:  %lu\n", (unsigned long)myData.executionTime);
	fprintf(fp, "c solutionMemory: %lu\n", (unsigned long)myData.memoryUsage);
	fprintf(fp, "c mixCount:       %lu\n", (unsigned long)myData.mixCount);
	fprintf(fp, "c extractCount:   %lu\n", (unsigned long)myData.extractCount);
	fprintf(fp, "c appendCount:    %lu\n", (unsigned long)myData.appendCount);
	fprintf(fp, "c splitCount:     %lu\n", (unsigned long)myData.splitCount);
	fprintf(fp, "c spliceCount:    %lu\n", (unsigned long)myData.spliceCount);
	fprintf(fp, "c purifyCount:    %lu\n", (unsigned long)myData.purifyCount);
	fprintf(fp, "c numVar:         %u\n",  inputCNF.numVar);
	fprintf(fp, "c numClause:      %u\n",  inputCNF.numClause);
	fprintf(fp, "c \n");

	if(fp != stdout)
		fclose(fp);

}
