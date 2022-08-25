#ifndef SRC_CAT_MY_CAT_H_
#define SRC_CAT_MY_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct cat_flags {
    int b;
    int e;
    int E;
    int s;
    int t;
    int T;
    int n;
    int err;
    int notfile;
};

void delete_flags(char *arg);
void parcer_flags(char **arg, struct cat_flags *flag);
void print_not_flags(FILE *fp);
void print_flag_n(FILE *fp);
void print_flag_E(FILE *fp);
void print_flag_e(FILE *fp);
void print_flag_b(FILE *fp);
void print_flag_s(FILE *fp);
void print_flag_t(FILE *fp);
void print_flag_T(FILE *fp);
void print_file(FILE *fp, struct cat_flags *flag);
void open_file(char *arg, struct cat_flags *flag);
void clear_cat_flags(struct cat_flags *flag);
void my_cat(int argc, char **argv);

#endif  //  SRC_CAT_MY_CAT_H_