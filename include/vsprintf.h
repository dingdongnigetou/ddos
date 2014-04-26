/*
 * (C) 2014 Jindong Huang
 *
 * include/vsprintf.h
 *
 * The interface of vsprintf.c
 *
 */


#ifndef _VSPRINTF_H
#define _VSPRINTF_H

typedef char *va_list;

/*
 * Storage alignment properties
 */
#define	 NATIVE_INT		 int
#define  _AUPBND         (sizeof (NATIVE_INT) - 1)
#define  _ADNBND         (sizeof (NATIVE_INT) - 1)

/*
 * Variable argument list macro definitions
 */
#define _bnd(X, bnd)    (((sizeof (X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)   (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
#define va_end(ap)      (void) 0
#define va_start(ap, A) (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))

int vsnprintf(char *buf, unsigned int size, const char *fmt, va_list args);
int vsprintf(char *buf, const char *fmt, va_list args);
int vsscanf(const char * buf, const char * fmt, va_list args);

#endif /* _VSPRINTF_H */

