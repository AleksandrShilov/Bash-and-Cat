#include "s21_grep.h"

void delete_flags(char *arg) {
    memset(arg, '\0', strlen(arg));
}

void template_copy(char **arg, char *template, size_t count, struct grep_flags *flag) {
    if (arg[count + 1] && flag->score_file > 4) {
        strcpy(template, arg[count - 1]);
    } else if (arg[count + 1] && flag->score_file <= 4) {
        strcpy(template, arg[count + 1]);
    } else {
        flag->noflgs = 0;
    }
}

void template_cat(char **arg, char *template, size_t count, struct grep_flags *flag) {
    if (flag->e_score > 1) {
        strcat(template, "|");
        strcat(template, arg[count + 1]);
    } else {
        strcat(template, arg[count + 1]);
    }
}

void parcer_flags(char **arg, struct grep_flags *flag, char *template) {
    size_t count = 0;
    while (arg[count]) {
        if (arg[count][0] == 45) {
            for (size_t i = 1; i < strlen(arg[count]); i++) {
                if (arg[count][i] == 'e') {
                    flag->e = 1;
                    flag->noflgs = 1;
                    flag->e_score++;
                    template_cat(arg, template, count, flag);
                } else if (arg[count][i] == 'i') {
                    flag->i = 1;
                    flag->noflgs = 1;
                    template_copy(arg, template, count, flag);
                } else if (arg[count][i] == 'v') {
                    flag->v = 1;
                    flag->noflgs = 1;
                    template_copy(arg, template, count, flag);
                } else if (arg[count][i] == 'c') {
                    flag->c = 1;
                    flag->noflgs = 1;
                    template_copy(arg, template, count, flag);
                } else if (arg[count][i] == 'l') {
                    flag->l = 1;
                    flag->noflgs = 1;
                    template_copy(arg, template, count, flag);
                } else if (arg[count][i] == 'n') {
                    flag->n = 1;
                    flag->noflgs = 1;
                    template_copy(arg, template, count, flag);
                } else if (arg[count][i] == 'h') {
                    flag->h = 1;
                    flag->noflgs = 1;
                    template_copy(arg, template, count, flag);
                } else if (arg[count][i] == 'f') {
                    flag->f = 1;
                    flag->noflgs = 1;
                    template_copy(arg, template, count, flag);
                } else if (arg[count][i] == 'o') {
                    flag->o = 1;
                    flag->noflgs = 1;
                    template_copy(arg, template, count, flag);
                } else {
                    flag->err = 1;
                }
            }
            delete_flags(arg[count]);
        }
        arg++;
    }
}

void print_not_flags(FILE *fp, char *regx, char *name_fp, struct grep_flags *flag) {
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;

    if ((regcomp(&reegex, regx, 0)) == 0) {
        ssize_t read;
        while ((read = getline(&line, &len, fp)) != -1) {
            if ((regexec(&reegex, line, 0, NULL, 0)) == 0) {
                if (flag->score_file >= 4) {
                    printf("%s:%s", name_fp, line);
                } else {
                    printf("%s", line);
                }
            }
        }
    }
    free(line);
    regfree(&reegex);
}

void print_flag_e(FILE *fp, char *regx, char *name_fp, struct grep_flags *flag) {
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;
    if ((regcomp(&reegex, regx, REG_EXTENDED)) == 0) {
        ssize_t read;
        while ((read = getline(&line, &len, fp)) != -1) {
            if ((regexec(&reegex, line, 0, NULL, 0)) == 0) {
                if (flag->score_file > 4 && flag->e_score == 1) {
                    printf("%s:%s", name_fp, line);
                } else {
                    printf("%s", line);
                }
            }
        }
    }
    free(line);
    regfree(&reegex);
}

void print_flag_i(FILE *fp, char *template, char *name_fp, struct grep_flags *flag) {
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;
    if ((regcomp(&reegex, template, REG_ICASE)) == 0) {
        ssize_t read;
        while ((read = getline(&line, &len, fp)) != -1) {
            if ((regexec(&reegex, line, 0, NULL, 0)) == 0) {
                if (flag->score_file > 4) {
                    printf("%s:%s", name_fp, line);
                } else {
                    printf("%s", line);
                }
            }
        }
    }
    free(line);
    regfree(&reegex);
}

void print_flag_v(FILE *fp, char *template, char *name_fp, struct grep_flags *flag) {
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;
    if ((regcomp(&reegex, template, REG_NOMATCH)) == 0) {
        ssize_t read;
        while ((read = getline(&line, &len, fp)) != -1) {
            if (!(regexec(&reegex, line, 0, NULL, 0)) == 0) {
                if (flag->score_file > 4) {
                    printf("%s:%s", name_fp, line);
                } else {
                    printf("%s", line);
                }
            }
        }
    }
    free(line);
    regfree(&reegex);
}

void print_flag_c(FILE *fp, char *template, char *name_fp, struct grep_flags *flag) {
    int count_str = 0;
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;
    if ((regcomp(&reegex, template, 0)) == 0) {
        ssize_t read;
        while ((read = getline(&line, &len, fp)) != -1) {
            if ((regexec(&reegex, line, 0, NULL, 0)) == 0) {
                count_str++;
            }
        }
    }
    if (flag->score_file > 4) {
        printf("%s:%d\n", name_fp, count_str);
    } else {
        printf("%d\n", count_str);
    }
    free(line);
    regfree(&reegex);
}

