#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "Invalid arguments\n");
        exit(1);
    }
    // char *argl[MAXARG];
    char c, buf[100];
    int i, st_pos = 0;
    for (i = 1; i < argc; ++i)
        argv[i - 1] = argv[i];
    i = 0;
    while (1) {
        do {
            if (read(0, &c, 1) == 0)
                exit(0);
            buf[i++] = c;
            if (c == ' ') {
                argv[argc++ - 1] = &buf[st_pos];
                st_pos = i;
            }
        } while (c != '\n');
        argv[argc] = 0;  // NULL
        if (fork() == 0)
            exec(argv[0], argv);
        else
            wait(0);
    }
}