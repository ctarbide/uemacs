/*
 * taken from https://github.com/openwall/blists/blob/main/misc.c,
 * misc.h not taken
 *
 * various functions removed, only concat maintained, see [1] for
 * more info on concat
 *
 * lconcat based on concat and inspired by strlcpy and strlcat semantics
 *
 * - [1]: https://openwall.info/wiki/people/solar/software/public-domain-source-code/concat
 */

/*
 * Miscellaneous system and library call wrappers.
 * See misc.h for the descriptions.
 *
 * Copyright (c) 1998-2008,2017,2018 Solar Designer <solar at openwall.com>
 * Copyright (c) 2017 ABC <abc at openwall.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

/* allocate combined string from NULL terminated variable argument list */
char*
concat(const char *s1, ...)
{
	va_list args;
	const char *s;
	char *p, *result;
	size_t l, m, n;

	if (!s1) return NULL;

	m = n = strlen(s1);
	va_start(args, s1);
	while ((s = va_arg(args, char *))) {
		l = strlen(s);
		if ((m += l) < l)
			break;
	}
	va_end(args);
	if (s || m >= INT_MAX)
		return NULL;

	result = (char *)malloc(m + 1);
	if (!result)
		return NULL;

	memcpy(p = result, s1, n);
	p += n;
	va_start(args, s1);
	while ((s = va_arg(args, char *))) {
		l = strlen(s);
		if ((n += l) < l || n > m)
			break;
		memcpy(p, s, l);
		p += l;
	}
	va_end(args);
	if (s || m != n || p != result + n) {
		free(result);
		return NULL;
	}

	*p = '\0';
	return result;
}

/* copy combined string from NULL terminated variable argument list,
 * result >= dstsize means buffer size is insufficient and truncation
 * occurred, i.e., mimics strlcpy and strlcat semantics, returns
 * SIZE_MAX on overflow */
size_t
lconcat(char *dst, size_t dstsize, const char *s1, ...)
{
	va_list args;
	size_t l, m;
	const char *s;
	if (!s1) {
		if (dst && dstsize) *dst = '\0';
		return 0;
	}
	s = s1;
	l = m = strlen(s);
	if (dst && dstsize) {
		char *p = dst;
		if (m < dstsize) {
			memcpy(p, s, l);
			p += l;
		}
		va_start(args, s1);
		while ((s = va_arg(args, char *))) {
			l = strlen(s);
			if ((m += l) < l) {
				m = SIZE_MAX;
				break;
			}
			if (m < dstsize) {
				memcpy(p, s, l);
				p += l;
			}
		}
		va_end(args);
		*p = '\0';
	} else {
		va_start(args, s1);
		while ((s = va_arg(args, char *))) {
			l = strlen(s);
			if ((m += l) < l) {
				m = SIZE_MAX;
				break;
			}
		}
		va_end(args);
	}
	return m;
}