void print_flag_l(FILE *fp, char *template, struct grep_flags *flag) {
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;
    if ((regcomp(&reegex, template, 0)) == 0) {
        ssize_t read;
        while ((read = getline(&line, &len, fp)) != -1) {
            if ((regexec(&reegex, line, 0, NULL, 0)) == 0) {
                flag->l_try = 1;
            }
        }
    }
    free(line);
    regfree(&reegex);
}

void print_flag_n(FILE *fp, char *template, char *name_fp, struct grep_flags *flag) {
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;
    if ((regcomp(&reegex, template, 0)) == 0) {
        ssize_t read;
        int count_str = 0;
        while ((read = getline(&line, &len, fp)) != -1) {
            count_str++;
            if ((regexec(&reegex, line, 0, NULL, 0)) == 0) {
                if (flag->score_file > 4) {
                    printf("%s:%d:%s", name_fp, count_str, line);
                } else {
                    printf("%d:%s", count_str, line);
                }
            }
        }
    }
    free(line);
    regfree(&reegex);
}

void print_flag_h(FILE *fp, char *template) {
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;
    if ((regcomp(&reegex, template, 0)) == 0) {
        ssize_t read;
        while ((read = getline(&line, &len, fp)) != -1) {
            if ((regexec(&reegex, line, 0, NULL, 0)) == 0) {
                printf("%s", line);
            }
        }
    }
    free(line);
    regfree(&reegex);
}

void print_flag_f(FILE *fp, char *template, char *name_fp) {
    char *line = NULL;
    char *name_file_regx = NULL;
    size_t len = 0;
    size_t len2 = 0;
    regex_t reegex;

    if (!(strcmp(template, name_fp) == 0)) {
        FILE *new_fp_regx;
        if ((new_fp_regx = fopen(template, "r"))) {
            while ((getline(&name_file_regx, &len2, new_fp_regx)) != -1) {
            }
            fclose(new_fp_regx);
        }

        if ((regcomp(&reegex, name_file_regx, 0)) == 0) {
            ssize_t read;
            while ((read = getline(&line, &len, fp)) != -1) {
                if ((regexec(&reegex, line, 0, NULL, 0)) == 0) {
                    printf("%s", line);
                }
            }
        }
        free(line);
        regfree(&reegex);
    }
}

void print_flag_o(FILE *fp, char *template, char *name_fp, struct grep_flags *flag) {
    char *line = NULL;
    size_t len = 0;
    regex_t reegex;
    regmatch_t pm;
    if ((regcomp(&reegex, template, 0)) == 0) {
        ssize_t read;
        while ((read = getline(&line, &len, fp)) != -1) {
            if ((regexec(&reegex, line, 1, &pm, REG_NOTBOL)) == 0) {
                if (flag->score_file > 4) {
                    printf("%s:", name_fp);
                }
                for (char *c = (line + pm.rm_so); c < line + pm.rm_eo; c++) {
                    putchar(*c);
                }
                printf("\n");
            }
        }
    }
    free(line);
    regfree(&reegex);
}

void print_file(FILE *fp, char *template, struct grep_flags *flag, char *name_fp) {
    if (flag->err == 0) {
        if (flag->e == 1) {
            print_flag_e(fp, template, name_fp, flag);
        }

        if (flag->i == 1) {
            print_flag_i(fp, template, name_fp, flag);
        }

        if (flag->v == 1) {
            print_flag_v(fp, template, name_fp, flag);
        }

        if (flag->c == 1) {
            print_flag_c(fp, template, name_fp, flag);
        }

        if (flag->l == 1) {
            print_flag_l(fp, template, flag);
        }

        if (flag->n == 1) {
            print_flag_n(fp, template, name_fp, flag);
        }

        if (flag->h == 1) {
            print_flag_h(fp, template);
        }

        if (flag->f == 1) {
            print_flag_f(fp, template, name_fp);
        }

        if (flag->o == 1) {
            print_flag_o(fp, template, name_fp, flag);
        }

        if (flag->noflgs == 0) {
            print_not_flags(fp, template, name_fp, flag);
        }
    }
}

void open_file(char *arg, char *template, struct grep_flags *flag) {
    FILE *fp;
    char *name = arg;

    if ((fp = fopen(name, "r"))) {
        print_file(fp, template, flag, name);
        fclose(fp);
        flag->notfile = 0;
    } else {
        flag->notfile = 1;
    }

    if (flag->l_try == 1) {
        printf("%s\n", name);
        flag->l_try = 0;
    }
}

void s21_grep(int argc, char **argv) {
    if (argc > 1) {
        int count = 0;
        char template[8024] = {0};
        struct grep_flags flag = {0};
        flag.score_file = argc;
        argv++;
        parcer_flags(argv, &flag, template);

        if (flag.noflgs == 0) {
            strcpy(template, argv[0]);
        }

        while (*argv) {
            count++;
            open_file(*argv, template, &flag);
            argv++;
        }

        if (flag.notfile == 1) {
            printf("Errors, No such file or directory\n");
        }
    } else {
        printf("Error, not arguments\n");
    }
}
