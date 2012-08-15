
###
### build.pl	
###
### Usage: $ perl build.pl
###

use Term::ANSIColor;	

$profile	= 1;	#set to build for gprof or gdb

#$compilier = "g++-mp-4.4";
$compilier = "g++";

print color 'blue';
print(@ARGV);
print("\n");
print color 'reset';

##############################################
############# set build options
##############################################
$outputExe = "execute/simulation";
$mainEntry = "src/simulation.cpp";

@inc_ARG = ("src/arguments.cpp");
@inc_CNF = ("src/inputCNF.cpp");
@inc_EXE = ("src/executeTest.cpp");
@inc_ALG = ("src/liptonSat.cpp", "src/ogiharaRaySat.cpp", "src/distributionSat.cpp");
@inc_DAT = ("src/dna32.cpp", "src/oligo.cpp", "src/gel.cpp", "src/datatypes.cpp");
@inc_VFY = ("src/verifySat.cpp");

@include = (@inc_ARG, @inc_CNF, @inc_EXE, @inc_ALG, @inc_DAT, @inc_VFY);


######### link for profiling with gprof
#
if($profile == 1){	@profileOptions = ("-g", "-pg");}
else			 {	@profileOptions = ("");}

@comp_link_OPTIONS = ("-o", $outputExe, @profileOptions);

##############################################
############# build
##############################################

@build = ($compilier, @comp_link_OPTIONS, $mainEntry, @include);

print color 'bold red';
print(@build);
print("\n\n");
system(@build);

print("\n\nComplete\n\n");

print color 'reset';
