#include <stdio.h>
#include <stdint.h>

#define FILE_NAME "binaryFile.dat"


typedef struct _example_struct
{
	int8_t   char_1;
	int8_t   char_2;
	uint32_t uInt_1;
	int16_t  ssInt_2;
	int32_t  sInt_3;
	int8_t   char_3;
} example_struct;


void dumpExampleStruct(example_struct* es);

int main()
{
	FILE* file;
	example_struct eStruct;

	char str[20] = "Test string";
	uint32_t uInt_1 = 22;
	int16_t ssInt_2 = 333;
	int32_t sInt_3 = 4444;
	printf("Writing to binary file %s\n", FILE_NAME);
	file = fopen(FILE_NAME, "wb");
	if (file != NULL)
	{
		fwrite(str, 1, sizeof(int8_t), file);
		fwrite(str + 1, 1, sizeof(int8_t), file);
		fwrite(&uInt_1, 1, sizeof(uint32_t), file);
		fwrite(&ssInt_2, 1, sizeof(int16_t), file);
		fwrite(&sInt_3, 1, sizeof(int32_t), file);
		fwrite(str + 2, 1, sizeof(int8_t), file);
		fclose(file);
		file = NULL;
	}

	printf("\n");
	printf("Reading struct from binary file %s\n", FILE_NAME);
	file = fopen(FILE_NAME, "rb");
	if (file != NULL)
	{
		fread(&eStruct, 1, sizeof(example_struct), file);
		dumpExampleStruct(&eStruct);
		fclose(file);
		file = NULL;
	}

	return 1;
}

void dumpExampleStruct(example_struct* es)
{
	printf("example_struct\n");
	printf("  char_1 = %c\n", es->char_1);
	printf("  char_2 = %c\n", es->char_2);
	printf("  uInt_1 = %d\n", es->uInt_1);
	printf("  ssInt_2 = %d\n", es->ssInt_2);
	printf("  sInt_3 = %d\n", es->sInt_3);
	printf("  char_3 = %c\n", es->char_3);
	printf("\n");
}

