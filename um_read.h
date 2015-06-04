/*
 * um_read.h
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * interface for reading a .um file into a uint32_t array of instructions
 *
 */

#ifndef UM_READ
#define UM_READ
#include <stdio.h>
#include <stdint.h>

/*
 * given FILE* opened from valid .um program, returns a uint32_t array 
 * corresponding to the sequence of instructions in the file
 */
uint32_t* read_program(FILE* um_program);

#endif