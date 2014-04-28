/*
 * (C) 2014 Jindong Huang
 * 
 * lib/string.c
 *
 * The implementation of string operations.
 * 
 */

unsigned int strnlen(const char *s, unsigned int count)
{
	const char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc);

	return sc - s;
}

unsigned int strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc);

	return sc - s;
}

void *memset(void *dest, int data, unsigned int size)
{
	char *d = (char *)dest;

	while (size--)
		*d++ = data;

	return dest;
}

void *memcpy(void *dest, const void *src, unsigned int size)
{
	char       *d = (char *)dest;
	const char *s = (const char *)src;

	while (size--) 
		*d++ = *s++;

	return dest;
}

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

