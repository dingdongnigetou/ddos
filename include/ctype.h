/*
 * (C) 2014 Jindong Huang
 *
 * include/ctype.h
 * 
 * The type of characters.
 *
 */

#ifndef _CTYPE_H_
#define _CTYPE_H_

#include <common.h>
#include <types.h>

static inline int isalpha(u_char c)
{
	if ((c >= 'a' && c <= 'z') || 
			(c >= 'A' && c <= 'Z'))
		return TRUE;

	return FALSE;
}

static inline int isdigit(u_char c)
{
	if (c >= '0' && c <= '9')
		return TRUE;

	return FALSE;
}

static inline int isspace(u_char c)
{
	if (c == ' ')
		return TRUE;

	return FALSE;
}

static inline int isalnum(u_char c)
{
	if (isalpha(c) || isdigit(c))
		return TRUE;

	return FALSE;
}

static inline int isxdigit(u_char c)
{
	if (isdigit(c) || c >= 'a' && c <= 'f'
			|| c >= 'A' && c <= 'F')
		return TRUE;

	return FALSE;

}

static inline int isupper(u_char c)
{
	if (c >= 'A' && c <= 'Z')
		return  TRUE;

	return FALSE;
}

static inline int islower(u_char c)
{
	if (c >= 'a' && c <= 'z')
		return TRUE;

	return FALSE;
}

static inline int toupper(u_char c)
{
	if (islower(c))
		c -= 'A' - 'a';

	return c;
}

static inline int tolower(u_char c)
{
	if (isupper(c))
		c += 'A' - 'a';

	return c;
}

#endif /* _CTYPE_H_ */

