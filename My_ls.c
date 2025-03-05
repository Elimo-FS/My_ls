#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdbool.h>

int readOptions(const char *path) {
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
                    return 0;
            }
        }
        return 1;
    }
    return 0;
}

///////////////////////////////////////////

void print_file_info(const char *filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        return;
    }

    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %ld", file_stat.st_nlink);

    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf(" %s %s", pw->pw_name, gr->gr_name);


    printf(" %ld", file_stat.st_size);

    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
    printf(" %s", time_str);

    printf(" %s\n", filename);
}

void list_directory(const char *path, int long_format) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue; // Ignore les fichiers cachés

        if (long_format)
            print_file_info(entry->d_name);
        else
            printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    int long_format = 0;

    // Vérifier si l'option -l est présente
    if (argc > 1 && strcmp(argv[1], "-l") == 0) {
        long_format = 1;
    }

    list_directory(".", long_format);
    return 0;
}

///////////////////////////////////

DIR *openDirectory(const char *path) {
    if (path[0] != '-') {
        printf("Processing: %s\n", path);
        DIR *element = opendir(path);
        if (element == NULL) {
            perror("Error opening folder");
            return NULL;
        }
        return element;
    }
    return NULL;
}

int checkDirectory(int argc, char *argv[]) {
    for (int i = 1; i < (argc); i++){
        if(argv[i][0] != '-'){
            return 1;
        }
    }
    return 0;
}

void readDirectory(DIR *element) {
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
        readOptions(currentDirectory[i]);
    } for (int i = 0; i < num_elements; i++){
        DIR *repertoire = openDirectory(currentDirectory[i]);
        if (repertoire != NULL) {
            readDirectory(repertoire);
            closedir(repertoire);
        }
    }
}

int main(int argc, char *argv[]) {
    char *defaultDirectory[] = {"."};
    char **currentDirectory = defaultDirectory;
    int num_elements = 1;
    if (checkDirectory(argc, argv)) {
        currentDirectory = &argv[1];
        num_elements = argc - 1;
    }

    readAll(currentDirectory, num_elements);
    return 0;
}