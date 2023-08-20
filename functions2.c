#include "main.h"

/**
 * print_unsigned - prints unsigned number
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: number printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int x = va_arg(types, unsigned long int);

	x = convert_size_unsgnd(x, size);

	if (x == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (x > 0)
	{
		buffer[i--] = (x % 10) + '0';
		x /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_octal - prints unsigned octal number
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 *
 * Return: octal number printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int x = va_arg(types, unsigned long int);
	unsigned long int y = x;

	UNUSED(width);

	x = convert_size_unsgnd(x, size);

	if (x == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (x > 0)
	{
		buffer[i--] = (x % 8) + '0';
		x /= 8;
	}

	if (flags & F_HASH && y != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - prints unsigned hexadecimal number
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
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - prints unsigned upper hexadecimal number
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
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 *
 * @types: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @precision: precision
 * @size: size
 * @map_to: Array of values to map the number to
 * @flag_ch: Calculates active flags
 *
 * Return: hexadecimal printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int x = va_arg(types, unsigned long int);
	unsigned long int y = x;

	UNUSED(width);

	x = convert_size_unsgnd(x, size);

	if (x == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (x > 0)
	{
		buffer[i--] = map_to[x % 16];
		x /= 16;
	}

	if (flags & F_HASH && y != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
