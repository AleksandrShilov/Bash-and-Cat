#include "my_cat.h"

void delete_flags(char *arg) {
    memset(arg, '\0', strlen(arg));
}

void parcer_flags(char **arg, struct cat_flags *flag) {
    size_t count = 0;
    while (arg[count]) {
        if (arg[count][0] == 45) {
            if (arg[count][1] == 45) {
                if (strcmp(arg[count], "--number-nonblank") == 0) {
                    flag->b = 1;
                } else if (strcmp(arg[count], "--show-ends") == 0) {
                    flag->e = 1;
                } else if (strcmp(arg[count], "--squeeze-blank") == 0) {
                    flag->s = 1;
                } else if (strcmp(arg[count], "--show-tabs") == 0) {
                    flag->t = 1;
                } else if (strcmp(arg[count], "--numbers") == 0) {
                    flag->n = 1;
                } else {
                    flag->err = 1;
                }
            } else {
                for (size_t i = 1; i < strlen(arg[count]); i++) {
                    if (arg[count][i] == 'b') {
                        flag->b = 1;
                    } else if (arg[count][i] == 'e') {
                        flag->e = 1;
                    } else if (arg[count][i] == 'E') {
                        flag->e = 1;
                    } else if (arg[count][i] == 's') {
                        flag->s = 1;
                    } else if (arg[count][i] == 't') {
                        flag->t = 1;
                    } else if (arg[count][i] == 'T') {
                        flag->T = 1;
                    } else if (arg[count][i] == 'n') {
                        flag->n = 1;
                    } else {
                        flag->err = 1;
                    }
                }
            }
            delete_flags(arg[count]);
        }
        arg++;
    }
}

void print_not_flags(FILE *fp) {
    char print_c;
    while ((print_c = fgetc(fp))!= EOF) {
        printf("%c", print_c);
    }
}

void print_flag_n(FILE *fp) {
    char print_c;
    char next_c;
    int number = 1;
    int first = 0;

    while ((print_c = fgetc(fp)) != EOF) {
        if (first == 0) {
            printf("%6d\t", number);
            number++;
            first = 1;
        }

        if (print_c == 10) {
            printf("%c", print_c);
            while ((next_c = fgetc(fp)) == 10) {
                printf("%6d\t", number);
                printf("%c", next_c);
                number++;
            }

            if (next_c != -1) {
                printf("%6d\t", number);
                printf("%c", next_c);
                number++;
            }
        } else {
            printf("%c", print_c);
        }
    }
}

void print_flag_E(FILE *fp) {
    char print_c;
    while ((print_c = fgetc(fp))!= EOF) {
        if (print_c == 10) {
            printf("%c", '$');
        }
        printf("%c", print_c);
    }
}

void print_flag_e(FILE *fp) {
    char print_c;
    while ((print_c = fgetc(fp))!= EOF) {
        if (print_c == 10) {
            printf("$\n");
        } else if (print_c >= 0 && print_c < 32 && print_c != 9) {
            printf("^%c", print_c + 64);
        } else if (print_c == 127) {
            printf("^%c", print_c - 64);
        } else if (print_c != -1) {
            printf("%c", print_c);
        }
    }
}
void print_flag_b(FILE *fp) {
    char print_c;
    char next_c;
    int number = 1;
    int first = 0;

    while ((print_c = fgetc(fp)) != EOF) {
        if (first == 0 && print_c != 10) {
            printf("%6d\t", number);
            number++;
            first = 1;
        }

        if (print_c == 10) {
            printf("%c", print_c);
            while ((next_c = fgetc(fp)) == 10) {
                printf("%c", next_c);
            }

            if (next_c != -1) {
                printf("%6d\t", number);
                printf("%c", next_c);
                number++;
            }
        } else {
            printf("%c", print_c);
        }
    }
}

void print_flag_s(FILE *fp) {
    char print_c;
    char next_c;

    while ((print_c = fgetc(fp)) != EOF) {
        if (print_c == 10) {
            printf("%c", print_c);
            if ((next_c = fgetc(fp)) == 10) {
                printf("%c", next_c);
                while (next_c == 10) {
                    next_c = fgetc(fp);
                }
                printf("%c", next_c);
            } else {
                if (next_c != -1) {
                    printf("%c", next_c);
                }
            }
        } else {
            printf("%c", print_c);
        }
    }
}

void print_flag_T(FILE *fp) {
    char print_c;
    while ((print_c = fgetc(fp))!= EOF) {
        if (print_c == 9) {
            printf("^I");
        } else {
            printf("%c", print_c);
        }
    }
}

void print_flag_t(FILE *fp) {
    char print_c;
    while ((print_c = fgetc(fp))!= EOF) {
        if (print_c == 9) {
            printf("^I");
        } else if (print_c >= 0 && print_c < 32 && print_c != 10) {
            printf("^%c", print_c + 64);
        } else if (print_c == 127) {
            printf("^%c", print_c - 64);
        } else if (print_c  != -1) {
            printf("%c", print_c);
        }
    }
}

void print_file(FILE *fp, struct cat_flags *flag) {
    if (flag->err == 0) {
        int no_flags = 0;
        if (flag->e == 1) {
            no_flags = 1;
            print_flag_e(fp);
        }

        if (flag->E == 1) {
            no_flags = 1;
            print_flag_E(fp);
        }

        if (flag->b == 1) {
            no_flags = 1;
            print_flag_b(fp);
        }

        if (flag->n == 1) {
            no_flags = 1;
            print_flag_n(fp);
        }

        if (flag->s == 1) {
            no_flags = 1;
            print_flag_s(fp);
        }

        if (flag->t == 1) {
            no_flags = 1;
            print_flag_t(fp);
        }

        if (flag->T == 1) {
            no_flags = 1;
            print_flag_T(fp);
        }

        if (no_flags == 0) {
            print_not_flags(fp);
        }
    } else {
        printf("Errors\n");
    }
}

void open_file(char *arg, struct cat_flags *flag) {
    FILE *fp;
    char *name = arg;

    if ((fp = fopen(name, "r"))) {
        print_file(fp, flag);
        fclose(fp);
        flag->notfile = 0;
    } else {
        flag->notfile = 1;
    }
}

void my_cat(int argc, char **argv) {
    if (argc > 1) {
        int count = 0;
        struct cat_flags flag = {0};
        argv++;
        parcer_flags(argv, &flag);
        while (*argv) {
            count++;
            open_file(*argv, &flag);
            argv++;
        }
        if (flag.notfile == 1) {
            printf("Errors, No such file or directory\n");
        }
    } else {
        printf("Error, not argumunts\n");
    }
}
