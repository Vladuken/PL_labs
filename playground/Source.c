#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

int sum(int count, ...)
{
	va_list args;
	int result = 0;
	va_start(args, count);
	for (int i = 0; i < count; i++)
	{
		result += va_arg(args, int);
	}
	va_end(args);

	return result;
}


void main()
{
	int avg = sum(11, 7, 3, 8);
	printf("%d", avg);
	getchar();
}

