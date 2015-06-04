/*
 * um_main.c
 * by Maxim Kachalov, 1 - 14 -2015
 * Universal Machine
 * 
 * main function to open, read and execute a .um program
 *
 */

#include <regex.h>
#include"um.h"
#include"um_seg.h"
#include"um_execute.h"
#include"um_read.h"

int main(int argc, char** argv) {
        const char* fp;
        if (argc != 2) {
                fprintf(stderr, 
                        "Call invalid, command syntax : './um [file.um]'\n");
                exit(1);
        }
        fp = argv[1];
        for (unsigned i = 0; ; i++){
                if (fp[i] == '\0') {
                fprintf(stderr, "File name must be in 'filename.um[z]' format\n");
                exit(1);
                }
                if ((fp[i] == '.') && (fp[i + 1] == 'u') 
                           && (fp[i + 2] == 'm')) {
                        break;
                }
        }
        FILE* program = fopen(fp, "rb");
        UM_T um = UM_new(program);
        fclose(program);
        execute_instruction(um);
        UM_free(&um);
}