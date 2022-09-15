#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "bloomfilter.h"
#include "bloomfilter.c"

#include "bitarr.h"
#include "bitarr.c"

#include "ops.h"
#define CHECK_OP_COUNT <CHECK_OP__COUNT>

/*
    return_output_file
    time_output_file
*/
int main(int argc, char *argv[]) {
    clock_t t0, t1;
    bitarr_t * check_results = bitarr_init(CHECK_OP_COUNT);

    t0 = clock(); //Start timer
    /* A python script will auto-insert operations here: */
    ///////////////////////////////////////////////////////
    <OPERATIONS>
    ///////////////////////////////////////////////////////
    t1 = clock(); //End timer

    //Open files
    FILE * return_file  = fopen(argv[1], "w");
    FILE * time_file    = fopen(argv[2], "w");

    //Log time
    int msec = (t1 - t0) * 1000 / CLOCKS_PER_SEC;
    fprintf(time_file, "ticks:\t%ju\nms:\t%ds",(uintmax_t) t1 - t0, msec);

    //Log check return values
    int i;
    for(i = 0; i < CHECK_OP_COUNT; i++) {
        fprintf(return_file, "%c\n" bitarr_check(check_results,i) ? 'T' : 'F');
    }
}

/*
Idea:

cmds.txt    - Contains commands insert/check of certain values
time.log    - Outputs timing for each operation
out.log     - Outputs return value for each operation

*/
