#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

//#pragma pack(push)  /* push current alignment to stack */
//#pragma pack(1)     /* set alignment to 1 byte boundary */

typedef struct _example_struct
{
	uint8_t   char_a;
	uint32_t    uint_b;
	uint16_t  short_c;
	uint16_t  short_d;
//} example_struct;
} __attribute__ ((packed)) example_struct;

//#pragma pack(pop)   /* restore original alignment from stack */


int main(void)
{	
	char arr1[1];
	char arr2[3];
	example_struct ex_struct;



	printf("arr1     size %"PRIuPTR"  \taddr: %p (4-byte alligned: %s)\n", sizeof(arr1),  &arr1,      ((intptr_t)(&arr1)%4)      ? "NO" : "YES");
	printf("arr2     size %"PRIuPTR"  \taddr: %p (4-byte alligned: %s)\n", sizeof(arr2),  &arr2,      ((intptr_t)(&arr2)%4)      ? "NO" : "YES");
	printf("struct   size %"PRIuPTR"  \taddr: %p (4-byte alligned: %s)\n", sizeof(example_struct), &ex_struct, ((intptr_t)(&ex_struct)%4) ? "NO" : "YES");
		
	return 0;
}
