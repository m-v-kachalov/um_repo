#include"um_seg.h"
#include<inttypes.h>
#include"table.h"
#include"atom.h"
#include"mem.h"

uint32_t max_ID = (((uint64_t)1 << 32) - 1);


inline bool map_segment(UM_T um, char b, char c)
{
  uint32_t cur_max_ID = um->cur_max_ID;
 // uint32_t* new_seg = calloc(um->r[c], sizeof(uint32_t));
  uint32_t* new_seg = calloc(sizeof(uint32_t), (um->r[c] + 1));
  new_seg[0] = um->r[c];
//  printf("new seg %u\n", new_seg[0]);
/*  for (unsigned i = 1; i <= um->r[c]; i++)
  {
    new_seg[i] = 0;
  }*/
  uint32_t cur_ID = 0; //generate_ID(um->unmapped_IDs);
  if (Seq_length(um->unmapped_IDs) == 0) 
  {
    if (cur_max_ID == max_ID) 
    {
      free(new_seg);
      return false;
    }
    else 
    {
      cur_ID = um->cur_max_ID++;
    }
  }
  else 
  {
    cur_ID = (uint32_t)(uintptr_t)Seq_remhi(um->unmapped_IDs);
  }
  Table_put(um->segments, Atom_int((long) cur_ID), (void*)new_seg);
  um->r[b] = cur_ID;
 // printf("r[c] %u\n", um->r[c]);
//  printf("ID %"PRIu32"\n", cur_ID);
  return true;
  //else
  //{
    //um->segments[cur_ID] = new_seg;
  //  return true;
  //}
}

/*
static inline uint32_t generate_ID(Seq_T unmapped_IDs)
{
  if (Seq_length(unmapped_IDs) == 0)
  {
    return 0;
  }
  else
  {
    return (uint32_t)(uintptr_t)Seq_remhi(unmapped_IDs);
  }   
}
*/
//uint32_t seg_load(

inline bool load_program(UM_T um, char b, char c)
{
  uint32_t* r = um->r;
  if (r[b] == 0) 
  {
    um->pgm_cntr = r[c];
    return true;
  } 
 // Table_remove(um->segments, Atom_int((long)0));
  uint32_t* cur_seg = (uint32_t*)Table_get(um->segments, Atom_int((long)r[b]));
  if (cur_seg == NULL) { return false; }
  free(um->seg_zero);
  //free(old_seg);
//  printf("cur seg %u\n", cur_seg[0]);
  uint32_t cur_len = cur_seg[0];
//  NEW(um->seg_zero);
  um->seg_zero = malloc(sizeof(uint32_t) * cur_len);
  for (uint32_t i = 1; i <= cur_len; i++)
  {
   // printf("cur_len"
    um->seg_zero[i - 1] = cur_seg[i];
  }
 // Table_put(um->segments, Atom_int((long)0), (void*)um->seg_zero);
  um->pgm_cntr = r[c];
  return true;
}

inline bool unmap_segment(UM_T um, char c)
{
  uint32_t cur_ID = um->r[c];
//  printf("unmap %u\n", cur_ID);
  uint32_t* cur_seg = (uint32_t*)Table_get(um->segments, Atom_int((long)cur_ID));
  if (cur_seg == NULL) 
  {
    return false;
  }
  free(cur_seg);
  Table_remove(um->segments, Atom_int((long)cur_ID));
  Seq_addhi(um->unmapped_IDs, (void*)(uintptr_t)cur_ID);
  return true;
}











