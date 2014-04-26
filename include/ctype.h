/*
 * (C) 2014 Jindong Huang
 *
 * include/ctype.h
 *
 * Functions of check characters.
 *
 */

#ifndef _CTYPE_H_
#define _CTYPE_H_

#define TRUE  1
#define FALSE 0

static inline int isalpha(unsigned char c)
{
	if ((c >= 'a' && c <= 'z') || 
			(c >= 'A' && c <= 'Z'))
		return TRUE;

	return FALSE;
}

static inline int isdigit(unsigned char c)
{
	if (c >= '0' && c <= '9')
		return TRUE;

	return FALSE;
}

static inline int isspace(unsigned char c)
{
	if (c == ' ')
		return TRUE;

	return FALSE;
}

static inline int isalnum(unsigned char c)
{
	if (isalpha(c) || isdigit(c))
		return TRUE;

	return FALSE;
}

static inline int isxdigit(unsigned char c)
{
	if (isdigit(c) || c >= 'a' && c <= 'f'
			|| c >= 'A' && c <= 'F')
		return TRUE;

	return FALSE;

}

static inline int isupper(unsigned char c)
{
	if (c >= 'A' && c <= 'Z')
		return  TRUE;

	return FALSE;
}

static inline int islower(unsigned char c)
{
	if (c >= 'a' && c <= 'z')
		return TRUE;

	return FALSE;
}

static inline int toupper(unsigned char c)
{
	if (islower(c))
		c -= 'A' - 'a';

	return c;
}

static inline int tolower(unsigned char c)
{
	if (isupper(c))
		c += 'A' - 'a';

	return c;
}

#endif /* _CTYPE_H_ */

