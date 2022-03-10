#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("%s <dir name>\n", argv[0]);
        return EXIT_FAILURE;
    }
    DIR *dir = opendir(argv[1]);
    if (!dir) {
        perror("opendir error\n");
        exit(EXIT_FAILURE);
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        printf("ent->d_name=%s\n", ent->d_name);
    }

    struct dirent **entlist;
    int n = scandir(argv[1], &entlist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        exit(EXIT_FAILURE);

    }
    int i = 0;
    while (i < n) {
        if (entlist[i]->d_type == DT_REG) {
            printf("entlist=%s\n", entlist[i]->d_name);
        }
        i++;
    }
    return EXIT_SUCCESS;
}
