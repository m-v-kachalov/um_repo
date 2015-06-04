/*
 * um_ops.h
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * interface for instructions 0 - 6
 *
 */

#ifndef UM_OPS
#define UM_OPS
#include <stdint.h>
#include <stdlib.h>
#include "um.h"

 /*
  * functions which correspond to instructions 0-6. functions 0, 3-6 expect 
  * the register pointer 'um->r' in addition to register indices, while 
  * 1,2 expect a valid UM_T (also in addition to register indices)
  */

void cond_move(uint32_t* r, int a, int b, int c);

void seg_load(UM_T um, int a, int b, int c);

void seg_store(UM_T um, int a, int b, int c);

void add(uint32_t* r, int a, int b, int c);

void multi(uint32_t* r, int a, int b, int c);

void divide(uint32_t* r, int a, int b, int c);

void nand(uint32_t* r, int a, int b, int c);

#endif