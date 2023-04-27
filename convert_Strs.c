#include "main.h"

unsigned int convert_s(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int parse_S(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_rev(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_Rot13(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_s - this function that Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @data: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_s(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(data, char *);
	if (str == NULL)
		return (_memcpy(cout, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_str_width(cout, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	while (*str != '\0' && prec > 0)
	{
		ret += _memcpy(cout, str, 1);
		prec--;
		str++;
	}

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}

/**
 * parse_S - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @data: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int parse_S(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, index;
	unsigned int ret = 0;

	(void)len;
	str = va_arg(data, char *);
	if (str == NULL)
		return (_memcpy(cout, null, 6));

	for (size = 0; str[size];)
		size++;

	ret += print_str_width(cout, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (index = 0; *(str + index) != '\0' && index < prec; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			ret += _memcpy(cout, hex, 2);
			if (*(str + index) < 16)
				ret += _memcpy(cout, &zero, 1);
			ret += convert_u_base(cout, *(str + index),
					     "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		ret += _memcpy(cout, (str + index), 1);
	}

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}

/**
 * convert_rev - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @data: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_rev(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(data, char *);
	if (str == NULL)
		return (_memcpy(cout, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_str_width(cout, flags, wid, prec, size);

	end = size - 1;
	prec = (prec == -1) ? size : prec;
	for (i = 0; end >= 0 && i < prec; i++)
	{
		ret += _memcpy(cout, (str + end), 1);
		end--;
	}

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}

/**
 * convert_Rot13 - Converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @data: A va_list pointing to the string to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A lenth modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_Rot13(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(data, char *);
	if (str == NULL)
		return (_memcpy(cout, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += print_str_width(cout, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (i = 0; *(str + i) != '\0' && i < prec; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				ret += _memcpy(cout, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			ret += _memcpy(cout, (str + i), 1);
	}

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}
