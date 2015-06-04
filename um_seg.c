/*
 * um_seg.c
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * implementation of segment mapping, unmapping and duplication
 *
 */

#include"um_seg.h"

/* 
 * maps a new segment comprised of r[c] words all of which are initialized 
 * to 0 and creates a valid ID for it, which is stored in r[b]
 */
void map_segment(UM_T um, char b, char c) {
        uint32_t* new_seg = calloc(sizeof(uint32_t), (um->r[c] + 1));
        new_seg[0] = um->r[c]; // store length of new segment in 0th 'word'
        uint32_t cur_ID;
      /* 
        if no unmapped IDs available, use current maximum ID and increment it.
        otherwise, use the most recently unmapped ID
      */
        if (Seq_length(um->unmapped_IDs) != 0) { 
                cur_ID = (uint32_t)(uintptr_t)Seq_remhi(um->unmapped_IDs); 
        }
        else {
                uint32_t len_segs = um->len_segs;
                if (len_segs == um->cur_max_ID) {
          // resize segments array if necessary
                        um->segments = realloc((void*)um->segments, 
                                     (sizeof(uint32_t*) * len_segs * 2));
                        um->len_segs *= 2;
          }
        cur_ID = um->cur_max_ID++;
        }

        // store pointer to 1st word in new segment in um->segments[cur_ID]
        um->segments[cur_ID] = (uint32_t*)&(new_seg[1]);
        um->r[b] = cur_ID;
}

// replaces current zero segment with a copy of 'um->segments[r[b]]'
void load_program(UM_T um, char b) {
        uint32_t* r = um->r;
        if (r[b] == 0) { 
                return; // no need to duplicate segment zero
        } 
        uint32_t* cur_seg = um->segments[r[b]];
        free(um->seg_zero); 
        /* 
        * get the number of words to be copied from the address 1 (i.e. 
        * sizeof(uint32_t)) before pointer in segments[ID] (see map_segment() 
        * above for how a mapped segment is stored in 'um->segments')
        */
        uint32_t cur_len = cur_seg[-1];
        um->seg_zero = malloc(sizeof(uint32_t) * cur_len);
        for (uint32_t i = 0; i < cur_len; i++) {
                um->seg_zero[i] = cur_seg[i];
        }
}

// unmaps segment[r[c]] and stores r[c] in Seq_T of unmapped IDs for reuse
void unmap_segment(UM_T um, char c) {
        uint32_t cur_ID = um->r[c];
        uint32_t* cur_seg = um->segments[cur_ID];
        /* 
        * address malloced in map_segment() is 1 (i.e. sizeof(uint32_t)) before 
        * address assigned to 'um->segments[ID]'. um->segments[ID] now points
        * to freed memory and is set to NULL to prevent invalidly freeing this 
        * address again when UM_free() is called
        */ 
        free(&(cur_seg[-1]));
        um->segments[cur_ID] = NULL;
        Seq_addhi(um->unmapped_IDs, (void*)(uintptr_t)cur_ID);
}