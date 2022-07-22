#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "s21_grep.h"
#include <regex.h>


int main(int argc, char *argv[]) {
    s21_grep(argc, argv);
    return 0;
}

