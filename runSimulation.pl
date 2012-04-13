
# runSimulation.pl


$arguments = "";

foreach $i (0 .. $#ARGV) {
	$arguments .= $ARGV[$i];
	$arguments .= " ";
}


system("perl build.pl");
system("perl executeMolecularSat.pl ".$arguments);
