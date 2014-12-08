#include"um_read.h"
#include<bitpack.h>

uint32_t* read_program(FILE* program) // should actually be called 'run_program'
{
  uint32_t temp, cur_word;
  temp = cur_word = 0;
  char* cur_word_ptr = (char*)&cur_word;
  char* temp_ptr = (char*)&temp; 
/*
  int op_code, a, b, c; 
  op_code = a = b = c = -1;
  unsigned val_13; */
  uint32_t num_words = 0, array_len = 4; 
  uint32_t* main_seg = malloc(sizeof(uint32_t) * array_len);
  //printf("op %u\tt\tnum words %u\n", op_code, num_words);
  do 
  {
    fread(&temp, 4, 1, program);
   // credit to 
   // http://graphics.stanford.edu/~seander/bithacks.html#BitReverseTable
   for (unsigned i = 0; i < 4; i++)
   {
     cur_word_ptr[i] = 
           ((temp_ptr[3 - i] * 0x80200802ULL) & 0x0884422110ULL) 
                                            * 0x0101010101ULL >> 32;
                              
   } 
   printf("%u\b", cur_word);
  /*op_code = (int)Bitpack_getu(cur_word, 4,  28);
 *
    if (op_code == 13)
    {
      a, val_13 = Bitpack_getu(cur_word, 25, 0), Bitpack_getu(cur_word, 3, 25);
      printf("a %u\t\tval_13 %u\n", a, val_13);
    }t 
    else
    {
      a, b, c = Bitpack_getu(cur_word, 3, 6), Bitpack_getu(cur_word, 3, 3), 
                 Bitpack_getu(cur_word, 3, 0); 
    }
    //printf("%u\n", op_code);
    printf("nw %u\n", num_words);*/
    main_seg[num_words++] = cur_word;
    if (num_words >= (array_len - 1)) 
    { 
      if (num_words >= (((uint64_t)1 << 32) - 1)) { printf("ERROR\n"); break; }
      main_seg = realloc((void*)main_seg, sizeof(uint32_t) * array_len * 2); 
      array_len *= 2; 
    }
  //  printf("num w %u\t\tarray len %u\n\n", num_words, array_len);
  } while (!feof(program));
  return main_seg;
}
