#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#include "hash/hash.h"
#include "hash/sdbm.c"

#include "bloomfilter/bloomfilter.h"

#define PAGE_SIZE_BYTES         ((unsigned) 4096)  //Page size in bytes
#define PAGE_SIZE_BITS          ((unsigned) PAGE_SIZE_BYTES*8) //Page size in bits

#define BITS_PER_ELEMENT    10  //This is "n/m"
#define MIL                 1000000

//Prototypes
int parse_lines (char * mapped, const char *** lines_output);

/*
    insert_file 
    query_file
*/
int main(int argc, char *argv[]) {

    //Set random seed
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned seed = tv.tv_usec * tv.tv_sec;
    srand(seed);

    clock_t t0, t1;
    
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

    int insert_keys_size;
    char * insert_mapped;
    const char **insert_keys;
    if (insert_stat.st_size > 0) {
        insert_mapped = mmap(0, insert_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, insert_fd, 0);
        insert_keys_size = parse_lines(insert_mapped, &insert_keys);
    } else {
        insert_keys_size = 0;
    }

    int query_keys_size;
    char * query_mapped;
    const char **query_keys;
    if (query_stat.st_size > 0) {
        query_mapped = mmap(0, query_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, query_fd, 0);
        query_keys_size = parse_lines(query_mapped, &query_keys);
    } else {
        query_keys_size = 0;
    }

    int requested_bits = (argc == 4) ? atoi(argv[3]) : insert_keys_size*BITS_PER_ELEMENT;

    printf("Input overview\n");
    printf("\tinsert count:\t%i\n", insert_keys_size);
    printf("\tinsert count in millions:\t%f\n", ((double) insert_keys_size) / MIL);
    printf("\tquery count:\t%i\n", query_keys_size);
    printf("\tquery count millions:\t%f\n",  ((double) query_keys_size) / MIL);
    printf("\trequested bits:\t%i\n", requested_bits);
    
    /*
        Initialize bloom filters
    */
    int num_pages = (requested_bits/PAGE_SIZE_BITS) + (requested_bits % PAGE_SIZE_BITS == 0 ? 0 : 1);
    int num_bits = num_pages*PAGE_SIZE_BITS;

    // assert(num_bits % PAGE_SIZE_BITS == 0);

    printf("Bit array size\n");
    printf("\tmb:\t%f\n", ((double) num_bits)/8000000.0);
    printf("\tbits:\t%i\n", num_bits);
    printf("\tpages:\t%i\n", num_bits/PAGE_SIZE_BITS);
    printf("\tbits per elements:\t%f\n", ((double) num_bits)/insert_keys_size);

    // Initialize bloom filter
    bloomfilt_t bf;
    bf.bitarr = INIT_BITARR(num_bits);
    bf.num_bits = num_bits;
    bf.num_pages = num_pages;


    // Have computer access every bytes in the bit array
    for(i = 0; i < num_bits; i += 8) 
        SET_BITARR(bf.bitarr, i);
    for(i = 0; i < num_bits; i += 8)
        UNSET_BITARR(bf.bitarr, i);

    for(i = 0; i < HASH_CONFIGS; i++) 
        bf.hash_configs[i] = generate_hash_config();   

    /*
        Time inserts on bloom filter
    */
    printf("Insertion timing\n");
    printf("\tnumber of ops:\t%i\n", insert_keys_size);

    t0 = clock(); //Start timer
    for (i = 0; i < insert_keys_size; i++)
        bloomfilter_insert(&bf, (char *) insert_keys[i]);
    t1 = clock(); //End timer

    double seconds = ((double) (t1 - t0)) / CLOCKS_PER_SEC;

    printf("\tticks:\t%i\n", t1 - t0);
    printf("\tseconds:\t%f\n", seconds);
    printf("\tthroughput:\t%f (ops/s)\n", ((double) insert_keys_size) / seconds);

    /*
        Compute accuracy
    */
    printf("Query positives\n");

    int r_pos = 0;

    for (i = 0; i < query_keys_size; i++) {
        if (bloomfilter_query(&bf, (char *) query_keys[i]))
            r_pos++;
    }

    printf("\ttotal tests:\t%i\n", query_keys_size);

    if (query_keys_size > 0) {
        printf("\tnum positives:\t%i\n", r_pos);
        printf("\tpositive rate:\t%f\n", ((double) r_pos)/((double) query_keys_size));
    }

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