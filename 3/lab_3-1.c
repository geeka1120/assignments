#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_NUM     1024
#define MAX_SIZE    100   
#define BUFF_SIZE   4096 

int main(void)
{
    int     i;
    char    buf[BUFF_SIZE];
    char    new_buf[BUFF_SIZE];

    /* finding files named 1.dat ~ 1024.dat in current directory */
    for (i = 1; i <= MAX_NUM; i++) {
        snprintf(buf, MAX_SIZE, "./%d.dat", i);
        /* if file exists */
        if (!(open(buf, O_RDONLY) < 0)) {
            /* if the file is named 10.dat */
            if (i == 10) {
                remove(buf);
                exit(0);
            } else {
                snprintf(new_buf, MAX_SIZE, "./%d.dat", i+1);
                rename(buf, new_buf);
                exit(0);
            }
        }
    }

    /* create 1.dat if no such file exists */
    creat("./1.dat", S_IRUSR);
    exit(0);
}