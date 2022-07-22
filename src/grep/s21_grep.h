#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>



struct grep_flags {
    int e;
    int e_score;
    int i;
    int v;
    int c;
    int l;
    int l_try;
    int n;
    int h;
    int f;
    int o;
    int err;
    int noflgs;
    int notfile;
    int score_file;
};

void delete_flags(char *arg);
void template_copy(char **arg, char *template, size_t count, struct grep_flags *flag);
void template_cat(char **arg, char *template, size_t count, struct grep_flags *flag);
void parcer_flags(char **arg, struct grep_flags *flag, char *template);
void print_not_flags(FILE *fp, char *regx, char *name_fp, struct grep_flags *flag);
void print_flag_e(FILE *fp, char *regx, char *name_fp, struct grep_flags *flag);
void print_flag_i(FILE *fp, char *template, char *name_fp, struct grep_flags *flag);
void print_flag_v(FILE *fp, char *template, char *name_fp, struct grep_flags *flag);
void print_flag_c(FILE *fp, char *template, char *name_fp, struct grep_flags *flag);
void print_flag_l(FILE *fp, char *template, struct grep_flags *flag);
void print_flag_n(FILE *fp, char *template, char *name_fp, struct grep_flags *flag);
void print_flag_h(FILE *fp, char *template);
void print_flag_f(FILE *fp, char *template, char *name_fp);
void print_flag_o(FILE *fp, char *template, char *name_fp, struct grep_flags *flag);
void print_file(FILE *fp, char *template, struct grep_flags *flag, char *name_fp);
void open_file(char *arg, char *template, struct grep_flags *flag);
void s21_grep(int argc, char **argv);

#endif  // SRC_GREP_S21_GREP_H_