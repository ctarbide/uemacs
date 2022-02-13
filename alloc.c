/*
 * this file contains public domain code from the icon language compiler, it was
 * taken from https://github.com/gtownsend/icon/blob/master/src/common/alloc.c
 */

/*
 * alloc.c -- allocation routines for the Icon compiler
 */

/* #include "../h/gsupport.h" */

#include "estruct.h"
#include "edef.h"
#include "efunc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if NEED_ICON_SALLOC
/*
 * salloc - allocate and initialize string
 */

char *salloc(char *s)
{
	char *s1;
	s1 = (char *)malloc(strlen(s) + 1);

	if (s1 == NULL) {
		fprintf(stderr, "salloc(%d): out of memory\n", (int)strlen(s) + 1);
		exit(EXIT_FAILURE);
	}

	return strcpy(s1, s);
}
#endif

#if NEED_ICON_ALLOC
/*
 * alloc - allocate n bytes
 */

pointer alloc(unsigned int n)
{
	register pointer a;

	if (n == 0) {			/* Work-around for 0 allocation */
		n = 1;
	}

	a = calloc(n, sizeof(char));

	if (a == NULL) {
		fprintf(stderr, "alloc(%d): out of memory\n", (int)n);
		exit(EXIT_FAILURE);
	}

	return a;
}
#endif
