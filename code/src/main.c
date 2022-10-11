#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include "hash.djb2.c"

#include "bloomfilter.h"
#include "bloomfilter.c"

#include "h_bloomfilter.h"
#include "h_bloomfilter.c"

#define BITS_PER_ELEMENT                    10  //This is "n/m"

//Prototypes
int parse_lines (char * mapped, const char *** lines_output);

/*
    insert_file
    query_file
*/
int main(int argc, char *argv[]) {
    clock_t t0, t1;
    double regular_time, hierarchical_time;

    int i;

    const char * insert_filename = argv[1];
    const char * query_filename  = argv[2];
    
    //Open files
    int insert_fd = open(insert_filename, O_RDONLY);
    int query_fd = open(query_filename, O_RDONLY);
    struct stat insert_stat;
    struct stat query_stat;
    fstat(insert_fd, &insert_stat);
    fstat(query_fd, &query_stat);

    char * insert_mapped = mmap(0, insert_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, insert_fd, 0);
    const char **insert_keys;
    int insert_keys_size = parse_lines(insert_mapped, &insert_keys);

    char * query_mapped = mmap(0, insert_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, query_fd, 0);
    const char **query_keys;
    int query_keys_size = parse_lines(query_mapped, &query_keys);

    printf("input information:\n\t%i inserts\n\t%i queries\n", insert_keys_size, query_keys_size);

    /*
        Initialize bloom filters
    */
    int needed_bits = insert_keys_size*BITS_PER_ELEMENT;
    int actual_bits = needed_bits + (PAGE_SIZE_BITS - ((needed_bits-1) % PAGE_SIZE_BITS)) + 1;

    printf("initialization information:\n\tcreating bloom filters with %i bits\n", actual_bits);

    //Hierarchal bloom filter.
    h_bloomfilt_t * h_bf = h_bloomfilter_init(actual_bits);

    //Regular bloom filter.
    bloomfilt_t * reg_bf = bloomfilter_init(actual_bits);

    /*
        Time inserts on regular bloom filter
    */
     printf("\nPerforming timing...\n\n");

    //Regular bloom filter
    t0 = clock(); //Start timer
    for (i = 0; i < insert_keys_size; i++)
        bloomfilter_insert(reg_bf, (char *) insert_keys[i]);
    for (i = 0; i < query_keys_size; i++)
        bloomfilter_check(reg_bf, (char *) query_keys[i]);
    t1 = clock(); //End timer
    regular_time = ((double) (t1 - t0)) / CLOCKS_PER_SEC;

    printf("regular duration:\n\t%f seconds\n\t%u ticks\n", regular_time, t1 - t0);

    //Hierarchal bloom filter
    t0 = clock(); //Start timer
    for (i = 0; i < insert_keys_size; i++) 
        h_bloomfilter_insert(h_bf, (char *) insert_keys[i]);
    for (i = 0; i < query_keys_size; i++) 
        h_bloomfilter_check(h_bf, (char *) query_keys[i]);
    t1 = clock(); //End timer
    hierarchical_time = ((double) (t1 - t0)) / CLOCKS_PER_SEC;

    printf("hierarchical duration:\n\t%f seconds\n\t%u ticks\n", hierarchical_time, t1 - t0);

}

/**
* Takes a block of character and seperates it into lines
* Note: modifies passed string, replacing '\n' with '\0\.
*
* @param mapped - a pointer to a region with read and write permission
* @return the number of lines put into lines_output
*/
int parse_lines (char * mapped, const char *** lines_output) {

    int count;
    int capacity = 2;
    const char ** lines = (const char**) malloc(sizeof(const char *) * capacity);

    //Add first line.
    count = 1;
    lines[0] = mapped;
    if (mapped[0] == '\n') {
        mapped[0] = '\0';
    }

    //Add remaining lines.
    int i = 1;
    while(mapped[i] != '\0') {
        if (mapped[i] == '\n') { 
            mapped[i] = '\0'; //Seperate the line from the string.
        
            //Ensure our line array has enough space.
            count++;
            if (capacity < count) {
                //Not enough capacity to store next line, grow array.
                capacity *= 2;
                lines = (const char**) realloc(lines, sizeof(const char *) * capacity);
            }

            //Add a pointer to the new line in the line array.
            lines[count - 1] = mapped + (i+1);
        }

        i++;
    }


    *lines_output = lines;
    return count;
}