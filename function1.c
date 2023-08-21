#include "main.h"

/**
 * print_char - print char
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/**
 * print_string - print string
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int l = 0, i;
	char *x = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (x == NULL)
	{
		x = "(null)";
		if (precision >= 6)
			x = "      ";
	}

	while (x[l] != '\0')
		l++;

	if (precision >= 0 && precision < l)
		l = precision;

	if (width > l)
	{
		if (flags & F_MINUS)
		{
			write(1, &x[0], l);
			for (i = width - l; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - l; i > 0; i--)
				write(1, " ", 1);
			write(1, &x[0], l);
			return (width);
		}
	}

	return (write(1, x, l));
}

/**
 * print_percent - print percent
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - print int
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: int printed
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - print unsigned binary
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: unsigned binary printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char x = '0' + a[i];

			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

