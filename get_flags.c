#include "main.h"

/**
 * get_flags - gets flags
 *
 * @format: char pointer for format
 * @i: int pointer for args
 *
 * Return: flags
 */
int get_flags(const char *format, int *i)
{
	int j, ci;
	int x = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (ci = *i + 1; format[ci] != '\0'; ci++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[ci] == FLAGS_CH[j])
			{
				x |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = ci - 1;

	return (x);
}
