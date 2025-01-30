#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

DIR *checkOptions(const char *path) {
    if (path[0] == '-') {
        int len = strlen(path);
        for (int i = 1; i < len; i++) {
            switch (path[i]) {
                case 'l':
                    printf("Hey l\n");
                    break;
                case 'R':
                    printf("Hey R\n");
                    break;
                case 'r':
                    printf("Hey r\n");
                    break;
                case 'd':
                    printf("Hey d\n");
                    break;
                case 't':
                    printf("Hey t\n");
                    break;
                case 'a':
                    printf("Hey a\n");
                    break;
                case 'A':
                    printf("Hey A\n");
                    break;
                case 'L':
                    printf("Hey L\n");
                    break;
                default:
                    fprintf(stderr, "Option doesn't exist!\n");
                    return NULL;
            }
        }
    }
}

DIR *openDirectory(const char *path) {
    if (path[0] != '-') {
        printf("Processing: %s\n", path);
        DIR *element = opendir(path);
        if (element == NULL) {
            perror("Error opening directory");
            return NULL;
        }
        return element;
    }
}

void readDirectory(DIR *element, int num_elements) {
    struct dirent *elements;
    while ((elements = readdir(element)) != NULL) {
        if (elements->d_name[0] != '.') {  //(*elements).d_name[0]
            printf("%s\t", elements->d_name);
        }
    }
    printf("\n");
}


void readAll(char **currentDirectory, int num_elements){
    for (int i = 0; i < num_elements; i++){
        checkOptions(currentDirectory[i]);
    } for (int i = 0; i < num_elements; i++){
        DIR *repertoire = openDirectory(currentDirectory[i]);
        if (repertoire != NULL) {
            readDirectory(repertoire, num_elements);
            closedir(repertoire);
        }
    }
}

int main(int argc, char *argv[]) {
    char *defaultDirectory[] = {"."};
    char **currentDirectory = defaultDirectory;
    int num_elements = 1;

    if (argc > 1) {
        currentDirectory = &argv[1];
        num_elements = argc - 1;
    }

    readAll(currentDirectory, num_elements);
    return 0;
}
