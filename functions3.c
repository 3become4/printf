#include "main.h"

/**
 * print_pointer - prints pointer variable
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: pointer printed
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ec = 0, padd = ' ';
	int i = BUFF_SIZE - 2, l = 2, padds = 1;
	unsigned long numa;
	char map[] = "0123456789abcdef";
	void *x = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (x == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	numa = (unsigned long)x;

	while (numa > 0)
	{
		buffer[i--] = map[numa % 16];
		numa /= 16;
		l++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		ec = '+', l++;
	else if (flags & F_SPACE)
		ec = ' ', l++;

	i++;

	return (write_pointer(buffer, i, l, width, flags, padd, ec, padds));
}

/**
 * print_non_printable - Prints ascii codes for non printable
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: hexadecimal printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, os = 0;
	char *x = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (x == NULL)
		return (write(1, "(null)", 6));

	while (x[i] != '\0')
	{
		if (is_printable(x[i]))
			buffer[i + os] = x[i];
		else
			os += append_hexa_code(x[i], buffer, i + os);

		i++;
	}

	buffer[i + os] = '\0';

	return (write(1, buffer, i + os));
}

/**
 * print_reverse - prints reverse string
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: reverse string printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *x;
	int i, c = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	x = va_arg(types, char *);

	if (x == NULL)
	{
		UNUSED(precision);

		x = ")Null(";
	}
	for (i = 0; x[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = x[i];

		write(1, &z, 1);
		c++;
	}
	return (c);
}
/**
 * print_rot13string - print string in rot13
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: rot13 printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *y;
	unsigned int i, j;
	int c = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	y = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (y == NULL)
		y = "(AHYY)";
	for (i = 0; y[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == y[i])
			{
				x = out[j];
				write(1, &x, 1);
				c++;
				break;
			}
		}
		if (!in[j])
		{
			x = y[i];
			write(1, &x, 1);
			c++;
		}
	}
	return (c);
}
