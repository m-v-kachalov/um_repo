/*
 * um_execute.h
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * interface for executing the instructions contained in the um zero segment
 *
 */
 
#ifndef UM_EXECUTE
#define UM_EXECUTE

#include<stdbool.h>
#include"um.h"

/* 
 * given UM_T initialized with UM_new() from a valid .um file, executes 
 * the sequence of instructions in 'um->zero_seg' i.e. segment 0
 */ 
void execute_instruction(UM_T um);

#endif