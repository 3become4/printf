#include "main.h"

/**
 * get_size - get size
 *
 * @format: char pointer of array
 * @i: arg list
 *
 * Return: size
 */
int get_size(const char *format, int *i)
{
	int ci = *i + 1;
	int x = 0;

	if (format[ci] == 'l')
		x = S_LONG;
	else if (format[ci] == 'h')
		x = S_SHORT;

	if (x == 0)
		*i = ci - 1;
	else
		*i = ci;

	return (x);
}
