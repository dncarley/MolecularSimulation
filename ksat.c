/*
char *synopsis =
"ksat <k> <n> <m> <#>
Produces a random CNF formula in DIMACS format.
 Parameters are k,n,m,number.
 k := number of literals per clause
 n := number of variables
 m := number of clauses -- sampled without replacement
 id# := formula id -- specifying how the random
        number generator should start
 If m<m', then phi_{k,n,m,#} subset phi_{k,n,m',#}.
 Clauses are chosen uniformly at random and independently
 of one another (without replacement), and choosing different
 id#'s gives independent formulas.
 It is required that k>0, n>0, m>=0, id#>=0,
 and that n>=k.
 If m>[n choose k]*2^k (the number of possible clauses),
 it will be reduced to this number.
";
*/
const char *synopsis = "Usage: ./ksat <k> <n> <m> <#>\n\n This program was modified to use srand()/rand() from ``stdlib.h'', removing the ``sprng.h'' dependencies.\n\nOriginal source available from:\n\thttp://research.microsoft.com/en-us/um/people/dbwilson/ksat/default.htm \n\n\0";


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK_POINTERS
//#include "sprng.h"
#define SEED 1

main (int argc, char *argv[])
{
  int k,n,m,id;	//,gtype;
  //int *str;
  unsigned long long int max;

  int *clauses;
  int i, j, l;
  int var, mask, shift;
  int hashmask, hashshift, *hashfn, *hashtbl, hash;
  /* Use &mask for low bits, >>shift for high bits.
   * Recommendation is to use high bits.
   */
  
  /* Parse arguments, and set up random stream
   */
  if (argc != 5) {fprintf(stderr,synopsis); exit(-1);}
  k = atoi(argv[1]);
  n = atoi(argv[2]);
  m = atoi(argv[3]);
  id= atoi(argv[4]);
  if (k<=0 || n<=0 || m<0 || id<0 || k>n) {fprintf(stderr,synopsis); exit(-1);}
  for (max=1, j=0; j<k; ++j)
    max = max * 2*(n-j)/(j+1);
  if (m>max) m=max;
  
  
  //  gtype = SPRNG_LFG;
  //str = init_sprng(gtype,id,/*nstreams*/ id+1,SEED,SPRNG_DEFAULT);
  srand ( id );



  /* Set up hash table and hash function to ensure sampling without replacement
   */
  hashfn = (int*)malloc((2*n+1)*sizeof(int));
  if (!hashfn) {fprintf(stderr,"Out of memory.\n"); exit(-1);}
  
  for (hashmask=1, hashshift=31; hashmask<2*m; hashmask<<=1, --hashshift);
  hashtbl = (int*)calloc(hashmask,sizeof(int));
  
  if (!hashtbl) {fprintf(stderr,"Out of memory.\n"); exit(-1);}
  --hashmask;
  
  for (i=0; i<=(n<<1); ++i)
    hashfn[i] = (rand()>>hashshift);
  hashfn = &(hashfn[n]);
  
  /* Generate random k-clauses
   */
  clauses = (int*)malloc(k*m*sizeof(int));
  if (!clauses) {fprintf(stderr,"Out of memory.\n"); exit(-1);}
  for (mask=1, shift=31; mask<n; mask<<=1, --shift);
  --mask;
  for (i=0; i<m;) {
    /* Generate a random k-clause with literals sorted by variable # */
    /* Choose k variables */
    for (j=0; j<k;) {
      while ((var=(rand()>>shift))>=n); ++var;
      for (l=0; l<j && clauses[i*k+l] != var; ++l);
      if (l==j) { /* variable new to the clause */
	for (l=j; l>0 && clauses[i*k+l-1] > var; --l)
	  clauses[i*k+l] = clauses[i*k+l-1];
	clauses[i*k+l] = var;
	++j;
      }
    }
    /* Assign signs */
    for (j=0; j<k; ++j) if (rand()&0x40000000) clauses[i*k+j] *= -1;
    /* Check to see if we generated this clause before */
    for (hash=0,j=0; j<k; ++j) hash ^= hashfn[clauses[i*k+j]];
    while (hashtbl[hash] &&
	   bcmp(&(clauses[i*k]),&(clauses[(hashtbl[hash]-1)*k]),k*sizeof(int)))
      hash = (hash+1)&hashmask;
    if (!hashtbl[hash]) { /* new clause */
      hashtbl[hash] = i+1;
      ++i;
    }
  }


  if (1 == 1)
  { /* Output the k-clauses in DIMACS format */
    printf("p cnf %d %d\n",n,m);
    for (i=0; i<m; ++i) {
      for (j=0; j<k; ++j) {
	printf("%d ",clauses[i*k+j]);
      }
      printf("0\n");
    }
  } else
  { /* Output the k-clauses in a format suitable for TCL */
    for (i=0; i<m; ++i) {
      printf("{");
      for (j=0; j<k; ++j) {
	printf("%d%s",clauses[i*k+j],j+1==k?"}\n":" ");
      }
    }
  }
  exit(0);
}
