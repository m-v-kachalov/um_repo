/*
 * um_read.c
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * implementation of a function to read .um file and create a uint32_t array
 * representing the sequence of instruction words in it
 *
 */

#include <stdlib.h>
#include "um_read.h"

/*
 * given FILE* opened from valid .um program, returns a uint32_t array 
 * corresponding to the sequence of instructions in the file
 */
uint32_t* read_program(FILE* program) {
        uint32_t temp, cur_word;
        temp = cur_word = 0;

        // char pointers used in lines 30-33 to change endian-ness
        char* cur_word_ptr = (char*)&cur_word;
        char* temp_ptr = (char*)&temp; 

        uint32_t num_words = 0;
        uint32_t array_len = 1;
        uint32_t* seg_z = malloc(sizeof(uint32_t) * array_len); // segment zero

        while (!feof(program)) {
                fread(&cur_word, 4, 1, program);
                // change big-endian .um file words to litle-endian instructions
                for (unsigned i = 0; i < 4; i ++) {
                        temp_ptr[i] = cur_word_ptr[3 - i];
                }
                seg_z[num_words] = temp;
                num_words += 1;
                // resize main segment if necessary
                if (num_words == array_len) { 
                        array_len *= 2;
                        seg_z = realloc(seg_z, sizeof(uint32_t) * array_len); 
                }
        }
        seg_z = realloc(seg_z, sizeof(uint32_t) * num_words);
        return seg_z;
}