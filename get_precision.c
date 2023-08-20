#include "main.h"

/**
 * get_precision - get precision
 *
 * @format: char pointer array
 * @i: args
 * @list: list of args
 *
 * Return: precision
 */
int get_precision(const char *format, int *i, va_list list)
{
	int ci = *i + 1;
	int x = -1;

	if (format[ci] != '.')
		return (x);

	x = 0;

	for (ci += 1; format[ci] != '\0'; ci++)
	{
		if (is_digit(format[ci]))
		{
			x *= 10;
			x += format[ci] - '0';
		}
		else if (format[ci] == '*')
		{
			ci++;
			x = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = ci - 1;

	return (x);
}
