#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "debug.h"

void debug(const char *fn, const char *fmt, ...)
{
	int c;		/* current char in format string */
	FILE *f;
	va_list ap;

	f = fopen(fn, "a");
	if (f == NULL)
		return;

	va_start(ap, fmt);
	while ((c = *fmt++) != 0) {
		if (c != '%') {
			fputc(c, f);
		} else {
			c = *fmt++;
			switch (c) {
			case 'd':
				fprintf(f, "%d", va_arg(ap, int));
				break;

			case 's':
				fprintf(f, "%s", va_arg(ap, char *));
				break;

			default:
				fputc(c, f);
			}
		}
	}
	va_end(ap);

	fclose(f);
}
