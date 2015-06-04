/*
 * um_execute.c
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * implementation of um_execute interface for executing um instructions
 *
 */

#include "um_execute.h"
#include "um_ops.h"
#include "um_seg.h"
#include "bitpack.h"

/* 
 * given UM_T initialized with UM_new() from a valid .um program, executes 
 * the sequence of instructions in 'um->zero_seg' i.e. segment 0
 */ 
void execute_instruction(UM_T um) { 
        for (uint32_t i = 0; ; i++) {
                uint32_t* r = um->r;
                uint32_t cur_word = um->seg_zero[i];
                int op_code = (int)Bitpack_getu(cur_word, 4,  28);
                if (op_code == 13) {
                        uint32_t val_13 = Bitpack_getu(cur_word, 25, 0);
                        int a = (int)Bitpack_getu(cur_word, 3, 25);
                        r[a] = val_13;
                } 
                else {  
                        int a = Bitpack_getu(cur_word, 3, 6);
                        int b = Bitpack_getu(cur_word, 3, 3); 
                        int c = Bitpack_getu(cur_word, 3, 0); 
                        switch(op_code) {
                                int cur_in;
                                uint64_t temp;
                                uint32_t* cur_seg;
                                case 0:
                                        cond_move(r, a, b, c);
                                        break; 

                                case 1:
                                        seg_load(um, a, b, c);
                                        break;

                                case 2:
                                        seg_store(um, a, b, c);
                                        break;

                                case 3:
                                        add(r, a, b, c);
                                        break;

                                case 4:
                                        multi(r, a, b, c);
                                        break;

                                case 5: 
                                        divide(r, a, b, c);
                                        break;

                                case 6:
                                        nand(r, a, b, c);
                                        break;

                                case 7:
                                        return;

                                case 8:
                                        map_segment(um, b, c);
                                        break;

                                case 9:
                                        unmap_segment(um, c);
                                        break;

                                case 10:
                                        putchar(r[c]);
                                        break;

                                case 11:
                                        cur_in = getchar();
                                        // if input is EOF, set r[c] to all 1s
                                        if (cur_in == -1) { 
                                                r[c] = ((uint64_t)1 << 32) - 1; 
                                        }
                                        else  { 
                                                r[c] = cur_in; 
                                        }
                                        break;

                                case 12:
                                        if (r[b] != 0){ 
                                                load_program(um, b); 
                                        }
                                        i = r[c] - 1;
                                        break;
                                }
                }   
        }
}
