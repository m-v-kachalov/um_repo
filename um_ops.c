
/*
 * um_ops.c
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * implementation of instructions 0 - 6 
 *
 */

#include "um_ops.h"

inline void cond_move(uint32_t* r, int a, int b, int c){
	if (r[c] != 0) { 
                r[a] = r[b]; 
        }
}

inline void seg_load(UM_T um, int a, int b, int c){
	uint32_t* r = um->r;
	uint32_t* cur_seg;
	if (r[b] == 0) { 
		cur_seg = um->seg_zero; 
	}
	else { 
                cur_seg = um->segments[r[b]]; 
        }
	r[a] = cur_seg[r[c]];
}

inline void seg_store(UM_T um, int a, int b, int c){
	uint32_t* r = um->r;
	uint32_t* cur_seg;
	if (r[a] == 0) { 
		cur_seg = um->seg_zero; 
	}
	else { 
		cur_seg = um->segments[r[a]]; 
	}
	cur_seg[r[b]] = r[c];
}

inline void add(uint32_t* r, int a, int b, int c){
        r[a] = r[b] + r[c];
}

inline void multi(uint32_t* r, int a, int b, int c){
        r[a] = r[b] * r[c];
}

inline void divide(uint32_t* r, int a, int b, int c){
        r[a] = r[b] / r[c];
}

inline void nand(uint32_t* r, int a, int b, int c){
        r[a] = ~(r[b] & r[c]);
}