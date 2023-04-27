#include "main.h"

unsigned int parse_hex(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int parse_X(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * parse_hex - this function that Converts an unsigned int argument to hex using abcdef
 *             and stores it to a buffer contained in a struct.
 * @data: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int parse_hex(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char *lead = "0x";

	if (len == LONG)
		num = va_arg(data, unsigned long int);
	else
		num = va_arg(data, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(cout, lead, 2);

	if (!(num == 0 && prec == 0))
		ret += convert_u_base(cout, num, "0123456789abcdef",
				flags, wid, prec);

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}

/**
 * parse_X - Converts an unsigned int argument to hex using ABCDEF
 *             and stores it to a buffer contained in a struct.
 * @data: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int parse_X(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char *lead = "0X";

	if (len == LONG)
		num = va_arg(data, unsigned long);
	else
		num = va_arg(data, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(cout, lead, 2);

	if (!(num == 0 && prec == 0))
		ret += convert_u_base(cout, num, "0123456789ABCDEF",
				flags, wid, prec);

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}
