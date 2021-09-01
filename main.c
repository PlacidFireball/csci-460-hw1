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
#define FREE_PAGE 1
#define BUSY_PAGE 0

typedef struct {
    long* job_page_number;
    long* page_num_mem;
} pmt;

typedef struct {
    long job_num;
    long size;
    long page_req;
    pmt* pmt_loc;
} job;

typedef struct {
    long* page_frame_num;
    int* status_arr;
} mem_map_table;


void create_job(job* in, long number, long size);
void handle_pmt(job* job, pmt* pmt_in);
void repl(); // read, execute print loop

int main(int argc, char* argv[]) {
    repl();
    return 0;
}

void repl() {
    const char* prompt = "\nPager > ";
    const char* help = "\nWelcome to the Pager! For help, type '?'"
                       "\n--Commands--"
                       "\n<job number> <bytes> - start a new job with a certain amount of memory"
                       "\n<job number> 0 - delete a job"
                       "\nprint - display the current memory status"
                       "\n? - display this prompt"
                       "\nexit - quit the pager";
    printf("%s", help);

    mem_map_table memory;
    memory.page_frame_num = (long*)malloc(sizeof(long)*NUM_PAGES);
    for (int i = 0; i < NUM_PAGES; i++) { memory.page_frame_num[i] = FREE_PAGE; }
    memory.status_arr = (int*)malloc(sizeof(int)*NUM_PAGES);
    for (int i = 0; i < NUM_PAGES; i++) { memory.status_arr[i] = FREE_PAGE; }

    job jobs[100]; // jobs array

    char* read_str = (char*)malloc(sizeof(char)*100); // collect user input
    char* arg; // tokenizing the read string
    char** end = (char**)NULL; // strol() stuff
    long job_number, mem_requested;

    printf("%s", prompt);
    fgets(read_str, 99, stdin);
    arg = strtok(read_str, " \n"); // tokenize the string on ' ' and/or '\n'
    while (strcmp(arg, "exit") != 0) {
        if (strcmp(arg, "?") == 0) { // display help
            printf("%s", help);
            printf("%s", prompt);
        }
        else if (strcmp(arg, "print") == 0) { // print off current memory status
            // TODO implement print memory status
        }
        else {
            job_number = strtol(arg, end, 10); // convert the argument to a long
            if (job_number < NUM_PAGES) { // so long as the job number is valid
                arg = strtok(NULL, " \n"); // grab the number of bytes requested from the string
                mem_requested = strtol(arg, end, 10); // convert it to a long
                // TODO implement job creation / deletion
                if (mem_requested != 0) { // if mem requested = 0 we are deleting a job
                    create_job(&jobs[job_number], job_number, mem_requested); // so we create one
                }
            }
        }
        printf("%s", prompt);
        fgets(read_str, 99, stdin);
        arg = strtok(read_str, " \n");
    }

    // Free it all!
    free(read_str);
    free(arg);
    free(memory.status_arr);
    free(memory.page_frame_num);

}

void create_job(job* in, long number, long size) {
    in->job_num = number; // set job number and size
    in->size = size;
    in->page_req = size/4096 + 1; // calculate how many pages it will take
    in->pmt_loc = (pmt*)NULL;
}

void handle_pmt(job* job, pmt* pmt_in) {

}