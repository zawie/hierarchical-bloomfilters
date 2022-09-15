#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "bloomfilter.h"
#include "bloomfilter.c"

/*
    mode
    cmds_input_file
    return_output_file
    time_output_file
    page_output_file
*/
int main(int argc, char *argv[]) {

    /* Parse input */
    char * mode         = argv[1];
    int num_elements    = atoi(argv[2]);

    //Open files
    FILE * cmd_file     = fopen(argv[3], "r");
    FILE * return_file  = fopen(argv[4], "w");
    FILE * time_file    = fopen(argv[5], "w");
    FILE * page_file    = fopen(argv[6], "w");

    //Create bloom filter
    if (strcmp(mode, "regular") == 0) {
        int num_bits = 10*num_elements;
        int k = 7;
        bloomfilt_t * bf = bloomfilter_init(num_bits, 7);

        char * cmd_line = NULL;
        size_t len_line = 0;

        clock_t t0, t1 = 0;
        t0 = clock();
        while (getline(&cmd_line, &len_line, cmd_file) != -1) {
            char op = cmd_line[0];
            cmd_line[strcspn(cmd_line, "\r\n")] = '\0'; //strip new line
            char * key = cmd_line + 1;
            clock_t t0, t1 = 0;

            if (op == '?') {
                // t0 = clock();
                bool contains = bloomfilter_check(bf, key);
                // t1 = clock();
                fprintf(return_file, "%s\n", contains ? "True" : "False");
            } else if (op == '+') {
                // t0 = clock();
                bloomfilter_insert(bf, key);
                // t1 = clock();
                fprintf(return_file, "\n");
            }
        }
        t1 = clock();
        int msec = (t1 - t0) * 1000 / CLOCKS_PER_SEC;
        printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
        // fprintf(time_file, "%ju\t-\t%ju\t=\t%ju\n", (uintmax_t) t1, (uintmax_t) t0, (uintmax_t) t1 - t0);

    }


}

/*
Idea:

cmds.txt    - Contains commands insert/check of certain values
time.log    - Outputs timing for each operation
out.log     - Outputs return value for each operation

*/
