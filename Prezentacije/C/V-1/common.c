#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>


int main(void)

{
	printf("================================\n");
	printf("Exercise1                       \n");
	printf("================================\n");

	//--------------------------------------------------

	printf("Question 1:");
	getchar();
	unsigned long long ullVar = 1000000000;
	int iVar = 0xFF11;
	printf("Result is %d bytes long\n", sizeof(ullVar - iVar));

	//--------------------------------------------------

	printf("\nQuestion 2: ");
	getchar();
	unsigned char ucVar1 = 128;
	char cVar2 = 128;
	char result = ucVar1 + cVar2;
	printf("%d + %d = %d\n", ucVar1, cVar2, result);

	//--------------------------------------------------

	printf("\nQuestion 3: ");
	getchar();
	int iVar1 = 2147483647;
	int iVar2 = -2147483648;
	result = iVar1 - iVar2;
	printf("%d - %d = %d\n", iVar1, iVar2, result);

	//--------------------------------------------------

	printf("\nQuestion 4: ");
	getchar();
	char c = 255;
	if (c > 128)
	{
		printf("This is unsigned number %d\n", c);
	}
	else
	{
		printf("This is signed number %d\n", c);
	}

	//--------------------------------------------------

	printf("\nQuestion 5: ");
	getchar();
	unsigned int i = 5;
	int j = -20;
	if (i + j > 5)
	{
		printf(">5 = %d\n", i + j);
	}
	else
	{
		printf("<5 = %d\n", i + j);
	}

	//--------------------------------------------------

	printf("\nQuestion 6: ");
	getchar();
	int16_t u16a = 30000;
	int16_t u16b = 30000;
	int32_t u32x = u16a + u16b;
	printf("Result is %d \n", u32x);
	//--------------------------------------------------

	printf("\nQuestion 7: ");
	float fVal = 5.0;
	double dVal;
	int iVal = -7;
	unsigned long ulVal = 1000;
	getchar();
	dVal = iVal * ulVal;
	printf("iVal * ulVal = %lf\n", dVal);
	dVal = iVal + fVal; 
	printf("ulVal + fVal = %lf\n", dVal);

	//--------------------------------------------------

	printf("\nQuestion 8: ");
	getchar();
	printf("Hex -1 is %x\n", -1);

	//--------------------------------------------------

	printf("\nQuestion 9: ");
	getchar();
	float fNumber = 1.1;
	double dNumber = 1.1;

	if (fNumber == dNumber)
	{
		printf("Float and Double are equal\n");
	}
	else
	{
		printf("Float and Double are NOT equal\n");
	}

	//--------------------------------------------------

	return 0;
}
