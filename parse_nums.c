#include "main.h"

unsigned int convert_Int(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_binary(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int parse_u(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_oct(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_Int - this function that Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @data: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_Int(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	long int d, copy;
	unsigned int ret = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (len == LONG)
		d = va_arg(data, long int);
	else
		d = va_arg(data, int);
	if (len == SHORT)
		d = (short)d;

	if (SPACE_FLAG == 1 && d >= 0)
		ret += _memcpy(cout, &space, 1);

	if (prec <= 0 && NEG_FLAG == 0) /* Handle width  */
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;

		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += _memcpy(cout, &plus, 1);
		if (ZERO_FLAG == 1 && d < 0)
			ret += _memcpy(cout, &neg, 1);

		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (wid -= count; wid > 0; wid--)
			ret += _memcpy(cout, &pad, 1);
	}
	if (ZERO_FLAG == 0 && d < 0)
		ret += _memcpy(cout, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += _memcpy(cout, &plus, 1);

	if (!(d == 0 && prec == 0))
		ret += convert_s_base(cout, d, "0123456789",
				flags, 0, prec);

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}

/**
 * convert_binary - Converts an unsigned int argument to binary
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
unsigned int convert_binary(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned int num;

	num = va_arg(data, unsigned int);

	(void)len;

	return (convert_u_base(cout, num, "01", flags, wid, prec));
}

/**
 * convert_oct - Converts an unsigned int to octal and
 *             stores it to a buffer contained in a struct.
 * @data: A va_list poinitng to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_oct(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char zero = '0';

	if (len == LONG)
		num = va_arg(data, unsigned long int);
	else
		num = va_arg(data, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(cout, &zero, 1);

	if (!(num == 0 && prec == 0))
		ret += convert_u_base(cout, num, "01234567",
				flags, wid, prec);

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}

/**
 * parse_u - Converts an unsigned int argument to decimal and
 *               stores it to a buffer contained in a struct.
 * @data: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @cout: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int parse_u(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;

	if (len == LONG)
		num = va_arg(data, unsigned long int);
	else
		num = va_arg(data, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (!(num == 0 && prec == 0))
		ret += convert_u_base(cout, num, "0123456789",
				flags, wid, prec);

	ret += print_negl_width(cout, ret, flags, wid);

	return (ret);
}
