// header file
#include "main.h"


void task1(void)
{
	int i ,n ;	
	print("in task 1\n");
	for(i=0; i < 999999 ; i++)
	{
		if(i%1000 == 0)
		{
			n = i;
			n = n/1000 ;
//			print(n+48);
		}
	}
}

void task2(void)
{
	int j = 0;	
	print("in task 2\n");
	for(;j<10;j++);
}

void main(void)
{
	timer_start();
	task1();
}
