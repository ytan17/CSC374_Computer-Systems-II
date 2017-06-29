
/*-------------------------------------------------------------------------*
 *---									---*
 *---		header.h						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2017 January 2		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

// need to be change, fix number to function or other variable
#ifndef HEADER_H_
#define HEADER_H_

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

//my code
extern void countWithList(int);
extern void countWithTree(int);
extern int getNextNumber();

#define		MAX_LINE	256

#define		RANGE_LOWEST	0

#define		RANGE_HIGHEST	32767

#define		MIN_NUM_NUMBERS	0

#define		MAX_NUM_NUMBERS	0x40000000

#endif 