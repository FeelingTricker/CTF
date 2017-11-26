// ConsoleApplication1.cpp: 
//Base64 codes in test.txt
//the programme print the raletive clear text

#include "stdafx.h"
#include<Windows.h>
char base64[100000] = { 0 };
int index = 0;
void convert(char * c)
{
	if (*c >= 'A'&&*c <= 'z')
	{
		*c = *c - 'A'-6;
		return;
	}
	if (*c >= '0'&&*c <= '9')
	{
		*c = *c - '0';
		return;
	}
	if (*c == '+')
		*c = 62;
	return;
	if (*c == '/')
		*c = 63;
}
int Cal_Num_of_equal_sign(char* s)
{
	int sum = 0;
	for (int i = 0; s[i] != '\0'; i++)
		if (s[i] == '=')
			sum++;
	return sum;
}
void Get_Hidden_Bit(char * s)
{
	int i = 0;
	while (s[i] != '=')
		i++;
	i--;
	convert(&s[i]);
	int equals;
	if ( !(equals = Cal_Num_of_equal_sign(s)))
		return;
	char k = 1;
	k=k << (2*equals-1);
	for (int j = 0; j < 2 * equals; j++)
	{
		int kk = k&s[i];
		if (kk != 0)
			base64[index++] = 1;
		else
			base64[index++] = 0;
		k=k >> 1;
	}

}
void Print_Clear_Text(void)
{
	for (int i = 0; i < index / 8 ; i++)
	{
		char c=0;
		int j = 8 * i;
			c +=  64 * base64[j+1]+ 32 * base64[j+2] + 16 * base64[j+3] + 8 * base64[j+4] + 4 * base64[j+5] + 2 * base64[j+6] + 1 * base64[j+7] ;
			putchar(c);
	}
}

int main()
{
		FILE * f = fopen("test.txt", "r");
		char a[100];
		int i;
		for (i = 0; !feof(f); )
		{
			fscanf(f, "%s", a);
			if (a[0] != '\0')
			{
				Get_Hidden_Bit(a);
			}	
		}
		Print_Clear_Text();
		printf("\n");
		int j;
		for (i = 0; i < index / 8; i++)
		{
			 j = 8 * i;
			for (int k = 0; k < 8; k++)
			{
				putchar(base64[j]==1?'1':'0');
				j++;
			}
			putchar('\n');
		}
		system("pause");
    return 0;
}
