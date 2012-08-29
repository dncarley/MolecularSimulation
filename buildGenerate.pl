
#buildGenerate.pl

#use Term::ANSIColor;
use POSIX;

my $buildCommand = "gcc ";
$buildCommand .= "src/external/ksat.c ";
$buildCommand .= " -o ./execute/ksat";

print($buildCommand."\n");
system($buildCommand);

$k = 3;
$n = 10;
$numRatioSets = 30;
$directory = "./data/testCNF_n10";

#generate fixed (n=20) 3-Sat sweep from [0.2, 14.0] 
@cla = (4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252, 256, 260, 264, 268, 272, 276, 280);
#@cla = ( 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, );
$numElements = @cla;

for($i = 0; $i < $numElements; $i++){

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
