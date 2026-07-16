#include <stdio.h>
struct Struct1  {
    		unsigned int a : 1;  // 1 bit for a (0 or 1)
    		unsigned int b : 3;  // 3 bits for b (0 to 7)
    		unsigned int c : 4;  // 4 bits for c (0 to 15)
    		unsigned int d : 8;  // 8 bits for d (0 to 255)
		    unsigned int : 0; // označava da se naredno polje mora pakovati u novi broj iako imam dovoljno prostora
	};

struct Struct2  {
    		unsigned int a;  // 1 bit for a (0 or 1)
    		unsigned int b;  // 3 bits for b (0 to 7)
    		unsigned int c;  // 4 bits for c (0 to 15)
    		unsigned int d;  // 8 bits for d (0 to 255)
	};
struct BezNule {
    unsigned int a : 1;
    unsigned int b : 3;
    unsigned int c : 4;
    unsigned int d : 8;
};

struct SaNulom {
    unsigned int a : 1;  // Ide u Blok 1
    unsigned int b : 3;  // Ide u Blok 1
    unsigned int c : 4;  // Ide u Blok 1
    
    unsigned int : 0;    // FORCE STOP! "Zatvori Blok 1 ovdje"
    
    unsigned int d : 8;  // Kompajler MORA započeti Blok 2 za d!
};
int main() {
    struct Struct1 s;

    s.a = 1; //1
    s.b = 5; //3 
    s.c = 10; //4
    s.d = 200; //8

    printf("Size of struct Struct1: %zu bytes\n", sizeof(s));
    printf("Values: a=%u, b=%u, c=%u, d=%u\n", s.a, s.b, s.c, s.d);


    s.a = 2; //010
    s.b = 8; //1000
    s.c = 16; //00010000
    s.d = 300; //0000000100101100

    printf("Values after modification: a=%u, b=%u, c=%u, d=%u\n", s.a, s.b, s.c, s.d);

    printf("Size of struct Struct1: %zu bytes\n", sizeof(struct Struct1));
    printf("Size of struct Struct2: %zu bytes\n", sizeof(struct Struct2));

    printf("Size of struct BezNule: %zu bytes\n", sizeof(struct BezNule));
    printf("Size of struct SaNulom: %zu bytes\n", sizeof(struct SaNulom));


    return 0;
}