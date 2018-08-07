#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "estruct.h"
#include "debug.h"

void debug(const char *fn, const char *fmt, ...)
{
	int c;		/* current char in format string */
	FILE *f;
	int v;
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
				v = va_arg(ap, int);
				fprintf(f, "0x%x", v);
				if (v >= (CONTROL + 0x20) && v <= (CONTROL + 0x7e))
					fprintf(f, " (CONTROL + '%c')", v - CONTROL);
				else if (v >= (META + 0x20) && v <= (META + 0x7e))
					fprintf(f, " (META + '%c')", v - META);
				else if (v >= (CTLX + CONTROL + 0x20) &&  v <= (CTLX + CONTROL + 0x7e))
					fprintf(f, " (CTLX | CONTROL | '%c')", v - CTLX - CONTROL);
				else if (v >= (META + CONTROL + 0x20) &&  v <= (META + CONTROL + 0x7e))
					fprintf(f, " (META | CONTROL | '%c')", v - META - CONTROL);
				else if (v >= 0x20 && v <= 0x7e)
					fprintf(f, " ('%c')", (char)v);
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
