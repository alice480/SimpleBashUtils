#ifndef SRC_GREP_GREP_FLAGS_WORK_H_
#define SRC_GREP_GREP_FLAGS_WORK_H_

#include <stdio.h>
#include <string.h>

#include "string_work.h"
#include "../common/file_work.h"

int flag_e(char *template, FILE *given_file, char *file_name, int output);
int flag_i(char *template, FILE *given_file, char *file_name, int output);
int flag_v(char *template, FILE *given_file, char *file_name, int output);
int flag_c(char *template, FILE *given_file, char *file_name, int output);
int flag_l(char *template, FILE *given_file, char *file_name);
int flag_n(char *template, FILE *given_file, char *file_name, int output);
int flag_h(char *template, FILE *given_file);
int flag_s(char *template, FILE *given_file, char *file_name, int output);
int flag_f(char *templates, FILE *given_file, char *file_name, int output);
int flag_o(char *template, FILE *given_file, char *file_name, int output);
void record_file_name(int flag, FILE *file, char *file_name);
int check_condition(char *template, char *str, int cflag);
int universal_flag(char *template, char *file_name, 
                  int low, int denial, int count, int file_names, int numbers, int errors, int empty, int output);

#endif  // SRC_GREP_GREP_FLAGS_WORK_H_