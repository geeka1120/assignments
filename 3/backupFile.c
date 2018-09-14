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

#define MAX_NUM             1024            /* 1.dat ~ 1024.dat */
#define BUFF_SIZE           4096            /* read content */
#define NAME_LENGTH         10              /* length for file name */
#define CONTENT_LENGTH      4               /* length for content */
#define TRUE                1
#define FALSE               0

int main(void)
{
    int     i;                      /* loop */
    int     n;                      /* read() output */
    int     fd;                     /* file descriptor */
    int     status;                 /* check if file exist */
    char    buf[NAME_LENGTH];       /* path */
    char    content[BUFF_SIZE];     /* read file content */

    status = FALSE;                 /* check if file exists */

    /* find files named 1.dat ~ 1024.dat in current directory */
    for (i = 1; i <= MAX_NUM; i++) {
        snprintf(buf, NAME_LENGTH, "%d.dat", i);
        /* if there is no file keep searching */
        if ((fd = open(buf, O_RDWR)) < 0)
            continue;
        else {
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
                snprintf(content, CONTENT_LENGTH, "%d", atoi(content)+1);
                /* set offset to 0 */
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
        creat("1.dat", S_IRUSR | S_IWUSR);
        exit(EXIT_SUCCESS);
    }
}