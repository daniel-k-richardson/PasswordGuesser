#include "password_generator.h"

char *format_string(char string[], const int string_len)
{
	for (int i = 0; i < string_len; i++) {
		if (string[i] == ' ') {
			memmove(&string[i], &string[i+1], string_len - i);
		}
	}	

	return string;
}