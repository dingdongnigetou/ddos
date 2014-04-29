/*
 * (C) 2014 Jindong Huang
 *
 * include/io_format.h
 *
 * The interface of ioformat.
 *
 */

#ifndef _IOFORMAT_H
#define _IOFORMAT_H

/*
 * Format the args into the buf with the fmt.
 *
 * if successful
 *      return the length of args (how many ch gonna to output)
 * else
 *      return -1
 *
 */
int ddprintf(char *buf, const char *fmt, char *args);

/*
 * Unformat the buf into the args with the fmt.
 *
 * if successful
 *      return the length of buf (how many ch gonna to input)
 * else 
 *      return -1
 *
 */
int ddscanf(char *buf, const char *fmt, char *args);

#endif /* _IOFORMAT_H */

