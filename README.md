
# Project Printf

A formatted output conversion C program completed as part of the low-level programming and advanced data structures. The program is a pseudo- recreation of the C standard library function, `printf`.

## Description of the project
The function `_printf` writes output to standard output. The function writes the output under the control of a `format` string that specifies how subsequent arguments (accessed via the variable-length argument facilities of `stdarg`) are converted for output.

### Return Value
Upon successful return, `_printf` returns the number of characters printed (excluding the terminating null byte used to end output to strings). If an output error is encountered, the function returns `-1`.

### Format of the Argument String
The `format` string argument is a constant character string composed of zero or more directives: ordinary characters (not `%`) which are copied unchanged to the output stream; and conversion specifications, each of which results in fetching zero or more subsequent arguments. Conversion specification is introduced by the character `%` and ends with a conversion specifier. The arguments must correspond with the conversion specifier, and are used in the order given.

### Conversion Specifiers

The conversion specifier (introduced by the character `%`) is a character that specifies the type of conversion to be applied. The conversion specifiers and their meaning are:

* **d, i**

The `int` argument is converted to signed decimal notation.

* **b**

The `unsigned int` argument is converted to signed decimal notation.

* **o, u, x, X**

The `unsigned int` argument is converted to unsigned octal (`o`), unsigned decimal (`u`), or unsigned hexadecimal (`x` and `X`). The letters `abcdef` are used for `x` conversions and the letters `ABCDEF` are used for `X` conversions.

* **c**

The `int` argument is converted to an `unsigned char`.

* **s**

The `const char *` argument is expected to be a pointer to a character array (aka. pointer to a string). Characters from the array are written starting from the first element of the array and ending at, but not including, the terminating null byte (`\0`).

* **S**

Identical to the `s` conversion specifier, except any non-printable characters in the array (ie. characters with an ASCII value < 32 or >= 127) are written as `\x` followed by the ASCII code value in hexadecimal (upper case, two characters).

* **r**

Identical to the `s` conversion specifier, except characters from the array are written in reverse, starting from, but not including, the terminating null byte (`\0`) and ending at the first element of the array.

* **R**

Identical to the `s` conversion specifier, except each character of the array is converted to its corresponding character in ROT13 before being written.

* **p**

The address of the argument is written. The address is written in hexadecimal with a leading `0x`.

* **%**

A `%` is written. No argument is converted. The complete conversion specification is `%%`.


## Authors
* oussama el aouzari <[oussama el aouzari](https://github.com/gtpoint)> - Alx software engineering student
* Abdennebi Bamansour <[bamansour1978](https://github.com/bamansour1978)> - Alx software engineering student
