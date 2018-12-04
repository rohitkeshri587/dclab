#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main () 
{ 
	int i=0, n=1000; 
	float a[1000], b[1000], sum=0.0f; 

	for (i=0; i< n; i++) 
		a[i] = b[i] = i + 1.0; 
	
	#pragma omp parallel for reduction(+:sum) 

	for (i=0; i< n; i++) 
		sum = sum + (a[i] * b[i]); 

	printf("Sum = %f\n",sum); 
} 
