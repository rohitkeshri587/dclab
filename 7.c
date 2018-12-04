#include <stdio.h>
#include <omp.h>
#define MINUS_INFINITY -9999 
#define MAXIMUM_VALUE 65535 


main()
{ 
	int i, n, cur_max, current_value; 
	omp_lock_t MAXLOCK; 
	printf("Enter the number of elements\n"); 
	scanf("%d", &n); 

	if (n<= 0)
 	{ 
		printf("The array elements cannot be stored\n"); 
		exit(1); 
	} 

	int array[n];

	srand(MAXIMUM_VALUE); 
	for (i = 0; i<n; i++) 
		array[i] = rand(); 
	if (n == 1)
 	{ 
		printf("The Largest Element In The Array Is %d", array[0]); 
		exit(1); 
	} 

	printf("The locking is going to start\n"); 
	omp_set_num_threads(8); 
	omp_init_lock(&MAXLOCK); 
	cur_max = MINUS_INFINITY; 
	printf("the lock is initialized\n"); 

	#pragma omp parallel for 
	for (i = 0; i<n; i = i + 1)
	{ 
		if (array[i] >cur_max)
		{ 
			omp_set_lock(&MAXLOCK); 
			if (array[i] >cur_max) 
				cur_max = array[i]; 
			omp_unset_lock(&MAXLOCK); 
		} 
	} 	
  
	omp_destroy_lock(&MAXLOCK); 
	printf("the lock is destroyed\n");

	current_value = array[0]; 
	for (i = 1; i<n; i++) 
		if (array[i] >current_value) 
			current_value = array[i]; 

	printf("The Array Elements Are \n"); 
	for (i = 0; i<n; i++) 
		printf("%d\t", array[i]); 
 
	if (current_value == cur_max) 
	printf("\nThe Max Value Is Same For Serial And Using Parallel OpenMP Directive\n"); 
	else
	{ 
		printf("\nThe Max Value Is Not Same In Serial And Using Parallel OpenMP Directive\n"); 
		exit(1); 
	} 

	printf("\nThe Largest Number Of The Array Is %d\n", cur_max); 
} 
