#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define N 100 
#define P 600 
#define M 100 
#define th 16

int main (int argc, char *argv[]) 
{ 

	int tid, nthreads, i, j, k; 
	double a[N][P], b[P][M], c[N][M]; 
	omp_set_num_threads(th);
	double time = omp_get_wtime();
	 
	#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k) 
	 {
		tid = omp_get_thread_num(); 
		 if (tid == 0) 
		 { 
			 nthreads = omp_get_num_threads(); 
			 printf("Starting matrix multiple example with %d threads\n",nthreads);  printf("Initializing matrices...\n"); 
		 } 
		 
		 #pragma omp for 
		 for (i=0; i<N; i++) 
			 for (j=0; j<P; j++) 
				 a[i][j]= i+j; 
		 #pragma omp for 
		 for (i=0; i<P; i++) 
			 for (j=0; j<M; j++) 
				 b[i][j]= i*j; 
		 #pragma omp for 
		 for (i=0; i<N; i++) 
			 for (j=0; j<M; j++) 
 				c[i][j]= 0; 
		  printf("Thread %d starting matrix multiply...\n",tid);
		  #pragma omp for 
		 for (i=0; i<N; i++) 
		 { 
			 printf("Thread=%d did row=%d\n",tid,i); 
			 for(j=0; j<M; j++) 
				 for (k=0; k<P; k++) 
					 c[i][j] += a[i][k] * b[k][j]; 
		 } 
	 } 
	printf("******************************************************\n"); printf("Result Matrix:\n"); 
	for (i=0; i<N; i++) 
	 { 
	 	for (j=0; j<M; j++) 
	 		printf("%6.2f    ", c[i][j]); 
	 	printf("\n"); 
	 } 

 
	printf("******************************************************\n"); 
  	printf ("\nDone In %f Seconds",omp_get_wtime() - time);
	printf("\n Using %d Threads",omp_get_max_threads());
	return(0); 
}
