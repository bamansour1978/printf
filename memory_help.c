#include "main.h"

unsigned int _memcpy(buff_t *cout, const char *src, unsigned int n);
void free_buffer(buff_t *cout);
buff_t *_buffer(void);

/**
 * _memcpy - this function that Copies n bytes from memory area src to
 *           the buffer contained in a buff_t struct.
 * @cout: A buff_t struct.
 * @src: A pointer to the memory area to copy.
 * @n: The number of bytes to be copied.
 *
 * Return: The number of bytes copied.
 */
unsigned int _memcpy(buff_t *cout, const char *src, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
	{
		*(cout->buffer) = *(src + index);
		(cout->len)++;

		if (cout->len == 1024)
		{
			write(1, cout->start, cout->len);
			cout->buffer = cout->start;
			cout->len = 0;
		}

		else
			(cout->buffer)++;
	}

	return (n);
}

/**
 * free_buffer - Frees a buff_t struct.
 * @cout: The buff_t struct to be freed.
 */
void free_buffer(buff_t *cout)
{
	free(cout->start);
	free(cout);
}

/**
 * _buffer - Initializes a variable of struct type buff_t.
 *
 * Return: A pointer to the initialized buff_t.
 */
buff_t *_buffer(void)
{
	buff_t *cout;

	cout = malloc(sizeof(buff_t));
	if (cout == NULL)
		return (NULL);

	cout->buffer = malloc(sizeof(char) * 1024);
	if (cout->buffer == NULL)
	{
		free(cout);
		return (NULL);
	}

	cout->start = cout->buffer;
	cout->len = 0;

	return (cout);
}
