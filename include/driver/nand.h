/*
 * (C) 2014 Jindong Huang
 *
 * include/nand.h
 *
 * The interface of nand flash driver.
 *
 */

#ifndef _NAND_H_
#define _NAND_H_

#include <types.h>

/*
 * erase the block of nandfalsh
 * form 0 to num
 *
 */
void nand_erase_block(u_int num);

/*
 * write data from buf into nandflash
 *
 */
int nand_write(u_int nand_start, u_char *buf, u_int len);

/*
 * read data form nand flash to buf
 */
int nand_read();

#endif /* _NAND_H_ */

