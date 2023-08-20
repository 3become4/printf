#include "main.h"

/**
 * get_width - Calculates width
 *
 * @format: Formatted string
 * @i: List of arguments
 * @list: list of arguments
 *
 * Return: width
 */
int get_width(const char *format, int *i, va_list list)
{
	int ii;
	int w = 0;

	for (ii = *i + 1; format[ii] != '\0'; ii++)
	{
		if (is_digit(format[ii]))
		{
			w *= 10;
			w += format[ii] - '0';
		}
		else if (format[ii] == '*')
		{
			ii++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = ii - 1;

	return (w);
}

