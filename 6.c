#include <stdio.h>
#include <omp.h>
#define MAXIMUM 100


main()
{ 
	int i, n, cur_max, current_value; 
	printf("Enter the number of elements\n"); 
	scanf("%d", &n); 

	if (n<= 0) 
	{ 
		printf("The array elements cannot be stored\n"); 
		exit(1); 
	} 

	int array[n];
	srand(MAXIMUM); 
	for (i = 0; i<n; i++) 
		array[i] = rand(); 
	if (n== 1) 
	{ 
		printf("The Largest Number In The Array is %d", array[0]); 
		exit(1); 
	} 


	cur_max = 0; 
	omp_set_num_threads(8); 

	#pragma omp parallel for 
	for (i = 0; i<n; i++) 
	{ 
		if (array[i] >cur_max) 
		#pragma omp critical 
		if (array[i] >cur_max) 
		cur_max = array[i]; 
	} 

	current_value = array[0]; 
	for (i = 1; i<n; i++) 
		if (array[i] >current_value) 
			current_value = array[i]; 
	
	printf("The Input Array Elements Are \n"); 
	for (i = 0; i<n; i++) 
		printf("%d\t", array[i]); 
	printf("\n"); 
 
	if (current_value == cur_max) 
		printf("\nThe Max Value Is Same From Serial And Parallel OpenMP Directive\n"); 
	else
	{ 
		printf("\nThe Max Value Is Not Same In Serial And Parallel OpenMP Directive\n"); 
		exit(1); 
	}  
	printf("\n"); 
	printf("\nThe Largest Number In The Given Array Is %d\n", cur_max); 
} 
