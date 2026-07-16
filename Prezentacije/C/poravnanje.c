#include <stdio.h>
int __attribute__((aligned(16))) x;

struct Example { 
	char a; 
	int b __attribute__((aligned(16)));
	double c; 
};


struct __attribute__((aligned(16))) Example2 { 
	char a; 
	int b;  
	double c; 
};


int main() {
    printf("Size of x: %zu\n", sizeof(x));
    printf("Size of struct Example: %zu\n", sizeof(struct Example));
    printf("Size of struct Example2: %zu\n", sizeof(struct Example2));
    return 0;
}