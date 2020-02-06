#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <fcntl.h>

void print_directory_contents(DIR *directory_to_print) {
    struct dirent* d = readdir(directory_to_print);
    DIR* tmp_dir;
    int tmp_fd;
    struct statfs* dir_stat;

    while (d != NULL) {
        tmp_fd = open(d->d_name, O_RDONLY);
        printf("%s\n", d->d_name);
        if (S_ISDIR(tmp_fd)) {
            printf("DIRRRR\n");
        }

        if (tmp_fd == -1) {
            printf("%s\n", tmp_fd);
        }

        printf("%d\n", fstatfs(tmp_fd, dir_stat));

        // if (d->d_type == "DT_DIR") {
        //     printf("Directory\n");
        // }

        d = readdir(directory_to_print);
    }
}

void print_buffer(char *buf) {
    char c;

}

int main() {
    FILE* input;
    DIR* directory_to_watch;
    int c;
    long num_characters_in_file = 0;
    char * file_buffer;
    struct stat* input_file_buffer;
    int fd;

    fd = open("input.md", O_RDONLY);


    input = fopen("input.md", "r");
    if (input == NULL) {
        printf("could not open file");
        exit(1);
    }

    fstat(fd, input_file_buffer);

    printf("%d\n", input_file_buffer->st_mode);

    directory_to_watch = opendir(".");

    print_directory_contents(directory_to_watch);

    fseek(input, 0, SEEK_END);

    num_characters_in_file = ftell(input);

    rewind(input);

    file_buffer = malloc(num_characters_in_file + 1);

    fread(file_buffer, 1, num_characters_in_file, input);

    printf("%ld", num_characters_in_file);

    free(file_buffer);

    return 0;
}
