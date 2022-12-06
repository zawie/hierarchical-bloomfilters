#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>

#define BUFF_SIZE (1 << 12)

char w_buff[BUFF_SIZE];

/*
    filename
    key_size
    amount_of_keys
*/
int main(int argc, char *argv[]) {

    const char * filename = argv[1];
    int key_size = atoi(argv[2]);
    int amount  = atoi(argv[3]);
    
    // //Set random seed
    // struct timeval t1;
    // gettimeofday(&t1, NULL);
    // unsigned seed = t1.tv_usec * t1.tv_sec;
    // srand(seed);

    // printf("Generating %i keys of size %i to file \"%s\" with seed %i.\n", amount, key_size, filename, seed);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    int i;
    for(i = 0; i < amount*(key_size+1) - 1; i++) {
        if (i > 0 && i % BUFF_SIZE == 0)  
            write(fd, w_buff, BUFF_SIZE);
        w_buff[i % BUFF_SIZE] = ((i+1) % (key_size+1) == 0) ? '\n' : '!' + rand()%94;
    }

    write(fd, w_buff, i % BUFF_SIZE);

    close(fd);
}
