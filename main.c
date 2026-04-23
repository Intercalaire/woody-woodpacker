#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

//de ce que j'ai vue un algo de chiffrement classique serait le chiffrement XOR (OU exlusif)

int main( int argc, char **argv)
{
    if(argc != 2)
        return (1);
    int fd;
    fd = open(argv[1], O_RDONLY);
    if(fd == -1)
        return (1);
    struct stat st;
    if (fstat(fd, &st) < 0)
    {
        perror("Erreur fstat");
        close(fd);
        return (1);
    }
    void *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped_data == MAP_FAILED) 
    {
        perror("Erreur mmap");
        close(fd);
        return (1);
    }
}