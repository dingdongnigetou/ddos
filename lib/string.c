/*
 * (C) 2014 Jindong Huang
 * 
 * lib/string.c
 *
 * The implementation of string operations.
 * 
 */

/*
 * set continuous area's value as data.
 *
 */
void *memset(void *dest, int data, unsigned int size)
{
	char *d = (char *)dest;

	while (size--)
		*d++ = data;

	return dest;
}

/*
 * Copy data from src to dest.
 *
 */
void *memcpy(void *dest, const void *src, unsigned int size)
{
	char       *d = (char *)dest;
	const char *s = (const char *)src;

	while (size--) 
		*d++ = *s++;

	return dest;
}

/*
 * Copy data form src to dest. 
 * Unlike memcpy(), memmove can 
 * handle the overlapped area 
 *
 */
void *memmove(void *dest, const void *src, unsigned int size)
{
	char       *d = (char *)dest;
	const char *s = (const char *)src;

	/* from the front */
	if (src > dest)
		while (size--)
			*d++ = *s++;

	/* from the end */
	if (dest > src){
		d = d + size - 1;
		s = s + size - 1;
		while (size--)
			*d-- = *s--;
	}

	return dest;
}

