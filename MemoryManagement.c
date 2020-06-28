/* Cameron Deao */
/* CST-221 */
/* Michael Landreth */
/* 6/28/2020 */

//This program works as a decimal conversion tool.
//Within the program a decimal is displayed in 32-bit binary,
//32-bit hexadecimal, and works through bitwise operators to 
//shift, mask, and add a hex value to create a new decimal.
//The new decimal is displayed alongside the new binary value
//and hexadecimal value.

#include <stdio.h>
#include <stdlib.h>

//Global variables
unsigned int temp;
int transformFinal;

//Method of displaying the binary value.
void displayBinary(int* val)
{
	int i, x;
	printf("Binary value of %d = ", *val);
	//Iterate through a for-loop
	for(i = 31; i >= 0; i--)
	{
		//Bitwise operation.
		x = *val >> i;
		
		//Print to console based on the result of the operator.
		if(x & 1)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	}
	printf("\n");
}

//Method of displaying the hexadecimal.
void displayHex(int* val)
{
	//Two 'printf' statements are used to avoid producing the wrong value.
	printf("Hex value of %d = ", *val);
	//Performing the calculation against the passed value.
	printf("%04x\n", *val);
}

//Method of shifting, masking, and adding the hex calculation.
void displayTransform(int* val)
{
	int temp;
	temp = *val << 16;
	printf("%d Shifted 16 bits: %d\n", *val, temp);	
	transformFinal = temp & *val;
	transformFinal = transformFinal | 0x07FF;
	printf("Final result after bitwise %d\n", transformFinal);
	displayBinary(&transformFinal);
	displayHex(&transformFinal);
}

int main(void)
{
	printf("Enter a value between 0 and 4095\n");
	scanf("%d", &temp);
	//Exception handling. Quits the program if an incorrect value is input.
	if(temp < 0 || temp > 4095)
	{
		fprintf(stderr, "Incorrect input. Exiting...\n");
		exit(EXIT_FAILURE);
	}
	
	displayBinary(&temp);
	displayHex(&temp);
	displayTransform(&temp);
	return 0;
}


