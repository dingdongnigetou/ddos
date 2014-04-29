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

/*
 * erase all the block of nandfalsh
 *
 */
void nand_erase_all();

/*
 * write data from buf into nandflash
 *
 */
void nand_write(unsigned int nand_start, unsigned char *buf,
		unsigned int len);

#endif /* _NAND_H_ */

