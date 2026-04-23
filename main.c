#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

//de ce que j'ai vue un algo de chiffrement classique serait le chiffrement XOR (OU exlusif)

/*
pour test le main.c

ls -l sample.c
gcc -m64 sample.c -o sample
ls -l sample
gcc main.c -o woody_woodpacker -Wall -Wextra -Werror
./woody_woodpacker sample
*/


int main( int argc, char **argv)
{
    if(argc != 2)
    {
        printf("./woody_woodpacker FILE");
        return (1);
    }
    int fd;
    fd = open(argv[1], O_RDONLY);
    if(fd == -1)
        return (1);

    off_t file_size = lseek(fd, 0, SEEK_END); //off_t permet au compilateur de gerer les 64 bites, c'est aussi une norme en C
        if (file_size < 0) {
            perror("Erreur lseek");
            close(fd);
            return (1);
    }
    void *map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) 
    {
        perror("Erreur mmap");
        close(fd);
        return (1);
    }
    printf("Le fichier '%s' de %ld octets est mappé en mémoire !\n", argv[1], file_size);

    if (munmap(map, file_size) < 0) {
        perror("Erreur munmap");
        close(fd);
        return (1);
    }
    close(fd);

    return (0);
}