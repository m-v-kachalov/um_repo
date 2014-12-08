// interface for the memory segments representation

#ifndef UM_READ
#define UM_READ

#include<stdbool.h>
#include"um.h"

bool map_segment(UM_T um, char b, char c);

static uint32_t generate_ID(Seq_T unmapped_IDs);

bool load_program(UM_T um, char b, char c);

bool unmap_segment(UM_T um, char c);

#endif
