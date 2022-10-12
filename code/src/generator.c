#include <stdio.h>
#include <fcntl.h>

/*
    filename
    key_size
    amount_of_keys
*/
int main(int argc, char *argv[]) {
   
    const char * filename = argv[1];
    int key_size = atoi(argv[2]);
    int amount  = atoi(argv[3]);

    printf("Generating %i keys of size %i to file \"%s\".\n", amount, key_size, filename);

    int fd = open(filename, O_CREAT | O_RDWR, 0644);

    size_t w_buff_size = key_size + 1; //extra char for new line
    char w_buff[w_buff_size];
    w_buff[key_size] = '\n';

    int l, c;
    for (l = 0; l < amount; l++) {
        for (c = 0; c < key_size; c++) {
            w_buff[c] = '0' + rand()%72;
        }
        write(fd, w_buff, w_buff_size);
    }

    close(fd);
}
