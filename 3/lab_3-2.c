/*
 * Lab#3
 * B289040 박정민
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_NUM     1024
#define MAX_SIZE    10   
#define BUFF_SIZE   4096 
#define TRUE        1
#define FALSE       0

int main(void)
{
    int     i;                      /* loop */
    int     n;                      /* read() output */
    int     fd;                     /* file descriptor */
    int     status;                 /* check if file exist */
    char    buf[BUFF_SIZE];         /* path */
    char    content[BUFF_SIZE];     /* file content */

    status = FALSE;

    /* find files named 1.dat ~ 1024.dat in current directory */
    for (i = 1; i <= MAX_NUM; i++) {
        snprintf(buf, MAX_SIZE, "./%d.dat", i);
        /* if there is a file */
        if (!((fd = open(buf, O_RDWR)) < 0)) {
            status = TRUE;
            /* if no content put 1 */
            if ((n = read(fd, content, BUFF_SIZE)) == 0) {
                content[0] = '1';
                write(fd, content, strlen(content));
            /* otherwise increment it */
            } else if (n > 0) {
                /* if the content is 10 remove it */
                if (atoi(content) == 10) {
                    remove(buf);
                    continue;
                }
                snprintf(content, MAX_SIZE, "%d", atoi(content)+1);
                lseek(fd, 0, SEEK_SET);
                write(fd, content, strlen(content));
            } else {
                printf("read error"); 
                exit(EXIT_FAILURE);
            }
        }
    }

    /* if successed finding files */
    if (status)
        exit(EXIT_SUCCESS);
    else {
        creat("./1.dat", S_IRUSR | S_IWUSR);
        exit(EXIT_SUCCESS);
    }
}