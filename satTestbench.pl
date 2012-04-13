
# satTestbench.pl

$outputExe = "execute/simulation";

##############################################
############# Execute
##############################################
#$cnf_file = "/Users/davidcarley/Dropbox/research/implementation/archive/aim-50-1_6-yes1-4.cnf";
#$cnf_file = "/Users/davidcarley/Dropbox/research/data/sat_benchmark/CBS_k3_n100_m403_b10/CBS_k3_n100_m403_b10_0.cnf";
#$cnf_file = "./data/toy/SET_100/SWEEP_100_3_5_5_000.cnf"; ### 
#$cnf_file = "./data/toy/simple1.cnf";
#$cnf_file = "./data/toy/simple2.cnf";
$cnf_file = "./data/toy/yoshida.cnf";		
#$cnf_file = "./data/toy/SET_150/SWEEP_150_3_10_15_000.cnf";

#$cnf_file = "./data/toy/SET_200/SWEEP_200_3_9_18_000.cnf";
#$cnf_file = "/Users/davidcarley/Dropbox/research/data/sat_benchmark/uf50-218/uf50-02.cnf";

#$cnf_file = "/Users/davidcarley/Dropbox/research/data/sat_benchmark/flat30-60/flat30-1.cnf";

#$algorithmType = "l";
#$algorithmType = "o";
#$algorithmType = "d";

my @commandArgs = (@options, "-a", $algorithmType,"-v", "-d", "-i", $cnf_file);

if( $debug){
	@run = ("gdb ".$outputExe);
}else{
	@run = ("./".$outputExe);
}
push(@run, @commandArgs);

print color 'bold green';
print(@run);
print("\n");

print color 'reset';

system(@run);
