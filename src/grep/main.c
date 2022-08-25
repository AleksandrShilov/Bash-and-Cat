#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my_grep.h"
#include <regex.h>


int main(int argc, char *argv[]) {
    my_grep(argc, argv);
    return 0;
}

