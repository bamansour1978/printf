#include "main.h"

void clean_up(va_list data, buff_t *cout);
int read_f_printf(const char *format, va_list data, buff_t *cout);
int _printf(const char *format, ...);

/**
 * clean_up - this function that performance cleanup operations for _printf.
 * @data: arguments provided to _printf.
 * @cout: buff_t struct.
 */
void clean_up(va_list data, buff_t *cout)
{
	va_end(data);
	write(1, cout->start, cout->len);
	free_buffer(cout);
}

/**
 * read_f_printf - this function that Reads through the format
 * of  string for _printf.
 * @format: Character string to print
 * @cout: buff_t struct containing a buffer.
 * @data: arguments to be printed.
 * int - ..
 * Return: The number of characters stored to @cout.
 */
int read_f_printf(const char *format, va_list data, buff_t *cout)
{
	int i, width, prec, ret_n = 0;
	char tmp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buff_t *, unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flags = handle_flag(format + i + 1, &tmp);
			width = handle_width(data, format + i + tmp + 1, &tmp);
			prec = handle_prec(data, format + i + tmp + 1,
					&tmp);
			len = handle_len(format + i + tmp + 1, &tmp);

			f = handle_specif(format + i + tmp + 1);
			if (f != NULL)
			{
				i += tmp + 1;
				ret_n += f(data, cout, flags, width, prec, len);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				ret_n = -1;
				break;
			}
		}
		ret_n += _memcpy(cout, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	clean_up(data, cout);
	return (ret_n);
}

/**
 * _printf - this function that prints a formatted string.
 * @format: Characters of string
 *
 * Return: The number of char printed.
 */
int _printf(const char *format, ...)
{
	buff_t *cout;
	va_list data;
	int ret_n;

	if (format == NULL)
		return (-1);
	cout = _buffer();
	if (cout == NULL)
		return (-1);

	va_start(data, format);
	ret_n = read_f_printf(format, data, cout);

	return (ret_n);
}
