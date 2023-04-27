#include "main.h"

unsigned int convert_char(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_perc(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_ptr(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_char - Converts an argument to an unsigned char and
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
unsigned int convert_char(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char c;
	unsigned int ret = 0;

	(void)prec;
	(void)len;

	c = va_arg(data, int);

	ret += print_wid(cout, ret, flags, wid);
	ret += _memcpy(cout, &c, 1);
	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}

/**
 * convert_perc - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @data: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int convert_perc(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char percent = '%';
	unsigned int ret = 0;

	(void)data;
	(void)prec;
	(void)len;

	ret += print_wid(cout, ret, flags, wid);
	ret += _memcpy(cout, &percent, 1);
	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}

/**
 * convert_ptr - Converts the address of an argument to hex and
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
unsigned int convert_ptr(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int ret = 0;

	(void)len;

	address = va_arg(data, unsigned long int);
	if (address == '\0')
		return (_memcpy(cout, null, 5));

	flags |= 32;
	ret += convert_u_base(cout, address, "0123456789abcdef",
			flags, wid, prec);
	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}
