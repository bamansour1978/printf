#include "main.h"

unsigned char handle_flag(const char *flag, char *index);
unsigned char handle_len(const char *modifier, char *index);
int handle_width(va_list data, const char *modifier, char *index);
int handle_prec(va_list data, const char *modifier, char *index);
unsigned int (*handle_specif(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char);

/**
 * handle_flag - this function Matches flags with corresponding values.
 * @flag: A pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 *
 * Return: If flag characters are matched - a corresponding value.
 *         Otherwise - 0.
 */
unsigned char handle_flag(const char *flag, char *index)
{
	int i, j;
	unsigned char ret = 0;
	flag_e flags[] = {
			{'+', PLUS},
			{' ', SPACE},
			{'#', HASH},
			{'0', ZERO},
			{'-', NEG},
			{0, 0}};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (ret == 0)
					ret = flags[j].value;
				else
					ret |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (ret);
}

/**
 * handle_len - Matches length modifiers with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char handle_len(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - Matches a width modifier with its corresponding value.
 * @data: A va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */
int handle_width(va_list data, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(data, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_prec - Matches a precision modifier with
 *                    its corresponding value.
 * @data: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a precision modifier is matched - its value.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int handle_prec(va_list data, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(data, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_specif - Matches a conversion specifier with
 *                     a corresponding conversion function.
 * @char: ..
 * @int: ..
 * @ buff_t: ..
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*handle_specif(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	convert_t converters[] = {
			{'c', convert_char},
			{'s', convert_s},
			{'d', convert_Int},
			{'i', convert_Int},
			{'%', convert_perc},
			{'b', convert_binary},
			{'u', parse_u},
			{'o', convert_oct},
			{'x', parse_hex},
			{'X', parse_X},
			{'S', parse_S},
			{'p', convert_ptr},
			{'r', convert_rev},
			{'R', convert_Rot13},
			{0, NULL}};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
