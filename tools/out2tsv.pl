
if($#ARGV == 1){
	$inDir = @ARGV[0];
	$outFile = @ARGV[1];
}else{
	print "Usage: perl out2tsv.pl <input directory> <output file>\n";
	exit 1;
}

open OUTFILE, ">".$outFile or die $!;
print OUTFILE "Filename\tAlgorithm\tm\tn\texecutionTime\tmemory\tisSat\tmixCount\textractCount\tappendCount\tsplitCount\tspliceCount\tpurifyCount\n";

@files = <$inDir*.out>;
foreach $file (@files) {

	open INFILE, "<".$file or die $!;
	
	my @lines = <INFILE>;
	chomp(@lines);
	my @rowData = ();
	$#rowData = 13;			#resize array for TSV row

	foreach(@lines){
		my @tokens = split / /, $_;
		
		if($tokens[0] eq 'c'){
			if($tokens[1] eq 'algorithmType:'){
				if($tokens[$#tokens] eq 'Lipton'){
					$rowData[1] = '0';
				}elsif($tokens[$#tokens] eq 'Ogihara-Ray'){
					$rowData[1] = '1';			
				}elsif($tokens[$#tokens] eq 'Distribution'){
					$rowData[1] = '2';
				}
			}elsif($tokens[1] eq 'algorithmTime:'){
				$rowData[4] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'solutionMemory:'){
				$rowData[5] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'mixCount:'){
				$rowData[7] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'extractCount:'){
				$rowData[8] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'appendCount:'){
				$rowData[9] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'splitCount:'){
				$rowData[10] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'spliceCount:'){
				$rowData[11] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'purifyCount:'){
				$rowData[12] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'numVar:'){
				$rowData[3] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'numClause:'){
				$rowData[2] = $tokens[$#tokens];
			}elsif($tokens[1] eq 'Input:'){
				$rowData[0] = $tokens[$#tokens];
			}
		}
		if($tokens[0] eq 's'){
			if($tokens[1] eq 'SATISFIABLE'){
				$rowData[6] = '1';			
			}elsif($tokens[1] eq 'UNSATISFIABLE'){
				$rowData[6] = '0';
			}else{
				$rowData[6] = '2';
			}		
		}
	}
#	chomp(@rowData);

	print OUTFILE join("\t", @rowData), "\n";
	close(INFILE);
}
close(OUTFILE);
