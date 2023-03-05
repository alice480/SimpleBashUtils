#ifndef SRC_GREP_GREP_H_
#define SRC_GREP_GREP_H_

#include <stdio.h>

#include "../common/file_work.h"
#include "grep_flags.h"

int *flags_search(char **argv, int argc);
int flags_count(char **argv, int len);
int check_conjoint(char *elem, char *flag);
int check_separate(char *elem, char *flag);
int check_single(int *flags, int number);
int single_flag(int argc, char **argv);
int several_flags(int argc, char **argv);
int separated_count(char **argv, int len);

#endif  // SRC_GREP_GREP_H_
