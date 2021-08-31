/*
 * Written by: Jared Weiss for Dr. Binhai Zhu for Assignment 1
 * in CSCI 460 at Montana State University.
 * Completed on: MM-DD-YYYY
 * Instructions for compilation:
 * run 'gcc -Wall main.c -o pager' in your terminal on any linux system
 * as for windows, I would recommend Visual Studio Code to run it. It should all be
 * pretty self-explanatory.
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_PAGES 16

typedef struct {
    long job_page_number;
    long page_num_mem;
} pmt;

typedef struct {
    long job_num;
    long size;
    pmt* pmt_loc;
} job_table;

typedef struct {
    long page_frame_num;
    long status;
} mem_map_table;

void repl(); // read, execute print loop

int main(int argc, char* argv[]) {

    repl();
    return 0;
}

void repl() {

    char *read_str = (char*)NULL; // collect user input
    char* arg; // tokenizing the read string
    char** end = (char**)NULL; // strol() stuff
    long job_number, mem_requested; // we'll collect
    scanf("%s", read_str);
    arg = strtok(read_str, " ");
    while (!strcmp(arg, "exit")) {
        job_number = strtol(arg, end, 10);
        if (job_number < NUM_PAGES) {
            arg = strtok(read_str, NULL);

        }
    }

}