#include "main.h"

/**
 * handle_write_char - Prints a string
 *
 * @c: char
 * @buffer: buffer
 * @flags: flags
 * @width: width
 * @precision: precision
 * @size: Size
 *
 * Return: chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char x = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		x = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = x;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Prints a string
 *
 * @is_negative: arguments
 * @ind: char
 * @buffer: buffer
 * @flags: flags
 * @width: width.
 * @precision: precision
 * @size: size
 *
 * Return: chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int l = BUFF_SIZE - ind - 1;
	char x = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		x = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision, l, x, extra_ch));
}

/**
 * write_num - Write number using bufffer
 *
 * @ind: index
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision
 * @length: length
 * @padd: Pading
 * @extra_c: Extra char
 *
 * Return: printed chars
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec, int length, char padd, char extra_c)
{
	int i, x = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--x] = extra_c;
			return (write(1, &buffer[x], i - x) +
				write(1, &buffer[ind], length - (1 - x)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes unsigned number
 *
 * @is_negative: if negative
 * @ind: index
 * @buffer: buffer
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 *
 * Return: written chars unsigned
 */
int write_unsgnd(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int l = BUFF_SIZE - ind - 1, i = 0;
	char x = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < l)
		x = ' ';

	while (precision > l)
	{
		buffer[--ind] = '0';
		l++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		x = '0';

	if (width > l)
	{
		for (i = 0; i < width - l; i++)
			buffer[i] = x;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], l) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], l));
		}
	}

	return (write(1, &buffer[ind], l));
}

/**
 * write_pointer - Write memory address
 *
 * @buffer: buffer
 * @ind: index
 * @length: Length
 * @width: Width
 * @flags: Flags
 * @padd: padding
 * @extra_c: extra char
 * @padd_start: Index of padding
 *
 * Return: number of chars
 */
int write_pointer(char buffer[], int ind, int length, int width,
	int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}