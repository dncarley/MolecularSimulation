
#
# included test benches
#@filePath  = <data/toy/*.cnf>;
#@filePath  = <data/testCNF/*.cnf>;
#@filePath  = <data/example/*.cnf>;
#@filePath  = <data/jnh/*.cnf>;
#@filePath  = <data/pret/*.cnf>;
#@filePath  = <data/uf20-91/*.cnf>;
#@filePath  = <data/logistics/*.cnf>;
#

use Term::ANSIColor;

$toFile = 0;			# 0 stdout, 1 to specified file
$debug = "";			# debug flag 
$cnfPath = "";

$outputExe = "execute/simulation";

my @algorithm;

foreach $i (0 .. $#ARGV) {
	
  if($ARGV[$i] eq "-l"){
  	push @algorithm, 'l';
  }
  if($ARGV[$i] eq "-o"){
  	push @algorithm, 'o';
  }
  if($ARGV[$i] eq "-d"){
  	push @algorithm, 'd';
  }
  if($ARGV[$i] eq "-f"){
  	$toFile = 1;
  }
  if($ARGV[$i] eq "-debug"){
  	$debug = '-d';
  }
  if($ARGV[$i] eq "-p"){
	$i += 1;
	if( $i <= $#ARGV){		
		$cnfPath = $ARGV[$i];	
	}else{
		print "Provide file path\n";
		exit(1);
	}
  }
}




###### If no algorithms specified, test all three algorithms
######
$algSize = @algorithm;
if( $algSize == 0 ){
	@algorithm = ('l', 'o', 'd');
}

###### Select path for cnf files
######
if( $cnfPath eq ""){
	@filePath  = <data/testCNF/*.cnf>;
	$cnfPath = "./";

}else{

	opendir(D, "$cnfPath") || die "Can't opedir $d: $!\n";
	@tempPath = readdir(D);
	closedir(D);
	
	$cnfPath = "./".$cnfPath;

	foreach(@tempPath){
		if( "$_\n" =~ m/$.cnf/ ){
			push @filePath, "$_";
		}
	}
}

##############################################
############# execute
##############################################

foreach $cnfFile (@filePath) {
	foreach $algorithmType (@algorithm){		

		$input = $cnfPath."/".$cnfFile;
		
		@dirTree = split /\.cnf$/, $cnfFile;
		$output  = "./";
		$output  .= @dirTree[$#dirTree];
		$output .= "-";
		$output .= $algorithmType;
		$output .= ".out";
					 	
		if( $toFile == 1){ @outputOptions = ("-w", $output); }
		else			 { @outputOptions = (); } 					

		## setup command line arguments
		my @commandArgs = (@options, "-a", $algorithmType, $debug, "i", $input, @outputOptions);
		@run = ("./".$outputExe);
		push(@run, @commandArgs);
		
		print color 'bold green';
		print(@run);		
		print("\n");
		print color 'reset';
				
		system(@run);
	} 
}
