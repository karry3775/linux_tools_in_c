#include <stdio.h>
#include <unistd.h>

#include <linux/limits.h>

int main(int argc, char** argv) {
    char buf[PATH_MAX];
    char* ret = getcwd(buf, PATH_MAX);
    if(!ret) {
        printf("Error reading current working directory");
        return -1;
    }

    printf("%s\n", buf);
    return 0;
}