
#use Term::ANSIColor;
use POSIX;

#buildGenerate.pl



my $buildCommand = "gcc ";
$buildCommand .= "ksat.c ";
$buildCommand .= " -o ./execute/ksat";

print($buildCommand."\n");
system($buildCommand);


$k = 3;
$numRatioSets = 3;
$directory = "./data/testCNF";

@var = (20, 20, 20, 20, 16, 20, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 16, 20, 20, 20, 20, 16);
@cla = (4, 8, 12, 16, 16, 24, 28, 32, 36, 32, 44, 48, 56, 48, 64, 68, 72, 76, 64, 88, 92, 96, 80, 108, 112, 116, 96, 128, 132, 136, 112, 144, 148, 152, 156, 128, 164, 172, 176, 144, 184, 192, 196, 160, 204, 212, 216, 176, 224, 232, 236, 192, 244, 252, 256, 208, 264, 268, 272, 276, 224);
$numElements = 61;

for($i = 0; $i < $numElements; $i++){

	$n = $var[$i];
	$m = $cla[$i];	
	$r = ceil($m/$n);

	for($s = 0; $s < $numRatioSets; $s++){
		
		$filename = $k;		$filename .= " ";
		$filename .= $n;	$filename .= " ";
		$filename .= $m;	$filename .= " ";
		$filename .= $s;	$filename .= " ";
		$buildCommand = "./execute/ksat ";
		$buildCommand .= $filename;

		$serial=sprintf("%03d",$s);	

		####### Create DIMACS cnf file
		$fileOut ="SWEEP_R";
		$fileOut .= $r;	$fileOut .= "_K";
		$fileOut .= $k;	$fileOut .= "_N";
		$fileOut .= $n;	$fileOut .= "_M";
		$fileOut .= $m;	$fileOut .= "_S";
		$fileOut .=	$serial;
		$fileOut .= ".cnf";
		
		$buildCommand .= "> ";
		$buildCommand .= $directory;
		$buildCommand .="/";
		$buildCommand .= $fileOut;
	
		system($buildCommand);		
	}
}
