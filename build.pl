
###
### build.pl	
###
### Usage: $ perl build.pl
###

use Term::ANSIColor;	

$profile	= 0;	#set to build for gprof

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
$mainEntry = "simulation.cpp";

@inc_ARG = ("arguments.cpp");
@inc_CNF = ("inputCNF.cpp");
@inc_EXE = ("executeTest.cpp");
@inc_ALG = ("liptonSat.cpp", "ogiharaRaySat.cpp", "distributionSat.cpp");
@inc_DAT = ("dna32.cpp", "oligo.cpp", "gel.cpp", "datatypes.cpp");
@inc_VFY = ("verifySat.cpp");

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
