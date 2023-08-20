#include "main.h"
/**
 * handle_print - Prints argument based on type
 *
 * @fmt: formatted string
 * @list: rgs list
 * @ind: indentation
 * @buffer: buffer
 * @flags: flags
 * @width: width
 * @precision: precision
 * @size: size
 *
 * Return: 1 or 2
 */
int handle_print(const char *fmt, int *ind, va_list list,
	char buffer[], int flags, int width, int precision, int size)
{
	int i, ul = 0, pc = -1;
	fmt_t x[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; x[i].fmt != '\0'; i++)
		if (fmt[*ind] == x[i].fmt)
			return (x[i].fn(list, buffer, flags, width, precision, size));

	if (x[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		ul += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			ul += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		ul += write(1, &fmt[*ind], 1);
		return (ul);
	}
	return (pc);
}
