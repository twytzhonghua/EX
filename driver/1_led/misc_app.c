
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>




int main(int argc, char **argv)
{
    int fd;
    char* filename;
    int val;


    filename = "/dev/chardrv_test";

    fd = open(filename, O_RDWR);
    if (fd < 0)
    {
        printf("error, can't open %s\n", filename);
        return 0;
    }

        val = atoi(argv[1]);
        write(fd, &val, 4);
   
    
    
    return 0;
}

