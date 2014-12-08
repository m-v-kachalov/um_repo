#include"um_execute.h"
#include"assert.h"
#include"um_seg.h"
#include"bitpack.h"
#include"atom.h"
#include<inttypes.h>


bool execute_instruction(UM_T um, um_word x)
{ 
  //uint32_t** segments = um->segments;
//uint32_t* seg_zero = um->seg_zero;
uint32_t* r = um->r;
unsigned char op_code, a, b, c; 
op_code = a = b = c = 0;
uint32_t val_13 = 0;
uint32_t cur_word = 0;
for (uint32_t i = 0; ; i++)
{
  cur_word = um->seg_zero[i];
  op_code = (unsigned char)Bitpack_getu(cur_word, 4,  28);
 // printf("pgm cntr %u\t\top code %i\n", um->pgm_cntr, op_code);
  //for (int i = 0; i<8;i++){ printf("r %i: %"PRIu32"\n", i, r[i] ); }
  //printf("\n\n");
//  if (op_code > 13) {fprintf(stderr, "CODE WRONG\n"); exit(1);}
  if (op_code == 13) 
  {
    val_13 = Bitpack_getu(cur_word, 25, 0);
    a = Bitpack_getu(cur_word, 3, 25);
    r[a] = val_13;
  }
  else 
  {  
     a = Bitpack_getu(cur_word, 3, 6), 
     b = Bitpack_getu(cur_word, 3, 3); 
     c = Bitpack_getu(cur_word, 3, 0); 
     switch(op_code)
     {
       //printf("op %u\n", op_code);
       int cur_in;
       uint64_t temp;
       uint32_t* cur_seg;
       case 0:
         if (r[c] != (uint32_t)0) { r[a] = r[b]; }
         break; 
      case 1:
     //    r[a] = segments[ r[b] ][ r[c] ];
         if (r[b] == 0) 
         { 
           cur_seg = um->seg_zero; 
           temp = r[c];
         }
         else 
         { 
           cur_seg = (uint32_t*)Table_get(um->segments, Atom_int((long)r[b])); 
           temp = r[c] + 1;
         }
         r[a] = cur_seg[temp];
         break;
      case 2:
         if (r[a] == 0) 
         { 
           cur_seg = um->seg_zero; 
           temp = r[b];
         }
         else 
         { 
           cur_seg = (uint32_t*)Table_get(um->segments, Atom_int((long)r[a])); 
           temp = r[b] + 1;
         }
         cur_seg[temp] = r[c];
         break;
      case 3:
       //  temp = (uint64_t)r[b] + (uint64_t)r[c];
         //if (temp > ((uint64_t)1 << 32) - 1) { temp = temp % ((uint64_t)1 << 32); }
         r[a] = (uint32_t)(r[b] + r[c]);
	 break;
      case 4:
         r[a] = (uint32_t)(r[b] * r[c]);
	 break;
      case 5: 
	 r[a] = r[b] / r[c];
	 break;
      case 6:
         //if (r[b] == r[c]) { r[a] = 0; }
	 r[a] = ~(r[b] & r[c]);
	 break;
      case 7:
	 return false;
      case 8:
         if (!map_segment(um, b, c)) {printf("error in mapping\n");}
	 break;
      case 9:
 	 if(!unmap_segment(um, c)) {printf("error in unmapping\n");}
	 break;
      case 10:
	 assert(r[c] < 255);
         printf("%c", r[c]);
	 break;
      case 11:
	// scanf("%i", &cur_in);
         cur_in = getc(stdin);
         assert(cur_in < 255);
         if (cur_in == -1) { r[c] = (uint32_t)((uint64_t)1 << 32) - 1; }
	 else  { r[c] = cur_in; }
	 break;
      case 12:
	 if (!(r[b] == 0))
	 {
	   if (!load_program(um, b, c)) 
           {
             fprintf(stderr, "error\n");
           }
         }
 	// printf("rC %u\n", r[c]);
	// um->pgm_cntr = r[c];
         i = r[c] - 1;
        // printf("pgm %u\n", um->pgm_cntr);
         break;
     }
  }
  //if (op_code == 12) { um->pgm_cntr += 1; }
}
  return true;
}
 





















  

