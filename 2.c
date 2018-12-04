#include <stdio.h>
#include <omp.h>
#include <unistd.h>

void A(int* a) 
{ 
	printf("a++\n"); 
   	(*a)++; 
} 

void B(int* a) 
{ 
	printf("a--\n"); 
   	(*a)--; 
}

void f(int* a) 
{ 
	#pragma omp critical 
	printf("I am Thread %d of %d\n",omp_get_thread_num(),omp_get_num_threads());                                                                                   
	A(a); 

	sleep(5); 

	#pragma omp critical 
	printf("I am Thread %d of %d\n",omp_get_thread_num(),omp_get_num_threads()); 
	B(a); 
} 

int main() 
{ 
	int i; 
	int a = 0; 

	#pragma omp parallel for 
	for(i=0;i<4;i++) 
   	{ 
		printf("No.of Threads triggerd is %d\n",omp_get_thread_num()); 
		f(&a); 
   	} 
	return 0; 
}
