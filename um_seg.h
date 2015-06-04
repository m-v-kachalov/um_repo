/*
 * um_seg.h
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * interface for management of segment mapping, unmapping and duplication.
 * the following functions execute instructions 8, 9 and 12 and assume that
 * parameter 'um' is a valid UM_T and b,c are valid register indices  
 */
 
#ifndef UM_SEG
#define UM_SEG

#include<stdbool.h>
#include"um.h"

/* 
 * maps a new segment comprised of r[c] words all of which are initialized 
 * to 0 and creates a valid ID for it, which is stored in r[b]
 */
void map_segment(UM_T um, char b, char c);

// replaces current zero segment with a copy of 'um->segments[r[b]]'
void load_program(UM_T um, char b);

// unmaps segment[r[c]] and stores r[c] in Seq_T of unmapped IDs for reuse
void unmap_segment(UM_T um, char c);

#endif