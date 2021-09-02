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

#define ARG_LEN 10
#define PAGE_SIZE 4096
#define NUM_PAGES 16
#define FREE_PAGE 1
#define BUSY_PAGE 0

typedef struct {
    //long* job_page_number; // unnecessary
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
    long num_pages;
    long size;
} mem_map_table;


void create_job(job* in, long number, long size);
void handle_pmt_insert(job* job);
void handle_pmt_delete(job* job);
pmt init_pmt(long page_req);
void free_pmt(pmt* free_pmt);
void repl(); // read, execute print loop
void init_memory();

mem_map_table memory; // global variable for our main memory

int main(int argc, char* argv[]) {
    init_memory();
    repl();
    return 0;
}

// TODO I broke everything :)

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

    job jobs[100]; // jobs array

    char* read_str = malloc(sizeof(char)*99);
    char* arg0 = malloc(sizeof(char)*ARG_LEN);
    char* arg1 = malloc(sizeof(char)*ARG_LEN);

    char** end = (char**)NULL; // strol() stuff
    long job_number, mem_requested;

    printf("%s", prompt);
    fgets(read_str, 99, stdin); // not working for some reason
    sscanf(read_str, "%10s %10s", arg0, arg1);
    while (strcmp(arg0, "exit") != 0) {
        if (strcmp(arg0, "?") == 0) {        // display help
            printf("%s", help);
            printf("%s", prompt);
        }
        else if (strcmp(arg0, "print") == 0) {                                 // print off current memory status
            for (int i = 0; i < memory.num_pages; i++) {
                printf("P%d:\t%s\n", i, memory.status_arr[i] == FREE_PAGE ? "Free" : "Busy");
            }
        }
        else {
            job_number = strtol(arg0, end, 10);                           // convert the argument to a long
            if (job_number < NUM_PAGES) {                                     // so long as the job number is valid
                mem_requested = strtol(arg1, end, 10);                   // convert it to a long
                // TODO implement job creation / deletion
                if (mem_requested != 0) {                                     // if mem requested = 0 we are deleting a job
                    create_job(&jobs[job_number], job_number, mem_requested); // so we create one
                    handle_pmt_insert(&jobs[job_number]);
                }
                else {
                    handle_pmt_delete(&jobs[job_number]);
                }
            }
        }
        printf("%s", prompt);
        fgets(read_str, 99, stdin); // not working for some reason
        sscanf(read_str, "%10s %10s", arg0, arg1);
    }

    // Free it all!
    free(arg0);
    free(arg1);
    free(memory.status_arr);
    free(memory.page_frame_num);

}

void create_job(job* in, long number, long size) {
    in->job_num = number; // set job number and size
    in->size = size;
    in->page_req = size/4096 + 1; // calculate how many pages it will take
    pmt _pmt = init_pmt(in->page_req);
    in->pmt_loc = &_pmt;
}

void handle_pmt_insert(job* job) {
    int available_pages = 0;
    for (int i = 0; i < memory.num_pages; i++) {            // calculate the number of available pages
        if (memory.status_arr[i] == FREE_PAGE) {
            available_pages++;
        }
    }

    if (job->page_req < available_pages) {                  // if the job will fit in main memory
        int j = 0;
        for (long i = 0; i < memory.num_pages; i++) {        // use first fit to insert the pages into memory
            if (memory.status_arr[i] == FREE_PAGE) {
                /* This line is a problem, that or malloc is being a bitch */
                job->pmt_loc->page_num_mem[j++] = i;        // tell the job where its pages are
                memory.status_arr[i] = BUSY_PAGE;           // tell the memory that that page is busy
                if (j == job->page_req) break;
            }
        }
    }
}

void handle_pmt_delete(job* job) {
    for (int i = 0; i < job->page_req; i++) {
        memory.status_arr[job->pmt_loc->page_num_mem[i]] = FREE_PAGE;
    }
    //free_pmt(job->pmt_loc); // segmentation fault here
}

void init_memory() {
    memory.page_frame_num = (long*)malloc(sizeof(long)*NUM_PAGES);
    for (int i = 0; i < NUM_PAGES; i++) { memory.page_frame_num[i] = FREE_PAGE; }
    memory.status_arr = (int*)malloc(sizeof(int)*NUM_PAGES);
    for (int i = 0; i < NUM_PAGES; i++) { memory.status_arr[i] = FREE_PAGE; }
    memory.size = PAGE_SIZE;
    memory.num_pages = NUM_PAGES;
}

pmt init_pmt(long page_req) {
    pmt* new_pmt = (pmt*)malloc(sizeof(pmt));
    new_pmt->page_num_mem = (long*)malloc(sizeof(long)*page_req);
    for (int i = 0; i < page_req; i++) new_pmt->page_num_mem[i] = 0;
    return *new_pmt;
}

void free_pmt(pmt* pmt_ptr) {
    free(pmt_ptr);
}
