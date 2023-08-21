#include "main.h"
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 *
 * @format: format.
 *
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, pri_c = 0, printed = 0;
	int f, w, p, s, buff_ind = 0;
	va_list x;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(x, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			pri_c++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			f = get_flags(format, &i);
			w = get_width(format, &i, x);
			p = get_precision(format, &i, x);
			s = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, x, buffer,
				f, w, p, s);
			if (printed == -1)
				return (-1);
			pri_c += printed;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(x);
	return (pri_c);
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
