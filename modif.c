#include "main.h"

unsigned int print_wid(buff_t *cout, unsigned int printed,
		unsigned char flags, int wid);
unsigned int print_str_width(buff_t *cout,
		unsigned char flags, int wid, int prec, int size);
unsigned int print_negl_width(buff_t *cout, unsigned int printed,
		unsigned char flags, int wid);

/**
 * print_wid - Stores leading spaces to a buffer for a width modifier.
 * @cout: A buff_t struct containing a character array.
 * @printed: The current number of characters already printed to cout
 *           for a given number specifier.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_wid(buff_t *cout, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		for (wid -= printed; wid > 0;)
			ret += _memcpy(cout, &width, 1);
	}

	return (ret);
}

/**
 * print_str_width - Stores leading spaces to a buffer for a width modifier.
 * @cout: A buff_t struct containing a character array.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @size: The size of the string.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_str_width(buff_t *cout,
		unsigned char flags, int wid, int prec, int size)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		wid -= (prec == -1) ? size : prec;
		for (; wid > 0; wid--)
			ret += _memcpy(cout, &width, 1);
	}

	return (ret);
}

/**
 * print_negl_width - this function that Stores trailing spaces to a buffer for a '-' flag.
 * @cout: A buff_t struct containing a character array.
 * @printed: The current number of bytes already stored to cout
 *           for a given specifier.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_negl_width(buff_t *cout, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int ret = 0;
	char width = ' ';

	if (NEG_FLAG == 1)
	{
		for (wid -= printed; wid > 0; wid--)
			ret += _memcpy(cout, &width, 1);
	}

	return (ret);
}
