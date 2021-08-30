/*
 * Written by: Jared Weiss for Dr. Binhai Zhu for Assignment 1
 * in CSCI 460 at Montana State University.
 * Completed on: MM-DD-YYYY
 * Instructions for compilation:
 * run 'gcc -Wall main.c -o pager' in your terminal on any linux system
 * as for windows, I would recommend Visual Studio Code to run it. It should all be
 * pretty self-explanatory.
 * */

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

    return 0;
}

