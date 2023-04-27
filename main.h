#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* flags Modifier */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buff_s - buffer struct.
 * @buffer: A pointer to array.
 * @start: pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buff_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buff_t;

/**
 * struct convert_to_s - converter struct.
 * @specifier: conversion specifier.
 * @func: pointer to a conversion function corresponding to specifier.
 *
 */
typedef struct convert_to_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buff_t *,
			unsigned char, int, int, unsigned char);
} convert_t;

/**
 * struct flag_s - flag struct.
 * @flag: character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_e;

int _printf(const char *format, ...);

/* Conversion Specifier Functions */
unsigned int convert_char(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_s(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_Int(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_perc(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_binary(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int parse_u(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_oct(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int parse_hex(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int parse_X(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int parse_S(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_ptr(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_rev(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_Rot13(va_list data, buff_t *cout,
		unsigned char flags, int wid, int prec, unsigned char len);

/* Handlers functions */
unsigned char handle_flag(const char *flags, char *index);
unsigned char handle_len(const char *modifier, char *index);
int handle_width(va_list data, const char *modifier, char *index);
int handle_prec(va_list data, const char *modifier, char *index);
unsigned int (*handle_specif(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char);

/* Modifiers functions */
unsigned int print_wid(buff_t *cout, unsigned int printed,
		unsigned char flags, int wid);
unsigned int print_str_width(buff_t *cout,
		unsigned char flags, int wid, int prec, int size);
unsigned int print_negl_width(buff_t *cout, unsigned int printed,
		unsigned char flags, int wid);

/* Helper Functions */
buff_t *_buffer(void);
void free_buffer(buff_t *cout);
unsigned int _memcpy(buff_t *cout, const char *src, unsigned int n);
unsigned int convert_s_base(buff_t *cout, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_u_base(buff_t *cout, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

#endif
