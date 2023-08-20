#include "main.h"

/**
 * _printf - Printf function
 *
 * @format: format.
 *
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, p = 0, pc = 0;
	int f, w, pr, s, bi = 0;
	va_list x;
	char buf[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(x, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buf[bi++] = format[i];
			if (bi == BUFF_SIZE)
				print_buffer(buf, &bi);
			write(1, &format[i], 1);
			pc++;
		}
		else
		{
			print_buffer(buf, &bi);
			f = get_flags(format, &i);
			w = get_width(format, &i, x);
			pr = get_precision(format, &i, x);
			s = get_size(format, &i);
			++i;
			p = handle_print(format, &i, x, buf,
				f, width, pr, s);
			if (p == -1)
				return (-1);
			pc += p;
		}
	}
	print_buffer(buf, &bi);
	va_end(x);
	return (pc);
}

/**
 * print_buffer - print buffer
 *
 * @buffer: char array
 * @buff_ind: index of buffer
 *
 * return: void
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
